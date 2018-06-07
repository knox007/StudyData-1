/**-----------------------------------------------------------------------------
 * \brief 캐릭터 애니메이션
 * 파일: main.cpp
 *
 * 설명: XML데이터를 화면에 출력해준다.
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
#include "ZNodeMgr.h"

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	"XML viewer"
#define FNAME_XML		"cylinder.xml"

// 스키닝을 Software방식으로 
#define DEF_SKINMETHOD	ZNodeMgr::SKINMETHOD_SW

// 스키닝을 Fixed Function방식으로 
//#define DEF_SKINMETHOD	ZNodeMgr::SKINMETHOD_FF

/**-----------------------------------------------------------------------------
 *  전역변수
 *------------------------------------------------------------------------------
 */
HWND					g_hwnd = NULL;

LPDIRECT3D9             g_pD3D       = NULL; // D3D 디바이스를 생성할 D3D객체변수
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // 렌더링에 사용될 D3D디바이스

D3DXMATRIXA16			g_matWorld;
D3DXMATRIXA16			g_matView;
D3DXMATRIXA16			g_matProj;

float					g_xRot = 0.0f;
float					g_yRot = 0.0f;
DWORD					g_dwMouseX = 0;			// 마우스의 좌표
DWORD					g_dwMouseY = 0;			// 마우스의 좌표
BOOL					g_bWireframe = FALSE;	// 와이어프레임으로 그릴것인가?
BOOL					g_bAnimate = FALSE;
int						g_nDrawMode = 2;		// 0 = all, 1 = bone, 2 = mesh
BOOL					g_bBBox = FALSE;
BOOL					g_bActive = TRUE;
BOOL					g_bLight = FALSE;

float					g_fFrames = 0.0f;

ZCamera*				g_pCamera = NULL;	// Camera 클래스
ZNodeMgr*				g_pNodeMgr = NULL;	// 노드를 관리하는 Node Manager클래스

/**-----------------------------------------------------------------------------
 * Direct3D 초기화
 *------------------------------------------------------------------------------
 */
HRESULT InitD3D( HWND hWnd )
{
    // 디바이스를 생성하기위한 D3D객체 생성
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // 디바이스를 생성할 구조체
    // 복잡한 오브젝트를 그릴것이기때문에, 이번에는 Z버퍼가 필요하다.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    /// 디바이스 생성
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // 기본컬링, CCW
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    // Z버퍼기능을 켠다.
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
 * 행렬 설정
 *------------------------------------------------------------------------------
 */
void InitMatrix()
{
	/// 월드 행렬 설정
	D3DXMatrixIdentity( &g_matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matWorld );

    /// 뷰 행렬을 설정
    D3DXVECTOR3 vEyePt( 0.0f, g_pNodeMgr->GetRadius(), -(g_pNodeMgr->GetRadius() * 2.0f) );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView );

    /// 실제 프로젝션 행렬
	D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 5000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &g_matProj );

	/// 프러스텀 컬링용 프로젝션 행렬
    D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 200.0f );

	/// 카메라 초기화
	g_pCamera->SetView( &vEyePt, &vLookatPt, &vUpVec );
}

/**-----------------------------------------------------------------------------
 * 기하정보 초기화
 *------------------------------------------------------------------------------
 */
HRESULT InitGeometry()
{
	// 최초의 마우스 위치 보관
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
	ZCParser*		pParser = NULL;		// 파서객체
	ZCParsedData*	pData = NULL;		// 파싱데이터 객체

	pParser = new ZCParser();			// 파서 초기화
	pData = new ZCParsedData();			// 파싱데이터 초기화
	if( !pParser->Parse( pData, fname ) ) return E_FAIL;	// 파서 작동!

	list<ZCMesh*>::iterator		it;	// STL반복자 선언
	for( it = pData->m_meshList.begin() ; it != pData->m_meshList.end() ; it++ )
	{
		g_pLog->Log( "-------------------------------------" );
		g_pLog->Log( "ID:[%d,%s]", (*it)->m_nObjectID, pData->m_info.strObjectNameTable[(*it)->m_nObjectID].c_str() );
		g_pLog->Log( "Parent:[%d,%s]", (*it)->m_nParentID, (*it)->m_nParentID == -1 ? "undefined" : pData->m_info.strObjectNameTable[(*it)->m_nParentID].c_str() );
		g_pLog->Log( "Vertex:[%d]", (*it)->m_vertex.size() );
		g_pLog->Log( "Index:[%d]", (*it)->m_triindex.size() );
		g_pLog->Log( "MergedVertex:[%d]", (*it)->m_vtxFinal.size() );
		g_pLog->Log( "Skin:[%s]", (*it)->m_isSkinned ? "true" : "false" );
		g_pLog->Log( "-------------------------------------" );
	}

	S_DEL( g_pNodeMgr );
	g_pNodeMgr = new ZNodeMgr( g_pd3dDevice, pData, DEF_SKINMETHOD );	//노드 매니저 생성

	g_fFrames = g_pNodeMgr->GetInfo()->fAnimationStart;

	S_DEL( pData );		// 파서객체 삭제
	S_DEL( pParser );	// 파싱데이터 객체 삭제

	g_bWireframe = FALSE;	// 와이어프레임으로 그릴것인가?
	g_bAnimate = FALSE;
	g_nDrawMode = 2;		// 0 = all, 1 = bone, 2 = mesh
	g_bBBox = FALSE;
	g_bLight = FALSE;
	InitGeometry();

	return S_OK;
}

