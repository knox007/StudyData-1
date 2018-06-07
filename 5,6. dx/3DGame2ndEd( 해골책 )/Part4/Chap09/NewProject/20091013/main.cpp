/**-----------------------------------------------------------------------------
 * \brief ĳ���� �ִϸ��̼�
 * ����: main.cpp
 *
 * ����: XML�����͸� ȭ�鿡 ������ش�.
 *       
 *------------------------------------------------------------------------------
 */

#define MAINBODY

#include <d3d9.h>
#include <d3dx9.h>
#include "ZCamera.h"
#include "ZFLog.h"
#include "ZCParser.h"
#include "ZCParsedData.h"
#include "ZSceneMgr.h"

#define WINDOW_CLASS	"EffectView"
#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	"XML Viewer"
//#define FNAME_XML		"teapot_torus.xml"
#define FNAME_XML		"teapot_torus.xml"
#define ID_COPYDATA		1123

// ��Ű���� Software������� 
#define DEF_SKINMETHOD	ZNodeMgr::SKINMETHOD_SW

// ��Ű���� Fixed Function������� 
//#define DEF_SKINMETHOD	ZNodeMgr::SKINMETHOD_FF

/**-----------------------------------------------------------------------------
 *  ��������
 *------------------------------------------------------------------------------
 */
HWND					g_hwnd = NULL;
HINSTANCE				g_hInst = NULL;

LPDIRECT3D9             g_pD3D       = NULL; // D3D ����̽��� ������ D3D��ü����
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // �������� ���� D3D����̽�

D3DXMATRIXA16			g_matWorld;
D3DXMATRIXA16			g_matView;
D3DXMATRIXA16			g_matProj;

float					g_xRot = 0.0f;
float					g_yRot = 0.0f;
DWORD					g_dwMouseX = 0;			// ���콺�� ��ǥ
DWORD					g_dwMouseY = 0;			// ���콺�� ��ǥ
BOOL					g_bWireframe = FALSE;	// ���̾����������� �׸����ΰ�?
BOOL					g_bAnimate = TRUE;
int						g_nDrawMode = 2;		// 0 = all, 1 = bone, 2 = mesh
BOOL					g_bBBox = FALSE;
BOOL					g_bActive = TRUE;
BOOL					g_bLight = TRUE;

float					g_fFrames = 0.0f;

ZCamera*				g_pCamera = NULL;	// Camera Ŭ����

/**-----------------------------------------------------------------------------
 * Direct3D �ʱ�ȭ
 *------------------------------------------------------------------------------
 */
HRESULT InitD3D( HWND hWnd )
{
    // ����̽��� �����ϱ����� D3D��ü ����
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // ����̽��� ������ ����ü
    // ������ ������Ʈ�� �׸����̱⶧����, �̹����� Z���۰� �ʿ��ϴ�.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    /// ����̽� ����
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // �⺻�ø�, CCW
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    // Z���۱���� �Ҵ�.
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 3, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	

    return S_OK;
}

/**-----------------------------------------------------------------------------
 * ��� ����
 *------------------------------------------------------------------------------
 */
void InitMatrix()
{
	/// ���� ��� ����
	D3DXMatrixIdentity( &g_matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matWorld );

    /// �� ����� ����
    D3DXVECTOR3 vEyePt( 0.0f, g_pSceneMgr->GetNodeMgr()->GetRadius(), -(g_pSceneMgr->GetNodeMgr()->GetRadius() * 2.0f) );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView );

    /// ���� �������� ���
	D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 5000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &g_matProj );

	/// �������� �ø��� �������� ���
    D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 200.0f );

	/// ī�޶� �ʱ�ȭ
	g_pCamera->SetView( &vEyePt, &vLookatPt, &vUpVec );
}

/**-----------------------------------------------------------------------------
 * �������� �ʱ�ȭ
 *------------------------------------------------------------------------------
 */
HRESULT InitGeometry()
{
	// ������ ���콺 ��ġ ����
	POINT	pt;
	GetCursorPos( &pt );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
	g_xRot = 0.0f;
	g_yRot = 0.0f;
	InitMatrix();

	return S_OK;
}

