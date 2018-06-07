#include "stdafx.h"
#include "DXUT.h"
#include "DXUTCamera.h"
#include "DXUTTest.h"

LPD3DXMESH              g_pMeshOcc;				// occluder mesh
D3DMATERIAL9			g_matOcc;
LPDIRECT3DTEXTURE9		g_ptexOcc;

LPD3DXMESH              g_pMeshFloor;			// floor mesh
D3DMATERIAL9			g_matFloor;
LPDIRECT3DTEXTURE9		g_ptexFloor;

D3DXVECTOR4				g_vLightPos;			// �׸��ڸ� ���� ����
D3DXPLANE				g_planeFloor;			// �׸��ڰ� �׷��� ����� ������
bool					g_bShadow = TRUE;

DWORD					g_dwWidth;
DWORD					g_dwHeight;
D3DXMATRIX				g_matWorld;

CModelViewerCamera	g_Camera;

//-----------------------------------------------------------------------------
// Name: D3DUtil_InitMaterial()
// Desc: Initializes a D3DMATERIAL9 structure, setting the diffuse and ambient
//       colors. It does not set emissive or specular colors.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitMaterial( D3DMATERIAL9& mtrl, FLOAT r=0.0f, FLOAT g=0.0f,
                                               FLOAT b=0.0f, FLOAT a=1.0f )
{
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.r = mtrl.Ambient.r = r;
    mtrl.Diffuse.g = mtrl.Ambient.g = g;
    mtrl.Diffuse.b = mtrl.Ambient.b = b;
    mtrl.Diffuse.a = mtrl.Ambient.a = a;
}




//-----------------------------------------------------------------------------
// Name: D3DUtil_InitLight()
// Desc: Initializes a D3DLIGHT structure, setting the light position. The
//       diffuse color is set to white; specular and ambient are left as black.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitLight( D3DLIGHT9& light, D3DLIGHTTYPE ltType,
                        FLOAT x=0.0f, FLOAT y=0.0f, FLOAT z=0.0f )
{
    D3DXVECTOR3 vecLightDirUnnormalized(x, y, z);
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
    light.Type        = ltType;
    light.Diffuse.r   = 1.0f;
    light.Diffuse.g   = 1.0f;
    light.Diffuse.b   = 1.0f;
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecLightDirUnnormalized );
    light.Position.x   = x;
    light.Position.y   = y;
    light.Position.z   = z;
    light.Range        = 1000.0f;
}

bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    if( pDeviceSettings->ver == DXUT_D3D9_DEVICE )
    {
		IDirect3D9* pD3D = DXUTGetD3D9Object();
        if( SUCCEEDED( pD3D->CheckDeviceFormat(
    	                   pDeviceSettings->d3d9.AdapterOrdinal, pDeviceSettings->d3d9.DeviceType,
    	                   pDeviceSettings->d3d9.AdapterFormat, D3DUSAGE_DEPTHSTENCIL,
    	                   D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
        {
            if( SUCCEEDED( pD3D->CheckDepthStencilMatch(
                               pDeviceSettings->d3d9.AdapterOrdinal, pDeviceSettings->d3d9.DeviceType,
                               pDeviceSettings->d3d9.AdapterFormat, pDeviceSettings->d3d9.pp.BackBufferFormat,
                               D3DFMT_D24S8 ) ) )
            {
                pDeviceSettings->d3d9.pp.AutoDepthStencilFormat = D3DFMT_D24S8;
            }
        }
    }
    
    return true;
}


HRESULT RestoreDeviceObjects( IDirect3DDevice9* pd3dDevice )
{
    // Setup a material
    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 0.0f, 0.0f );
    pd3dDevice->SetMaterial( &mtrl );

    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    // Set miscellaneous render states
    pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
    pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
    pd3dDevice->SetRenderState( D3DRS_ZENABLE,        TRUE );
    pd3dDevice->SetRenderState( D3DRS_AMBIENT,        0x000F0F0F );

    // Set the world matrix
    D3DXMatrixIdentity( &g_matWorld );
    pd3dDevice->SetTransform( D3DTS_WORLD,  &g_matWorld );

	// ī�޶� ����
	D3DXVECTOR3 vEye = D3DXVECTOR3( 0.0f, .2f, -4.0f );
	D3DXVECTOR3 vLookAt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	g_Camera.SetViewParams( &vEye, &vLookAt );

    // Set up lighting states
    D3DLIGHT9 light;
    D3DUtil_InitLight( light, D3DLIGHT_DIRECTIONAL, 0.0f, -1.0f, 0.0f );
    pd3dDevice->SetLight( 0, &light );
    pd3dDevice->LightEnable( 0, TRUE );
    pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	// �׸��� ������ �� ������ �ʱ�ȭ
	g_vLightPos = D3DXVECTOR4( 1, 3, 0, 1 );
	g_planeFloor = D3DXPLANE( 0, 1.0f, 0, 0.5f );

    return S_OK;
}

HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice )
{
	TCHAR			str[128];
	DWORD			dwNumMat;	// �о���� ������ ����
    LPD3DXBUFFER	pD3DXMtrlBuffer;
	D3DXMATERIAL*	d3dxMaterials;

	// �ٴڸ޽� ����
	D3DXLoadMeshFromX( _T("data\\plane.x"), D3DXMESH_SYSTEMMEM, pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &dwNumMat, &g_pMeshFloor );
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_matFloor = d3dxMaterials[0].MatD3D;
	g_matFloor.Ambient = g_matFloor.Diffuse;
	g_ptexFloor = NULL;
	if( d3dxMaterials[0].pTextureFilename != NULL && strlen(d3dxMaterials[0].pTextureFilename) > 0 )
	{
		TCHAR	wcs[128];
		wcscpy( str, _T("data\\") );
		mbstowcs( wcs, d3dxMaterials[0].pTextureFilename, strlen(d3dxMaterials[0].pTextureFilename)+1 ); 
		wcscat( str, wcs );
		D3DXCreateTextureFromFile( pd3dDevice, str, &g_ptexFloor );
	}

	// ��ü�޽� ����
	D3DXLoadMeshFromX( _T("data\\tiger.x"), D3DXMESH_SYSTEMMEM, pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &dwNumMat, &g_pMeshOcc );
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_matOcc = d3dxMaterials[0].MatD3D;
	g_matOcc.Ambient = g_matOcc.Diffuse;
	g_ptexOcc = NULL;
	if( d3dxMaterials[0].pTextureFilename != NULL && strlen(d3dxMaterials[0].pTextureFilename) > 0 )
	{
		TCHAR	wcs[128];
		wcscpy( str, _T("data\\") );
		mbstowcs( wcs, d3dxMaterials[0].pTextureFilename, strlen(d3dxMaterials[0].pTextureFilename)+1 ); 
		wcscat( str, wcs );
		D3DXCreateTextureFromFile( pd3dDevice, str, &g_ptexOcc );
	}

	return S_OK;
}

HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{	
	RestoreDeviceObjects( pd3dDevice );

	return S_OK;
}	


void CALLBACK OnLostDevice( void* pUserContext )
{
	SAFE_RELEASE( g_pMeshOcc );
	SAFE_RELEASE( g_pMeshFloor );
	SAFE_RELEASE( g_ptexOcc );
	SAFE_RELEASE( g_ptexFloor );
}

HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT hr;

	// ī�޶� ������� ����
	float fAspectRatio = pBackBufferSurfaceDesc->Width 
		/ (FLOAT)pBackBufferSurfaceDesc->Height;
	g_Camera.SetProjParams( D3DX_PI/4, fAspectRatio, 0.1f, 1000.0f );
	g_Camera.SetWindow( pBackBufferSurfaceDesc->Width, 
		pBackBufferSurfaceDesc->Height );	
	V( pd3dDevice->SetTransform( D3DTS_PROJECTION, g_Camera.GetProjMatrix() ) );

	// ���� ������Ʈ ����
	LoadMesh( pd3dDevice );

	g_dwWidth = pBackBufferSurfaceDesc->Width;
	g_dwHeight = pBackBufferSurfaceDesc->Height;

	//V_RETURN( D3DXCreateBox( pd3dDevice, 1.0f, 1.0f, 1.0f, &g_pMesh, 0 ) );

	return S_OK;
}

void CALLBACK OnDestroyDevice( void* pUserContext )
{
	SAFE_RELEASE( g_pMeshOcc );
	SAFE_RELEASE( g_pMeshFloor );
	SAFE_RELEASE( g_ptexOcc );
	SAFE_RELEASE( g_ptexFloor );
}

void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	g_Camera.FrameMove( fElapsedTime );
}

// �ٴ��� �׸���.
void DrawFloor(IDirect3DDevice9* pd3dDevice)
{
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity( &matWorld );
    D3DXMatrixRotationX( &matWorld, -(D3DX_PI)/2.0f );
	matWorld._41 = 0.0f;
	matWorld._42 = -.5f;
	matWorld._43 = 0.0f;

    pd3dDevice->SetMaterial( &g_matFloor );
    pd3dDevice->SetTexture( 0, g_ptexFloor );
	pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	g_pMeshFloor->DrawSubset(0);
}

// ��ü�� �׸���.
void DrawOcc(IDirect3DDevice9* pd3dDevice)
{
    pd3dDevice->SetMaterial( &g_matOcc );
    pd3dDevice->SetTexture( 0, g_ptexOcc );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
//	pd3dDevice->SetTransform( D3DTS_WORLD, &g_matWorld );
	g_pMeshOcc->DrawSubset(0);
}

// ��ü�� �׸��ڸ� ���ٽ� ���ۿ� �׸���.
void DrawStencil(IDirect3DDevice9* pd3dDevice)
{
	D3DXMATRIX	matShadow;
	D3DXMatrixShadow( &matShadow, &g_vLightPos, &g_planeFloor );

    pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );			// Z���۸� ����
    pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,  FALSE );		// Z���ۿ� �������
    pd3dDevice->SetRenderState( D3DRS_STENCILENABLE, TRUE );		// ���ٽ��� �Ҵ�

    pd3dDevice->SetRenderState( D3DRS_SHADEMODE,     D3DSHADE_FLAT );	// ��Ƽ�� �������� �÷� ���̵�

    pd3dDevice->SetRenderState( D3DRS_STENCILFUNC,  D3DCMP_ALWAYS );			// ���ٽ� �Լ�����
    pd3dDevice->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP );
    pd3dDevice->SetRenderState( D3DRS_STENCILFAIL,  D3DSTENCILOP_KEEP );

    pd3dDevice->SetRenderState( D3DRS_STENCILREF,       0x1 );		// ������ų ��
    pd3dDevice->SetRenderState( D3DRS_STENCILMASK,      0xffffffff );
    pd3dDevice->SetRenderState( D3DRS_STENCILWRITEMASK, 0xffffffff );
    pd3dDevice->SetRenderState( D3DRS_STENCILPASS,      D3DSTENCILOP_INCR );	// ���� �׷�����, ���ٽǿ��� 1�� ������Ų��

    pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );		// �޽ð� ȭ�鿡 �׷����� ���� ���´�
    pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ZERO );
    pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
//	V( pd3dDevice->SetTransform( D3DTS_VIEW, g_Camera.GetViewMatrix() ) );

	matShadow =  *(g_Camera.GetWorldMatrix()) * matShadow;

	pd3dDevice->SetTransform( D3DTS_WORLD, &matShadow );
	g_pMeshOcc->DrawSubset(0);		// ���ٽ� ���ۿ� �޽ø� �׸���.

    // ������ ���� ���󺹱�
    pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    pd3dDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
    pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,     TRUE );
    pd3dDevice->SetRenderState( D3DRS_STENCILENABLE,    FALSE );
    pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
}

