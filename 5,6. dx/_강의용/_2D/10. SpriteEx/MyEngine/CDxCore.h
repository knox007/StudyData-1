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
	DWORD		m_dwScrWidth;
	DWORD		m_dwScrHeight;
	BOOL		m_bShowCursor;
	BOOL		m_bWindowMode;
	TCHAR		m_tszClassName[256];

	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
	void	CleanUp();
	HRESULT	Idle();
	//-------------------------------
	//	d3d
	LPDIRECT3D9				m_pD3D;
	D3DPRESENT_PARAMETERS	m_D3DPp;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	//-------------------------------
	CInputManager*	m_pInputManager;
	CDxSprite*		m_pDxSpriteManager;

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
	//-------------------------------
	//	procedure
	virtual	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	//-------------------------------


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