HRESULT LoadXML( char* fname )
{

	S_DEL( g_pSceneMgr );
	g_pSceneMgr = new ZSceneMgr();
	
	g_pSceneMgr->Open( g_pd3dDevice, fname, DEF_SKINMETHOD );

	g_bWireframe = FALSE;	// ���̾����������� �׸����ΰ�?
	g_bAnimate = TRUE;
	g_nDrawMode = 2;		// 0 = all, 1 = bone, 2 = mesh
	g_bBBox = FALSE;
	g_bLight = TRUE;
	
	InitGeometry();

	return S_OK;
}

HRESULT InitObjects( char* fname )
{
	S_DEL( g_pCamera );
	S_DEL( g_pLog );

	g_pCamera = new ZCamera;			// ī�޶� �ʱ�ȭ
	g_pLog = new ZFLog( ZF_LOG_TARGET_CONSOLE );	// �α밴ü �ʱ�ȭ

	return LoadXML( fname );
}

void DeleteObjects()
{
	/// ��ϵ� Ŭ���� �Ұ�
	S_DEL( g_pSceneMgr );
	S_DEL( g_pCamera );
	S_DEL( g_pLog );
}

/**-----------------------------------------------------------------------------
 * �ʱ�ȭ ��ü�� �Ұ�
 *------------------------------------------------------------------------------
 */
VOID Cleanup()
{
    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();
}


/**-----------------------------------------------------------------------------
 * ���� ����
 *------------------------------------------------------------------------------
 */
VOID SetupLights()
{
	/// ���� ����
	if( g_bLight )
	{
		D3DXVECTOR3 vecDir;									/// ���⼺ ����(directional light)�� ���� ���� ����
		D3DLIGHT9 light;									/// ���� ����ü
		ZeroMemory( &light, sizeof(D3DLIGHT9) );			/// ����ü�� 0���� �����.
		light.Type       = D3DLIGHT_DIRECTIONAL;			/// ������ ����(�� ����,���⼺ ����,����Ʈ����Ʈ)
		light.Diffuse.r  = 1.0f;							/// ������ ����� ���
		light.Diffuse.g  = 1.0f;
		light.Diffuse.b  = 1.0f;
		vecDir = D3DXVECTOR3( 0, 0, 1 );
		D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );	/// ������ ������ �������ͷ� �����.
		light.Range       = 1000.0f;									/// ������ �ٴٸ��� �ִ� �ִ�Ÿ�
		g_pd3dDevice->SetLight( 0, &light );							/// ����̽��� 0�� ���� ��ġ
		g_pd3dDevice->LightEnable( 0, TRUE );							/// 0�� ������ �Ҵ�
		g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			/// ���������� �Ҵ�
		g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00a0a0a0 );		/// ȯ�汤��(ambient light)�� �� ����
	}
	else
	{
		g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
		g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00ffffff );		/// ȯ�汤��(ambient light)�� �� ����
	}
}
/**-----------------------------------------------------------------------------
 * Status���� ���
 *------------------------------------------------------------------------------
 */
void LogStatus( void )
{
	g_pLog->Log( "FillMode:%s", g_bWireframe ? "wireframe" : "Solid");
	g_pLog->Log( "Animation:%s", g_bAnimate ? "On" : "Off" );
	g_pLog->Log( "DrawMode:%s", g_nDrawMode == 0 ? "All" : g_nDrawMode == 1 ? "Bone" : "Mesh" );
	g_pLog->Log( "BoundingBox:%s", g_bBBox ? "On" : "Off" );
}


/**-----------------------------------------------------------------------------
 * FPS(Frame Per Second)���
 *------------------------------------------------------------------------------
 */
void LogFPS(void)
{
	static DWORD	nTick = 0;
	static DWORD	nFPS = 0;

	/// 1�ʰ� �����°�?
	if( GetTickCount() - nTick > 1000 )
	{
		nTick = GetTickCount();
		/// FPS�� ���
		g_pLog->Log("FPS:%d", nFPS );

		nFPS = 0;
		LogStatus();	/// ���������� ���⼭ ���(1�ʿ� �ѹ�)
		return;
	}
	nFPS++;
}


/**-----------------------------------------------------------------------------
 * ���콺 �Է� ó��
 *------------------------------------------------------------------------------
 */
