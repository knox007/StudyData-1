// Interface for the CD3DApp class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _D3DApp_H_
#define _D3DApp_H_

class CD3DApp
{
protected:
	TCHAR					m_sCls[128]		;
	HINSTANCE				m_hInst			;			// Hinstance
	HWND					m_hWnd			;			// The main app window
	HMENU					m_hMenu			;			// App menu bar (stored here when fullscreen)
	DWORD					m_dWinStyle		;			// Saved window style for mode switches
	DWORD					m_dScnW			;			// Screen Width
	DWORD					m_dScnH			;			// Screen Height

	BOOL					m_bWindow		;			// Window mode
	BOOL					m_bActive		;
	BOOL					m_bDeviceLost	;
	BOOL					m_bDestroyed	;
	
	RECT					m_rcWinBounds	;			// Saved window bounds for mode switches
	RECT					m_rcWinClient	;			// Saved client area size for mode switches
	
	D3DDISPLAYMODE			m_d3dMode		;			// Display Mode
	D3DPRESENT_PARAMETERS	m_d3dParam		;
	LPDIRECT3D9             m_pD3D			;			// D3D
	LPDIRECT3DDEVICE9       m_pd3dDevice	;			// Device
	LPD3DXSPRITE			m_pd3dSprite	;			// 2D Sprite

	FLOAT					m_fFps			;	

public:
	CD3DApp();
	
	HRESULT			Create( HINSTANCE);
	HRESULT			Run();
	HRESULT			Cleanup();
	HRESULT			Render3D();
	HRESULT			Reset3D();
	static	LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM);

protected:
	virtual HRESULT Init()			{ return 0; }
	virtual HRESULT Destroy()		{ return 0; }

	virtual HRESULT FrameMove()		{ return 0; }
	virtual HRESULT Render()		{ return 0; }

	virtual HRESULT	Restore()		{ return 0; }
	virtual HRESULT	Invalidate()	{ return 0; }
	
	virtual LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM);

protected:
	void			UpdateFrame();

public:
	HINSTANCE			GetHinst()	{	return m_hInst;			}
	HWND				GetHwnd()	{	return m_hWnd;			}
	LPDIRECT3DDEVICE9	GetDevice()	{	return m_pd3dDevice;	}
};


#endif

