#include <windows.h>
#include <assert.h>
#include "ZXml.h"
#include "ZPreDefines.h"
#include "ZParser.h"
#include "ZFLog.h"
#include "ZNode.h"

/// 최초 생성자
ZParser::ZParser()
{
	m_pXML = new ZXML;
}

/// 소멸자
ZParser::~ZParser()
{
	m_pXML->Close();
	S_DEL( m_pXML );
}

void ZParser::_PostProcess( ZParsedData* pData )
{
	list<ZNode*>::iterator  i, j;
	ZNode*	pFrom = NULL;
	ZNode*	pTo = NULL;

	for( i = pData->m_nodeList.begin() ; i != pData->m_nodeList.end() ; i++ )
	{
		if( (*i)->m_nNodeType == ZNode::MESH ||
			(*i)->m_nNodeType == ZNode::SPHERE ||
			(*i)->m_nNodeType == ZNode::CYLINDER )
		{
			pData->m_geomList.push_back( (ZGeometry*)(*i) );

			/// calculate bounding box & bounding sphere
			((ZGeometry*)(*i))->CalcBounder();
		}
		
		if( (*i)->m_nNodeType == ZNode::LIGHT )
			pData->m_lightList.push_back( (ZLight*)(*i) );

		if( (*i)->m_strNodeType == (string)NODE_CAMERA_CLASS )
		{
			pFrom = (*i);

			/// 아래의 for루프는 맥스 스크립트의 특성상 다음과 같이 코딩해도 될 듯하다.
			/// i++; pTo = (*i)
			for( j = pData->m_nodeList.begin() ; j != pData->m_nodeList.end() ; j++ )
				if( (*j)->m_strNodeType == (string)NODE_CAMERATARGET_CLASS )
				{
					pTo = (*j);
					break;
				}
		}
	}

	if( pFrom && pTo )
	{
		ZCamera*	pCamera = new ZCamera;
		*((ZNode*)pCamera) = *pFrom;
		pCamera->m_vFrom = Vector3f( pFrom->m_tmWorld._41, pFrom->m_tmWorld._42, pFrom->m_tmWorld._43 ); 
		pCamera->m_vTo = Vector3f( pTo->m_tmWorld._41, pTo->m_tmWorld._42, pTo->m_tmWorld._43 );
		pCamera->m_vUp = Vector3f( 0.0f, 1.0f, 0.0f );
		pCamera->GenerateMatrix();
		pData->m_pCamera = pCamera;
	}
}

/// XML 데이터를 파싱한다.
int	ZParser::Parse_XML( ZParsedData* pData, char* lpszFilename )
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

	if( !_ParseNode( pData ) )
	{
		g_pLog->Log( "can't parse object block in [%] file.", lpszFilename );
		return 0;
	}

	_PostProcess( pData );

	return 1;		
}

