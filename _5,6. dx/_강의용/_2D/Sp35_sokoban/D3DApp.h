// Interface for the CD3DApplication class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _D3DAPP_H_
#define _D3DAPP_H_

class CD3DApplication
{
protected:
	HINSTANCE	m_hInst		;													// Window Instance
	CHAR		m_sCls[128]	;													// Window Class Name
	CHAR		m_sWin[128]	;													// Window Title
	HWND		m_hWnd		;													// Main Window Handle
	DWORD		m_dWinStyle	;													// Window Style
	DWORD		m_dScnX		;													// Screen Width
	DWORD		m_dScnY		;													// Screen Height
	BOOL		m_bShowCusor;													// Show Cusor

protected:
	LPDIRECT3D9				m_pD3D		;			// 1. Direct3D
	LPDIRECT3DDEVICE9		m_pd3dDevice;			// 2. Direct3D Device
	D3DPRESENT_PARAMETERS	m_d3dpp		;			// 3. D3D Present Parameters
	LPD3DXSPRITE			m_pd3dSprite;			// 4. 2D Sprite
	BOOL					m_bWindow	;			// 5. Window Mode?

public:
	CD3DApplication();
	virtual ~CD3DApplication();

	//Window+Device���� �Լ���
	INT		Create(HINSTANCE hInst);											// Window ����
	INT		Run();																// Winodw Main Loop �Լ�
	void	Cleanup();															// ������ ���� �Լ�
	virtual	LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM);						// ������ �޽��� ó���Լ�
	static	LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);					// Window Message Procedure function

public:
	virtual	HRESULT	Init();														// Game Data ����
	virtual	HRESULT	Destroy();													// Game Data �Ҹ�
	virtual	HRESULT	FrameMove();												// Game Data ����
	virtual	HRESULT	Render();													// Game Data �׸���

public:																			// Application
	HINSTANCE			GetInstance(){	return	m_hInst		;	}
	HWND				GetHwnd()	{	return m_hWnd		;	}
	DWORD				GetScnW()	{	return m_dScnX		;	}
	DWORD				GetScnH()	{	return m_dScnY		;	}
	
	LPDIRECT3DDEVICE9	GetDevice()	{	return m_pd3dDevice	;	}
	LPD3DXSPRITE		GetSprite()	{	return m_pd3dSprite	;	}
};


#endif