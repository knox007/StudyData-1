//============================================================
#pragma warning(disable : 4996)		//	c4996 ���� ����.
//============================================================
#pragma comment(lib, "d3d9.lib")	//	���̺귯�� �߰�.
									//	�Ӽ� - ��Ŀ - �Է� - �߰� ���Ӽ�
//============================================================
#include <windows.h>
#include <d3d9.h>
//============================================================
char				g_sCls[128];
HINSTANCE			g_hInst = NULL;	//	������ �ν��Ͻ�
HWND				g_hWnd = NULL;	//	������ �ڵ�
DWORD				g_dWinStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;	//	������ ��Ÿ��.
DWORD				g_dScnX = 800;			//	������	�ʺ�
DWORD				g_dScnY = 600;			//			����		
BOOL				g_bWindow = TRUE;		// ������ ���
BOOL				g_bShowCusor = TRUE;	// Ŀ�� ���� ����.
//============================================================
LPDIRECT3D9			g_pD3D = NULL;			// D3D ��ü
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;	// ����̽� ��ü, �Ϲ������� �׷��� ī��� ���� ����.
int					g_VtxProcessMode = D3DCREATE_HARDWARE_VERTEXPROCESSING;	//	���ؽ� ���μ��� ���.
//============================================================
//Window/DX ���� �Լ���
void RegistWinClass(const char* pszClassName);
HWND CreateWindows(HINSTANCE hInst);
HRESULT InitDX();
void SetVtxProcessMode();
INT Run();
void Cleanup();

//���� ���� ���� �Լ���
INT		Init();
void	Destroy();
INT		FrameMove();
INT		Render();

LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//============================================================
void RegistWinClass(const char* pszClassName)
{
	strcpy(g_sCls, pszClassName);

	WNDCLASS wc =
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, g_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(LTGRAY_BRUSH)
		, NULL
		, g_sCls
	};

	RegisterClass(&wc);

}//	void RegistWinClass()
//============================================================
void SetVtxProcessMode()
{
	D3DCAPS9 d3dCaps;

	//	�ϵ����(�׷��� ī��)�� �����ϴ� ��ġ Ư��.
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps);

	if( d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )	//	�ϵ���� ���ؽ� ���μ��� ���� ���� Ȯ��.
		g_VtxProcessMode = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		g_VtxProcessMode = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

}//	void SetVtxProcessMode()
//============================================================
HRESULT InitDX()
{
	//	D3D����
	//	-	Direct3D ��ü�� SDK ������ ���� ��� ���� ���θ� Ȯ�����ְ�
	//		����� �� �ִٸ� NULL�� �ƴ� ���� ��ȯ�Ѵ�.
	//	-	D3D_SDK_VERSION�� ������.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// ����̽��� �����ϱ� ���ؼ��� ������Ʈ �Ķ���� ����ü�� �ʿ�
	// ���� 0���� �����Ѵ��� �Ϻθ� ��������

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = g_bWindow;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//	�ĸ� ���ۿ� ���� ���۰� ��ȯ�� ��(Fliping Chain) ��� ����.
												//	D3DSWAPEFFECT_DISCARD�� ȿ����.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//	�ĸ� ������ �ȼ� ����.
	d3dpp.EnableAutoDepthStencil = TRUE;		//	����/ ���ٽ� ���۸� ����� ������.(d3d�� �ڵ����� �����ϰ� ������)
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//	����/ ���ٽ� ������ ����.

	//	���ؽ� ���μ��� ����.
	SetVtxProcessMode();

	// D3DADAPTER_DEFAULT: �⺻ �׷��� ī��.
	// D3DDEVTYPE_HAL : �ϵ���� ����(���� ū �ӵ�)�� ���� ���ΰ�.. �ϵ���� ��
	// ���� ���� ��� D3D�� ����Ʈ����� �̸� ��ü �� �� �ִ�.

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL
		, g_hWnd
		, g_VtxProcessMode
		, &d3dpp
		, &g_pd3dDevice)))
	{
		g_pD3D->Release();
		return E_FAIL;
	}

	return S_OK;

}//	HRESULT InitDX()
//============================================================
HWND CreateWindows(HINSTANCE hInst)
{
	g_hInst = hInst;

	//	������ Ŭ���� ���.
	RegistWinClass("Create Device");

	RECT rc;
	SetRect(&rc, 0, 0, g_dScnX, g_dScnY);
	AdjustWindowRect(&rc, g_dWinStyle, FALSE);	//	g_dWinStyle �Ӽ��� �´�
												//	�޴��� ����(FALSE) ��������
												//	���� Ŭ���̾�Ʈ ���� ����.

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

	return CreateWindow(g_sCls
		, g_sCls
		, g_dWinStyle
		, (iScnSysW - (rc.right - rc.left)) / 2
		, (iScnSysH - (rc.bottom - rc.top)) / 2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, GetDesktopWindow()
		, NULL
		, g_hInst
		, NULL);

}//	HWND CreateWindows(HINSTANCE hInst)
//============================================================
void Cleanup()
{
	Destroy();

	if (g_pd3dDevice)
	{
		g_pd3dDevice->Release();
		g_pd3dDevice = NULL;
	}

	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}//	void Cleanup()
