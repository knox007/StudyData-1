#ifndef _JFRFRAMEWORK_H_
#define _JFRFRAMEWORK_H_
#pragma once
 
#include<d3d9.h>
#include<tchar.h>
#include "PreDef_FR.h"


class IGameInterfaceBase;
class CPRCore;
class CPUTTimer;
class CPUTTimerEx;
class CPRFont;
class CPRInput;
class CPRCamera;


#ifdef _FR_TIMEREX_
	class CPUtTimerEx;
#endif

#ifdef _FR_FRAMESKIPPER_
	class CPUtFrameSkip;
#endif

class CPFrFrameWork
{
public:
	CPFrFrameWork()				{ InitMembers(); }
	virtual ~CPFrFrameWork()	{ ClearMembers(); }
	void	InitMembers();
	void	ClearMembers();

	void	Register( HINSTANCE hInstance, TCHAR* ptszClassName );
	HWND	Create( TCHAR* ptszTitle, HINSTANCE hInst, bool bWindowed );
	void	SetSize( int nWid, int nHei, int nPosX = 0, int nPosY = 0 );

	
	void	Run( TCHAR* tszTitle, HINSTANCE hInstance, int nWid, int nHei, bool bWindowed = true, int nPosX = 0, int nPosY = 0 );
	void	ToggleFullScreen();
	HRESULT	ToggleWireFrame();
//	static	LRESULT CALLBACK StaticWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT	CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int		GetWidth();
	int		GetHeight();
	void	LinkApp( IGameInterfaceBase* pApp );

	CPRCore*	GetRenderer()	{ return m_pRender; }
	CPRCamera*	GetCamera()	{ return m_pCamera; }

#ifndef _FR_TIMEREX_
	CPUTTimer*	GetTimer()		{ return m_pTimer; }
#else
	CPUtTimerEx*	GetTimer()		{ return m_pTimerEx; }
#endif

	CPRFont*	GetFont()		{ return m_pFont; }
	CPRInput*	GetInput()		{ return m_pInput; }
	HWND		GetHwnd()		{ return m_hWnd; }
	

	IGameInterfaceBase*	GetInterface()	{ return m_pGameInterface; }
	

private:
	bool	Init( TCHAR* tszTitle, HINSTANCE hInstance, int nWid, int nHei, bool bWindowed = true, int nPosX = 0, int nPosY = 0 );	
	HRESULT	OnCreateDevice();
	HRESULT	OnResetDevice();
	HRESULT	OnLostDevice();
	HRESULT	OnDestroyDevice();
	void	OnUpdate( float fElapsedTime = 0 );
	void	UpdateCamera( float fElapsedTime );
	void	UpdateLight( float fElapsedTime );
	void	ResetCamera();
	HRESULT	OnRender( IDirect3DDevice9* pDevice, float fElapsed );
	void	Pause( BOOL bRender, BOOL bTimer );
	

	HWND				m_hWnd;
	HINSTANCE			m_hInst;
	bool				m_bActive;
	int					m_nWindowWidth;
	int					m_nWindowHeight;
	int					m_nFullScrWidth;
	int					m_nFullScrHeight;
	WINDOWPLACEMENT		m_WindowPlacement;
	DWORD				m_dwFillMode;
	bool				m_bRenderPaused;
	bool				m_bTimerPaused;
	int					m_nRenderingPauseCount;
	int					m_nTimerPauseCount;
	bool				m_bClosing;	

	IGameInterfaceBase*		m_pGameInterface;
	CPRCore*		m_pRender;
	CPUTTimer*		m_pTimer;
	CPRFont*		m_pFont;
	CPRCamera*		m_pCamera;
	CPRInput*		m_pInput;

	

#ifdef _FR_TIMEREX_
	CPUtTimerEx*	m_pTimerEx;
#endif

#ifdef	_FR_FRAMESKIPPER_
	CPUtFrameSkip*	m_pFrameSkipper;
#endif


};


#endif	//	_JFRFRAMEWORK_H_