int	ZParser::_ParseInfo( ZParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNode*		pNode = NULL;

	g_pLog->Log( "Parsing Info" );

	pList = m_pXML->FindElement( "Body/Info/NodeCount" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
	pData->m_info.nObjectCount = atoi( str );

	pList = m_pXML->FindElement( "Body/Info/GeometryCount" );	pList->get_item( 0, &pNode );	m_pXML->GetElementText( pNode, str );
	pData->m_info.nGeometryCount = atoi( str );
	
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

	return 1;
}

int	ZParser::_ParseMaterial( ZParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNode = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	g_pLog->Log( "Parsing Material" );

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
		pData->m_materialTable[i].opacity = (float)atof( str );

		pListChild = m_pXML->FindElement( pNode, "Power" );
		pListChild->get_item( 0, &pNodeChild );
		m_pXML->GetElementText( pNodeChild, str );
		pData->m_materialTable[i].power = (float)atof( str );

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

int	ZParser::_ParseNode( ZParsedData* pData )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNode*		pNode = NULL;
//	ZNode*				pMesh;
	int					nObjectID;
	string				strNodeType;

	g_pLog->Log( "Parsing Objects..." );

	pList = m_pXML->FindElement( "Body/Object" );
	pList->get_length( &nCount );
	for( i = 0 ; i < nCount ; i++ )
	{

		pList->get_item( i, &pNode );
		m_pXML->GetAttributeText( pNode, "ID", str );
		nObjectID = atoi( str );
		m_pXML->GetAttributeText( pNode, "Class", str );
		strNodeType = str;

		g_pLog->Log( "Parsing [%s]...", pData->m_info.strObjectNameTable[i].c_str() );

		if( strNodeType == (string)NODE_MESH_CLASS )
		{
			ZMesh* pMesh;
			pMesh = new ZMesh;
			pMesh->m_nObjectID = nObjectID;
			pMesh->m_strNodeType = strNodeType;
			pMesh->m_nNodeType = ZNode::MESH;
			pData->m_nodeList.push_back( (ZNode*)pMesh );
			if( !_ParseNodeBBox( (ZGeometry*)pMesh, pNode ) ) return 0;
			if( !_ParseNodeTM( pMesh, pNode ) ) return 0;

			if( !_ParseMeshVertex( (ZMesh*)pMesh, pNode ) ) return 0;
			if( !_ParseMeshVertexNormal( (ZMesh*)pMesh, pNode ) ) return 0;
// 아직 texture는 지원하지 않는다.
//				if( !_ParseMeshTVertex( (ZMesh*)pMesh, pNode ) ) return 0;
			if( !_ParseMeshTriIndex( (ZMesh*)pMesh, pNode ) ) return 0;
//				if( !_ParseMeshTexIndex( (ZMesh*)pMesh, pNode ) ) return 0;
		}
		else
		if( strNodeType == (string)NODE_SPHERE_CLASS )
		{
			ZSphere* pMesh;
			pMesh = new ZSphere;
			pMesh->m_nObjectID = nObjectID;
			pMesh->m_strNodeType = strNodeType;
			pMesh->m_nNodeType = ZNode::SPHERE;
			pData->m_nodeList.push_back( (ZNode*)pMesh );
			if( !_ParseNodeBBox( (ZGeometry*)pMesh, pNode ) ) return 0;
			if( !_ParseNodeTM( pMesh, pNode ) ) return 0;
			if( !_ParseSphere( (ZSphere*)pMesh, pNode ) ) return 0;
		}
		else
		if( strNodeType == (string)NODE_CYLINDER_CLASS )
		{
			ZCylinder* pMesh;
			pMesh = new ZCylinder;
			pMesh->m_nObjectID = nObjectID;
			pMesh->m_strNodeType = strNodeType;
			pMesh->m_nNodeType = ZNode::CYLINDER;
			pData->m_nodeList.push_back( (ZNode*)pMesh );
			if( !_ParseNodeBBox( (ZGeometry*)pMesh, pNode ) ) return 0;
			if( !_ParseNodeTM( pMesh, pNode ) ) return 0;
			if( !_ParseCylinder( (ZCylinder*)pMesh, pNode ) ) return 0;
		}
		else	/// camera, light, etc...
		{
			ZNode* pMesh;
			pMesh = new ZNode;
			pMesh->m_nObjectID = nObjectID;
			pMesh->m_strNodeType = strNodeType;
			if( strNodeType == (string)NODE_LIGHT_CLASS ) pMesh->m_nNodeType = ZNode::LIGHT;
			if( strNodeType == (string)NODE_CAMERA_CLASS ) pMesh->m_nNodeType = ZNode::CAMERA;
			if( strNodeType == (string)NODE_CAMERATARGET_CLASS ) pMesh->m_nNodeType = ZNode::CAMERATARGET;
			pData->m_nodeList.push_back( pMesh );
			if( !_ParseNodeTM( pMesh, pNode ) ) return 0;
		}
	}

	return 1;
}

int	ZParser::_ParseSphere( ZSphere* pMesh, IXMLDOMNode* pNode )
{
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing Sphere" ) );

	pListChild = m_pXML->FindElement( pNode, "Material" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_nMaterialID = atoi( str );

	pListChild = m_pXML->FindElement( pNode, "Radius" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_fRadius = (float)atof( str );

	return 1;
}

int	ZParser::_ParseCylinder( ZCylinder* pMesh, IXMLDOMNode* pNode )
{
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing Cylinder" ) );

	pListChild = m_pXML->FindElement( pNode, "Material" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_nMaterialID = atoi( str );

	pListChild = m_pXML->FindElement( pNode, "Radius" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_fRadius = (float)atof( str );

	pListChild = m_pXML->FindElement( pNode, "Height" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_fHeight = (float)atof( str );

	return 1;
}

int	ZParser::_ParseNodeBBox( ZGeometry* pMesh, IXMLDOMNode* pNode )
{
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing BoundingBox" ) );

	pListChild = m_pXML->FindElement( pNode, "BoundingBox/Max" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_bbox.vMax = _StrToVector3f( str );

	pListChild = m_pXML->FindElement( pNode, "BoundingBox/Min" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetElementText( pNodeChild, str );
	pMesh->m_bbox.vMin = _StrToVector3f( str );
	
	return 1;
}

int	ZParser::_ParseNodeTM( ZNode* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;
	Vector4f			v[4];
	assert( g_pLog->Log( "Parsing TM" ) );

	pListChild = m_pXML->FindElement( pNode, "LocalTM/Value" );
	pListChild->get_length( &nCount );
	for( i = 0 ; i < nCount ; i++ )
	{
		pListChild->get_item( i, &pNodeChild );
		m_pXML->GetElementText( pNodeChild, str );
		v[i] = _StrToVector4f( str );
	}
	pMesh->m_tmLocal._11 = v[0].x;	pMesh->m_tmLocal._12 = v[0].y;	pMesh->m_tmLocal._13 = v[0].z;	pMesh->m_tmLocal._14 = v[0].w;
	pMesh->m_tmLocal._21 = v[1].x;	pMesh->m_tmLocal._22 = v[1].y;	pMesh->m_tmLocal._23 = v[1].z;	pMesh->m_tmLocal._24 = v[1].w;
	pMesh->m_tmLocal._31 = v[2].x;	pMesh->m_tmLocal._32 = v[2].y;	pMesh->m_tmLocal._33 = v[2].z;	pMesh->m_tmLocal._34 = v[2].w;
	pMesh->m_tmLocal._41 = v[3].x;	pMesh->m_tmLocal._42 = v[3].y;	pMesh->m_tmLocal._43 = v[3].z;	pMesh->m_tmLocal._44 = v[3].w;

	pListChild = m_pXML->FindElement( pNode, "WorldTM/Value" );
	pListChild->get_length( &nCount );
	for( i = 0 ; i < nCount ; i++ )
	{
		pListChild->get_item( i, &pNodeChild );
		m_pXML->GetElementText( pNodeChild, str );
		v[i] = _StrToVector4f( str );
	}
	pMesh->m_tmWorld._11 = v[0].x;	pMesh->m_tmWorld._12 = v[0].y;	pMesh->m_tmWorld._13 = v[0].z;	pMesh->m_tmWorld._14 = v[0].w;
	pMesh->m_tmWorld._21 = v[1].x;	pMesh->m_tmWorld._22 = v[1].y;	pMesh->m_tmWorld._23 = v[1].z;	pMesh->m_tmWorld._24 = v[1].w;
	pMesh->m_tmWorld._31 = v[2].x;	pMesh->m_tmWorld._32 = v[2].y;	pMesh->m_tmWorld._33 = v[2].z;	pMesh->m_tmWorld._34 = v[2].w;
	pMesh->m_tmWorld._41 = v[3].x;	pMesh->m_tmWorld._42 = v[3].y;	pMesh->m_tmWorld._43 = v[3].z;	pMesh->m_tmWorld._44 = v[3].w;

	return 1;
}

int	ZParser::_ParseMeshVertex( ZMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing Vertex" ) );

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

int	ZParser::_ParseMeshVertexNormal( ZMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing VertexNormal" ) );

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

int	ZParser::_ParseMeshTVertex( ZMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TexVertex" ) );

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

int	ZParser::_ParseMeshTriIndex( ZMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TriIndex" ) );

	pListChild = m_pXML->FindElement( pNode, "TriIndex" );
	pListChild->get_item( 0, &pNodeChild );
	m_pXML->GetAttributeText( pNodeChild, "MaterialCount", str );
//	pMesh->m_nMaterialCount = atoi( str );

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

int	ZParser::_ParseMeshTexIndex( ZMesh* pMesh, IXMLDOMNode* pNode )
{
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	assert( g_pLog->Log( "Parsing TexIndex" ) );

	pListChild = m_pXML->FindElement( pNode, "TexIndex/Value" );
	pListChild->get_length( &nCount );
	pMesh->m_texindex.resize( nCount );
	for( i = 0 ; i < nCount ; i++ )
	{
		pListChild->get_item( i, &pNodeChild );
		m_pXML->GetElementText( pNodeChild, str );
		pMesh->m_texindex[i].index = _StrToIndex3i( str );
	}

	return 1;
}

Index3i ZParser::_StrToIndex3i( char str[] )
{
	Index3i		val;
	char*		sep = " [],\n";

	val.i[0] = atoi( strtok( str, sep ) );
	val.i[1] = atoi( strtok( NULL, sep ) );
	val.i[2] = atoi( strtok( NULL, sep ) );

	return val;
}

Color3f ZParser::_StrToColor3f( char str[] )
{
	Color3f		val;
	char*		sep = " [],\n";

	strtok( str, sep );		// skip 'Color' string
	val.r = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.g = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.b = (float)atof( strtok( NULL, sep ) ) / 255.0f;

	return val;
}

Color4f ZParser::_StrToColor4f( char str[] )
{
	Color4f		val;
	char*		sep = " [],\n";

	strtok( str, sep );		// skip 'Color' string
	val.r = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.g = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.b = (float)atof( strtok( NULL, sep ) ) / 255.0f;
	val.a = (float)0.0f;

	return val;
}

Vector2f ZParser::_StrToVector2f( char str[] )
{
	Vector2f	val;
	char*		sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );

	return val;
}

Vector3f ZParser::_StrToVector3f( char str[] )
{
	Vector3f	val;
	char*		sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );
	val.z = (float)atof( strtok( NULL, sep ) );

	return val;
}

Vector4f ZParser::_StrToVector4f( char str[] )
{
	Vector4f	val;
	char*		sep = " [],\n";

	val.x = (float)atof( strtok( str, sep ) );
	val.y = (float)atof( strtok( NULL, sep ) );
	val.z = (float)atof( strtok( NULL, sep ) );
	val.w = (float)atof( strtok( NULL, sep ) );

	return val;
}

