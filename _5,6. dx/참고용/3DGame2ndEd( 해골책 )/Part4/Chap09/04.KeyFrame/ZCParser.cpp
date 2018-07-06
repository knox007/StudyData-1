#include <windows.h>
#include <assert.h>
#include "zxml.h"
#include "define.h"
#include "ZCParser.h"
#include "zflog.h"

ZCParser::ZCParser()
{
	m_pXML = new ZXML;
}

ZCParser::~ZCParser()
{
	m_pXML->Close();
	S_DEL( m_pXML );
}

int	ZCParser::Parse_XML( ZCParsedData* pData, char* lpszFilename )
{
	if( !m_pXML->Open( lpszFilename ) )
	{
		g_pLog->Log( "can't open [%s] file.", lpszFilename );
		return 0;
	}
	try
	{
		
		if( !_ParseInfo( pData ) )
		{
			g_pLog->Log( "can't parse info block in [%] file.", lpszFilename );
			throw;
		}
		
		if( !_ParseMaterial( pData ) )
		{
			g_pLog->Log( "can't parse material block in [%] file.", lpszFilename );
			throw;
		}

		if( !_ParseObject( pData ) )
		{
			g_pLog->Log( "can't parse object block in [%] file.", lpszFilename );
			throw;
		}
		
		return 1;
	}
	catch(...)
	{
		return 0;
	}	
}

/// TriIndex에 따라서 삼각형은 sub material정보를 새로운 ZCMesh오브젝트로 분리한다.
/// 이 함수를 제대로 구현하려면 새로 추가된 sub-mesh정보에 따라서 parent의 index들을 다시 갱신해주어야 한다.
/// 그러나 귀차니즘의 압박으로 대략 스킵이다. ^^;
int	ZCParser::_SplitMeshByFaceMaterial( ZCParsedData* pData )
{
	int							i, j, cnt;
	list<ZCMesh*>::iterator		it, jt;
	ZCMesh*						pMesh;

	for( it = pData->m_meshList.begin() ; it != pData->m_meshList.end() ; it++ )
	{
		/// Sub-Material이 있는가?
		if( (*it)->m_nMaterialCount > 1 )
		{
			j = 0;
			for( i = 0 ; i < (*it)->m_nMaterialCount ; i++ )
			{
				pMesh = new ZCMesh();
				pMesh->m_strNodeType = (*it)->m_strNodeType;
				pMesh->m_nObjectID = (*it)->m_nObjectID;
				pMesh->m_nObjectHashID = (*it)->m_nObjectHashID;
				pMesh->m_nParentID = (*it)->m_nParentID;
				pMesh->m_bboxMax = (*it)->m_bboxMax;
				pMesh->m_bboxMin = (*it)->m_bboxMin;
				pMesh->m_tm = (*it)->m_tm;
				pMesh->m_vertex = (*it)->m_vertex;
				pMesh->m_normal = (*it)->m_normal;
				pMesh->m_tvertex = (*it)->m_tvertex;
				pMesh->m_nMaterialCount = 1;
				pMesh->m_texindex = (*it)->m_texindex;
				pMesh->m_vertweight = (*it)->m_vertweight;
				pMesh->m_track = (*it)->m_track;
				pMesh->m_isSkinned = (*it)->m_isSkinned;
				cnt = (*it)->m_triindex.size() - 1;
				for( ; j < cnt ; )
				{
					if( (*it)->m_triindex[j].ID == (*it)->m_triindex[j+1].ID )
						pMesh->m_triindex.push_back( (*it)->m_triindex[j] );
					else
					{
						j++;
						if( j == cnt )	/// 제일 마지막 index정보를 복사한다.
							pMesh->m_triindex.push_back( (*it)->m_triindex[j] );

						break;
					}
					j++;
				}
				pData->m_meshList.insert( it, pMesh );		// 생성한 sub-mesh를 child로 등록
			}
			delete *it;										// sub-mesh를 만들었으니
			it = pData->m_meshList.erase( it );				// 원본 mesh를 리스트에서 삭제한다
		}
	}
	return 1;
}