// ��ü�� �׸��ڸ� ȭ�鿡 �׸���.
void DrawShadow(IDirect3DDevice9* pd3dDevice)
{
	struct SQUARE
	{
		enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
		D3DXVECTOR4	p;	// pos
		DWORD		d;	// diffuse
	};

	// ȭ����ü�� ���� �޽�(4����)
	SQUARE	v[4];
    FLOAT sx = (FLOAT)g_dwWidth;
    FLOAT sy = (FLOAT)g_dwHeight;
    v[0].p = D3DXVECTOR4(  0, sy, 0.0f, 1.0f );
    v[1].p = D3DXVECTOR4(  0,  0, 0.0f, 1.0f );
    v[2].p = D3DXVECTOR4( sx, sy, 0.0f, 1.0f );
    v[3].p = D3DXVECTOR4( sx,  0, 0.0f, 1.0f );
    v[0].d = 0x7f000000;
    v[1].d = 0x7f000000;
    v[2].d = 0x7f000000;
    v[3].d = 0x7f000000;

	DrawStencil( pd3dDevice );	// ���ٽ� ���ۿ� �׸��ڸ� �׸���

    pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );			// Z���۸� ����
	pd3dDevice->SetRenderState( D3DRS_STENCILENABLE,    TRUE );	// ���ٽ��� �Ҵ�
    pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );	// ���ĺ����� �Ҵ�
    pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );	
    pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

    pd3dDevice->SetRenderState( D3DRS_STENCILREF,  0x1 );			// 1�� �񱳿���
    pd3dDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL );	// (���ٽǰ� >= 1) �̸� �׸���.
    pd3dDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP );

    pd3dDevice->SetFVF( SQUARE::FVF );
    pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &v[0], sizeof(SQUARE) );

    pd3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
    pd3dDevice->SetRenderState( D3DRS_STENCILENABLE,    FALSE );
    pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        FALSE );
    pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
}

void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	HRESULT hr;

	// ����� Ŭ����
	V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffc0c0c0, 1.0f, 0) );


	// �޽� �׸���
	pd3dDevice->BeginScene();

	DrawFloor( pd3dDevice );					// �ٴ��� �׸���
	if( g_bShadow ) DrawShadow( pd3dDevice );	// �׸��ڸ� �׸���
	V( pd3dDevice->SetTransform( D3DTS_WORLD, g_Camera.GetWorldMatrix() ) );
	V( pd3dDevice->SetTransform( D3DTS_VIEW, g_Camera.GetViewMatrix() ) );
	DrawOcc( pd3dDevice );						// �޽ø� �׸���

	pd3dDevice->EndScene();
}

LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
	// ī�޶� ��Ʈ�� ����
	return g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    // Direct3D 9 �ݹ� ����
	DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );	
	DXUTSetCallbackD3D9DeviceCreated( OnCreateDevice );
	DXUTSetCallbackD3D9DeviceReset( OnResetDevice );
	DXUTSetCallbackD3D9FrameRender( OnFrameRender );
	DXUTSetCallbackD3D9DeviceLost( OnLostDevice );
	DXUTSetCallbackD3D9DeviceDestroyed( OnDestroyDevice );

	// �Ϲ� �ݹ� �Լ� ����
	DXUTSetCallbackMsgProc( MsgProc );
	DXUTSetCallbackFrameMove( OnFrameMove );
    
	// DXUT�ʱ��, ������ â�� Direct3D����̽� ����
	DXUTInit( true, true ); 
	DXUTCreateWindow( L"TestApp" );
	DXUTCreateDevice( true, 640, 480 );

	// ������ ���� ����
	DXUTMainLoop();

	// TODO: Perform any application-level cleanup here

	return DXUTGetExitCode();
}
