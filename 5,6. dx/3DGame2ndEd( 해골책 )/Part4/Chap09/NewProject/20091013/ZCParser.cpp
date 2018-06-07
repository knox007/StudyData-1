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

int	ZCParser::Parse( ZCParsedData* pData, char* lpszFilename )
{
	if( !Parse_XML( pData, lpszFilename ) ) return 0;
	g_pLog->Log( "Parsing XML Successed!" );

	if( !Parse_Split( pData ) ) return 0;
	g_pLog->Log( "Parser Split process Successed!" );

	if( !Parse_Merge( pData ) ) return 0;
	g_pLog->Log( "Parsing Merge process Successed!" );

	return 1;
}

int	ZCParser::Parse_XML( ZCParsedData* pData, char* lpszFilename )
{
	if( !m_pXML->Open( lpszFilename ) )
	{
		g_pLog->Log( "can't open [%s] file.", lpszFilename );
		return 0;
	}
	if( !_ParseInfo( pData ) )
	{
		g_pLog->Log( "can't parse info block in [%] file.", lpszFilename );
		return 0;
	}
	
	if( !_ParseMaterial( pData ) )
	{
		g_pLog->Log( "can't parse material block in [%] file.", lpszFilename );
		return 0;
	}

	if( !_ParseObject( pData ) )
	{
		g_pLog->Log( "can't parse object block in [%] file.", lpszFilename );
		return 0;
	}
		
	return 1;
}

/// TriIndex에 따라서 삼각형은 sub material정보를 새로운 ZCMesh오브젝트로 분리한다.
int	ZCParser::_SplitMeshByFaceMaterial( ZCParsedData* pData )
{
	unsigned long					i, j, cnt;
	std::list<ZCMesh*>::iterator	it, jt;
	ZCMesh*							pMesh;
	ZCMesh*							pOrig;

	g_pLog->Log( "_SplitMeshByFaceMaterial() enter!" );

	for( it = pData->m_meshList.begin() ; it != pData->m_meshList.end() ; it++ )
	{
		g_pLog->Log( "[_SplitMeshByFaceMaterial()] %d: %d ", (*it)->m_nObjectID, (*it)->m_nMaterialCount );
		if( (*it)->m_strNodeType.compare( "Editable_mesh" ) ) continue;

		/// Sub-Material이 있는가?
		if( (*it)->m_nMaterialCount > 1 )
		{
			// sub-meterial개수만큼 sub-mesh가 생성되므로
			// strObjectNameTable을 sub-mesh개수만큼 늘려준다.
			// 이때, id와 배열의 위치가 매칭되도록 하는 것이 중요하다
			// sub-mesh의 이름들은 전부다 공백문자 " " 이다.
			pData->m_info.strObjectNameTable.insert( pData->m_info.strObjectNameTable.begin() + (*it)->m_nObjectID + 1, (*it)->m_nMaterialCount-1, " " );
			
			// sub-meterial개수만큼 sub-mesh가 생성되므로
			// BoneTables이 가리키는 뼈대의 번호중 생성되는 sub-mesh에 해당하는 번호는 
			// 그만큼 뒤로 밀어야 한다.
			for( i = 0 ; i < pData->m_info.BoneTable.size() ; i++ )
			{
				if( pData->m_info.BoneTable[i] > (*it)->m_nObjectID )
					pData->m_info.BoneTable[i] += ((*it)->m_nMaterialCount-1);
			}

			// sub-meterial개수만큼 sub-mesh가 생성되므로
			// object id와 parent id값들을 중간에 끼어넣는 sub-mesh개수만큼 증가시킨다
			for( jt = pData->m_meshList.begin() ; jt != pData->m_meshList.end() ; jt++ )
			{
				if( (*jt)->m_nObjectID > (*it)->m_nObjectID )
					(*jt)->m_nObjectID += ((*it)->m_nMaterialCount-1);
				if( (*jt)->m_nParentID > (*it)->m_nObjectID )
					(*jt)->m_nParentID += ((*it)->m_nMaterialCount-1);
			}

			j = 0;
			pOrig = *it;
			it = pData->m_meshList.erase( it );	// 원본 mesh를 리스트에서만 삭제한다
												// 아직 pOrig는 유효하다
			for( i = 0 ; i < (unsigned long)pOrig->m_nMaterialCount ; i++ )
			{
				pMesh = new ZCMesh();
				pMesh->m_strNodeType = pOrig->m_strNodeType;
				pMesh->m_nObjectID = pOrig->m_nObjectID+i;	// object id를 증가시키며 submesh등록
				pMesh->m_nObjectHashID = pOrig->m_nObjectHashID;
				pMesh->m_nParentID = pOrig->m_nParentID;
				pMesh->m_bboxMax = pOrig->m_bboxMax;
				pMesh->m_bboxMin = pOrig->m_bboxMin;
				pMesh->m_tmLocal = pOrig->m_tmLocal;
				pMesh->m_tmWorld = pOrig->m_tmWorld;
				pMesh->m_vertex = pOrig->m_vertex;
				pMesh->m_normal = pOrig->m_normal;
				pMesh->m_tvertex = pOrig->m_tvertex;
				pMesh->m_nMaterialCount = 1;
//				pMesh->m_texindex = pOrig->m_texindex;
				pMesh->m_vertweight = pOrig->m_vertweight;
				pMesh->m_track = pOrig->m_track;
				pMesh->m_isSkinned = pOrig->m_isSkinned;
				cnt = pOrig->m_triindex.size() - 1;
				for( ; j < cnt ; )
				{
					if( pOrig->m_triindex[j].ID == pOrig->m_triindex[j+1].ID )
					{
						pMesh->m_triindex.push_back( pOrig->m_triindex[j] );
						if( pOrig->m_texindex.size() )
							pMesh->m_texindex.push_back( pOrig->m_texindex[j] );
					}
					else
					{
						j++;
						if( j == cnt )	/// 제일 마지막 index정보를 복사한다.
						{
							pMesh->m_triindex.push_back( pOrig->m_triindex[j] );
							if( pOrig->m_texindex.size() )
								pMesh->m_texindex.push_back( pOrig->m_texindex[j] );
						}

						break;
					}
					j++;
				}
				// 생성한 sub-mesh를 child로 등록
				// (STL의 insert는 it앞에 insert한다.)
				it = pData->m_meshList.insert( it, pMesh );
			}
			S_DEL( pOrig );	// sub-mesh를 만들었으니 원본mesh를 메모리에서 삭제
		}
	}

	g_pLog->Log( "_SplitMeshByFaceMaterial() leave" );

	pData->m_info.nObjectCount = pData->m_meshList.size();
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
		for( i = cnt ; i < 4 ; i++ )
		{
			t.ID[i] = 0;
			t.fWeight[i] = 0;
		}
	}
	
	/// script에서 출력한 가중치값은 큰값순서로(올림차순) 정렬되어있다.
	/// 때문에 앞에서 4개만 값을 취하면 된다.
	for( i = 0 ; i < 3 ; i++ )
	{
		vm.b[i] = t.fWeight[i];
	}
	vm.i = BLENDINDEX( t.ID[3], t.ID[2], t.ID[1], t.ID[0] );
}

