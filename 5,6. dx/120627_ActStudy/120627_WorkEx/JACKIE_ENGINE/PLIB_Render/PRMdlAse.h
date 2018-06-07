#pragma once
#include "probject.h"
#include "PUtCommon.h"
#include "PRCommonVtxInfo.h"
#include "PRCommonTypeDef.h"
#include "PRAseGeom.h"

class CPRMdlAse :	public CPRObject
{
public:
	CPRMdlAse(void)				{ InitMembers(); }
	virtual ~CPRMdlAse(void)	{ ClearMembers(); }	
	void	InitMembers();
	void	ClearMembers();

	virtual	bool	OnCreate( void* pDev, void* ptszFName, void* ptszMdlTxtrPath );
	virtual	bool	OnUpdate( float fElapsedTime = 0.0f );
	virtual	HRESULT OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	virtual	void	OnLost()	{};
	virtual	void	OnReset( LPDIRECT3DDEVICE9 pDev )	{};
    
protected:
	bool	Confirm( TCHAR* ptszConfirmFName );
	bool	Load();
	
	bool	CreateVtx( LPDIRECT3DDEVICE9 pDev );	 
	bool	CreateTVtx( LPDIRECT3DDEVICE9 pDev );
	bool	CreateIdx( LPDIRECT3DDEVICE9 pDev );
	bool	CreateTexture( LPDIRECT3DDEVICE9 pDev, TCHAR* ptszTxtrPath );
	

	TCHAR	m_tszFile[MAX_PATH];
	TCHAR	m_tszConfirmFile[MAX_PATH];

	int			m_nTotGeom;
	CPRAseGeom*	m_pGeomArr;

	int			m_nTotMtrl;
	SPRAseMtrl*	m_pMtrlArr;

	LPDIRECT3DDEVICE9	m_pDev;
	
};
//	CPRMdlAse
