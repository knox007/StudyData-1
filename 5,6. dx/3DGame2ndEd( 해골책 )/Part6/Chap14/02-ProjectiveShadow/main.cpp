/**-----------------------------------------------------------------------------
 * \brief ���� �׸��� ó��
 * ����: main.cpp
 *
 * ����: ���� �׸��ڸ� ȭ�鿡 ����ϴ� ���
 *       
 *------------------------------------------------------------------------------
 */

#define MAINBODY

#include <d3d9.h>
#include <d3dx9.h>
#include "ZCamera.h"
#include "ZFrustum.h"
#include "ZFLog.h"

#define FNAME_MESH		"teapot2.x"
#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	"Texture Projection Tutorial"

/**-----------------------------------------------------------------------------
 *  ��������
 *------------------------------------------------------------------------------
 */
HWND					g_hwnd = NULL;

LPDIRECT3D9             g_pD3D       = NULL; // D3D ����̽��� ������ D3D��ü����
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // �������� ���� D3D����̽�
LPDIRECT3DVERTEXSHADER9	g_pVS = NULL;			/// ���� ���̴�
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; /// ������ ������ ��������
LPDIRECT3DINDEXBUFFER9	g_pIB        = NULL; /// �ε����� ������ �ε�������
LPDIRECT3DTEXTURE9      g_pTexFloor  = NULL; /// �ٴ� �ؽ�ó
LPDIRECT3DTEXTURE9      g_pTexProj   = NULL; /// ������ �ؽ�ó
LPDIRECT3DSURFACE9      g_pSurProj   = NULL; /// ������ �ؽ�ó�� ���ǽ�

LPDIRECT3DVERTEXDECLARATION9	g_pDecl = NULL;	/// ������ ��������

D3DXMATRIXA16			g_matWorld;
D3DXMATRIXA16			g_matView;
D3DXMATRIXA16			g_matProj;
D3DXMATRIXA16			g_matTexProj;
D3DXMATRIXA16			g_matWorld2Light;
D3DXVECTOR3				g_vLightPos;

float					g_xRot = 0.0f;
float					g_yRot = 0.0f;
DWORD					g_dwMouseX = 0;			// ���콺�� ��ǥ
DWORD					g_dwMouseY = 0;			// ���콺�� ��ǥ
BOOL					g_bWireframe;			// ���̾����������� �׸����ΰ�?
BOOL					g_bFrustum = TRUE;
BOOL					g_bLight = TRUE;
BOOL					g_bActive = TRUE;

ZCamera*				g_pCamera = NULL;	// Camera Ŭ����
ZFrustum*				g_pFrustum = NULL;
LPD3DXMESH				g_pMesh = NULL;

/// ����� ������ ������ ����ü
struct MYVERTEX
{
	enum { FVF = (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2) };
    float	px, py, pz;		/// ������ ��ȯ�� ��ǥ
	float	nx, ny, nz;		/// ������ ����
	float	tx, ty;		/// �ؽ�ó ��ǥ
	float	sx, sy;		/// �ؽ�ó ��ǥ
};

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

	D3DCAPS9 caps;
	DWORD dwVSProcess;
	// ����̽��� �ɷ°�(caps)�� �о�´�
	g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

	// �����ϴ� �������̴� ������ 1.0���϶�� SW���̴���, 1.0�̻��̸� HW���̴��� �����Ѵ�.
	dwVSProcess = ( caps.VertexShaderVersion < D3DVS_VERSION(1,0) ) ? D3DCREATE_SOFTWARE_VERTEXPROCESSING : D3DCREATE_HARDWARE_VERTEXPROCESSING;

    /// ����̽� ����
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      dwVSProcess, 
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // �⺻�ø�, CCW
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    // Z���۱���� �Ҵ�.
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return S_OK;
}

/**-----------------------------------------------------------------------------
 * �������۸� �����ϰ� �������� ä���ִ´�.
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

    /// �������� ����
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( sizeof(Verts), 0, MYVERTEX::FVF, D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    /// �������۸� ������ ä���. 
    VOID* pVertices;
    if( FAILED( g_pVB->Lock( 0, sizeof(Verts), (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, Verts, sizeof(Verts) );
    g_pVB->Unlock();


	return S_OK;
}

/**-----------------------------------------------------------------------------
 * �������̴��� �д´�.
 *------------------------------------------------------------------------------
 */