int	ZCParser::_MergeVertex( ZCParsedData* pData )
{
	unsigned long					i, j, cnt;
	std::list<ZCMesh*>::iterator	it, jt;
	ZCMesh*							pMesh;
	VertMerged*						pVert;
	Index3i*						pIndex;
	DWORD							vindex, tindex;

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
		pData->m_info.fAnimationStart = (float)atoi( str );
		
		pList = m_pXML->FindElement( "Body/Info/AnimationEnd" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
		pData->m_info.fAnimationEnd = (float)atoi( str );
		
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

int	ZCParser::_ParseCamera( ZCParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNode = NULL;
	IXMLDOMNode*		pNodeChild = NULL;
	KeyPos				pos;

	g_pLog->Log( "Parsing Camera" );

	// Read Camera
	{
		pList = m_pXML->FindElement( "Body/Cameras/TargetCamera/name/value" );
		pList->get_item( 0, &pNode );
		if( !pNode )return 0;
		m_pXML->GetElementText( pNode, str );
		pData->m_camera.strNameCamera = str;

		pList = m_pXML->FindElement( "Body/Cameras/TargetCamera/position/value" );
		pList->get_item( 0, &pNode );
		m_pXML->GetElementText( pNode, str );
		pData->m_camera.posCamera = _MaxToD3D( &_StrToVector3f( str ) );

		pList = m_pXML->FindElement( "Body/Cameras/TargetCamera/fov/value" );
		pList->get_item( 0, &pNode );
		m_pXML->GetElementText( pNode, str );
		pData->m_camera.fov = atof( str) ;

		pList = m_pXML->FindElement( "Body/Cameras/TargetCamera/position/controller/Key" );
		pList->get_length( &nCount );
		if( !nCount )
		{
			pData->m_camera.trkCamera.pos.resize( 1 );
			pData->m_camera.trkCamera.pos[0].frame = 0.0f;
			pData->m_camera.trkCamera.pos[0].value = pData->m_camera.posCamera;
		}
		else
		{
			pData->m_camera.trkCamera.pos.resize( nCount );
			for( i = 0 ; i < nCount ; i++ )
			{
				pList->get_item( i, &pNode );
				m_pXML->GetAttributeText( pNode, "time", str );
				pData->m_camera.trkCamera.pos[i].frame = atof( str );
				m_pXML->GetElementText( pNode, str );
				pData->m_camera.trkCamera.pos[i].value = _MaxToD3D( &_StrToVector3f( str ) );
			}
		}
	}

	// Read Target
	{
		pList = m_pXML->FindElement( "Body/Cameras/TargetObject/name/value" );
		pList->get_item( 0, &pNode );
		m_pXML->GetElementText( pNode, str );
		pData->m_camera.strNameTarget = str;

		pList = m_pXML->FindElement( "Body/Cameras/TargetObject/position/value" );
		pList->get_item( 0, &pNode );
		m_pXML->GetElementText( pNode, str );
		pData->m_camera.posTarget = _MaxToD3D( &_StrToVector3f( str ) );

		pList = m_pXML->FindElement( "Body/Cameras/TargetObject/position/controller/key" );
		pList->get_length( &nCount );
		if( !nCount )
		{
			pData->m_camera.trkTarget.pos.resize( 1 );
			pData->m_camera.trkTarget.pos[0].frame = 0.0f;
			pData->m_camera.trkTarget.pos[0].value = pData->m_camera.posTarget;
		}
		else
		{
			for( i = 0 ; i < nCount ; i++ )
			{
				pData->m_camera.trkTarget.pos.resize( nCount );
				pList->get_item( i, &pNode );
				m_pXML->GetAttributeText( pNode, "time", str );
				pData->m_camera.trkCamera.pos[i].frame = atof( str );
				m_pXML->GetElementText( pNode, str );
				pData->m_camera.trkCamera.pos[i].value = _MaxToD3D( &_StrToVector3f( str ) );
			}
		}
	}

	return 1;
}

int	ZCParser::_ParseMaterial_Map_Coord( IXMLDOMNode* pNode, ZTMaterial_Map_Coord* pCoord )
{
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->blur, "blur" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pCoord->mapping, "mapping" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pCoord->mapChannel, "mapChannel" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pCoord->mappingType, "mappingType" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pCoord->UVW_Type, "UVW_Type" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->U_Mirror, "U_Mirror" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->V_Mirror, "V_Mirror" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->U_Tile, "U_Tile" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->V_Tile, "V_Tile" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->showMapOnBack, "showMapOnBack" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->Noise_On, "Noise_On" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pCoord->Noise_Animate, "Noise_Animate" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->phase, "phase" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->U_Offset, "U_Offset" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->V_Offset, "V_Offset" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->U_Tiling, "U_Tiling" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->V_Tiling, "V_Tiling" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->U_Angle, "U_Angle" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->V_Angle, "V_Angle" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->W_Angle, "W_Angle" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->Noise_Amount, "Noise_Amount" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->Noise_Size, "Noise_Size" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pCoord->Noise_Levels, "Noise_Levels" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pCoord->Blur_Offset, "Blur_Offset" );

	return 1;
}

int	ZCParser::_ParseMaterial_Map( IXMLDOMNode* pNode, ZTMaterial_Map* pMap )
{
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pMap->enabled, "enabled" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->amount, "amount" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->clipu, "clipu" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->clipv, "clipv" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->clipw, "clipw" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->cliph, "cliph" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->jitter, "jitter" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pMap->useJitter, "useJitter" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pMap->apply, "apply" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pMap->cropPlace, "cropPlace" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pMap->filtering, "filtering" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pMap->monoOutput, "monoOutput" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pMap->rgbOutput, "rgbOutput" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pMap->alphaSource, "alphaSource" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pMap->preMultAlpha, "preMultAlpha" );

	{	// material.map.coords
		pListChild = m_pXML->FindElement( pNode, "coords" );
		pListChild->get_item( 0, &pNodeChild );
		if( pNodeChild ) _ParseMaterial_Map_Coord( pNodeChild, &pMap->coords );
	}

	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FILENAME, &pMap->fileName, "fileName" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->startTime, "startTime" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pMap->playBackRate, "playBackRate" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pMap->endCondition, "endCondition" );
	_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pMap->tieTimeToMatIDs, "tieTimeToMatIDs" );

	return 1;
}

