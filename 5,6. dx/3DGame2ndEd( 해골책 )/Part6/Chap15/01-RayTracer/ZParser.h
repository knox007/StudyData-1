#ifndef _ZPARSER_H_
#define _ZPARSER_H_

#include "ZXml.h"
#include "ZPreDefines.h"
#include "ZNode.h"
#include "ZParsedData.h"

/// XML데이터 파서
class ZParser
{
	ZXML*		m_pXML;	/// XML파일을 파싱하기 위한 기본 객체
public:
			ZParser();
			~ZParser();
private:
	Index3i		_StrToIndex3i( char str[] );	/// 문자열을 Index3i로 변형
	Color3f		_StrToColor3f( char str[] );	/// 문자열을 Color3f로 변형
	Color4f		_StrToColor4f( char str[] );	/// 문자열을 Color4f로 변형
	Vector2f	_StrToVector2f( char str[] );	/// 문자열을 Vector2f로 변형
	Vector3f	_StrToVector3f( char str[] );	/// 문자열을 Vector3f로 변형
	Vector4f	_StrToVector4f( char str[] );	/// 문자열을 Vector4f로 변형

	int		_ParseInfo( ZParsedData* pData );
	int		_ParseMaterial( ZParsedData* pData );
	int		_ParseNode( ZParsedData* pData );
	int		_ParseNodeBBox( ZGeometry* pMesh, IXMLDOMNode* pNode );
	int		_ParseNodeTM( ZNode* pMesh, IXMLDOMNode* pNode );
	int		_ParseSphere( ZSphere* pMesh, IXMLDOMNode* pNode );
	int		_ParseCylinder( ZCylinder* pMesh, IXMLDOMNode* pNode );
	int		_ParseMeshVertex( ZMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseMeshVertexNormal( ZMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseMeshTVertex( ZMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseMeshTriIndex( ZMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseMeshTexIndex( ZMesh* pMesh, IXMLDOMNode* pNode );
	void	_PostProcess( ZParsedData* pData );
public:
	int		Parse_XML( ZParsedData* pData, char* lpszFilename );

	int		Parse( ZParsedData* pData, char* lpszFilename )
	{
		if( !Parse_XML( pData, lpszFilename ) ) return 0;
		return 1;
	}
};

#endif // _ZPARSER_H_