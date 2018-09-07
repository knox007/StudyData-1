/**-----------------------------------------------------------------------------
 * \brief 텍스처 투영
 * 파일: main.cpp
 *
 * 설명: 텍스처를 투영하는 것을 보여준다.
 *       
 *------------------------------------------------------------------------------
 */

#define MAINBODY

#include <d3d9.h>
#include <d3dx9.h>
#include "ZCamera.h"
#include "ZFrustum.h"
#include "ZFLog.h"

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	"Texture Projection Tutorial"

#define FNAME_MESH		"teapot2.x"
#define	SCALE_MESH		1.0f
#define POS_X_MESH		0.0f
#define POS_Y_MESH		30.0f
#define POS_Z_MESH		0.0f

/**-----------------------------------------------------------------------------
 *  전역변수
 *------------------------------------------------------------------------------
 */
HWND					g_hwnd = NULL;

LPDIRECT3D9             g_pD3D       = NULL; // D3D 디바이스를 생성할 D3D객체변수
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // 렌더링에 사용될 D3D디바이스
LPDIRECT3DVERTEXSHADER9	g_pVS = NULL;			/// 정점 쉐이더
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; /// 정점을 보관할 정점버퍼
LPDIRECT3DINDEXBUFFER9	g_pIB        = NULL; /// 인덱스를 보관할 인덱스버퍼
LPDIRECT3DTEXTURE9      g_pTexFloor  = NULL; /// 바닥 텍스처
LPDIRECT3DTEXTURE9      g_pTexProj   = NULL; /// 투영될 텍스처

LPDIRECT3DVERTEXDECLARATION9	g_pDecl = NULL;	/// 정점들 선언정보

D3DXMATRIXA16			g_matWorld;
D3DXMATRIXA16			g_matView;
D3DXMATRIXA16			g_matProj;
D3DXMATRIXA16			g_matTexProj;
D3DXMATRIXA16			g_matWorld2Light;
D3DXVECTOR3				g_vLightPos;

float					g_xRot = 0.0f;
float					g_yRot = 0.0f;
DWORD					g_dwMouseX = 0;			// 마우스의 좌표
DWORD					g_dwMouseY = 0;			// 마우스의 좌표
BOOL					g_bWireframe;			// 와이어프레임으로 그릴것인가?
BOOL					g_bFrustum = TRUE;
BOOL					g_bLight = TRUE;
BOOL					g_bActive = TRUE;

ZCamera*				g_pCamera = NULL;	// Camera 클래스
ZFrustum*				g_pFrustum = NULL;
LPD3DXMESH				g_pMesh = NULL;

/// 사용자 정점을 정의할 구조체
struct MYVERTEX
{
	enum { FVF = (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2) };
    float	px, py, pz;		/// 정점의 변환된 좌표
	float	nx, ny, nz;		/// 정점의 색깔
	float	tx, ty;		/// 텍스처 좌표
	float	sx, sy;		/// 텍스처 좌표
};

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

	D3DCAPS9 caps;
	DWORD dwVSProcess;
	// 디바이스의 능력값(caps)을 읽어온다
	g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

	// 지원하는 정점쉐이더 버전이 1.0이하라면 SW쉐이더를, 1.0이상이면 HW쉐이더를 생성한다.
	dwVSProcess = ( caps.VertexShaderVersion < D3DVS_VERSION(1,0) ) ? D3DCREATE_SOFTWARE_VERTEXPROCESSING : D3DCREATE_HARDWARE_VERTEXPROCESSING;

    /// 디바이스 생성
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      dwVSProcess, 
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // 기본컬링, CCW
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    // Z버퍼기능을 켠다.
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return S_OK;
}

/**-----------------------------------------------------------------------------
 * 정점버퍼를 생성하고 정점값을 채워넣는다.
 *------------------------------------------------------------------------------
 */
