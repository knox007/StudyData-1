// Interface for the CD3DApp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _D3DApp_H_
#define _D3DApp_H_

class CD3DApp
{
public:
	TCHAR					m_sCls[128]	;
	HINSTANCE				m_hInst		;
	HWND					m_hWnd		;
	DWORD					m_dWinStyle	;
	DWORD					m_dScnX		;			// Screen Width
	DWORD					m_dScnY		;			// Screen Height
	BOOL					m_bShowCusor;			// Show Cusor
	BOOL					m_bWindow	;			// Window mode

	D3DPRESENT_PARAMETERS	m_d3dpp		;
	LPDIRECT3D9				m_pD3D		;			// D3D
	LPDIRECT3DDEVICE9		m_pd3dDevice;			// Device

public:
	CD3DApp();

	//Window
	INT		Create(HINSTANCE hInst);
	INT		Run();
	void	Cleanup();
	INT		Render3D();

	virtual INT		Init()				{		return 0;	}
	virtual void	Destroy()			{					}
	virtual INT		Render()			{		return 0;	}
	virtual INT		FrameMove()			{		return 0;	}

	virtual	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

protected:
};

#endif