void ProcessMouse( void )
{
	POINT	pt;
	float	fDelta = 0.001f;	// ���콺�� �ΰ���, �� ���� Ŀ������ ���� �����δ�.

	GetCursorPos( &pt );
	int dx = pt.x - g_dwMouseX;	// ���콺�� ��ȭ��
	int dy = pt.y - g_dwMouseY;	// ���콺�� ��ȭ��

	g_pCamera->RotateLocalX( dy * fDelta );	// ���콺�� Y�� ȸ������ 3D world��  X�� ȸ����
	g_pCamera->RotateLocalY( dx * fDelta );	// ���콺�� X�� ȸ������ 3D world��  Y�� ȸ����
	D3DXMATRIXA16*	pmatView = g_pCamera->GetViewMatrix();		// ī�޶� ����� ��´�.
	g_pd3dDevice->SetTransform( D3DTS_VIEW, pmatView );			// ī�޶� ��� ����


	// ���콺�� �������� �߾����� �ʱ�ȭ
//	SetCursor( NULL );	// ���콺�� ��Ÿ���� �ʰ� �ʴ�.
	RECT	rc;
	GetClientRect( g_hwnd, &rc );
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen( g_hwnd, &pt );
	SetCursorPos( pt.x, pt.y );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
}

/**-----------------------------------------------------------------------------
 * Ű���� �Է� ó��
 *------------------------------------------------------------------------------
 */
void ProcessKey( void )
{
	if( GetAsyncKeyState( 'A' ) ) g_pCamera->MoveLocalZ( 0.5f );	// ī�޶� ����!
	if( GetAsyncKeyState( 'Z' ) ) g_pCamera->MoveLocalZ( -0.5f );	// ī�޶� ����!
}

/**-----------------------------------------------------------------------------
 * �Է� ó��
 *------------------------------------------------------------------------------
 */
void ProcessInputs( void )
{
	ProcessMouse();
	ProcessKey();
}

/**-----------------------------------------------------------------------------
 * �ִϸ��̼� ����
 *------------------------------------------------------------------------------
 */
VOID Animate()
{
	D3DXMATRIXA16	matTM;
	D3DXMATRIXA16	matX;
	D3DXMATRIXA16	matY;

	ZTObjectInfo*	pInfo = g_pSceneMgr->GetNodeMgr()->GetInfo();

	SetupLights();					// ��������
	ProcessInputs();				// �Է�ó��
	D3DXMatrixRotationX( &matX, g_xRot );
	D3DXMatrixRotationY( &matY, g_yRot );
	matTM = matX * matY;
//	D3DXMatrixScaling( &matTM, 0.1f, 0.1f, 0.1f );
	g_pSceneMgr->GetNodeMgr()->SetTM( &matTM );
	g_pSceneMgr->SetFrame( g_fFrames );
	if( g_bAnimate )
	{
		g_fFrames += 1.0f;
		if( g_fFrames > pInfo->fAnimationEnd ) g_fFrames = pInfo->fAnimationStart;
	}

	LogFPS();						// �α�
}


/**-----------------------------------------------------------------------------
 * ȭ�� �׸���
 *------------------------------------------------------------------------------
 */
VOID Render()
{
    /// �ĸ���ۿ� Z���� �ʱ�ȭ
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200,200,200), 1.0f, 0 );
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, g_bWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID );

	/// �ִϸ��̼� ��ļ���
	Animate();
    /// ������ ����
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
		if( g_nDrawMode != 4 )
		{
			g_pSceneMgr->Draw();		// ��� �׸���
		}
		
		if( g_bBBox )
			g_pSceneMgr->DrawBBox();	// ������ �׸���

		g_pd3dDevice->EndScene();
    }

    /// �ĸ���۸� ���̴� ȭ������!
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

void ChangeFolder( char* str )
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char path[128];

	_splitpath( str, drive, dir, fname, ext );
	strcpy( path, drive );
	strcat( path, dir);
	SetCurrentDirectory( path );
}