HRESULT InitObjects()
{
	S_DEL( g_pCamera );
	S_DEL( g_pLog );

	g_pCamera = new ZCamera;			// 카메라 초기화
	g_pLog = new ZFLog( ZF_LOG_TARGET_WINDOW );	// 로깅객체 초기화

	return LoadXML( FNAME_XML );
}

void DeleteObjects()
{
	/// 등록된 클래스 소거
	S_DEL( g_pNodeMgr );
	S_DEL( g_pCamera );
	S_DEL( g_pLog );
}

/**-----------------------------------------------------------------------------
 * 초기화 객체들 소거
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
 * 광원 설정
 *------------------------------------------------------------------------------
 */
VOID SetupLights()
{
	/// 광원 설정
	if( g_bLight )
	{
		D3DXVECTOR3 vecDir;									/// 방향성 광원(directional light)이 향할 빛의 방향
		D3DLIGHT9 light;									/// 광원 구조체
		ZeroMemory( &light, sizeof(D3DLIGHT9) );			/// 구조체를 0으로 지운다.
		light.Type       = D3DLIGHT_DIRECTIONAL;			/// 광원의 종류(점 광원,방향성 광원,스포트라이트)
		light.Diffuse.r  = 1.0f;							/// 광원의 색깔과 밝기
		light.Diffuse.g  = 1.0f;
		light.Diffuse.b  = 1.0f;
		vecDir = D3DXVECTOR3( 0, 0, 1 );
		D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );	/// 광원의 방향을 단위벡터로 만든다.
		light.Range       = 1000.0f;									/// 광원이 다다를수 있는 최대거리
		g_pd3dDevice->SetLight( 0, &light );							/// 디바이스에 0번 광원 설치
		g_pd3dDevice->LightEnable( 0, TRUE );							/// 0번 광원을 켠다
		g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			/// 광원설정을 켠다
		g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00a0a0a0 );		/// 환경광원(ambient light)의 값 설정
	}
	else
	{
		g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
		g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00ffffff );		/// 환경광원(ambient light)의 값 설정
	}
}
/**-----------------------------------------------------------------------------
 * Status정보 출력
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
 * FPS(Frame Per Second)출력
 *------------------------------------------------------------------------------
 */
void LogFPS(void)
{
	static DWORD	nTick = 0;
	static DWORD	nFPS = 0;

	/// 1초가 지났는가?
	if( GetTickCount() - nTick > 1000 )
	{
		nTick = GetTickCount();
		/// FPS값 출력
		g_pLog->Log("FPS:%d", nFPS );

		nFPS = 0;
		LogStatus();	/// 상태정보를 여기서 출력(1초에 한번)
		return;
	}
	nFPS++;
}


/**-----------------------------------------------------------------------------
 * 마우스 입력 처리
 *------------------------------------------------------------------------------
 */