int	ZCParser::_ParseMaterial( ZCParsedData* pData )
{
	int					i, j;
	long				nCount = 0;
	long				nMapCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNode = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	g_pLog->Log( "Parsing Material" );

	pList = m_pXML->FindElement( "Body/Materials/Slot" );
	pList->get_length( &nCount );
	pData->m_materials.resize( nCount );
	for( i = 0 ; i < nCount ; i++ )
	{
		pList->get_item( i, &pNode );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pData->m_materials[i].shaderType , "shaderType" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].wire , "wire" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].twoSided , "twoSided" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].faceMap , "faceMap" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].faceted , "faceted" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_STRING, &pData->m_materials[i].shaderByName , "shaderByName" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pData->m_materials[i].opacityType , "opacityType" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].opacity , "opacity" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pData->m_materials[i].opacityFallOffType , "opacityFallOffType" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].opacityFallOff , "opacityFallOff" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].ior , "ior" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].wireSize , "wireSize" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pData->m_materials[i].wireUnits , "wireUnits" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].applyReflectionDimming , "applyReflectionDimming" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].dimLevel , "dimLevel" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].reflectionLevel , "reflectionLevel" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_INT, &pData->m_materials[i].sampler , "sampler" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].samplerEnable , "samplerEnable" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].samplerAdaptThreshold , "samplerAdaptThreshold" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].samplerAdaptOn , "samplerAdaptOn" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].samplerAdvancedOptions , "samplerAdvancedOptions" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_STRING, &pData->m_materials[i].samplerByName , "samplerByName" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].UserParam0 , "UserParam0" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].UserParam1 , "UserParam1" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].samplerUseGlobal , "samplerUseGlobal" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].subSampleTextureOn , "subSampleTextureOn" );

		// MAP
		pListChild = m_pXML->FindElement( pNode, "Map" );
		pListChild->get_length( &nMapCount );
		pData->m_materials[i].map.resize( nMapCount );
		for( j = 0 ; j < nMapCount ; j++ )
		{
			pListChild->get_item( j, &pNodeChild );
			_ParseMaterial_Map( pNodeChild, &pData->m_materials[i].map[j] );
		}

		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].bounce , "bounce" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].staticFriction , "staticFriction" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].slidingFriction , "slidingFriction" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_COLOR3, &pData->m_materials[i].ambient , "ambient" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_COLOR3, &pData->m_materials[i].diffuse , "diffuse" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_COLOR3, &pData->m_materials[i].specular , "specular" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].adTextureLock , "adTextureLock" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].adLock , "adLock" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].dsLock , "dsLock" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_BOOL, &pData->m_materials[i].useSelfIllumColor , "useSelfIllumColor" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].selfIllumAmount , "selfIllumAmount" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_COLOR3, &pData->m_materials[i].selfIllumColor , "selfIllumColor" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].specularLevel , "specularLevel" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].glossiness , "glossiness" );
		_ReadValues( pNode, ZTKeyBase::KEYTYPE_FLOAT, &pData->m_materials[i].soften , "soften" );
	}

	return 1;
}

