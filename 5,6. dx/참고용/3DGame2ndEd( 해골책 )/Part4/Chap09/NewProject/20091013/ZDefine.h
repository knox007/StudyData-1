#ifndef _ZDEFINE_H_
#define _ZDEFINE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include "define.h"
//#include "ZSceneMgr.h"

struct ZTObjectInfo
{
	int				nObjectCount;
	int				nMeshCount;
	float			fAnimationStart;
	float			fAnimationEnd;
	int				nKeyType;
	int				nSkinType;
	std::vector<std::string>	strObjectNameTable;
	std::vector<int>		BoneTable;
	std::vector<int>		MeshTable;
	~ZTObjectInfo()
	{
		stl_wipe_vector( strObjectNameTable );
		stl_wipe_vector( BoneTable );
	}
};
/*
struct ZMaterial
{
	D3DMATERIAL9			material;	/// 재질
	float					opacity;	/// 투명도
	LPDIRECT3DTEXTURE9		pTex[4];	/// 0 = diffuse, 1 = normal, 3 = specular, etc...
	ZMaterial()
	{
		for( int i = 0 ; i < 4 ; i++ ) pTex[i] = NULL;
	}
	~ZMaterial()
	{
		for( int i = 0 ; i < 4 ; i++ ) S_REL( pTex[i] );
	}
};
*/
struct ZTKeyBase
{
	enum KEYTYPE { KEYTYPE_BASE, KEYTYPE_STRING, KEYTYPE_FILENAME, KEYTYPE_BOOL, KEYTYPE_INT, KEYTYPE_FLOAT, KEYTYPE_POINT3, KEYTYPE_POINT4, KEYTYPE_QUATERNION, KEYTYPE_COLOR3 };

	int				type;
	float			frame;
};

struct ZTKeyString : public ZTKeyBase
{
	std::string			value;
};

struct ZTKeyBool : public ZTKeyBase
{
	BOOL			value;
};

struct ZTKeyInt : public ZTKeyBase
{
	int				value;
};

struct ZTKeyFloat : public ZTKeyBase
{
	float			value;
};

struct ZTKeyPoint3 : public ZTKeyBase
{
	D3DXVECTOR3		value;
};

struct ZTKeyPoint4 : public ZTKeyBase
{
	D3DXVECTOR4		value;
};

struct ZTKeyQuat : public ZTKeyBase
{
	D3DXQUATERNION	value;
};

struct ZTKeyPos : public ZTKeyPoint3
{
//	D3DXVECTOR3		value;
};

struct ZTKeyRot : public ZTKeyQuat
{
//	D3DXQUATERNION	value;
};

struct ZTKeyScl : public ZTKeyPoint3
{
//	D3DXVECTOR3		value;
};

struct ZTKeyBone
{	
	ZTKeyPos				pos;
	ZTKeyRot				rot;
	ZTKeyScl				scl;
};

// for old interface
struct ZTKeys
{	
	std::vector<ZTKeyPos>		pos;
	std::vector<ZTKeyRot>		rot;
	std::vector<ZTKeyScl>		scl;
	~ZTKeys() { stl_wipe_vector( pos ); stl_wipe_vector( rot); stl_wipe_vector( scl ); }
};

struct ZTRigidVertex
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
};

struct ZTSkinnedVertex
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX1) };
	D3DXVECTOR3	p;
	float		b[3];
	DWORD		i;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
};

struct ZTSWSkinnedVertex
{
	D3DXVECTOR3	p;
	float		b[4];
	DWORD		i[4];
};

struct ZTBOXVERTEX
{
	enum { FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE };

	float x, y, z;	/// 정점의 변환된 좌표
	DWORD color;	/// 정점의 색깔
	ZTBOXVERTEX() { x = 0; y = 0; z = 0; color = 0; }
	ZTBOXVERTEX( float f1, float f2, float f3, DWORD c ) { x = f1; y = f2; z = f3; color = c; }
};

#endif // _ZDEFINE_H_