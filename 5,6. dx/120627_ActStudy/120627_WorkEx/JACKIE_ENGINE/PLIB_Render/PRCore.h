#ifndef _JRCORE_H_
#define _JRCORE_H_
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "PRCommonFunc.h"

class CPRLight;


class CPRCore
{
public:
	CPRCore()				{ InitMembers(); }	
	virtual ~CPRCore()		{ ClearMembers(); }
	void	InitMembers();
	void	ClearMembers();

	bool				Init( HWND hWnd, bool bWindowMode );

	BOOL				Reset();
	LPDIRECT3D9			GetD3D()			{ return m_pD3D; }
	PRLPD3DDEV9			GetDevice()			{ return m_pDevice; }
	D3DDISPLAYMODE*		GetDisplayMode()	{ return &m_DisplayMode; }
	CPRLight*			GetLight()			{ return m_pLight; }

	//	Device Func.
	HRESULT		Clear()
				{	return devClr( m_pDevice, m_dwClearRectCnt, m_pClearRectsArr, m_dwClearFlag, m_dColorBackScreen, m_fZ, m_dwStencil ); }
	HRESULT		SetFillMode( DWORD dwState )	
				{	return devSetRSFillMode( m_pDevice, dwState ); }
	DWORD		devGetFillMode();


	HRESULT		BeginScene()	{ return devBeginScene(m_pDevice); }
	HRESULT		EndScene()		{ return devEndScene(m_pDevice); }
	HRESULT		Present( RECT* pSourceRect = NULL, RECT* pDestRect = NULL, HWND hDestWindowOverride = NULL, RGNDATA* pDirtyRegion = NULL )
				{	return m_pDevice->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion ); }

	HRESULT		SetTransformWorld( D3DMATRIX* pMat );
	HRESULT		SetTransformView( D3DMATRIX* pMat );
	HRESULT		SetTransformProjection( D3DMATRIX* pMat );
	
	
	void		SaveScreenShot( char *pszFileName );
					

	bool		m_bWindowMode;

private:
	bool					BuildPresentParam();
	HWND					m_hWnd;
	LPDIRECT3D9				m_pD3D;
	PRLPD3DDEV9				m_pDevice;
	D3DCAPS9				m_Caps;
	D3DPRESENT_PARAMETERS	m_Param;
	D3DDISPLAYMODE			m_DisplayMode;

	//	Device::Clear 설정 인자값.
	D3DCOLOR				m_dColorBackScreen;
	DWORD					m_dwClearRectCnt;
	D3DRECT*				m_pClearRectsArr;
	DWORD					m_dwClearFlag;
	float					m_fZ;
	DWORD					m_dwStencil;

	CPRLight*				m_pLight;
};

#endif	//	_JRCORE_H_