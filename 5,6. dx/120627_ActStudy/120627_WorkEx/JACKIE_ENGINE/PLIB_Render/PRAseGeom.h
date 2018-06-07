#pragma once
#ifndef _PRASEGEOM_H_
#define _PRASEGEOM_H_
#include <tchar.h>
#include <WinDef.h>

#include "PUtCommon.h"
#include "PRCommonVtxInfo.h"
#include "PRCommonTypeDef.h"

//----------------------------------------------------------------------------------------
struct SPRAseMtrl
{
	TCHAR			_tszTxtrName[MAX_PATH];
	PRDXIMGINFO		_ImgInfo;
	PRDXTXTRBUFF9	_pD3dTxtr;

	SPRAseMtrl()
	{
		PUT_ZERO_MEMORY( _tszTxtrName );
		PUT_ZERO_MEMORY( _ImgInfo );
		_pD3dTxtr	=	NULL;
	}

	~SPRAseMtrl()
	{
		PUT_SAFE_RELEASE( _pD3dTxtr );
	}

};//SPRAseMtrl
//----------------------------------------------------------------------------------------
class CPRAseGeom
{
public:
	CPRAseGeom()	{ InitMembers(); }
	~CPRAseGeom()	{ ClearMembers(); }	
	void	InitMembers();
	void	ClearMembers();
	bool	CreateVtx( LPDIRECT3DDEVICE9 pDev );
	bool	CreateVtxDiff( LPDIRECT3DDEVICE9 pDev );
	bool	CreateVtxNorm( LPDIRECT3DDEVICE9 pDev );
	bool	CreateVtxNormDiff( LPDIRECT3DDEVICE9 pDev );
	bool	CreateVtxNormTex1( LPDIRECT3DDEVICE9 pDev );
	bool	CreateVtxNormDiffTex1( LPDIRECT3DDEVICE9 pDev );
	bool	CreateIdx( LPDIRECT3DDEVICE9 pDev );
	

	TCHAR*	GetNodeName()		{ return m_tszNodeName; }
	
	int		GetTotVtxCnt()	{ return m_nTotVtx; }
	void	SetTotVtxCnt( int nVal )	{ m_nTotVtx = nVal; }
	
	int		GetTotIdxCnt()	{ return m_nTotIdx; }
	void	SetTotIdxCnt( int nVal )	{ m_nTotIdx = nVal; }
	
	int		GetTotTVtxCnt()	{ return m_nTotTVtx; }
	void	SetTotTVtxCnt( int nVal )	{ m_nTotTVtx = nVal; }

	int		GetTotTIdxCnt()	{ return m_nTotTIDx; }
	void	SetTotTidxCnt( int nVal )	{ m_nTotTIDx = nVal; }

	int		GetMtrlRef()	{ return m_nMtrlRef; }
	void	SetMtrlRef( int nVal )		{ m_nMtrlRef = nVal; }

	DWORD	GetFVF()	{ return m_dwFVF; }
	void	SetFVF( DWORD dwFVF )	{ m_dwFVF = dwFVF; }
	void	AddFVF( DWORD dwFVF )	
	{
		DWORD dwCurFVF = GetFVF();
		dwCurFVF |= dwFVF;
		SetFVF( dwCurFVF );
	}

	sPRVtx_Xyz		GetVtx( int nCur )			{ return m_pVtxXyzArr[nCur]; }
	sPRVtx_Xyz		GetVtxNorm( int nCur )		{ return m_pVtxNormArr[nCur]; }
	sPRTVtx			GetTVtx( int nCur )			{ return m_pTVtxArr[nCur]; }
	
	sPRINDEX16		GetIdx3D( int nCur )			{ return m_pIDxArr[nCur]; }

	bool			OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );

	sPRVtx_Xyz*	m_pVtxXyzArr;
	sPRVtx_Xyz*	m_pVtxNormArr;
	sPRTVtx*	m_pTVtxArr;

	
	sPRINDEX16_2D*	m_pIDxArr2D;
	sPRINDEX16*		m_pIDxArr;
	
	
	sPRINDEX16*		m_pTIDxArr;


private:

	TCHAR	m_tszNodeName[64];

	int	m_nMtrlRef;
	int	m_nTotVtx;
	int	m_nTotIdx;
	int	m_nTotTVtx;
	int	m_nTotTIDx;	

	int m_nActTotVtx;
	int	m_nActTotIdx;

	int	m_nTotCurVtx;
	int	m_nTotCurIdx;	

	sPRINDEX16_2D*	m_pCurIdx2D;
	sPRINDEX16*		m_pCurIdx;
	void*			m_pCurVtxArr;

	DWORD	m_dwFVF;
	size_t	m_unVtxStructSize;

	

	PRDXVTXBUFF9	m_pBuffVtx;
	PRDXIDXBUFF9	m_pBuffIdx;
};
//	class CPRAseGeom
//----------------------------------------------------------------------------------------


#endif//_PRASEGEOM_H_