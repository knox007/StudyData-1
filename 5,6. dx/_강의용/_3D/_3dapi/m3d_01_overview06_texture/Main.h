// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _MAIN_H_
#define _MAIN_H_


LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


// ������ �ؽ�ó�� �����ϱ� ���� UV��ǥ�� ����
struct VtxUV
{
	D3DXVECTOR3	p;																// ���� ��ġ
	FLOAT		u, v;															// �ؽ�ó ��ǥ(���� ��ǥ)

	enum {	FVF = (D3DFVF_XYZ|D3DFVF_TEX1), };									// TEX1�� 1�� �ؽ�ó ��ǥ 1�� �ǹ�.
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
	LPDIRECT3DVERTEXBUFFER9 m_pVB			;									// ���� ����
	LPDIRECT3DTEXTURE9		m_pTx			;									// �ؽ�ó �����Ϳ� ���� �ּ�

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
