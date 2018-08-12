// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _MAIN_H_
#define _MAIN_H_


LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


// 정점에 텍스처를 매핑하기 위해 UV좌표를 구성
struct VtxUV
{
	D3DXVECTOR3	p;																// 정점 위치
	FLOAT		u, v;															// 텍스처 좌표(매핑 좌표)

	enum {	FVF = (D3DFVF_XYZ|D3DFVF_TEX1), };									// TEX1의 1은 텍스처 좌표 1개 의미.
};



class CMain
{
public:
	TCHAR					m_sCls[128]		;
	HINSTANCE				m_hInst			;
	HWND					m_hWnd			;
	DWORD					m_dWinStyle		;
	DWORD					m_dScnX			;									// Screen Width
	DWORD					m_dScnY			;									// Screen Height


public:
	LPDIRECT3D9             m_pD3D			;									// D3D
	LPDIRECT3DDEVICE9       m_pd3dDevice	;									// Device

public:
	LPDIRECT3DVERTEXBUFFER9 m_pVB			;									// 정점 버버
	LPDIRECT3DTEXTURE9		m_pTx			;									// 텍스처 데이터에 대한 주소

public:
	INT		Init();
	void	Destroy();
	void	Render();

	INT		FrameMove();

	CMain();
	virtual ~CMain();

	INT		Create( HINSTANCE hInst);
	INT		Run();
	void	Cleanup();
	
	LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
};

extern CMain*	g_pApp;

#endif
