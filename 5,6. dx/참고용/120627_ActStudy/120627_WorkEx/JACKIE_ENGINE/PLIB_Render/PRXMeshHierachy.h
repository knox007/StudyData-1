#pragma once

#include "PRCommonTypeDef.h"

class CPRXMeshHierachy :
	public ID3DXAllocateHierarchy
{
public:
	CPRXMeshHierachy()	{ InitMembers(); }

	STDMETHOD( CreateFrame )(			const char* pszName, 
										LPD3DXFRAME	*pretNewFrame );

	STDMETHOD( CreateMeshContainer )(	const char *pszName, 
										const D3DXMESHDATA *pMeshData,
										const D3DXMATERIAL	*pMtrlEx, 
										const D3DXEFFECTINSTANCE *pEffectInstances,
										DWORD dwNumMaterials, 
										const DWORD *pdwAdjacency, 
										LPD3DXSKININFO pSkinInfo,
										PRDXMESHCONTAINER *ppResNewMeshContainer );

	STDMETHOD( DestroyFrame )(			LPD3DXFRAME pFrameToFree );

	STDMETHOD( DestroyMeshContainer )(	PRDXMESHCONTAINER pMeshContainerToFree );

	void	SetPath( char *pszPath );

	PRDXTXTRBUFF9*	GetTextures()			{ return m_ppTexturesEx; }
	PRDXTXTRBUFF9	GetTexture( int nIdx )	{ return m_ppTexturesEx[nIdx]; }
	D3DMATERIAL9*		GetMtrls()				{ return m_pMaterial; }
	D3DMATERIAL9		GetMtrl( int nIdx )		{ return m_pMaterial[nIdx]; }
	DWORD				GetMtrlSize()			{ return m_dwMtrlsSize; }

private:
	void	InitMembers();

	char				m_szPath[MAX_PATH];
	PRDXTXTRBUFF9	*m_ppTexturesEx;
	D3DMATERIAL9		*m_pMaterial;
	DWORD				m_dwMtrlsSize;

};
//	CPRXMeshHierachy