/**-----------------------------------------------------------------------------
 * ������ ���ν���
 *------------------------------------------------------------------------------
 */
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY :
            Cleanup();
            PostQuitMessage( 0 );
            return 0;

		case WM_RBUTTONDOWN :
		{
			TCHAR	str[512];

			g_bActive = FALSE;

			OPENFILENAME ofn = { sizeof(OPENFILENAME), 
								 hWnd, 
								 g_hInst,
								 "Mesh Files(*.xml)\0*.xml\0\0",
								 NULL, 
								 0, 
								 1, 
								 NULL, 
								 512, 
								 str, 
								 512,
								 NULL, 
								 "Open XML File", 
								 0 /*OFN_FILEMUSTEXIST*/, 
								 0, 
								 1,
								 ".xml", 
								 0, 
								 NULL, 
								 NULL,
								 NULL,
								 0,
								 0,
			};

			BOOL b = GetOpenFileName( &ofn );
			
			if( b )
			{

				LoadXML( str );
			}

			g_bActive = TRUE;
		}
			break;

		case WM_KEYDOWN : 
			switch( wParam )
			{
				case VK_ESCAPE :
					PostMessage( hWnd, WM_DESTROY, 0, 0L );
					break;
				case VK_LEFT : g_yRot -= 0.1f; break;
				case VK_RIGHT : g_yRot += 0.1f; break;
				case VK_UP : g_xRot -= 0.1f; break;
				case VK_DOWN : g_xRot += 0.1f; break;
				case '5' : 
					g_bLight = !g_bLight;
					break;
				case '1' :
					g_bWireframe = !g_bWireframe;
					break;
				case '2' :
					++g_nDrawMode;
					g_nDrawMode %= 3;
					break;
				case '3' :
					g_bBBox = !g_bBBox;
					break;
				case '4' :
					g_bAnimate = !g_bAnimate;
					break;
			}
			break;
			case WM_COPYDATA :
				{
					char	str[128];
					COPYDATASTRUCT *p;

					p = (COPYDATASTRUCT *)lParam;
					if( p->dwData == ID_COPYDATA )
					{
						memcpy( str, p->lpData, p->cbData );
						ChangeFolder( str );
						LoadXML( str );
					}
				}
				break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




/**-----------------------------------------------------------------------------
 * ���α׷� ������
 *------------------------------------------------------------------------------
 */
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR lpszCMD, INT )
{
	char	str[128];

	/// �̹� �� �������̸� �����Ѵ�.
	HWND h = FindWindow( WINDOW_CLASS, WINDOW_TITLE );
	if( h )
	{
		/// ���⼭ WM_COPYDATA�� ����ؼ� ���ο� ���ϸ��� ������.
		COPYDATASTRUCT cs;
		
		cs.dwData = ID_COPYDATA;
		cs.cbData = lstrlen( lpszCMD ) + 1;
		cs.lpData = lpszCMD;

		SendMessage( h, WM_COPYDATA, NULL, (LPARAM)&cs );

		return 0;
	}

    /// ������ Ŭ���� ���
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      hInst, NULL, NULL, NULL, NULL,
                      WINDOW_CLASS, NULL };
    RegisterClassEx( &wc );

    /// ������ ����
    HWND hWnd = CreateWindow( WINDOW_CLASS, WINDOW_TITLE,
                              WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_W, WINDOW_H,
                              NULL, NULL, hInst, NULL );

	g_hwnd = hWnd;
	g_hInst = hInst;

	if( lpszCMD[0] )
	{
		strcpy( str, lpszCMD );
		ChangeFolder( str );
	}
	else
		strcpy( str, FNAME_XML );

    /// Direct3D �ʱ�ȭ
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		if( SUCCEEDED( InitObjects( str ) ) )
		{
			if( SUCCEEDED( InitGeometry() ) )
			{

        		/// ������ ���
				ShowWindow( hWnd, SW_SHOWDEFAULT );
				UpdateWindow( hWnd );

        		/// �޽��� ����
				MSG msg;
				ZeroMemory( &msg, sizeof(msg) );
				while( msg.message!=WM_QUIT )
				{
            		/// �޽���ť�� �޽����� ������ �޽��� ó��
					if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
					{
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}
					else /// ó���� �޽����� ������ Render()�Լ� ȣ��
					{
						if( g_bActive ) Render();
					}
				}
			}
		}
    }

	DeleteObjects();
    UnregisterClass( WINDOW_CLASS, wc.hInstance );
    return 0;
}
