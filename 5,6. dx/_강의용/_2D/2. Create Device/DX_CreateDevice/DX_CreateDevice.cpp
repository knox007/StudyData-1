//============================================================
#pragma warning(disable : 4996)		//	c4996 에러 무시.
//============================================================
#pragma comment(lib, "d3d9.lib")	//	라이브러리 추가.
									//	속성 - 링커 - 입력 - 추가 종속성
//============================================================
#include <windows.h>
#include <d3d9.h>
//============================================================
char				g_sCls[128];
HINSTANCE			g_hInst = NULL;	//	윈도우 인스턴스
HWND				g_hWnd = NULL;	//	윈도우 핸들
DWORD				g_dWinStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;	//	윈도우 스타일.
DWORD				g_dScnX = 800;			//	윈도우	너비
DWORD				g_dScnY = 600;			//			높이		
BOOL				g_bWindow = TRUE;		// 윈도우 모드
BOOL				g_bShowCusor = TRUE;	// 커서 노출 상태.
//============================================================
LPDIRECT3D9			g_pD3D = NULL;			// D3D 객체
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;	// 디바이스 객체, 일반적으로 그래픽 카드와 같은 개념.
int					g_VtxProcessMode = D3DCREATE_HARDWARE_VERTEXPROCESSING;	//	버텍스 프로세싱 방법.
//============================================================
//Window/DX 관련 함수들
void RegistWinClass(const char* pszClassName);
HWND CreateWindows(HINSTANCE hInst);
HRESULT InitDX();
void SetVtxProcessMode();
INT Run();
void Cleanup();

//게임 실행 관련 함수들
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

	//	하드웨어(그래픽 카드)가 제공하는 장치 특성.
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps);

	if( d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )	//	하드웨어 버텍스 프로세싱 지원 여부 확인.
		g_VtxProcessMode = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		g_VtxProcessMode = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

}//	void SetVtxProcessMode()
//============================================================
HRESULT InitDX()
{
	//	D3D생성
	//	-	Direct3D 객체는 SDK 버전에 따른 사용 가능 여부를 확인해주고
	//		사용할 수 있다면 NULL이 아닌 값을 반환한다.
	//	-	D3D_SDK_VERSION는 고정값.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = g_bWindow;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//	후면 버퍼와 전면 버퍼가 교환될 때(Fliping Chain) 방법 설정.
												//	D3DSWAPEFFECT_DISCARD가 효과적.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//	후면 버퍼의 픽셀 포멧.
	d3dpp.EnableAutoDepthStencil = TRUE;		//	깊이/ 스텐실 버퍼를 사용할 것인지.(d3d가 자동으로 생성하고 관리함)
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//	깊이/ 스텐실 버퍼의 포멧.

	//	버텍스 프로세싱 설정.
	SetVtxProcessMode();

	// D3DADAPTER_DEFAULT: 기본 그래픽 카드.
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.

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

	//	윈도우 클래스 등록.
	RegistWinClass("Create Device");

	RECT rc;
	SetRect(&rc, 0, 0, g_dScnX, g_dScnY);
	AdjustWindowRect(&rc, g_dWinStyle, FALSE);	//	g_dWinStyle 속성에 맞는
												//	메뉴가 없는(FALSE) 윈도우의
												//	순수 클라이언트 영역 설정.

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
		//	GetMessage() 함수는 해당 프로그램이 운영체제에서 보낸 메시지를 받을 때까지 기다린다.
		//	입력이 없는 경우에도 다른 처리( NPC의 AI, 네트웍 등 유저의 입력과 무관한 동작 )를 해야하므로
		//	이는 적합하지 않다.
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

	// 게임 데이터 생성

	//
	////////////////////////////////////////////////////////////////////////////

	return 0;
}
//============================================================
void Destroy()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 해제

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
	1.	화면 초기화.
	2.	디바이스의 BeginScene() 함수를 호출하여 장면을 후면 버퍼(Back Face Buffer)에 그린다.
	3.	장면을 그린다.(렌더링)
	4.	EndScene() 함수를 호출하여 장면을 다 그렸다는 것을 알린다.
	5.	Present() 함수를 호출하여 전면 버퍼(Front Face Buffer)와 후면 버퍼를 교체한다.
	6.	1부터 5를 반복.
	*/
	
	// 실질적으로는 버퍼(후면 버퍼: 색상, 깊이, 스텐실)를 지우는 것이 아니라 채우는 것이다.
	// D3DCLEAR_TARGET: 색상 버퍼를 지운다.
	// D3DCLEAR_ZBUFFER: 깊이 버퍼를 지운다.
	// D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER 설정이 일반적.
	g_pd3dDevice->Clear(0
		, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(0, 120, 160)
		, 1.0f, 0);


	// BeginScene과 EndScene에 렌더링을 걸어주어야 된다.
	if (FAILED(g_pd3dDevice->BeginScene()))
		return -1;

	////////////////////////////////////////////////////////////////////////////
	//

	// 렌더링

	//
	////////////////////////////////////////////////////////////////////////////


	// EndScene
	g_pd3dDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
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