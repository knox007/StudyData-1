// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	strcpy(m_sCls, "Mck_D3D");
	
	m_hInst			= NULL;
	m_hWnd			= NULL;
	m_dWinStyle		= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	m_dScnX			= 800;
	m_dScnY			= 600;
	
	
	
	m_pD3D			= NULL;
	m_pd3dDevice	= NULL;
	
	m_pMesh			= NULL;
	m_pMeshMtrl		= NULL;
	m_pMeshTexture	= NULL;
	m_dwNumMtrl		= 0L;  
	
	
}


CMain::~CMain()
{
}


INT CMain::Create( HINSTANCE hInst)
{
	m_hInst	= hInst;
	// 윈도우 클래스 등록
	WNDCLASS wc =
	{
		(CS_CLASSDC | CS_DBLCLKS)
		, WndProc
		, 0L
		, 0L
		, m_hInst//GetModuleHandle(NULL)
		, LoadIcon(NULL, IDI_APPLICATION)
		, LoadCursor(NULL, IDC_ARROW)
		, (HBRUSH)GetStockObject(WHITE_BRUSH)
		, NULL
		, m_sCls
	};
	
	RegisterClass( &wc );
	
	// 윈도우 생성
	
	RECT rc={0, 0, m_dScnX, m_dScnY};
	AdjustWindowRect( &rc, m_dWinStyle, FALSE);
	
	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);
	
	m_hWnd = CreateWindow( m_sCls
		, "X-File"
		, m_dWinStyle
		, (iScnSysW - (rc.right-rc.left))/2
		, (iScnSysH - (rc.bottom-rc.top))/2
		, (rc.right-rc.left)
		, (rc.bottom-rc.top)
		, GetDesktopWindow()
		, NULL
		, m_hInst
		, NULL );
	
	
	// D3D생성
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
    if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return E_FAIL;

	
	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅
	D3DPRESENT_PARAMETERS d3dpp={0}; 

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.EnableAutoDepthStencil= TRUE;
	d3dpp.AutoDepthStencilFormat= D3DFMT_D16;
	d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferFormat = d3ddm.Format;
	
	
	// D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.
	
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice ) ) )
	{
		return E_FAIL;
	}
	
	
	Init();
	
	ShowWindow( m_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( m_hWnd );
	
	
	return S_OK;
}


void CMain::Cleanup()
{
	Destroy();
	
	if( m_pd3dDevice != NULL) 
		m_pd3dDevice->Release();
	
	if( m_pD3D != NULL)
		m_pD3D->Release();
}


LRESULT CMain::MsgProc( HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}
	
	return DefWindowProc( m_hWnd, msg, wParam, lParam );
}



INT CMain::Run()
{	    
	// Enter the message loop
	MSG msg;
	memset( &msg, 0, sizeof(msg) );
	
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			FrameMove();
			Render();
		}
	}
	
	return 0;
}



INT CMain::Init()
{
	//머티리얼 버퍼를 가져오기 위한 임시 버퍼
	LPD3DXBUFFER pD3DXMtrlBuffer;
	
	//1. 메쉬를 먼저 로딩한다.
	
	if( FAILED( D3DXLoadMeshFromX( "xFile/Tiger.x"
		,	D3DXMESH_SYSTEMMEM
		,	m_pd3dDevice, NULL
		,	&pD3DXMtrlBuffer, NULL
		,	&m_dwNumMtrl, &m_pMesh ) ) )
	{
		MessageBox(NULL, "Could not find tiger.x", "Meshes.exe", MB_OK);
		return E_FAIL;
	}
	
	
	// 2. 머티리얼과 텍스처를 생성한다.

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMtrl = new D3DMATERIAL9[m_dwNumMtrl];
	m_pMeshTexture  = new LPDIRECT3DTEXTURE9[m_dwNumMtrl];
	
	for( DWORD i=0; i<m_dwNumMtrl; i++ )
	{
		// 머티리얼 복사
		m_pMeshMtrl[i] = d3dxMaterials[i].MatD3D;
		
		// 머티리얼의 Ambient 설정
		m_pMeshMtrl[i].Ambient = m_pMeshMtrl[i].Diffuse;
		
		m_pMeshTexture[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename != NULL &&  lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
		{
			
			// 텍스처를 생성한다.
			TCHAR	sFile[512];

			sprintf(sFile, "xFile/%s", d3dxMaterials[i].pTextureFilename);
			
			if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, sFile, &m_pMeshTexture[i] ) ) )
			{
				MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
			}

		}
	}
	
	// 임시 버퍼를 해제한다.
	pD3DXMtrlBuffer->Release();
	


	
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;									// 광원의 종류
	light.Diffuse.r  = 0.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f),
						 1.0f,
						 sinf(timeGetTime()/350.0f) );
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range       = 1000.0f;												// 광원의 효과가 미치는 거리
	m_pd3dDevice->SetLight( 0, &light );
	m_pd3dDevice->LightEnable( 0, TRUE );
	
	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xFFFFFFFF);					// 마지막으로 엠비언트 광의 색상을 설정한다.
	
	return 0;
}

