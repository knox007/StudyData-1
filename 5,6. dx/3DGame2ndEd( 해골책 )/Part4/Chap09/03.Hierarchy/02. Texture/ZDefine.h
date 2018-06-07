#ifndef _ZDEFINE_H_
#define _ZDEFINE_H_

#include <d3d9.h>
#include <d3dx9.h>

struct ZObjectInfo
{
	int				nObjectCount;
	int				nMeshCount;
	float			fAnimationStart;
	float			fAnimationEnd;
	int				nKeyType;
	int				nSkinType;
	vector<string>	strObjectNameTable;
	vector<int>		BoneTable;
	~ZObjectInfo()
	{
		stl_wipe_vector( strObjectNameTable );
		stl_wipe_vector( BoneTable );
	}
};

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

struct ZRigidVertex
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
};

struct ZSkinnedVertex
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX1) };
	D3DXVECTOR3	p;
	float		b[3];
	DWORD		i;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
};

#endif // _ZDEFINE_H_