HRESULT InitVB()
{
	MYVERTEX Verts[4] = 
	{
		{ -100, 0, -100, 0, 1, 0, 0, 1, 0, 1 },
		{ -100, 0,  100, 0, 1, 0, 0, 0, 0, 1 },
		{  100, 0, -100, 0, 1, 0, 1, 1, 0, 1 },
		{  100, 0,  100, 0, 1, 0, 1, 0, 0, 1 }
	};

    /// 정점버퍼 생성
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( sizeof(Verts), 0, MYVERTEX::FVF, D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    /// 정점버퍼를 값으로 채운다. 
    VOID* pVertices;
    if( FAILED( g_pVB->Lock( 0, sizeof(Verts), (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, Verts, sizeof(Verts) );
    g_pVB->Unlock();


	return S_OK;
}

/**-----------------------------------------------------------------------------
 * 정점쉐이더를 읽는다.
 *------------------------------------------------------------------------------
 */
HRESULT InitVS()
{
	D3DVERTEXELEMENT9	decl[MAX_FVF_DECL_SIZE];
	// FVF를 사용해서 정점선언값을 자동으로 채워넣는다
	D3DXDeclaratorFromFVF( MYVERTEX::FVF, decl );
	// 정점선언값으로 g_pDecl을 생성한다.
	g_pd3dDevice->CreateVertexDeclaration( decl, &g_pDecl );
	LPD3DXBUFFER pCode;

	// simple.vs 파일을 읽어와서 정점쉐이더 인터페이스를 생성한다.
	if( FAILED( D3DXAssembleShaderFromFile( "shadow.vs", NULL, NULL, 0, &pCode, NULL ) ) )
		return E_FAIL;

	g_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &g_pVS);

	S_REL( pCode );

	return S_OK;
}

void InitTexture()
{
	D3DXCreateTextureFromFile( g_pd3dDevice, "panda.jpg", &g_pTexFloor );
	D3DXCreateTextureFromFile( g_pd3dDevice, "hiah.bmp", &g_pTexProj );
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
    D3DXVECTOR3 vEyePt( 0.0f, 100.0f, -(float)200.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView );

    /// 실제 프로젝션 행렬
	D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &g_matProj );

	/// 카메라 초기화
	g_pCamera->SetView( &vEyePt, &vLookatPt, &vUpVec );
}

/**-----------------------------------------------------------------------------
 * 기하정보 초기화
 *------------------------------------------------------------------------------
 */
HRESULT InitObjects()
{
	S_DEL( g_pCamera );
	S_DEL( g_pLog );

	g_pCamera = new ZCamera;			// 카메라 초기화
	g_pFrustum = new ZFrustum;
	g_pLog = new ZFLog( ZF_LOG_TARGET_WINDOW );	// 로깅객체 초기화

	LPD3DXMESH  pMesh = NULL;
    LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	DWORD dwNumMaterials;

    if( FAILED( D3DXLoadMeshFromX( FNAME_MESH, D3DXMESH_SYSTEMMEM,g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &dwNumMaterials, &pMesh ) ) )
		return E_FAIL;

	pMesh->CloneMeshFVF( D3DXMESH_SYSTEMMEM, MYVERTEX::FVF, g_pd3dDevice, &g_pMesh );
	S_REL( pMesh );

    S_REL( pD3DXMtrlBuffer );

	InitVB();
	InitVS();
	InitTexture();

	return S_OK;
}

void DeleteObjects()
{
	/// 등록된 클래스 소거
	S_DEL( g_pCamera );
	S_DEL( g_pFrustum );
	S_DEL( g_pLog );

	S_REL( g_pMesh );
}

HRESULT InitGeometry()
{
	InitMatrix();

	// 최초의 마우스 위치 보관
	POINT	pt;
	GetCursorPos( &pt );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
	g_xRot = 0.0f;
	g_yRot = 0.0f;
	return S_OK;
}


/**-----------------------------------------------------------------------------
 * 초기화 객체들 소거
 *------------------------------------------------------------------------------
 */
VOID Cleanup()
{
	S_REL( g_pVB );
	S_REL( g_pIB );
	S_REL( g_pVS );
	S_REL( g_pDecl );
	S_REL( g_pTexProj );
	S_REL( g_pTexFloor );
	S_REL( g_pd3dDevice );
	S_REL( g_pD3D );
}


/**-----------------------------------------------------------------------------
 * 광원 설정
 *------------------------------------------------------------------------------
 */
VOID SetupLights()
{
	g_vLightPos = D3DXVECTOR3( 100, 100, -100 );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );			/// 광원설정을 켠다
	g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00a0a0a0 );		/// 환경광원(ambient light)의 값 설정
	/// 광원 설정
	if( g_bLight )
	{
		D3DXMATRIXA16	m;
		D3DXMatrixRotationY( &m, GetTickCount() / 1000.0f );
		D3DXVec3TransformCoord( &g_vLightPos, &g_vLightPos, &m );
	}
}
/**-----------------------------------------------------------------------------
 * Status정보 출력
 *------------------------------------------------------------------------------
 */