void CMain::Destroy()
{
	if( m_pMeshMtrl != NULL ) 
		delete[] m_pMeshMtrl;
	
	if( m_pMeshTexture )
	{
		for( DWORD i = 0; i < m_dwNumMtrl; i++ )
		{
			if( m_pMeshTexture[i] )
				m_pMeshTexture[i]->Release();
		}
		
		delete[] m_pMeshTexture;
	}
	
	if( m_pMesh != NULL )
		m_pMesh->Release();
	
}

INT CMain::FrameMove()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixRotationY( &matWorld, timeGetTime()/1000.0f );						// 회전행렬
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );						// 디바이스의 월드 행렬을 설정한다.
	
	// 뷰 행렬 만들기
	D3DXMATRIX m_mtViw;
	D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );										// 카메라의 위치
	D3DXVECTOR3 vLookAt( 0.0f, 0.0f, 0.0f );									// 카메라가 보고있는 방향
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );										// 카메라의 업벡터
	D3DXMatrixLookAtLH(&m_mtViw, &vEyePt, &vLookAt, &vUpVec );				// 뷰 행렬을 만들어 주는 함수
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_mtViw );							// 디바이스의 뷰행렬을 설정한다.
	
	
	// 투영 행렬 만들기
	D3DXMATRIX m_mtPrj;
	FLOAT	fScreenW = (FLOAT)800;
	FLOAT	fScreenH = (FLOAT)600;
	FLOAT	fFOV	= D3DX_PI/4.0f;
	FLOAT	fAspect	= fScreenW/fScreenH;
	FLOAT	fNear	= 1.f;
	FLOAT	fFar	= 5000.f;
	
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_mtPrj );					// 디바이스의 투영행렬을 설정한다.	
	
	return 0;
}


void CMain::Render()
{
	if( NULL == m_pd3dDevice )
		return;
	
	// 실질적으로는 버퍼(백버퍼: 색상, 깊이, 스텐실)를 지우는 것이 아니라 채우는 것이다.
	// D3DCLEAR_TARGET: 색상 버퍼를 지운다.
	// D3DCLEAR_ZBUFFER: 깊이 버퍼를 지운다.
	// Clear에서 D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER 설정은 가장 흔한 방법이다.
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,128,200), 1.0f, 0 );
	
	
	// BeginScene과 EndScene에 렌더링을 걸어주어야 된다.
	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return;
	
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );				// 양면을 다 그릴 경우에 컬링을 끈다.
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );						// 라이팅을 끈다.( 옵션)
	
	
	for( DWORD i=0; i<m_dwNumMtrl; i++ )
	{
		// Set the material and texture for this subset
		m_pd3dDevice->SetMaterial( &m_pMeshMtrl[i] );
		m_pd3dDevice->SetTexture( 0, m_pMeshTexture[i] );
		
		// Draw the mesh subset
		m_pMesh->DrawSubset( i );
	}
	
	// End the scene
	m_pd3dDevice->EndScene();
	
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );							// 마지막으로 후면버퍼를 전면버퍼로 교체한다.( flipping)
}
