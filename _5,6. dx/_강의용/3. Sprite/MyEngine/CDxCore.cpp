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

}//	CDxCore::CDxCore()
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

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

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
	m_D3DPp.AutoDepthStencilFormat = D3DFMT_D16;

	// D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
		{
			SAFE_RELEASE(m_pD3DDevice);
			SAFE_RELEASE(m_pD3D);
			return E_FAIL;
		}
	}

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

	if (FAILED(Init()))
		return FALSE;

	return TRUE;

}//	INT	CDxCore::Create(HINSTANCE hInst)
//-------------------------------
void CDxCore::CleanUp()
{
	Destroy();

	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
	
}//	void CDxCore::CleanUp()
//-------------------------------
INT CDxCore::Run()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		
		}//	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		else
		{
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

	// EndScene
	m_pD3DDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
	m_pD3DDevice->Present(0, 0, 0, 0);

	return S_OK;

}//	HRESULT CDxCore::OnRender()
//-------------------------------
HRESULT	CDxCore::Idle()
{
	if (NULL == m_pD3DDevice)
		return E_FAIL;
	
	if (FAILED(FrameMove()))
		return E_FAIL;

	if (FAILED(OnRender()))
		return E_FAIL;

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
CDxCore::~CDxCore()
{
}
//-------------------------------