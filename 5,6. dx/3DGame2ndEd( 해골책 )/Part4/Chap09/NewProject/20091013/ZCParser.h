#ifndef _ZCPARSER_H_
#define _ZCPARSER_H_

#include "zxml.h"
#include "define.h"
#include "zcmesh.h"
#include "zcparseddata.h"
#include "ZFLog.h"

/// 파서
class ZCParser
{
	ZXML*		m_pXML;	/// XML파일을 파싱하기 위한 기본 객체
public:
			ZCParser();
			~ZCParser();
private:
	Index3i				_StrToIndex3i( char str[] );	/// 문자열을 Index3i로 변형
	Color3f				_StrToColor3f( char str[] );	/// 문자열을 Color3f로 변형
	Vector2f			_StrToVector2f( char str[] );	/// 문자열을 Vector2f로 변형
	Vector3f			_StrToVector3f( char str[] );	/// 문자열을 Vector3f로 변형
	Vector4f			_StrToVector4f( char str[] );	/// 문자열을 Vector4f로 변형
	Vector3f			_MaxToD3D( Vector3f* pVec );	/// MAX vector데이터를 D3D vector로
	BOOL				_StrToBool( char str[] );		/// true, false변환
	int					_StrToInt( char str[] );
	float				_StrToFloat( char str[] );
	D3DXVECTOR3			_StrToPoint3( char str[] );		/// Point3를 D3D vector로
	D3DXVECTOR4			_StrToPoint4( char str[] );		/// Point4를 D3D vector로
	D3DXQUATERNION		_StrToQuat( char str[] );	/// MAX Quat를 D3D Quat로
	ZTKeyBase::KEYTYPE	_StrToKeytype( char str[] );
	void				_StrToFilename( char* dst, char str[] );

	int		_ReadValues( IXMLDOMNode* pNode, ZTKeyBase::KEYTYPE nCtrlType, ZCtrlBase* pCtrl, char strNode[] );


	int		_ParseInfo( ZCParsedData* pData );
	int		_ParseCamera( ZCParsedData* pData );

	int		_ParseMaterial( ZCParsedData* pData );
	int		_ParseMaterial_Map( IXMLDOMNode* pNode, ZTMaterial_Map* pMap );
	int		_ParseMaterial_Map_Coord( IXMLDOMNode* pNode, ZTMaterial_Map_Coord* pCoord );

	int		_ParseObject( ZCParsedData* pData );
	int		_ParseObjectParent( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectBBox( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectTM( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectVertex( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectVertexNormal( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectTVertex( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectTriIndex( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectTexIndex( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectVertWeight( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_ParseObjectKey( ZCMesh* pMesh, IXMLDOMNode* pNode );
	int		_SplitMeshByFaceMaterial( ZCParsedData* pData );
	void	_MergeBlendWeight( VertMerged& vm, VertWeight& vw );
	int		_MergeVertex( ZCParsedData* pData );

public:
	int		Parse_XML( ZCParsedData* pData, char* lpszFilename );
	int		Parse_Split( ZCParsedData* pData ) { return _SplitMeshByFaceMaterial( pData ); }
	int		Parse_Merge( ZCParsedData* pData ) { return _MergeVertex( pData ); }

	int		Parse( ZCParsedData* pData, char* lpszFilename );
};

#endif // _ZPARSER_H_