// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _MAIN_H_
#define _MAIN_H_


LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


// 정점에 Texture를 붙이기 위해서는 UV좌표가 필요하다.
struct VtxUV
{
	D3DXVECTOR3 p;																// 정점 위치
	FLOAT		u, v;															// 텍스처의 좌표(0,1 사이이다.)
	
	enum {	FVF = (D3DFVF_XYZ|D3DFVF_TEX1), };									//D3DFVF_TEX1의 1은 텍스처가 1장 붙여 있는 것을 의미.
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
	LPD3DXMESH              m_pMesh			;									// 메쉬: 정점의 집합이다.
	D3DMATERIAL9*           m_pMeshMtrl		;									// 메쉬에 적용되는 머티리얼
	LPDIRECT3DTEXTURE9*     m_pMeshTexture	;									// 머티리얼에 대응하는 텍스처
	DWORD                   m_dwNumMtrl		;									// 머티리얼의 숫자. 렌더링은 머티리얼 단위로 진행한다.
	
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