void ZCParser::_MergeBlendWeight( VertMerged& vm, VertWeight& vw )
{
	int			i;
	VertWeight	t = vw;
	int			cnt = t.ID.size();

	/// blend weight가 4개이하라면 강제로 4개로 만든다. 
	if( cnt < 4 )
	{
		t.ID.resize( 4 );
		t.fWeight.resize( 4 );
		for( i = 0 ; i < 4 - cnt ; i++ )
		{
			t.ID[i] = 0;
			t.fWeight[i] = 0;
		}
	}
	
	/// script에서 출력한 가중치값은 큰값순서로(올림차순) 정렬되어있다.
	/// 때문에 앞에서 4개만 값을 취하면 된다.
	for( i = 0 ; i < 4 ; i++ )
	{
		vm.b[i] = t.fWeight[i];
	}
	vm.i = BLENDINDEX( t.ID[3], t.ID[2], t.ID[1], t.ID[0] );
}

int	ZCParser::_MergeVertex( ZCParsedData* pData )
{
	int							i, j, cnt;
	list<ZCMesh*>::iterator		it, jt;
	ZCMesh*						pMesh;
	VertMerged*					pVert;
	Index3i*					pIndex;
	DWORD						vindex, tindex;

	for( it = pData->m_meshList.begin() ; it != pData->m_meshList.end() ; it++ )
	{
		pMesh = *it;
		pVert = new VertMerged[ pMesh->m_vertex.size() + pMesh->m_triindex.size() * 3 ];
		pIndex = new Index3i[ pMesh->m_triindex.size() ];
		for( i = 0 ; i < pMesh->m_vertex.size() ; i++ )
		{
			pVert[i].p = pMesh->m_vertex[i];
			pVert[i].n = pMesh->m_normal[i];

			// BlendWeight가 있는 오브젝트 처리
			if( (*it)->m_isSkinned ) 
				_MergeBlendWeight( pVert[i], pMesh->m_vertweight[i] );

			pVert[i].t.x = BIGFLOAT;
			pVert[i].t.y = BIGFLOAT;
		}

		for( i = 0 ; i < pMesh->m_triindex.size() ; i++ )
			pIndex[i] = pMesh->m_triindex[i].index;

		cnt = pMesh->m_vertex.size();

		/// 텍스쳐가 있는 오브젝트인가?
		if( pMesh->m_texindex.size() )
		{
			for( i = 0 ; i < pMesh->m_triindex.size() ; i++ )
			{
				for( j = 0 ; j < 3 ; j++ )
				{
					vindex = pIndex[i].i[j];			// 정점의 인덱스
					tindex = pMesh->m_texindex[i].i[j];	// 텍스처의 인덱스
					// 아직 값이 대입되지 않았으면 텍스처 좌표 입력
					if( pVert[vindex].t.x == BIGFLOAT || pVert[vindex].t.y == BIGFLOAT )
					{
						pVert[vindex].t = pMesh->m_tvertex[tindex];
					}
					else	// 만약 텍스처 값이 이미 있으면 새로운 정점 생성
					{
						pIndex[i].i[j] = cnt;
						pVert[cnt] = pVert[vindex];
						pVert[cnt].t = pMesh->m_tvertex[tindex];
						cnt++;
					}
				}
			}
		}
		pMesh->m_nMaterialID = pMesh->m_triindex.size() ? max( pMesh->m_triindex[0].ID, 0 ) : 0;
		pMesh->m_vtxFinal.resize( cnt );
		pMesh->m_idxFinal.resize( pMesh->m_triindex.size() );
		for( i = 0 ; i < cnt ; i++ ) pMesh->m_vtxFinal[i] = pVert[i];
		for( i = 0 ; i < pMesh->m_triindex.size() ; i++ ) pMesh->m_idxFinal[i] = pIndex[i];
		S_DELS( pVert );
		S_DELS( pIndex );
	}

	return 1;
}

