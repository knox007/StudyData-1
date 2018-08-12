//========================================================
#include "Global.h"
//========================================================
CDxCore*	g_pDxCore;
//========================================================
//-------------------------------
CDxCore::CDxCore()
{
	g_pDxCore = this;

	strcpy(m_tszClassName, "2D Game App");

	m_hInst = NULL;
	m_hWnd = NULL;
	m_dwWinStyle	= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	m_dwScrWidth	= 800;
	m_dwScrHeight	= 600;

	m_bShowCursor	= TRUE;
	m_bWindowMode	= TRUE;			// Window mode

	m_pD3D			= NULL;			// D3D
	m_pD3DDevice	= NULL;			// Device

	m_pInputManager = NULL;			//	입력 매니져.

	m_pDxCamera = NULL;

	m_fFPS = 60;
	ZeroMemory(m_tszFPS, sizeof(m_tszFPS));

	m_bDeviceLost = FALSE;

}//	CDxCore::CDxCore()
//-------------------------------
CDxCore::~CDxCore() { CleanUp(); }
//-------------------------------
void CDxCore::RegistWinClass()
{
	// Register the window class
	WNDCLASS wc =
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(WHITE_BRUSH)
		, NULL
		, m_tszClassName
	};

	RegisterClass(&wc);

}//	void CDxCore::RegistWinClass()
//-------------------------------
HRESULT CDxCore::CreateWindows()
{
	//	regist win class
	RegistWinClass();

	//Create the application's window
	RECT rc;
	SetRect(&rc, 0, 0, m_dwScrWidth, m_dwScrHeight);
	AdjustWindowRect(&rc, m_dwWinStyle, FALSE);

	int iScnSysW = GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow(m_tszClassName
		, m_tszClassName
		, m_dwWinStyle
		, (iScnSysW - (rc.right - rc.left)) / 2
		, (iScnSysH - (rc.bottom - rc.top)) / 2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, NULL
		, NULL
		, m_hInst
		, NULL);

	if (m_hWnd == NULL)
		return E_FAIL;

	GetWindowRect(m_hWnd, &m_rcWin);

	return S_OK;

}//	HRESULT CDxCore::CreateWindows()
//-------------------------------
HRESULT CDxCore::CreateDX()
{
	// D3D생성
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅
	ZeroMemory(&m_D3DPp, sizeof(m_D3DPp));
	m_D3DPp.Windowed = m_bWindowMode;
	m_D3DPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPp.BackBufferFormat = d3ddm.Format;
	m_D3DPp.BackBufferCount = 2;
	m_D3DPp.BackBufferWidth = m_dwScrWidth;
	m_D3DPp.BackBufferHeight = m_dwScrHeight;
	m_D3DPp.EnableAutoDepthStencil = TRUE;
	//	http://telnet.or.kr/directx/graphics/reference/d3d/constants/d3dpresent.htm
	//	런타임은 윈도우 클라이언트 영역을 즉시 갱신한다.
	//	어댑터 리프레쉬 간격중에 2 회 이상 이 갱신을 실시하는 일이 있다.
	//	이것은, DirectX 8.0 의 D3DSWAPEFFECT_COPY 를 사용하는 것에 동일하다. 
	//	IDirect3DDevice9::Present 에 직접 영향을 주는 경우가 있다. 이 옵션은, 윈도우 스왑 체인 및 풀 스크린 스왑 체인의 양쪽 모두로 항상 사용할 수 있다.
	m_D3DPp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_D3DPp.AutoDepthStencilFormat = D3DFMT_D16;

	//	D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	//	D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING	:	정점처리를 gpu에 맡김.
	//	D3DCREATE_SOFTWARE_VERTEXPROCESSING :	CPU에 맡김.
	//	D3DCREATE_MIXED_VERTEXPROCESSING    :	HVP, SVP간의 전환 가능.

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
		{
			SAFE_RELEASE(m_pD3DDevice);
			SAFE_RELEASE(m_pD3D);
			return E_FAIL;
		
		}//	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))

	}//	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	
	// DX의 스프라이트는 디바이스가 생성된 후에 만들어야 한다.
	m_pDxSpriteManager = new CDxSprite();
	if (FAILED(m_pDxSpriteManager->Create(m_pD3DDevice)))
	{
		SAFE_DELETE(m_pDxSpriteManager);

		SAFE_RELEASE(m_pD3DDevice);
		SAFE_RELEASE(m_pD3D);

		return E_FAIL;
	}

	m_pDxFont = new CDxFont();

	return S_OK;

}//	HRESULT CDxCore::CreateDX()
//-------------------------------
BOOL CDxCore::Create(HINSTANCE hInst)
{
	m_hInst = hInst;

	if (CreateWindows() == E_FAIL)
		return FALSE;

	if (CreateDX() == E_FAIL)
		return FALSE;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	ShowCursor(m_bShowCursor);
	
	//	입력 관리자.
	m_pInputManager = new CInputManager();
	m_pInputManager->Create(m_hWnd);

	//	카메라 관리자.
	m_pDxCamera = new CDxCamera();
	m_pDxCamera->Create(m_pD3DDevice, 0.01f, 0.1f);

	if (FAILED(Init()))
		return FALSE;

	if (FAILED(Restore()))
		return FALSE;

	return TRUE;

}//	INT	CDxCore::Create(HINSTANCE hInst)
//-------------------------------
void CDxCore::CleanUp()
{
	Destroy();
	SAFE_DELETE(m_pDxCamera);
	SAFE_DELETE(m_pDxFont);
	SAFE_DELETE(m_pInputManager);
	SAFE_DELETE(m_pDxSpriteManager);
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
	
}//	void CDxCore::CleanUp()
//-------------------------------
INT CDxCore::Run()
{
	HACCEL hAccel = LoadAccelerators(NULL, MAKEINTRESOURCE(IDR_ACCEL));

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			if (hAccel == NULL || m_hWnd == NULL || 0 == TranslateAccelerator(m_hWnd, hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			
			}//	if (hAccel == NULL || m_hWnd == NULL || 0 == TranslateAccelerator(m_hWnd, hAccel, &msg))
		
		}//	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		else
		{
			// cpu 타임을 다른 프로세스에게 양도.
			if (m_bDeviceLost)
				Sleep(100);

			if (m_bDeviceLost)
			{	
				HRESULT hr;

				// 디바이스를 계속해서 활용 할 수 있는지 테스트.
				if (FAILED(hr = m_pD3DDevice->TestCooperativeLevel()))
				{
					// 디바이스를 리셋한다.
					// 디바이스를 리셋하려면 디바이스와 관련된 모든 객체들의
					// 상태를 로스트(lost) 상태로 만들어야 한다.
					if (D3DERR_DEVICENOTRESET == hr)
						Reset3D();
					else if (D3DERR_DEVICELOST == hr) { }

				}//	if (FAILED(hr = m_pD3DDevice->TestCooperativeLevel()))
				else
					m_bDeviceLost = FALSE;

			}//	if (m_bDeviceLost)

			if (FAILED(Idle()))
				break;
			
		}//	~if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))

	}//	while (msg.message != WM_QUIT)

	UnregisterClass(m_tszClassName, m_hInst);

	return 0;

}//	INT CDxCore::Run()
//-------------------------------
HRESULT CDxCore::OnRender()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.0f, 0);

	if (FAILED(m_pD3DDevice->BeginScene()))
		return E_FAIL;
	
	if (FAILED(Render()))
		return E_FAIL;
	
	m_pD3DDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
	HRESULT hr = m_pD3DDevice->Present(0, 0, 0, 0);

	// 이 경우는 전체화면상태에서 다른 윈도우가 활성화 될 때(예를들어
	// ALT+TAB키, CTRL+ESC키 동작시) 필요하다.
	// 이 과정을 거쳐야만 계속해서 디바이스를 사용할 수 있다.
	// 일단 로스트 상태로 둔다.
	if (D3DERR_DEVICELOST == hr)
		m_bDeviceLost = TRUE;

	return S_OK;

}//	HRESULT CDxCore::OnRender()
//-------------------------------
HRESULT	CDxCore::Idle()
{
	if (NULL == m_pD3DDevice)
		return E_FAIL;
	
	if (FAILED(FrameMove()))
		return E_FAIL;

	if (m_bDeviceLost == FALSE)
	{
		if (FAILED(OnRender()))
			return E_FAIL;

	}//	if (m_bDeviceLost == FALSE)	

	return S_OK;

}//	HRESULT	CDxCore::Idle()
//-------------------------------
LRESULT WINAPI CDxCore::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)	{ return g_pDxCore->MsgProc(hWnd, msg, wParam, lParam); }
//-------------------------------
LRESULT CDxCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//------------------------
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					break;

				}//	case VK_ESCAPE:

			}//	switch (wParam)

			break;

		}//	case WM_KEYDOWN:

		case WM_DESTROY:
		{
			CleanUp();
			PostQuitMessage(0);
			break;

		}//	case WM_DESTROY:
				
	}//	switch (msg)
	//------------------------

	return DefWindowProc(hWnd, msg, wParam, lParam);

}//	LRESULT CDxCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//-------------------------------
INT CDxCore::Reset3D()
{
	m_bWindowMode ^= 1;

	Invalidate();

	if(m_pDxFont->GetFont())
		m_pDxFont->GetFont()->OnLostDevice();

	if (m_pDxSpriteManager->GetSprite())
		m_pDxSpriteManager->GetSprite()->OnLostDevice();

	m_D3DPp.Windowed = m_bWindowMode;
	m_D3DPp.FullScreen_RefreshRateInHz = m_bWindowMode ? 0 : 60;

	if (FAILED(m_pD3DDevice->Reset(&m_D3DPp)))
		return E_FAIL;

	if (m_pDxSpriteManager->GetSprite())
		m_pDxSpriteManager->GetSprite()->OnResetDevice();

	if(m_pDxFont->GetFont())
		m_pDxFont->GetFont()->OnResetDevice();

	if (m_bWindowMode)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, m_dwWinStyle);

		SetWindowPos(m_hWnd, HWND_NOTOPMOST
			, m_rcWin.left
			, m_rcWin.top
			, m_rcWin.right - m_rcWin.left
			, m_rcWin.bottom - m_rcWin.top
			, SWP_SHOWWINDOW
		);		
	}else
		SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_SYSMENU | WS_VISIBLE);
	
	Sleep(100);

	Restore();

	return S_OK;

}//	INT CDxCore::Reset3D()
//-------------------------------
void CDxCore::UpdateFPS()
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;
	static DWORD dwLastTime = timeGetTime();

	DWORD curTime = timeGetTime();
	float timeDelta = (curTime - dwLastTime) * 0.001f;

	timeElapsed += timeDelta;

	++frameCount;

	if (timeElapsed >= 1.0f)
	{
		float fps = (float)frameCount / timeElapsed;
		sprintf(m_tszFPS, TEXT("게임속도 FPS: %f"), fps);     //FPS출력 하는 소스

		frameCount = 0;
		timeElapsed = 0.0f;

	}//	if (timeElapsed >= 1.0f)

	dwLastTime = curTime;

}//	void CDxCore::UpdateFPS()
//-------------------------------