int ZCParser::_ReadValues( IXMLDOMNode* pNode, ZTKeyBase::KEYTYPE nCtrlType, ZCtrlBase* pCtrl, char strNode[] )
{
	long				i;
	long				nCount;
	char				str[128];
	char				str2[128];
	char				dst[128];
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;
	ZTKeyBase*			pKeyBase;

	pList = m_pXML->FindElement( pNode, strNode );
	pList->get_item( 0, &pNodeChild );

	if( !pNodeChild ) return 0;

	pListChild = m_pXML->FindElement( pNodeChild, "controller/Key" );
	pListChild->get_length( &nCount );
	if( nCount )
	{
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNode );
			m_pXML->GetAttributeText( pNode, "time", str2 );
			m_pXML->GetElementText( pNode, str );

			switch( nCtrlType )
			{
				case ZTKeyBase::KEYTYPE_FILENAME:
					{
						ZTKeyString*	pKey = new ZTKeyString;
						pKey->type = ZTKeyBase::KEYTYPE_STRING;
						pKey->frame = _StrToFloat( str2 );
						_StrToFilename( dst, str );
						pKey->value = dst;
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_STRING:
					{
						ZTKeyString*	pKey = new ZTKeyString;
						pKey->type = ZTKeyBase::KEYTYPE_STRING;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = str;
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_BOOL:
					{
						ZTKeyBool*	pKey = new ZTKeyBool;
						pKey->type = ZTKeyBase::KEYTYPE_BOOL;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = _StrToBool( str );
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_INT:
					{
						ZTKeyInt*	pKey = new ZTKeyInt;
						pKey->type = ZTKeyBase::KEYTYPE_INT;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = _StrToInt( str );
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_FLOAT:
					{
						ZTKeyFloat*	pKey = new ZTKeyFloat;
						pKey->type = ZTKeyBase::KEYTYPE_FLOAT;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = _StrToFloat( str );
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_POINT3:
					{
						ZTKeyPoint3*	pKey = new ZTKeyPoint3;
						pKey->type = ZTKeyBase::KEYTYPE_POINT3;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = _StrToPoint3( str );
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_POINT4:
					{
						ZTKeyPoint4*	pKey = new ZTKeyPoint4;
						pKey->type = ZTKeyBase::KEYTYPE_POINT4;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = _StrToPoint4( str );
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_QUATERNION:
					{
						ZTKeyQuat*	pKey = new ZTKeyQuat;
						pKey->type = ZTKeyBase::KEYTYPE_QUATERNION;
						pKey->frame = _StrToFloat( str2 );
						pKey->value = _StrToQuat( str );
						pKeyBase = pKey;
					}
					break;
				case ZTKeyBase::KEYTYPE_COLOR3:
					{
						ZTKeyPoint3*	pKey = new ZTKeyPoint3;
						Color3f			v;
						pKey->type = ZTKeyBase::KEYTYPE_POINT3;
						pKey->frame = _StrToFloat( str2 );
						v = _StrToColor3f( str );
						pKey->value.x = v.x;
						pKey->value.y = v.y;
						pKey->value.z = v.z;
						pKeyBase = pKey;
					}
					break;
				default :
					break;
			}
			
			pCtrl->AddKey( pKeyBase );
		}
	}
	else
	{
		pListChild = m_pXML->FindElement( pNodeChild, "value" );
		pListChild->get_item( 0, &pNode );
		m_pXML->GetElementText( pNode, str );
		switch( nCtrlType )
		{
			case ZTKeyBase::KEYTYPE_FILENAME:
				{
					ZTKeyString*	pKey = new ZTKeyString;
					pKey->type = ZTKeyBase::KEYTYPE_STRING;
					pKey->frame = _StrToFloat( str2 );
					_StrToFilename( dst, str );
					pKey->value = dst;
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_STRING:
				{
					ZTKeyString*	pKey = new ZTKeyString;
					pKey->type = ZTKeyBase::KEYTYPE_STRING;
					pKey->frame = 0;
					pKey->value = str;
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_BOOL:
				{
					ZTKeyBool*	pKey = new ZTKeyBool;
					pKey->type = ZTKeyBase::KEYTYPE_BOOL;
					pKey->frame = 0;
					pKey->value = _StrToBool( str );
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_INT:
				{
					ZTKeyInt*	pKey = new ZTKeyInt;
					pKey->type = ZTKeyBase::KEYTYPE_INT;
					pKey->frame = 0;
					pKey->value = _StrToInt( str );
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_FLOAT:
				{
					ZTKeyFloat*	pKey = new ZTKeyFloat;
					pKey->type = ZTKeyBase::KEYTYPE_FLOAT;
					pKey->frame = 0;
					pKey->value = _StrToFloat( str );
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_POINT3:
				{
					ZTKeyPoint3*	pKey = new ZTKeyPoint3;
					pKey->type = ZTKeyBase::KEYTYPE_POINT3;
					pKey->frame = 0;
					pKey->value = _StrToPoint3( str );
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_POINT4:
				{
					ZTKeyPoint4*	pKey = new ZTKeyPoint4;
					pKey->type = ZTKeyBase::KEYTYPE_POINT4;
					pKey->frame = 0;
					pKey->value = _StrToPoint4( str );
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_QUATERNION:
				{
					ZTKeyQuat*	pKey = new ZTKeyQuat;
					pKey->type = ZTKeyBase::KEYTYPE_QUATERNION;
					pKey->frame = 0;
					pKey->value = _StrToQuat( str );
					pKeyBase = pKey;
				}
				break;
			case ZTKeyBase::KEYTYPE_COLOR3:
				{
					ZTKeyPoint3*	pKey = new ZTKeyPoint3;
					Color3f			v;
					pKey->type = ZTKeyBase::KEYTYPE_POINT3;
					pKey->frame = _StrToFloat( str2 );
					v = _StrToColor3f( str );
					pKey->value.x = v.x;
					pKey->value.y = v.y;
					pKey->value.z = v.z;
					pKeyBase = pKey;
				}
			default :
				break;
		}
		
		pCtrl->AddKey( pKeyBase );
	}

	return 1;
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
			pMesh->m_tmLocal.row[i] = _StrToVector4f( str );
		}

		pListChild = m_pXML->FindElement( pNode, "WorldTM/Value" );
		pListChild->get_length( &nCount );
		for( i = 0 ; i < nCount ; i++ )
		{
			pListChild->get_item( i, &pNodeChild );
			m_pXML->GetElementText( pNodeChild, str );
			pMesh->m_tmWorld.row[i] = _StrToVector4f( str );
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
				pListChild2->get_item( j, &pNodeChild2 );
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
	char*		sep = " ()[],\n";

	if( str[0] == '(' )
	{
		strtok( str, sep );		// skip 'Color' string
		val.x = (float)atof( strtok( NULL, sep ) ) / 255.0f;
		val.y = (float)atof( strtok( NULL, sep ) ) / 255.0f;
		val.z = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	}
	else
	{
		val.x = (float)atof( strtok( str,  sep ) ) / 255.0f;
		val.y = (float)atof( strtok( NULL, sep ) ) / 255.0f;
		val.z = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	}

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

Vector3f ZCParser::_MaxToD3D( Vector3f* pVec )
{
	Vector3f	val;
	val.x = pVec->x;
	val.y = pVec->z;
	val.z = pVec->y;

	return val;
}

BOOL ZCParser::_StrToBool( char str[] )
{
	return (BOOL)!_stricmp( str, "true" );
}

int ZCParser::_StrToInt( char str[] )
{
	return atoi( str );
}

float ZCParser::_StrToFloat( char str[] )
{
	return (float)atof( str );
}

D3DXVECTOR3	ZCParser::_StrToPoint3( char str[] )
{
	D3DXVECTOR3		val;
	char*			sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.z = (float)atof( strtok( NULL, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );

	return val;
}

D3DXVECTOR4	ZCParser::_StrToPoint4( char str[] )
{
	D3DXVECTOR4		val;
	char*			sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.z = (float)atof( strtok( NULL, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );
	val.w = (float)atof( strtok( NULL, sep ) );

	return val;
}

D3DXQUATERNION ZCParser::_StrToQuat( char str[] )
{
	D3DXQUATERNION	q;
	Vector4f		val = _StrToVector4f( str );

	q.x = -val.x;
	q.y = -val.z;
	q.z = -val.y;
	q.w = val.w;

	return q;
}
void ZCParser::_StrToFilename( char* dst, char str[] )
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath( str, drive, dir, fname, ext );
	strcpy( dst, fname );
	strcat( dst, ext );
}

ZTKeyBase::KEYTYPE ZCParser::_StrToKeytype( char str[] )
{
//	if( !_stricmp( str, "Bezier_Bool" ) ) return ZTKeyBase::KEYTYPE_BOOL;
//	if( !_stricmp( str, "Bezier_Int" ) ) return ZTKeyBase::KEYTYPE_INT;
	if( !_stricmp( str, "Bezier_Float" ) ) return ZTKeyBase::KEYTYPE_FLOAT;
	if( !_stricmp( str, "Bezier_Color" ) ) return ZTKeyBase::KEYTYPE_POINT3;
	if( !_stricmp( str, "Bezier_Position" ) ) return ZTKeyBase::KEYTYPE_POINT3;

	return ZTKeyBase::KEYTYPE_BASE;
}
