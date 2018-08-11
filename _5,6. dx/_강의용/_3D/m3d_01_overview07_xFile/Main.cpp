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
	// ������ Ŭ���� ���
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
	
	// ������ ����
	
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
	
	
	// D3D����
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// D3D�� ���ؼ� ȭ�� ��带 ã�´�.
	D3DDISPLAYMODE d3ddm;
    if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return E_FAIL;

	
	// ����̽��� �����ϱ� ���ؼ��� ������Ʈ �Ķ���� ����ü�� �ʿ�
	// ���� 0���� �����Ѵ��� �Ϻθ� ��������
	D3DPRESENT_PARAMETERS d3dpp={0}; 

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.EnableAutoDepthStencil= TRUE;
	d3dpp.AutoDepthStencilFormat= D3DFMT_D16;
	d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferFormat = d3ddm.Format;
	
	
	// D3DADAPTER_DEFAULT: ��κ��� �׷���ī��� ��� ����� ��� �̺κ��� ����
	// D3DDEVTYPE_HAL : �ϵ���� ����(���� ū �ӵ�)�� ���� ���ΰ�.. �ϵ���� ��
	// ���� ���� ��� D3D�� ����Ʈ����� �̸� ��ü �� �� �ִ�.
	
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
	//��Ƽ���� ���۸� �������� ���� �ӽ� ����
	LPD3DXBUFFER pD3DXMtrlBuffer;
	
	//1. �޽��� ���� �ε��Ѵ�.
	
	if( FAILED( D3DXLoadMeshFromX( "xFile/Tiger.x"
		,	D3DXMESH_SYSTEMMEM
		,	m_pd3dDevice, NULL
		,	&pD3DXMtrlBuffer, NULL
		,	&m_dwNumMtrl, &m_pMesh ) ) )
	{
		MessageBox(NULL, "Could not find tiger.x", "Meshes.exe", MB_OK);
		return E_FAIL;
	}
	
	
	// 2. ��Ƽ����� �ؽ�ó�� �����Ѵ�.

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMtrl = new D3DMATERIAL9[m_dwNumMtrl];
	m_pMeshTexture  = new LPDIRECT3DTEXTURE9[m_dwNumMtrl];
	
	for( DWORD i=0; i<m_dwNumMtrl; i++ )
	{
		// ��Ƽ���� ����
		m_pMeshMtrl[i] = d3dxMaterials[i].MatD3D;
		
		// ��Ƽ������ Ambient ����
		m_pMeshMtrl[i].Ambient = m_pMeshMtrl[i].Diffuse;
		
		m_pMeshTexture[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename != NULL &&  lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
		{
			
			// �ؽ�ó�� �����Ѵ�.
			TCHAR	sFile[512];

			sprintf(sFile, "xFile/%s", d3dxMaterials[i].pTextureFilename);
			
			if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, sFile, &m_pMeshTexture[i] ) ) )
			{
				MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
			}

		}
	}
	
	// �ӽ� ���۸� �����Ѵ�.
	pD3DXMtrlBuffer->Release();
	


	
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;									// ������ ����
	light.Diffuse.r  = 0.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f),
						 1.0f,
						 sinf(timeGetTime()/350.0f) );
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range       = 1000.0f;												// ������ ȿ���� ��ġ�� �Ÿ�
	m_pd3dDevice->SetLight( 0, &light );
	m_pd3dDevice->LightEnable( 0, TRUE );
	
	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xFFFFFFFF);					// ���������� �����Ʈ ���� ������ �����Ѵ�.
	
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
	D3DXMatrixRotationY( &matWorld, timeGetTime()/1000.0f );						// ȸ�����
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );						// ����̽��� ���� ����� �����Ѵ�.
	
	// �� ��� �����
	D3DXMATRIX m_mtViw;
	D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );										// ī�޶��� ��ġ
	D3DXVECTOR3 vLookAt( 0.0f, 0.0f, 0.0f );									// ī�޶� �����ִ� ����
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );										// ī�޶��� ������
	D3DXMatrixLookAtLH(&m_mtViw, &vEyePt, &vLookAt, &vUpVec );				// �� ����� ����� �ִ� �Լ�
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_mtViw );							// ����̽��� ������� �����Ѵ�.
	
	
	// ���� ��� �����
	D3DXMATRIX m_mtPrj;
	FLOAT	fScreenW = (FLOAT)800;
	FLOAT	fScreenH = (FLOAT)600;
	FLOAT	fFOV	= D3DX_PI/4.0f;
	FLOAT	fAspect	= fScreenW/fScreenH;
	FLOAT	fNear	= 1.f;
	FLOAT	fFar	= 5000.f;
	
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_mtPrj );					// ����̽��� ��������� �����Ѵ�.	
	
	return 0;
}


void CMain::Render()
{
	if( NULL == m_pd3dDevice )
		return;
	
	// ���������δ� ����(�����: ����, ����, ���ٽ�)�� ����� ���� �ƴ϶� ä��� ���̴�.
	// D3DCLEAR_TARGET: ���� ���۸� �����.
	// D3DCLEAR_ZBUFFER: ���� ���۸� �����.
	// Clear���� D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER ������ ���� ���� ����̴�.
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,128,200), 1.0f, 0 );
	
	
	// BeginScene�� EndScene�� �������� �ɾ��־�� �ȴ�.
	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return;
	
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );				// ����� �� �׸� ��쿡 �ø��� ����.
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );						// �������� ����.( �ɼ�)
	
	
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
	
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );							// ���������� �ĸ���۸� ������۷� ��ü�Ѵ�.( flipping)
}
