#include "StdAfx.h"
#include "PFrFrameWork.h"
#include "PRCore.h"
#include "IGameInterfaceBase.h"
#include "PUTTimer.h"
#include "PRFont.h"
#include "PUTCommon.h"
#include "PRInput.h"
#include "PRCamera.h"
#include "PRLight.h"


#ifdef _FR_TIMEREX_
#include "PUtTimerEx.h"
#endif

#ifdef _FR_FRAMESKIPPER_
#include "PUtFrameSkip.h"
#endif
 
#include "PUtLog.h"

CPFrFrameWork* g_pFrameWork	=	NULL;

//------------------------------------------------------------------------------------------------------------
LRESULT	CALLBACK	gWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !g_pFrameWork->GetInterface() )
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	
	return g_pFrameWork->GetInterface()->WndProc( hWnd, uMsg, wParam, lParam );
	
}//	gWndProc
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::InitMembers()
{
	g_pFrameWork			=	this;
	m_pGameInterface		=	NULL;
	m_pRender				=	NULL;
	m_pTimer				=	NULL;
	m_pFont					=	NULL;
	m_pCamera				=	NULL;
#ifdef _FR_TIMEREX_
	m_pTimerEx				=	NULL;
#endif

#ifdef _FR_FRAMESKIPPER_
	m_pFrameSkipper			=	NULL;
#endif
	
	m_hWnd					=	NULL;
	m_hInst					=	NULL;
	m_bActive				=	true;
	m_nWindowWidth			=	0;
	m_nWindowHeight			=	0;
	m_nFullScrWidth			=	0;
	m_nFullScrHeight		=	0;

	m_dwFillMode			=	D3DFILL_SOLID;
	//m_dwFillMode			=	D3DFILL_SOLID;
	m_bRenderPaused			=	false;
	m_bTimerPaused			=	false;
	m_nRenderingPauseCount	=	0;
	m_nTimerPauseCount		=	0;
	m_bClosing				=	false;

	
	PUT_ZERO_MEMORY(m_WindowPlacement);
}//	InitMembers
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::ClearMembers()
{
	gUtTimerDestroy;
	gPRInputDestroy;
	m_bClosing	=	true;
	OnLostDevice();
	OnDestroyDevice();	
	PUT_SAFE_DELETE( m_pGameInterface );
	PUT_SAFE_DELETE( m_pFont );
	PUT_SAFE_DELETE( m_pCamera );
	PUT_SAFE_DELETE( m_pRender );
	

#ifdef _FR_TIMEREX_
	PUT_SAFE_DELETE( m_pTimerEx );
#endif

#ifdef _FR_FRAMESKIPPER_
	PUT_SAFE_DELETE( m_pFrameSkipper );
#endif
 
}//	Release
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::Register( HINSTANCE hInstance, TCHAR* ptszClassName )
{
	WNDCLASSEX wcex;
	wcex.cbSize         = sizeof( WNDCLASSEX ); 
	wcex.style          = CS_DBLCLKS;
//	wcex.lpfnWndProc    = (WNDPROC)CPFrFrameWork::StaticWndProc;
	wcex.lpfnWndProc    = gWndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	//	wcex.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_LOGO ) );
	wcex.hIcon			= LoadIcon( hInstance, NULL );
	wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground  = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = ptszClassName;
	//	wcex.hIconSm		= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_LOGO ) );
	wcex.hIconSm		= LoadIcon( hInstance, NULL );

	// 윈도우 등록
	RegisterClassEx( &wcex );
}//	Register
//------------------------------------------------------------------------------------------------------------
HWND CPFrFrameWork::Create( TCHAR* ptszTitle, HINSTANCE hInst, bool bWindowed )
{
	HWND hWnd = NULL;

	hWnd = CreateWindow(	ptszTitle,
		ptszTitle,
		bWindowed ? WS_OVERLAPPEDWINDOW : WS_EX_TOPMOST,
		0, 0,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInst,
		this
		);

	return hWnd;
}//	Create
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::SetSize( int nWid, int nHei, int nPosX, int nPosY )
{
	// Adjust to desired size
	RECT rect = { nPosX, nPosY, nWid, nHei };
	AdjustWindowRect( &rect, GetWindowLong( GetHwnd(), GWL_STYLE ), FALSE );
	SetWindowPos( GetHwnd(),
		HWND_TOP,
		0, 0,
		rect.right - rect.left,
		rect.bottom - rect.top, 
		SWP_NOZORDER | SWP_NOMOVE  );

	ShowWindow( GetHwnd(), SW_SHOW );
	UpdateWindow( GetHwnd() );

	// 현재 위치/사이즈 저장
	PUT_ZERO_MEMORY( m_WindowPlacement );
	m_WindowPlacement.length = sizeof( WINDOWPLACEMENT );
	GetWindowPlacement( GetHwnd(), &m_WindowPlacement );
}//	SetSize
//------------------------------------------------------------------------------------------------------------
HRESULT CPFrFrameWork::OnDestroyDevice()
{
	if( GetInterface() )
		GetInterface()->OnDestroyDevice();

	return S_OK;
}//	OnDestroyDevice
//------------------------------------------------------------------------------------------------------------
bool CPFrFrameWork::Init( TCHAR* ptszTitle, HINSTANCE hInstance, int nWid, int nHei, bool bWindowed /* = true */, int nPosX /* = 0*/, int nPosY /* = 0*/ )
{
	m_hInst			=	hInstance;
	m_nWindowWidth	=	nWid;
	m_nWindowHeight	=	nHei;

	//	윈도우 클래스 등록
	Register( hInstance, ptszTitle );

	//	윈도우 핸들 생성
	m_hWnd = Create( ptszTitle, hInstance, bWindowed );
	if( !GetHwnd() )
	{
		PUTSHOWERR(PUT_CSTR_TCHAR("CPFrFrameWork::Init - Create") );
		return false;
	}

	//	크기 설정
	SetSize( m_nWindowWidth, m_nWindowHeight, nPosX, nPosY );

	PUTNEW( m_pRender, CPRCore );
	if( !GetRenderer() )
	{
		PUTSHOWERR(PUT_CSTR_TCHAR("CPFrFrameWork::Init - new CJRender") );
		return false;
	}

	//	랜더러 초기화.
	if( !GetRenderer()->Init( GetHwnd(), bWindowed ) )
	{
		PUTSHOWERR(PUT_CSTR_TCHAR("CPFrFrameWork::Init - GetRenderer()->Init") );
		return false;
	}

	m_nFullScrWidth		=	GetRenderer()->GetDisplayMode()->Width;
	m_nFullScrHeight	=	GetRenderer()->GetDisplayMode()->Height;

	//	카메라 생성.
	D3DXVECTOR3	vecEye( 5.0f, 5.0f, -5.0f );
	D3DXVECTOR3	vecLookAt( 0.0f, 0.0f, 0.0f );
	PUTNEW( m_pCamera, CPRCamera );
	m_pCamera->Init( GetRenderer()->GetDevice(), &vecEye, &vecLookAt );

	//	타이머 생성.
	m_pTimer	=	gUtTimer;

#ifdef _FR_TIMEREX_
	m_pTimerEx	=	new CPUtTimerEx;
#endif	//	_FR_TIMEREX_


#ifdef _FR_FRAMESKIPPER_
	m_pFrameSkipper = new CPUtFrameSkip;
	m_pFrameSkipper->Init( 1000.0f );
#endif	//	_FR_FRAMESKIPPER_

	
	//	폰트 생성.	
	PUTNEW( m_pFont, CPRFont );
	
	//	입력 디바이스 생성.
	m_pInput	=	gPRInput;
	GetInput()->Init( hInstance, GetHwnd() );


 
	OnCreateDevice();
	OnResetDevice();

	Pause( false, false );

	return true;
}//	Init
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::Run( TCHAR* ptszTitle, HINSTANCE hInstance, int nWid, int nHei, bool bWindowed, int nPosX, int nPosY )
{
	if( !Init(ptszTitle, hInstance, nWid, nHei, bWindowed, nPosX, nPosY ) )
	{
		PUTSHOWERR(PUT_CSTR_TCHAR("if( !Init(g_ptszWndTitle, hInstance, 800, 600 ) ) - error "));
		return;
	}

	if( !GetInterface()->Init() )
	{
		PUTSHOWERR(PUT_CSTR_TCHAR("if( !m_pGameInterface->Init() ) - error "));
		return;
	}

	MSG msg;
	while (1)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
				break;

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}//	if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		else
		{
			if( GetRenderer() && GetRenderer()->GetDevice() != NULL && m_bActive )
			{
#ifdef _FR_TIMEREX_

				float fElapsedTime = 0.0f;
				if( m_pTimerEx )
					fElapsedTime = (float)m_pTimerEx->GetElapsedTime();

#ifdef _FR_FRAMESKIPPER_
				if( 0.0f < fElapsedTime && fElapsedTime < 1.0f )
				{
					if( m_pFrameSkipper && m_pFrameSkipper->Update( fElapsedTime ) )					
					{
#endif	//	_FR_FRAMESKIPPER_
						OnUpdate( fElapsedTime );
						OnRender( GetRenderer()->GetDevice(), fElapsedTime );
#ifdef _FR_FRAMESKIPPER_
						PUTOutputDebugStr( "fElapsedTime = %f\n", fElapsedTime );
					}
				}
#endif	//	_FR_FRAMESKIPPER_				
				
#else	//	~_FR_TIMEREX_
				if( GetTimer() != NULL )
					GetTimer()->OnUpdate();

				float fElapsedTime = GetTimer()->GetElapsedTime();

				OnUpdate( fElapsedTime );
				OnRender( GetRenderer()->GetDevice(), fElapsedTime );
//				PUTOutputDebugStr( "fElapsedTime = %f\n", fElapsedTime );

#endif	//	_FR_TIMEREX_				

			}//	if( GetRenderer() && GetRenderer()->GetDevice() != NULL && m_bActive )

		}//	~if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	}
}//	Run
//------------------------------------------------------------------------------------------------------------
HRESULT CPFrFrameWork::OnCreateDevice()
{
	HRESULT hr = E_FAIL;
	if( m_pGameInterface && GetRenderer() )
	{
		hr = m_pGameInterface->OnCreateDevice( GetRenderer()->GetDevice() );
	}

	return hr;
}//	OnCreateDevice
//------------------------------------------------------------------------------------------------------------
HRESULT CPFrFrameWork::OnResetDevice()
{
	Pause( false, false );

	ResetCamera();
		
	if( GetInterface() && GetRenderer() )
	{
		GetInterface()->OnResetDevice( GetRenderer()->GetDevice() );
	}

	return S_OK;
}//	OnResetDevice
//------------------------------------------------------------------------------------------------------------
void	CPFrFrameWork::ResetCamera()
{
	//	Projection		
	GetCamera()->SetProjParams( GetCamera()->GetProjParam(CPRCamera::ePROJPARAM_FOV),
								GetCamera()->GetProjParam(CPRCamera::ePROJPARAM_ASPECT),
								GetCamera()->GetProjParam(CPRCamera::ePROJPARAM_NEAR),
								GetCamera()->GetProjParam(CPRCamera::ePROJPARAM_FAR) );	

}//	ResetCamera
//------------------------------------------------------------------------------------------------------------
HRESULT CPFrFrameWork::OnLostDevice()
{
	if( !m_bClosing  )
	{
		Pause( true, true );
	}

	if( GetInterface() )
		GetInterface()->OnLostDevice();

	return S_OK;

}//	OnLostDevice
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::OnUpdate( float fElapsedTime )
{
	if( GetInterface() != NULL &&
		GetRenderer() != NULL &&
		GetTimer() != NULL )
	{
		GetInput()->FrameMove();

		UpdateCamera( fElapsedTime );
		UpdateLight( fElapsedTime );
		
		GetInterface()->OnUpdate( fElapsedTime );
	}

}//	Update
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::UpdateCamera( float fElapsedTime )
{
	if( !GetCamera() )
		return;
 
	GetCamera()->ResetTmpDelta();

	//@	카메라 이동.
	if (GetInput()->IsKeyDown(DIK_W))
		GetCamera()->SetMove( D3DXVECTOR3(0, 0, 1), fElapsedTime );
	if (GetInput()->IsKeyDown(DIK_A))
		GetCamera()->SetMove( D3DXVECTOR3(-1, 0, 0), fElapsedTime );	
	if (GetInput()->IsKeyDown(DIK_S))		
		GetCamera()->SetMove( D3DXVECTOR3(0, 0, -1), fElapsedTime );
	if (GetInput()->IsKeyDown(DIK_D))		
		GetCamera()->SetMove( D3DXVECTOR3(1, 0, 0), fElapsedTime );
	if (GetInput()->IsKeyDown(DIK_Q))		
		GetCamera()->SetMove( D3DXVECTOR3(0, 0, 1), fElapsedTime );	
	if (GetInput()->IsKeyDown(DIK_E))		
		GetCamera()->SetMove( D3DXVECTOR3(0, 0, -1), fElapsedTime );

	GetCamera()->CheckEnableBoostMove( false );
	GetCamera()->CheckEnableBoostRotate( false );
	if (GetInput()->IsKeyDown(DIK_LSHIFT))	  
	{
		GetCamera()->CheckEnableBoostMove( true );
		GetCamera()->CheckEnableBoostRotate( true );
	}

	float fDeltaX = GetInput()->GetMouseDelta()->x;
	float fDeltaY = GetInput()->GetMouseDelta()->y;
	float fDeltaZ = GetInput()->GetMouseDelta()->z;

	// 마우스 가운데 버튼
	if( GetInput()->IsMouseDown(CPRInput::eMOUSEBTTNCLICK_WHEEL) )
	{
		GetCamera()->SetPosDelta( fDeltaX, fDeltaY, fElapsedTime );
	}	

	if( GetCamera()->GetType() == CPRCamera::eTYPE_THIRD )
		GetCamera()->SetDistToTargetCur( fDeltaZ );
	else
		GetCamera()->SetSpeed( CPRCamera::eSPEED_MOVE, fDeltaZ );
	
	//회전.
	// 마우스 누를때만 마우스 이동량을 얻어온다.
	if(	GetInput()->IsMouseDown(CPRInput::eMOUSEBTTNCLICK_RIGHT) &&
		!GetInput()->IsKeyDown( DIK_LCONTROL ) )
	{
		GetCamera()->SetRotate( fDeltaX, fDeltaY, fElapsedTime );
	}

	GetCamera()->OnUpdate(fElapsedTime);

	D3DMATRIX*	pMatView	=	(D3DMATRIX*)GetCamera()->GetMat( CPRCamera::eMAT_VIEW );
	GetRenderer()->SetTransformView( pMatView );

	D3DMATRIX* pMatProj		=	(D3DMATRIX*)GetCamera()->GetMat(CPRCamera::eMAT_PROJECTION);
	GetRenderer()->SetTransformProjection( pMatProj );

}//	UpdateCamera
//------------------------------------------------------------------------------------------------------------
void	CPFrFrameWork::UpdateLight( float fElapsedTime )
{
	float fDeltaX = GetInput()->GetMouseDelta()->x;
	float fDeltaY = GetInput()->GetMouseDelta()->y;
	
	//회전.
	// 마우스 누를때만 마우스 이동량을 얻어온다.
	if( GetInput()->IsMouseDown(CPRInput::eMOUSEBTTNCLICK_RIGHT) &&
		GetInput()->IsKeyDown( DIK_LCONTROL ) )
	{
		GetRenderer()->GetLight()->SetRotate( fDeltaX, fDeltaY, fElapsedTime );
		
	}else
		GetRenderer()->GetLight()->SetRotate( 0, 0, fElapsedTime );


	GetRenderer()->GetLight()->OnUpdate( fElapsedTime );
	
}
//------------------------------------------------------------------------------------------------------------
HRESULT CPFrFrameWork::OnRender( IDirect3DDevice9* pDevice, float fElapsedTime )
{
	if( !GetRenderer() )
		return E_FAIL;

	if( !m_bActive || ( GetRenderer()->GetDevice() == NULL ) )
		return E_FAIL;

	HRESULT hRes = GetRenderer()->GetDevice()->TestCooperativeLevel();
	if( FAILED( hRes ) )
	{
		if( hRes == D3DERR_DEVICELOST )
		{
			Sleep( 50 );
			return E_FAIL;
		}else
		{
			OnLostDevice();

			if( GetRenderer()->Reset() == D3DERR_DEVICELOST )
			{
				Sleep( 50 );
				return E_FAIL;
			}else
			{
				OnResetDevice();
			}
		}
	}

	if( GetInterface() != NULL && !m_bRenderPaused && GetTimer() != NULL )
	{ 
		GetInterface()->RenderFrame( pDevice, fElapsedTime );		 
	}

	return S_OK;
}//	Render
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::ToggleFullScreen()
{
	if( GetRenderer() == NULL || !m_bActive )
		return;

	Pause( true, true );

	GetRenderer()->m_bWindowMode = !GetRenderer()->m_bWindowMode;

	if( GetRenderer()->m_bWindowMode )
	{
		SetWindowLong( GetHwnd(), GWL_STYLE, WS_OVERLAPPEDWINDOW );
	}
	else
	{
		PUT_ZERO_MEMORY( m_WindowPlacement );
		m_WindowPlacement.length	=	sizeof( m_WindowPlacement );
		GetWindowPlacement( GetHwnd(), &m_WindowPlacement );

		SetWindowLong( GetHwnd(), GWL_STYLE, WS_EX_TOPMOST );
	}

	OnLostDevice();
	GetRenderer()->Reset();
	OnResetDevice();

	if( GetRenderer()->m_bWindowMode )
	{
		SetWindowPlacement( GetHwnd(), &m_WindowPlacement );
	}

	Pause( FALSE, FALSE );
}//	ToggleFullScreen
//------------------------------------------------------------------------------------------------------------
HRESULT CPFrFrameWork::ToggleWireFrame()
{
	m_dwFillMode = ( m_dwFillMode == D3DFILL_SOLID ) ? D3DFILL_WIREFRAME : D3DFILL_SOLID;

	return GetRenderer()->SetFillMode( m_dwFillMode );
}//	ToggleWireFrame
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::Pause( BOOL bRender, BOOL bTimer )
{
	m_nRenderingPauseCount += bRender? 1 : -1;
	m_nRenderingPauseCount = ( m_nRenderingPauseCount < 0 ) ? 0 : m_nRenderingPauseCount; 

	m_nTimerPauseCount += bTimer ? 1 : -1;
	m_nTimerPauseCount = ( m_nTimerPauseCount < 0 ) ? 0 : m_nTimerPauseCount;

	m_bRenderPaused = ( m_nRenderingPauseCount > 0 );
	m_bTimerPaused = ( m_nTimerPauseCount > 0 );

	if( GetTimer() != NULL )
	{
		if( m_bTimerPaused )
			GetTimer()->Stop();
		else
			GetTimer()->Start();
	}

}//	Pause
//------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK CPFrFrameWork::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	case WM_PAINT:
		if( !GetRenderer() )
			break;

		if( GetRenderer()->GetDevice() )
		{
//			OnUpdate();
//			OnRender( GetRenderer()->GetDevice() );
		}
		ValidateRect( hWnd, 0 );
		break;

	case WM_SIZE:
		if( wParam == SIZE_MINIMIZED )
			m_bActive = false;
		else
		{
			m_bActive = true;
			m_nWindowWidth	= LOWORD( lParam );
			m_nWindowHeight = HIWORD( lParam );

			if( !GetRenderer() )
				break;
			if( GetRenderer()->GetDevice() )
			{
				OnLostDevice();
				GetRenderer()->Reset();
				OnResetDevice();
//				OnUpdate();
//				OnRender( GetRenderer()->GetDevice() );
			}
		}
		break;	

	case WM_RBUTTONDOWN:		
		SetCapture( hWnd );
		break;

	case WM_RBUTTONUP:
		ReleaseCapture();
		break;

	case WM_MOUSEWHEEL:
		{
			int nVal = HIWORD( wParam );
		}
		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}//	WndProc
//------------------------------------------------------------------------------------------------------------
int CPFrFrameWork::GetWidth()
{
	if( GetRenderer()->m_bWindowMode )
		return m_nWindowWidth;

	return m_nFullScrWidth;
}//	GetWidth
//------------------------------------------------------------------------------------------------------------
int CPFrFrameWork::GetHeight()
{
	if( GetRenderer()->m_bWindowMode )
		return m_nWindowHeight;

	return m_nFullScrHeight;
}//	GetHeight
//------------------------------------------------------------------------------------------------------------
void CPFrFrameWork::LinkApp( IGameInterfaceBase* pApp )
{
	m_pGameInterface	=	pApp;	
	GetInterface()->LinkFramework( this );
}//	LinkApp
//------------------------------------------------------------------------------------------------------------
//	EOF