HRESULT InitVS()
{
	D3DVERTEXELEMENT9	decl[MAX_FVF_DECL_SIZE];
	// FVF�� ����ؼ� ���������� �ڵ����� ä���ִ´�
	D3DXDeclaratorFromFVF( MYVERTEX::FVF, decl );
	// ������������ g_pDecl�� �����Ѵ�.
	g_pd3dDevice->CreateVertexDeclaration( decl, &g_pDecl );
	LPD3DXBUFFER pCode;

	// simple.vs ������ �о�ͼ� �������̴� �������̽��� �����Ѵ�.
	if( FAILED( D3DXAssembleShaderFromFile( "shadow.vs", NULL, NULL, 0, &pCode, NULL ) ) )
		return E_FAIL;

	g_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &g_pVS);

	S_REL( pCode );

	return S_OK;
}

void InitTexture()
{
    D3DDISPLAYMODE d3ddm;
    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	D3DXCreateTextureFromFile( g_pd3dDevice, "panda.jpg", &g_pTexFloor );
//	D3DXCreateTextureFromFile( g_pd3dDevice, "hiah.bmp", &g_pTexProj );

	D3DXCreateTexture(g_pd3dDevice, 128, 128, 0, D3DUSAGE_RENDERTARGET, d3ddm.Format, D3DPOOL_DEFAULT, &g_pTexProj );
	g_pTexProj->GetSurfaceLevel( 0, &g_pSurProj );
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
    D3DXVECTOR3 vEyePt( 0.0f, 200.0f, -(float)300.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView );

    /// ���� �������� ���
	D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &g_matProj );

	/// ī�޶� �ʱ�ȭ
	g_pCamera->SetView( &vEyePt, &vLookatPt, &vUpVec );
}

/**-----------------------------------------------------------------------------
 * �������� �ʱ�ȭ
 *------------------------------------------------------------------------------
 */
HRESULT InitObjects()
{
	S_DEL( g_pCamera );
	S_DEL( g_pLog );

	g_pCamera = new ZCamera;			// ī�޶� �ʱ�ȭ
	g_pFrustum = new ZFrustum;
	g_pLog = new ZFLog( ZF_LOG_TARGET_WINDOW );	// �α밴ü �ʱ�ȭ
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
	/// ��ϵ� Ŭ���� �Ұ�
	S_DEL( g_pCamera );
	S_DEL( g_pFrustum );
	S_DEL( g_pLog );

	S_REL( g_pMesh );}

HRESULT InitGeometry()
{
	InitMatrix();

	// ������ ���콺 ��ġ ����
	POINT	pt;
	GetCursorPos( &pt );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
	g_xRot = 0.0f;
	g_yRot = 0.0f;
	return S_OK;
}


/**-----------------------------------------------------------------------------
 * �ʱ�ȭ ��ü�� �Ұ�
 *------------------------------------------------------------------------------
 */
VOID Cleanup()
{
	S_REL( g_pVB );
	S_REL( g_pIB );
	S_REL( g_pVS );
	S_REL( g_pDecl );
	S_REL( g_pSurProj );
	S_REL( g_pTexProj );
	S_REL( g_pTexFloor );
	S_REL( g_pd3dDevice );
	S_REL( g_pD3D );
}


/**-----------------------------------------------------------------------------
 * ���� ����
 *------------------------------------------------------------------------------
 */
VOID SetupLights()
{
    D3DMATERIAL9 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
    g_pd3dDevice->SetMaterial( &mtrl );

	D3DLIGHT9	l;
    ZeroMemory( &l, sizeof(l) );
	l.Type      = D3DLIGHT_POINT;
    l.Diffuse.r = 0.6f;
    l.Diffuse.g = 0.6f;
    l.Diffuse.b = 0.6f;
    l.Range        = 300.0f;
//    l.Attenuation1 = 0.4f;

	g_vLightPos = D3DXVECTOR3( 100, 100, -100 );

	// ������ ȸ����ų���ΰ�?
	if( g_bLight )
	{
		D3DXMATRIXA16	m;
		D3DXMatrixRotationY( &m, GetTickCount() / 1000.0f );
		D3DXVec3TransformCoord( &g_vLightPos, &g_vLightPos, &m );
	}

    l.Position     = g_vLightPos;
	g_pd3dDevice->SetLight( 0, &l );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
	g_pd3dDevice->LightEnable( 0, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING , TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00a0a0a0 );		/// ȯ�汤��(ambient light)�� �� ����
}
/**-----------------------------------------------------------------------------
 * Status���� ���
 *------------------------------------------------------------------------------
 */