void ProcessMouse( void )
{
	POINT	pt;
	float	fDelta = 0.001f;	// 마우스의 민감도, 이 값이 커질수록 많이 움직인다.

	GetCursorPos( &pt );
	int dx = pt.x - g_dwMouseX;	// 마우스의 변화값
	int dy = pt.y - g_dwMouseY;	// 마우스의 변화값

	g_pCamera->RotateLocalX( dy * fDelta );	// 마우스의 Y축 회전값은 3D world의  X축 회전값
	g_pCamera->RotateLocalY( dx * fDelta );	// 마우스의 X축 회전값은 3D world의  Y축 회전값
	D3DXMATRIXA16*	pmatView = g_pCamera->GetViewMatrix();		// 카메라 행렬을 얻는다.
	g_pd3dDevice->SetTransform( D3DTS_VIEW, pmatView );			// 카메라 행렬 셋팅


	// 마우스를 윈도우의 중앙으로 초기화
//	SetCursor( NULL );	// 마우스를 나타나지 않게 않다.
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
 * 키보드 입력 처리
 *------------------------------------------------------------------------------
 */
void ProcessKey( void )
{
	if( GetAsyncKeyState( 'A' ) ) g_pCamera->MoveLocalZ( 0.5f );	// 카메라 전진!
	if( GetAsyncKeyState( 'Z' ) ) g_pCamera->MoveLocalZ( -0.5f );	// 카메라 후진!
}

/**-----------------------------------------------------------------------------
 * 입력 처리
 *------------------------------------------------------------------------------
 */
void ProcessInputs( void )
{
	ProcessMouse();
	ProcessKey();
}

/**-----------------------------------------------------------------------------
 * 애니메이션 설정
 *------------------------------------------------------------------------------
 */
VOID Animate()
{
	D3DXMATRIXA16	matTM;
	D3DXMATRIXA16	matX;
	D3DXMATRIXA16	matY;

	ZObjectInfo*	pInfo = g_pNodeMgr->GetInfo();

	SetupLights();					// 광원설정
	ProcessInputs();				// 입력처리
	D3DXMatrixRotationX( &matX, g_xRot );
	D3DXMatrixRotationY( &matY, g_yRot );
	matTM = matX * matY;
//	D3DXMatrixScaling( &matTM, 0.1f, 0.1f, 0.1f );
	g_pNodeMgr->SetTM( &matTM );
	g_pNodeMgr->Animate( g_fFrames );		// 노드 애니메이션 시키기
	if( g_bAnimate )
	{
		g_fFrames += 1.0f;
		if( g_fFrames > pInfo->fAnimationEnd ) g_fFrames = pInfo->fAnimationStart;
	}

	LogFPS();						// 로깅
}


/**-----------------------------------------------------------------------------
 * 화면 그리기
 *------------------------------------------------------------------------------
 */
VOID Render()
{
    /// 후면버퍼와 Z버퍼 초기화
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200,200,200), 1.0f, 0 );
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, g_bWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID );

	/// 애니메이션 행렬설정
	Animate();
    /// 렌더링 시작
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
		if( g_nDrawMode != 4 )
		{
			g_pNodeMgr->Draw( g_nDrawMode );		// 노드 그리기
		}
		
		if( g_bBBox )
			g_pNodeMgr->DrawBBox( g_nDrawMode );	// 경계상자 그리기

		g_pd3dDevice->EndScene();
    }

    /// 후면버퍼를 보이는 화면으로!
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




/**-----------------------------------------------------------------------------
 * 윈도우 프로시져
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
			g_bActive = FALSE;

			char	str[512];
			OPENFILENAME ofn = { sizeof(OPENFILENAME), hWnd, NULL,
								 "Mesh Files(*.xml)\0*.xml\0\0",
								 NULL, 0, 1, NULL, 512, str, 512,
								 NULL, "Open XML File", OFN_FILEMUSTEXIST, 0, 1,
								 ".xml", 0, NULL, NULL };

			if( GetOpenFileName( &ofn ) )
				LoadXML( str );

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
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




/**-----------------------------------------------------------------------------
 * 프로그램 시작점
 *------------------------------------------------------------------------------
 */
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    /// 윈도우 클래스 등록
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "BasicFrame", NULL };
    RegisterClassEx( &wc );

    /// 윈도우 생성
    HWND hWnd = CreateWindow( "BasicFrame", WINDOW_TITLE,
                              WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_W, WINDOW_H,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

	g_hwnd = hWnd;

    /// Direct3D 초기화
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		if( SUCCEEDED( InitObjects() ) )
		{
			if( SUCCEEDED( InitGeometry() ) )
			{

        		/// 윈도우 출력
				ShowWindow( hWnd, SW_SHOWDEFAULT );
				UpdateWindow( hWnd );

        		/// 메시지 루프
				MSG msg;
				ZeroMemory( &msg, sizeof(msg) );
				while( msg.message!=WM_QUIT )
				{
            		/// 메시지큐에 메시지가 있으면 메시지 처리
					if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
					{
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}
					else /// 처리할 메시지가 없으면 Render()함수 호출
					{
						if( g_bActive ) Render();
					}
				}
			}
		}
    }

	DeleteObjects();
    UnregisterClass( "BasicFrame", wc.hInstance );
    return 0;
}
