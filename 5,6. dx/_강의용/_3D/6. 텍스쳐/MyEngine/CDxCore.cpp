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

	m_pInputManager = NULL;			//	�Է� �Ŵ���.

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
	// D3D����
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// D3D�� ���ؼ� ȭ�� ��带 ã�´�.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	// ����̽��� �����ϱ� ���ؼ��� ������Ʈ �Ķ���� ����ü�� �ʿ�
	// ���� 0���� �����Ѵ��� �Ϻθ� ��������
	ZeroMemory(&m_D3DPp, sizeof(m_D3DPp));
	m_D3DPp.Windowed = m_bWindowMode;
	m_D3DPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPp.BackBufferFormat = d3ddm.Format;
	m_D3DPp.BackBufferCount = 2;
	m_D3DPp.BackBufferWidth = m_dwScrWidth;
	m_D3DPp.BackBufferHeight = m_dwScrHeight;
	m_D3DPp.EnableAutoDepthStencil = TRUE;
	//	http://telnet.or.kr/directx/graphics/reference/d3d/constants/d3dpresent.htm
	//	��Ÿ���� ������ Ŭ���̾�Ʈ ������ ��� �����Ѵ�.
	//	����� �������� �����߿� 2 ȸ �̻� �� ������ �ǽ��ϴ� ���� �ִ�.
	//	�̰���, DirectX 8.0 �� D3DSWAPEFFECT_COPY �� ����ϴ� �Ϳ� �����ϴ�. 
	//	IDirect3DDevice9::Present �� ���� ������ �ִ� ��찡 �ִ�. �� �ɼ���, ������ ���� ü�� �� Ǯ ��ũ�� ���� ü���� ���� ��η� �׻� ����� �� �ִ�.
	m_D3DPp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_D3DPp.AutoDepthStencilFormat = D3DFMT_D16;

	//	D3DADAPTER_DEFAULT: ��κ��� �׷���ī��� ��� ����� ��� �̺κ��� ����
	//	D3DDEVTYPE_HAL : �ϵ���� ����(���� ū �ӵ�)�� ���� ���ΰ�.. �ϵ���� ������ ���� ��� D3D�� ����Ʈ����� �̸� ��ü �� �� �ִ�.
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING	:	����ó���� gpu�� �ñ�.
	//	D3DCREATE_SOFTWARE_VERTEXPROCESSING :	CPU�� �ñ�.
	//	D3DCREATE_MIXED_VERTEXPROCESSING    :	HVP, SVP���� ��ȯ ����.

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
		{
			SAFE_RELEASE(m_pD3DDevice);
			SAFE_RELEASE(m_pD3D);
			return E_FAIL;
		
		}//	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))

	}//	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	
	// DX�� ��������Ʈ�� ����̽��� ������ �Ŀ� ������ �Ѵ�.
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
	
	//	�Է� ������.
	m_pInputManager = new CInputManager();
	m_pInputManager->Create(m_hWnd);

	//	ī�޶� ������.
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
			// cpu Ÿ���� �ٸ� ���μ������� �絵.
			if (m_bDeviceLost)
				Sleep(100);

			if (m_bDeviceLost)
			{	
				HRESULT hr;

				// ����̽��� ����ؼ� Ȱ�� �� �� �ִ��� �׽�Ʈ.
				if (FAILED(hr = m_pD3DDevice->TestCooperativeLevel()))
				{
					// ����̽��� �����Ѵ�.
					// ����̽��� �����Ϸ��� ����̽��� ���õ� ��� ��ü����
					// ���¸� �ν�Ʈ(lost) ���·� ������ �Ѵ�.
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

	// �ĸ���� ������� ��ü( flipping)
	HRESULT hr = m_pD3DDevice->Present(0, 0, 0, 0);

	// �� ���� ��üȭ����¿��� �ٸ� �����찡 Ȱ��ȭ �� ��(�������
	// ALT+TABŰ, CTRL+ESCŰ ���۽�) �ʿ��ϴ�.
	// �� ������ ���ľ߸� ����ؼ� ����̽��� ����� �� �ִ�.
	// �ϴ� �ν�Ʈ ���·� �д�.
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
		sprintf(m_tszFPS, TEXT("���Ӽӵ� FPS: %f"), fps);     //FPS��� �ϴ� �ҽ�

		frameCount = 0;
		timeElapsed = 0.0f;

	}//	if (timeElapsed >= 1.0f)

	dwLastTime = curTime;

}//	void CDxCore::UpdateFPS()
//-------------------------------