//========================================================
#pragma once
//========================================================
#ifndef _DXCORE_H_
#define _DXCORE_H_
//========================================================
class CDxCore
{
protected:
	//-------------------------------
	//	win
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	DWORD		m_dwWinStyle;
	RECT		m_rcWin;			// 스크린 모드 전환을 위한 클라이언트 영역.
	DWORD		m_dwScrWidth;
	DWORD		m_dwScrHeight;
	BOOL		m_bShowCursor;
	BOOL		m_bWindowMode;
	TCHAR		m_tszClassName[256];
	BOOL		m_bDeviceLost;


	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
	void	CleanUp();
	HRESULT	Idle();
	//-------------------------------
	//	d3d
	LPDIRECT3D9				m_pD3D;
	D3DPRESENT_PARAMETERS	m_D3DPp;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	CDxSprite*				m_pDxSpriteManager;
	CDxFont*				m_pDxFont;
	//-------------------------------
	//	etc
	CInputManager*	m_pInputManager;
	//	fps	
	//	http://skmagic.tistory.com/298
	float	m_fFPS;
	TCHAR	m_tszFPS[256];

	//-------------------------------
public:
	//-------------------------------
	CDxCore();
	~CDxCore();
	//-------------------------------
	//	core
	BOOL	Create(HINSTANCE hInst);
	INT		Run();	
	//-------------------------------
	//	game
	virtual INT		Init()		{ return 0; }	
	virtual INT		Render()	{ return 0; }
	virtual INT		FrameMove() { return 0; }
	virtual void	Destroy()	{			}
	virtual void	Invalidate(){			}
	virtual HRESULT	Restore()	{ return S_OK; }
	//-------------------------------
	//	procedure
	virtual	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	//-------------------------------
	//	etc
	void UpdateFPS();
	INT Reset3D();
	


private:
	//-------------------------------
	void RegistWinClass();
	HRESULT CreateWindows();
	HRESULT CreateDX();
	HRESULT OnRender();
	//-------------------------------
	

};	//class CDxCore
//========================================================
#endif	//	_DXCORE_H_