//============================================================
LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//-----------------------
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					break;
				}
			}

			return 0;
		}
		//-----------------------
		case WM_DESTROY:
		{
			Cleanup();
			PostQuitMessage(0);
			return 0;
		}
		//-----------------------

	}//	switch (msg)

	return DefWindowProc(hWnd, msg, wParam, lParam);

}//	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//============================================================
INT Run()
{
	// Enter the message loop
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		//	GetMessage() �Լ��� �ش� ���α׷��� �ü������ ���� �޽����� ���� ������ ��ٸ���.
		//	�Է��� ���� ��쿡�� �ٸ� ó��( NPC�� AI, ��Ʈ�� �� ������ �Է°� ������ ���� )�� �ؾ��ϹǷ�
		//	�̴� �������� �ʴ�.
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (FAILED(FrameMove()))
				SendMessage(g_hWnd, WM_QUIT, 0, 0);

			if (FAILED(Render()))
				SendMessage(g_hWnd, WM_QUIT, 0, 0);
		}

	}//	while (msg.message != WM_QUIT)

	UnregisterClass(g_sCls, g_hInst);

	return 0;

}//	INT Run()
//============================================================
INT Init()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// ���� ������ ����

	//
	////////////////////////////////////////////////////////////////////////////

	return 0;
}
//============================================================
void Destroy()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// ���� ������ ����

	//
	////////////////////////////////////////////////////////////////////////////
}
//============================================================
INT FrameMove()
{
	return 0;
}
//============================================================
INT Render()
{
	if (NULL == g_pd3dDevice)
		return -1;

	/*
	1.	ȭ�� �ʱ�ȭ.
	2.	����̽��� BeginScene() �Լ��� ȣ���Ͽ� ����� �ĸ� ����(Back Face Buffer)�� �׸���.
	3.	����� �׸���.(������)
	4.	EndScene() �Լ��� ȣ���Ͽ� ����� �� �׷ȴٴ� ���� �˸���.
	5.	Present() �Լ��� ȣ���Ͽ� ���� ����(Front Face Buffer)�� �ĸ� ���۸� ��ü�Ѵ�.
	6.	1���� 5�� �ݺ�.
	*/
	
	// ���������δ� ����(�ĸ� ����: ����, ����, ���ٽ�)�� ����� ���� �ƴ϶� ä��� ���̴�.
	// D3DCLEAR_TARGET: ���� ���۸� �����.
	// D3DCLEAR_ZBUFFER: ���� ���۸� �����.
	// D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER ������ �Ϲ���.
	g_pd3dDevice->Clear(0
		, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(0, 120, 160)
		, 1.0f, 0);


	// BeginScene�� EndScene�� �������� �ɾ��־�� �ȴ�.
	if (FAILED(g_pd3dDevice->BeginScene()))
		return -1;

	////////////////////////////////////////////////////////////////////////////
	//

	// ������

	//
	////////////////////////////////////////////////////////////////////////////


	// EndScene
	g_pd3dDevice->EndScene();

	// �ĸ���� ������� ��ü( flipping)
	return g_pd3dDevice->Present(0, 0, 0, 0);

}//	INT Render()
//============================================================
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return MsgProc(hWnd, msg, wParam, lParam);
}
//============================================================
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	if (FAILED(g_hWnd = CreateWindows(hInst)))
		return FALSE;

	//*
	if (FAILED( InitDX() ))
		return FALSE;
	//*/

	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);
	ShowCursor(g_bShowCusor);

	if (FAILED(Init()))
		return -1;

	return Run();
}
//============================================================