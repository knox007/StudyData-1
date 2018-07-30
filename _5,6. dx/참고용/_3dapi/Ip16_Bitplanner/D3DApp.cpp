// Implementation of the CD3DApp class.
//
//////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


static CD3DApp*	g_pD3DApp;


CD3DApp::CD3DApp()
{
	g_pD3DApp           = this;

	strcpy(m_sCls, "2D Game App");
	
	m_hInst			= NULL;
	m_hWnd			= NULL;
	m_dWinStyle		= WS_OVERLAPPED| WS_CAPTION| WS_SYSMENU| WS_VISIBLE;
	m_dScnW			= 800;
	m_dScnH			= m_dScnW * 3/4;

	m_bWindow		= TRUE;			// Window mode
	m_bActive		= TRUE;
	m_bDeviceLost	= FALSE;
	m_bDestroyed	= FALSE;

	m_pD3D			= NULL;			// D3D
	m_pd3dDevice	= NULL;			// Device
	m_pd3dSprite	= NULL;			// 2D Sprite

	m_fFps			= 60;
}


HRESULT CD3DApp::Create( HINSTANCE hInst)
{

	if( m_hWnd == NULL)
	{
		m_hInst	= hInst;

		WNDCLASS wc =								// Register the window class
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
			, m_sCls
		};

		RegisterClass( &wc );

		RECT rc;									//Create the application's window

		SetRect( &rc, 0, 0, m_dScnW, m_dScnH);
		AdjustWindowRect( &rc, m_dWinStyle, FALSE );

		int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
		int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

		m_hWnd = CreateWindow( m_sCls
			, m_sCls
			, m_dWinStyle
			, (iScnSysW - (rc.right-rc.left))/2
			, (iScnSysH - (rc.bottom-rc.top))/2
			, (rc.right  - rc.left)
			, (rc.bottom - rc.top)
			, NULL
			, NULL
			, m_hInst
			, NULL );
	}
	
	m_hMenu = GetMenu(m_hWnd);
	m_dWinStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	GetWindowRect( m_hWnd, &m_rcWinBounds );
	GetClientRect( m_hWnd, &m_rcWinClient );
	
	
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;
	
	if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_d3dMode ) ) )
		return E_FAIL;
	
	memset(&m_d3dParam, 0, sizeof(m_d3dParam));
	
	m_d3dParam.Windowed					= m_bWindow;
	m_d3dParam.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_d3dParam.BackBufferFormat			= m_d3dMode.Format;
	m_d3dParam.BackBufferCount			= 2;
	m_d3dParam.BackBufferWidth			= m_dScnW;
	m_d3dParam.BackBufferHeight			= m_dScnH;
	m_d3dParam.EnableAutoDepthStencil	= TRUE;
	m_d3dParam.AutoDepthStencilFormat	= D3DFMT_D16;
	m_d3dParam.FullScreen_RefreshRateInHz = m_d3dParam.Windowed? 0 : m_d3dMode.RefreshRate;
	m_d3dParam.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	m_d3dParam.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE ;
	
	
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3dParam, &m_pd3dDevice ) ) )
	{
		if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dParam, &m_pd3dDevice ) ) )
		{
			SAFE_RELEASE(	m_pd3dDevice	);
			SAFE_RELEASE(	m_pD3D			);
			return -1;
		}
	}

	
	if(FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
	{
		SAFE_RELEASE(	m_pd3dDevice	);
		SAFE_RELEASE(	m_pD3D			);
		return E_FAIL;
	}


	::ShowWindow( m_hWnd, SW_SHOW );
	::UpdateWindow( m_hWnd );
	::ShowCursor(TRUE);
	
	if(FAILED(Init()))
		return -1;
	
	return S_OK;
}



LRESULT CALLBACK CD3DApp::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return g_pD3DApp->MsgProc( hWnd, uMsg, wParam, lParam );
}


LRESULT CD3DApp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_PAINT:
			break;
		
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_INACTIVE)
				m_bActive = FALSE;
			else
				m_bActive = TRUE;
			
			return 0;
		}

		case WM_COMMAND:
		{
			switch( LOWORD(wParam) )
			{
				case IDM_TOGGLEFULLSCREEN:
				{
					Reset3D();
					return 0;
				}
			}

			break;
		}

		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0,0);
					break;
				}
			}

			break;
		}
		
		case WM_CLOSE:
		case WM_DESTROY:
			Cleanup();
			PostQuitMessage(0);
			return 0;
	}
	
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}