void LogStatus( void )
{
	g_pLog->Log( "FillMode:%s", g_bWireframe ? "wireframe" : "Solid");
	g_pLog->Log( "Animation:%s", g_bLight ? "On" : "Off" );
	g_pLog->Log( "Eye:[%f,%f,%f]", g_pCamera->GetEye()->x, g_pCamera->GetEye()->y, g_pCamera->GetEye()->z ); 
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
	g_matView = *pmatView;

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
	D3DXMATRIXA16	matScale;
	SetupLights();					// 광원설정
	ProcessInputs();				// 입력처리

	D3DXMatrixRotationX( &matX, g_xRot );
	D3DXMatrixRotationY( &matY, g_yRot );
	D3DXMatrixScaling( &matScale, SCALE_MESH, SCALE_MESH, SCALE_MESH );
	g_matWorld = matScale * matX * matY;
	g_matWorld._41 = POS_X_MESH; g_matWorld._42 = POS_Y_MESH; g_matWorld._41 = POS_Z_MESH;

	D3DXMatrixLookAtLH( &g_matWorld2Light, &g_vLightPos, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
	D3DXMatrixPerspectiveFovLH( &g_matTexProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );

	D3DXMATRIXA16	mVP = g_matWorld2Light * g_matTexProj;
	g_pFrustum->Make( &mVP );
	LogFPS();						// 로깅
}

void SetupVSConst( D3DXMATRIXA16 &matWorld )
{
	D3DXMATRIXA16	m;

	/// 행렬의 값을 정점쉐이더 상수테이블에 셋팅(c0 ~ c7)
	m = g_matProj;
	D3DXMatrixTranspose( &m, &m );
	g_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&m, 4 );	// matWorld

	m = matWorld * g_matView;
	D3DXMatrixTranspose( &m, &m );
	g_pd3dDevice->SetVertexShaderConstantF( 4, (float*)&m, 3 );	// matProj

	m = matWorld * g_matWorld2Light * g_matTexProj;
	D3DXMatrixTranspose( &m, &m );
	g_pd3dDevice->SetVertexShaderConstantF( 7, (float*)&m, 3 ); // matView
}

void DrawFloor()
{
	D3DXMATRIXA16	matWorld;

	g_matTexProj._11 = 2.0f/100;
	g_matTexProj._22 = 2.0f/100;
	D3DXMatrixIdentity( &matWorld );
	SetupVSConst( matWorld );

	g_pd3dDevice->SetTexture( 0, g_pTexFloor );
	g_pd3dDevice->SetTexture( 1, g_pTexProj );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );

	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

	g_pd3dDevice->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
	g_pd3dDevice->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );

	g_pd3dDevice->SetVertexDeclaration( g_pDecl );
	g_pd3dDevice->SetVertexShader( g_pVS );
	g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(MYVERTEX) );
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
	g_pd3dDevice->SetVertexShader( NULL );
}

void DrawMesh()
{
	D3DXMATRIXA16	matWorld;

	D3DXMatrixIdentity( &matWorld );
	g_matTexProj._11 = 2.0f/100;
	g_matTexProj._22 = 2.0f/100;
	SetupVSConst( g_matWorld );

	g_pd3dDevice->SetTexture( 0, NULL );
	g_pd3dDevice->SetTexture( 1, g_pTexProj );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );

	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
	g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

	g_pd3dDevice->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );
	g_pd3dDevice->SetTextureStageState( 2, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );

	g_pd3dDevice->SetVertexDeclaration( g_pDecl );
	g_pd3dDevice->SetVertexShader( g_pVS );
	g_pMesh->DrawSubset( 0 );
	g_pd3dDevice->SetVertexShader( NULL );
}

void DrawTexture()
{
	struct VTX
	{
		enum { FVF=D3DFVF_XYZRHW|D3DFVF_TEX1 };
		float px, py, pz, pw;
		float tx, ty;
	};
	VTX vtx[4] =
	{
		{   0, 127, 0, 1, 0, 1 },
		{   0,   0, 0, 1, 0, 0 },
		{ 127, 127, 0, 1, 1, 1 },
		{ 127,   0, 0, 1, 1, 0 }
	};
	g_pd3dDevice->SetTexture( 0, g_pTexProj );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	g_pd3dDevice->SetFVF( VTX::FVF );
	g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(VTX) );
	g_pd3dDevice->SetTexture( 0, NULL );
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
		DrawTexture();

		DrawFloor();
		DrawMesh();
		if( g_bFrustum ) g_pFrustum->Draw( g_pd3dDevice );

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
				case '1' :
					g_bWireframe = !g_bWireframe;
					break;
				case '2' :
					g_bLight = !g_bLight;
					break;
				case '3' : 
					g_bFrustum= !g_bFrustum;
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