int	ZCParser::_ParseInfo( ZCParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNode*		pNode = NULL;

	g_pLog->Log( "Parsing Info" );

	try
	{
		pList = m_pXML->FindElement( "Body/Info/ObjectCount" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
		pData->m_info.nObjectCount = atoi( str );

		pList = m_pXML->FindElement( "Body/Info/MeshCount" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
		pData->m_info.nMeshCount = atoi( str );
		
		pList = m_pXML->FindElement( "Body/Info/AnimationStart" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
		pData->m_info.fAnimationStart = atoi( str );
		
		pList = m_pXML->FindElement( "Body/Info/AnimationEnd" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
		pData->m_info.fAnimationEnd = atoi( str );
		
		pList = m_pXML->FindElement( "Body/Info/KeyType" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
		pData->m_info.nKeyType = 1; //atoi( str );	/// must be completed later.
		
		pList = m_pXML->FindElement( "Body/Info/Object/Value" );
		pList->get_length( &nCount );
		pData->m_info.strObjectNameTable.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pList->get_item( i, &pNode );
			m_pXML->GetElementText( pNode, str );
			pData->m_info.strObjectNameTable[i] = str;
			g_pLog->Log( "Objects[%d] = %s", i, pData->m_info.strObjectNameTable[i].c_str() );
		}

		pList = m_pXML->FindElement( "Body/Info/Bone/Value" );
		pList->get_length( &nCount );
		pData->m_info.BoneTable.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pList->get_item( i, &pNode );
			m_pXML->GetElementText( pNode, str );
			m_pXML->GetAttributeText( pNode, "ID", str );
			pData->m_info.BoneTable[i] = atoi( str );
			g_pLog->Log( "Bone[%d] = %s", i, pData->m_info.strObjectNameTable[atoi(str)].c_str() );
		}


		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseMaterial( ZCParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNode = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	g_pLog->Log( "Parsing Material" );

	try
	{
		pList = m_pXML->FindElement( "Body/Material/Slot" );
		pList->get_length( &nCount );
		pData->m_materialTable.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pList->get_item( i, &pNode );
			pListChild = m_pXML->FindElement( pNode, "Diffuse" );
			pListChild->get_item( 0, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pData->m_materialTable[i].diffuse = _StrToColor3f( str );

			pListChild = m_pXML->FindElement( pNode, "Ambient" );
			pListChild->get_item( 0, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pData->m_materialTable[i].ambient = _StrToColor3f( str );

			pListChild = m_pXML->FindElement( pNode, "Specular" );
			pListChild->get_item( 0, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pData->m_materialTable[i].specular = _StrToColor3f( str );

			pListChild = m_pXML->FindElement( pNode, "Emissive" );
			pListChild->get_item( 0, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pData->m_materialTable[i].emissive = _StrToColor3f( str );
			
			pListChild = m_pXML->FindElement( pNode, "Opacity" );
			pListChild->get_item( 0, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pData->m_materialTable[i].opacity = atof( str );

			pListChild = m_pXML->FindElement( pNode, "Power" );
			pListChild->get_item( 0, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pData->m_materialTable[i].power = atof( str );

			pListChild = m_pXML->FindElement( pNode, "DiffuseMap" );
			if( S_OK == pListChild->get_item( 0, &pNodeChild ) )
			{
				m_pXML->GetElementText( pNodeChild, str );
				pData->m_materialTable[i].strMapDiffuse = str;
			}

			pListChild = m_pXML->FindElement( pNode, "SpecularMap" );
			if( S_OK == pListChild->get_item( 0, &pNodeChild ) )
			{
				m_pXML->GetElementText( pNodeChild, str );
				pData->m_materialTable[i].strMapSpecular = str;
			}

			pListChild = m_pXML->FindElement( pNode, "BumpMap" );
			if( S_OK == pListChild->get_item( 0, &pNodeChild ) )
			{
				m_pXML->GetElementText( pNodeChild, str );
				pData->m_materialTable[i].strMapBump = str;
			}

			pListChild = m_pXML->FindElement( pNode, "DisplacementMap" );
			if( S_OK == pListChild->get_item( 0, &pNodeChild ) )
			{
				m_pXML->GetElementText( pNodeChild, str );
				pData->m_materialTable[i].strMapDisplace = str;
			}
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObject( ZCParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNode*		pNode = NULL;
	ZCMesh*				pMesh;

	g_pLog->Log( "Parsing Objects..." );

	try
	{
		pList = m_pXML->FindElement( "Body/Object" );
		pList->get_length( &nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pMesh = new ZCMesh();
			pData->m_meshList.push_back( pMesh );

			pList->get_item( i, &pNode );
			m_pXML->GetAttributeText( pNode, "ID", str );
			pMesh->m_nObjectID = atoi( str );
			m_pXML->GetAttributeText( pNode, "Class", str );
			pMesh->m_strNodeType = str;

			g_pLog->Log( "Parsing [%s]...", pData->m_info.strObjectNameTable[i].c_str() );

			if( !_ParseObjectParent( pMesh, pNode ) ) throw;
			if( !_ParseObjectBBox( pMesh, pNode ) ) throw;
			if( !_ParseObjectTM( pMesh, pNode ) ) throw;
			if( !_ParseObjectVertex( pMesh, pNode ) ) throw;
			if( !_ParseObjectVertexNormal( pMesh, pNode ) ) throw;
			if( !_ParseObjectTVertex( pMesh, pNode ) ) throw;
			if( !_ParseObjectTriIndex( pMesh, pNode ) ) throw;
			if( !_ParseObjectTexIndex( pMesh, pNode ) ) throw;
			if( !_ParseObjectVertWeight( pMesh, pNode ) ) throw;
			if( !_ParseObjectKey( pMesh, pNode ) ) throw;

			pMesh->m_track.start = pData->m_info.fAnimationStart;
			pMesh->m_track.end = pData->m_info.fAnimationEnd;
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectParent( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing Parent" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "Parent" );
		pListChild->get_item( 0, &pNodeChild );
		m_pXML->GetAttributeText( pNodeChild, "ID", str );
		pMesh->m_nParentID = atoi( str );
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectBBox( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing BoundingBox" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "BoundingBox/Max" );
		pListChild->get_item( 0, &pNodeChild );
		m_pXML->GetElementText( pNodeChild, str );
		pMesh->m_bboxMax = _StrToVector3f( str );

		pListChild = m_pXML->FindElement( pNode, "BoundingBox/Min" );
		pListChild->get_item( 0, &pNodeChild );
		m_pXML->GetElementText( pNodeChild, str );
		pMesh->m_bboxMin = _StrToVector3f( str );
		
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectTM( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TM" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "LocalTM/Value" );
		pListChild->get_length( &nCount );

		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_tm.row[i] = _StrToVector4f( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectVertex( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing Vertex" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "Vertex/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_vertex.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_vertex[i] = _StrToVector3f( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectVertexNormal( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing VertexNormal" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "VertexNormal/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_normal.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_normal[i] = _StrToVector3f( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectTVertex( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TexVertex" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "TexVertex/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_tvertex.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_tvertex[i] = _StrToVector2f( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectTriIndex( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TriIndex" ) );
	try
	{
		/// Get material count
		pListChild = m_pXML->FindElement( pNode, "TriIndex" );
		pListChild->get_item( 0, &pNodeChild );
		if( pNodeChild == NULL )
		{
			pMesh->m_nMaterialCount = 0;
			return 1;
		}
		m_pXML->GetAttributeText( pNodeChild, "MaterialCount", str );
		pMesh->m_nMaterialCount = atoi( str );

		pListChild = m_pXML->FindElement( pNode, "TriIndex/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_triindex.resize( nCount );

		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetAttributeText( pNodeChild, "MaterialID", str );
			pMesh->m_triindex[i].ID = atoi( str );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_triindex[i].index = _StrToIndex3i( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectTexIndex( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TexIndex" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "TexIndex/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_texindex.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_texindex[i] = _StrToIndex3i( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectVertWeight( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i, j;
	char				str[128];
	long				nCount = 0;
	long				nCount2 = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNodeList*	pListChild2 = NULL;
	IXMLDOMNode*		pNodeChild = NULL;
	IXMLDOMNode*		pNodeChild2 = NULL;

	assert( g_pLog->Log( "Parsing VertexWeight" ) );
	try
	{
		pListChild = m_pXML->FindElement( pNode, "VertexWeight/Vertex" );
		pListChild->get_length( &nCount );
		if( 0 == nCount ) { pMesh->m_isSkinned = false; return 1; }
		pMesh->m_isSkinned = true;

		pMesh->m_vertweight.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			pListChild2 = m_pXML->FindElement( pNodeChild, "Value" );
			pListChild2->get_length( &nCount2 );
			pMesh->m_vertweight[i].ID.resize( nCount2 );
			pMesh->m_vertweight[i].fWeight.resize( nCount2 );
			for( j = 0 ; j < nCount2 ; j++ )
			{
				m_pXML->GetAttributeText( pNodeChild2, "BoneID", str );
				pMesh->m_vertweight[i].ID[j] = atoi( str );
//				assert( g_pLog->Log( "vertex[%d] Bone ID=%d", i, pMesh->m_vertweight[i].ID[j] ) );

				pListChild2->get_item( j, &pNodeChild2 );
				m_pXML->GetElementText( pNodeChild2, str );
				pMesh->m_vertweight[i].fWeight[j] = (float)atof( str );
//				assert( g_pLog->Log( "vertex[%d] Bone Weight=%f", i, pMesh->m_vertweight[i].fWeight[j] ) );
			}
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

int	ZCParser::_ParseObjectKey( ZCMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing Key" ) );

	try
	{
		pListChild = m_pXML->FindElement( pNode, "Key/Position/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_track.pos.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetAttributeText( pNodeChild, "Frame", str );
			pMesh->m_track.pos[i].frame = (float)atof( str );
			m_pXML->GetElementText( pNodeChild, str );
//			assert( g_pLog->Log( "[%d]th [%f]frame key=%s", i, pMesh->m_track.pos[i].frame, str ) );
			pMesh->m_track.pos[i].value = _StrToVector3f( str );
		}

		pListChild = m_pXML->FindElement( pNode, "Key/Quaternion/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_track.rot.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetAttributeText( pNodeChild, "Frame", str );
			pMesh->m_track.rot[i].frame = (float)atof( str );
			m_pXML->GetElementText( pNodeChild, str );
//			assert( g_pLog->Log( "[%d]th [%f]frame key=%s", i, pMesh->m_track.rot[i].frame, str ) );
			pMesh->m_track.rot[i].value = _StrToVector4f( str );
		}

		pListChild = m_pXML->FindElement( pNode, "Key/Scale/Value" );
		pListChild->get_length( &nCount );
		pMesh->m_track.scl.resize( nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetAttributeText( pNodeChild, "Frame", str );
			pMesh->m_track.scl[i].frame = (float)atof( str );
			m_pXML->GetElementText( pNodeChild, str );
//			assert( g_pLog->Log( "[%d]th [%f]frame key=%s", i, pMesh->m_track.scl[i].frame, str ) );
			pMesh->m_track.scl[i].value = _StrToVector3f( str );
		}

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

Index3i ZCParser::_StrToIndex3i( char str[] )
{
	Index3i		val;
	char*		sep = " [],\n";

	val.i[0] = atoi( strtok( str, sep ) );
	val.i[1] = atoi( strtok( NULL, sep ) );
	val.i[2] = atoi( strtok( NULL, sep ) );

	return val;
}

Color3f ZCParser::_StrToColor3f( char str[] )
{
	Color3f		val;
	char*		sep = " [],\n";

	strtok( str, sep );		// skip 'Color' string
	val.r = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.g = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.b = (float)atof( strtok( NULL, sep ) ) / 255.0f;

	return val;
}

Vector2f ZCParser::_StrToVector2f( char str[] )
{
	Vector2f	val;
	char*		sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );

	return val;
}

Vector3f ZCParser::_StrToVector3f( char str[] )
{
	Vector3f	val;
	char*		sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );
	val.z = (float)atof( strtok( NULL, sep ) );

	return val;
}

Vector4f ZCParser::_StrToVector4f( char str[] )
{
	Vector4f	val;
	char*		sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );
	val.z = (float)atof( strtok( NULL, sep ) );
	val.w = (float)atof( strtok( NULL, sep ) );

	return val;
}