void LogStatus( void )
{
	g_pLog->Log( "FillMode:%s", g_bWireframe ? "wireframe" : "Solid");
	g_pLog->Log( "Animation:%s", g_bLight ? "On" : "Off" );
	g_pLog->Log( "Eye:[%f,%f,%f]", g_pCamera->GetEye()->x, g_pCamera->GetEye()->y, g_pCamera->GetEye()->z ); 
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
	g_matView = *pmatView;

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
	D3DXMATRIXA16	matScale;
	SetupLights();					// ��������
	ProcessInputs();				// �Է�ó��

	D3DXMatrixRotationX( &matX, g_xRot );
	D3DXMatrixRotationY( &matY, g_yRot );
	D3DXMatrixScaling( &matScale, 1, 1, 1 );
	g_matWorld = matScale * matX * matY;
	g_matWorld._41 = 0; g_matWorld._42 = 20; g_matWorld._43 = 0;

	D3DXMatrixLookAtLH( &g_matWorld2Light, &g_vLightPos, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
	D3DXMatrixPerspectiveFovLH( &g_matTexProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );

	D3DXMATRIXA16	mVP = g_matWorld2Light * g_matTexProj;
	g_pFrustum->Make( &mVP );
	LogFPS();						// �α�
}

void SetupVSConst( D3DXMATRIXA16 &matWorld )
{
	D3DXMATRIXA16	m;

	m = g_matProj;
	D3DXMatrixTranspose( &m, &m );
	g_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&m, 4 );	// Proj

	m = matWorld * g_matView;
	D3DXMatrixTranspose( &m, &m );
	g_pd3dDevice->SetVertexShaderConstantF( 4, (float*)&m, 3 );	// World * View

	m = matWorld * g_matWorld2Light * g_matTexProj;
	D3DXMatrixTranspose( &m, &m );
	g_pd3dDevice->SetVertexShaderConstantF( 7, (float*)&m, 3 ); // World * World-to-Light * Texture Proejction
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
	D3DXMATRIXA16	m;
	D3DXMatrixIdentity( &m );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matWorld );

	g_pd3dDevice->SetTexture( 0, NULL );
	g_pd3dDevice->SetTexture( 1, NULL );

	g_pMesh->DrawSubset( 0 );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &m );
}

void GenerateTexture()
{
	LPDIRECT3DSURFACE9	p = NULL;
	g_pd3dDevice->GetRenderTarget( 0, &p );
	g_pd3dDevice->SetRenderTarget( 0, g_pSurProj );

	g_pd3dDevice->BeginScene();
	D3DXMATRIXA16	matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 500.0f );
	matProj.m[0][0] = 2.5;
	matProj.m[1][1] = 2.5;

    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	// TEXTUREFACTOR������ ������
	g_pd3dDevice->SetTexture( 0,NULL );
	g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(0,128,128,128) );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matWorld );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matWorld2Light );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	g_pMesh->DrawSubset( 0 );
	D3DXMatrixIdentity( &matProj );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matProj );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &g_matProj );

	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->EndScene();

	g_pd3dDevice->SetRenderTarget( 0, p );
	S_REL( p );
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
	GenerateTexture();
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pd3dDevice->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    /// ������ ����
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {

		DrawTexture();
		DrawFloor();
		DrawMesh();

		if( g_bFrustum ) 
			g_pFrustum->Draw( g_pd3dDevice );

		g_pd3dDevice->EndScene();
    }

    /// �ĸ���۸� ���̴� ȭ������!
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
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
 * ���α׷� ������
 *------------------------------------------------------------------------------
 */
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    /// ������ Ŭ���� ���
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "BasicFrame", NULL };
    RegisterClassEx( &wc );

    /// ������ ����
    HWND hWnd = CreateWindow( "BasicFrame", WINDOW_TITLE,
                              WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_W, WINDOW_H,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

	g_hwnd = hWnd;

    /// Direct3D �ʱ�ȭ
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		if( SUCCEEDED( InitObjects() ) )
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
    UnregisterClass( "BasicFrame", wc.hInstance );
    return 0;
}