HRESULT CD3DApp::Cleanup()
{
	if(m_bDestroyed)
		return 0;
	
	m_bDestroyed = 1;
	
	Destroy();
	
	SAFE_RELEASE(	m_pd3dSprite	);
	SAFE_RELEASE(	m_pd3dDevice	);
	SAFE_RELEASE(	m_pD3D			);
	
	if(m_hMenu)
	{
		DestroyMenu( m_hMenu );
		m_hMenu = NULL;
	}
	
	if(m_hWnd)
	{
		DestroyWindow( m_hWnd );
		m_hWnd = NULL;
	}
	
	if(m_hInst)
	{
		UnregisterClass( m_sCls, m_hInst);
		m_hInst = NULL;
	}

	return 0;
}



HRESULT CD3DApp::Run()
{
	MSG  msg;
	bool bGotMsg;

	// Load keyboard accelerators
	HACCEL hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

	
	memset(&msg, 0, sizeof(MSG));
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	
	while(WM_QUIT != msg.message)
	{
		if( m_bActive )
		{
			bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );
		}
		
		else
			bGotMsg = ( GetMessage( &msg, NULL, 0U, 0U ) != 0 );
		
		if( bGotMsg )
		{
			if( hAccel == NULL || m_hWnd == NULL || 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			if( m_bDeviceLost )
				Sleep( 100 );

			if( m_bActive )
			{
				if( FAILED( Render3D() ) )
					SendMessage( m_hWnd, WM_CLOSE, 0, 0 );
			}
		}
	}
	

	return 0;
}


void CD3DApp::UpdateFrame()
{
	static int		iCnt =0;
	static DWORD	dB = timeGetTime();
	DWORD			dE = timeGetTime();
	
	++iCnt;
	
	if(iCnt>30)
	{
		m_fFps = FLOAT(dE-dB);
		m_fFps = iCnt*1000/m_fFps;
		
		iCnt = 0;
		dB = dE;
	}
}




HRESULT CD3DApp::Render3D()
{
	if( NULL == m_pd3dDevice )
		return -1;
	
	HRESULT hr;
	
	if( m_bDeviceLost )
	{
		if( FAILED( hr = m_pd3dDevice->TestCooperativeLevel() ) )
		{
			if( D3DERR_DEVICELOST == hr )
				return S_OK;

			if( D3DERR_DEVICENOTRESET == hr )									// Check if the device needs to be reset.
			{
				if( FAILED( hr = Reset3D() ) )
					return hr;
			}
			return hr;
		}

		m_bDeviceLost = FALSE;
	}
	
	
	if(FAILED(FrameMove()))
		return -1;
	
	if(FAILED(Render()))
		return -1;
	
	UpdateFrame();

	hr = m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	
	if( D3DERR_DEVICELOST == hr )
		m_bDeviceLost = TRUE;
	
	
	
	return 0;
}


HRESULT CD3DApp::Reset3D()
{
	Invalidate();

	m_bWindow ^=1;

	if(	m_pd3dSprite	)
		m_pd3dSprite->OnLostDevice();


	if(m_bWindow)
		m_d3dParam.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE ;
	else
		m_d3dParam.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT ;

	m_d3dParam.Windowed					= m_bWindow;
	m_d3dParam.FullScreen_RefreshRateInHz= m_bWindow? 0 : 60;

	if(FAILED(m_pd3dDevice->Reset(&m_d3dParam)))
		return -1;

	if(	m_pd3dSprite	)
		m_pd3dSprite->OnResetDevice();


	if(m_bWindow)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, m_dWinStyle);
		SetWindowPos(m_hWnd, HWND_NOTOPMOST
			, m_rcWinBounds.left
			, m_rcWinBounds.top
			, m_rcWinBounds.right	- m_rcWinBounds.left
			, m_rcWinBounds.bottom	- m_rcWinBounds.top
			, SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowLong( m_hWnd, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE );
	}

	Sleep(100);

	Restore();

	return 0;
}

