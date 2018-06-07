/**----------------------------------------------------------------------------
 * \brief �ؽ��� ����
 * ����: Textures.cpp
 *
 * ����: 3���� ������Ʈ�� �ؽ��Ŀ� ���յɶ� ���� ���ǰ��ְ� �ȴ�. �ؽ��Ķ� ��ġ
 *       �������� ������, �����ϰ� ���̰ų� �ٿ��� �鿡 ���̰� �ȴ�. �Ϲ�������
 *       �ؽ��Ĵ� �̹��� ����(JPG,BMP,TGA��)�� D3DX�迭�� �Լ��� ����ؼ� �о��
 *       ���� ����ϰ� �ȴ�. �������ۿ� ���������� Lock(), Unlock()�Լ��� ����ؼ�
 *       �޸𸮿� ���������� ���� �ִ�. �̷��� ������ �ؽ��ĸ� �鿡 ���̴� ������
 *       �ؽ��� �����̶�� �Ѵ�.
 *
 *       �ؽ��Ĵ� ���������� ����Ǳ����ؼ� �ؽ�����ǥ�踦 ���ԵǴµ�, ������ ����
 *       �� �̷��� �ؽ��� ��ǥ�� �����ϰ� �־���Ѵ�. �Ϲ������δ� (u,v) ��ǥ�踦
 *       ����ϰ� u,v�� ���� 0.0 ~ 1.0 ������ ���̴�. �ؽ��� ��ǥ�� ���ʿ� ������
 *       ���� ������, �ǽð����� ��������Ͽ� �� �پ��� ȿ���� ������ �ִ�.
 *       (mirror, sphere���� ��)
 *------------------------------------------------------------------------------
 */
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>

/// SHOW_HOW_TO_USE_TCI�� ����ȰͰ� ������� �������� ������ ����� �ݵ�� ���� ����.
/// #define SHOW_HOW_TO_USE_TCI

/**-----------------------------------------------------------------------------
 *  ��������
 *------------------------------------------------------------------------------
 */
LPDIRECT3D9             g_pD3D       = NULL; /// D3D ����̽��� ������ D3D��ü����
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; /// �������� ���� D3D����̽�
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; /// ������ ������ ��������
LPDIRECT3DTEXTURE9      g_pTexture   = NULL; /// �ؽ��� ����

/// ����� ������ ������ ����ü
/// �ؽ��� ��ǥ�� �߰��Ǿ��ٴ� ���� �˼� �ִ�.
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; /// 3���� ��ǥ
    D3DCOLOR    color;    /// ����
#ifndef SHOW_HOW_TO_USE_TCI
    FLOAT       tu, tv;   /// �ؽ��� ��ǥ
#endif
};

/// ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF��
#ifdef SHOW_HOW_TO_USE_TCI
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#else
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#endif



/**-----------------------------------------------------------------------------
 * Direct3D �ʱ�ȭ
 *------------------------------------------------------------------------------
 */
HRESULT InitD3D( HWND hWnd )
{
    /// ����̽��� �����ϱ����� D3D��ü ����
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    /// ����̽��� ������ ����ü
    /// ������ ������Ʈ�� �׸����̱⶧����, �̹����� Z���۰� �ʿ��ϴ�.
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

    /// �ø������ ����.
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    /// �������� ����.
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    /// Z���۱���� �Ҵ�.
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return S_OK;
}




/**-----------------------------------------------------------------------------
 * �������� �ʱ�ȭ
 * �������ۿ� �ؽ��� ����
 *------------------------------------------------------------------------------
 */
HRESULT InitGeometry()
{
    /// D3DX�迭 �Լ��� ����ؼ� ���Ϸκ��� �ؽ��� ����(banana.bmp)
    if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "banana.bmp", &g_pTexture ) ) )
    {
        /// ���������� ������ ������ �������� �˻�
        if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "..\\banana.bmp", &g_pTexture ) ) )
        {
        	/// �ؽ��� ���� ����
            MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
            return E_FAIL;
        }
    }

    /// �������� ����
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    /// �������۸� ������ ä���.
    /// �ؽ����� u,v��ǥ���� 0.0 ~ 1.0 ������ ������ ä���ְ� �ִ�.
    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    for( DWORD i=0; i<50; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(50-1);

        pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
        pVertices[2*i+0].color    = 0xffffffff;
#ifndef SHOW_HOW_TO_USE_TCI								/// SHOW_HOW_TO_USE_TCI�� ����Ǿ� ������ �ؽ��� ��ǥ�� �������� �ʴ´�.
        pVertices[2*i+0].tu       = ((FLOAT)i)/(50-1);	/// �ؽ����� u��ǥ 0/49, 1/49, 2/49 ... 49/49 (�� 0.0 ~ 1.0)
        pVertices[2*i+0].tv       = 1.0f;				/// �ؽ����� v��ǥ 1.0
#endif

        pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
        pVertices[2*i+1].color    = 0xff808080;
#ifndef SHOW_HOW_TO_USE_TCI								/// SHOW_HOW_TO_USE_TCI�� ����Ǿ� ������ �ؽ��� ��ǥ�� �������� �ʴ´�.
        pVertices[2*i+1].tu       = ((FLOAT)i)/(50-1);	/// �ؽ����� u��ǥ 0/49, 1/49, 2/49 ... 49/49 (�� 0.0 ~ 1.0)
        pVertices[2*i+1].tv       = 0.0f;				/// �ؽ����� v��ǥ 0.0
#endif
    }
    g_pVB->Unlock();

    return S_OK;
}




/**-----------------------------------------------------------------------------
 * �ʱ�ȭ�� ��ü�� �Ұ�
 *------------------------------------------------------------------------------
 */
VOID Cleanup()
{
    if( g_pTexture != NULL )
        g_pTexture->Release();

    if( g_pVB != NULL )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}



/**-----------------------------------------------------------------------------
 * ��� ����
 *------------------------------------------------------------------------------
 */
VOID SetupMatrices()
{
	/// �������
    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity( &matWorld );
    D3DXMatrixRotationX( &matWorld, timeGetTime()/1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    /// ������� ����
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    /// �������� ��� ����
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}




/**-----------------------------------------------------------------------------
 * ȭ�� �׸���
 *------------------------------------------------------------------------------
 */
VOID Render()
{
    /// �ĸ���ۿ� Z���۸� �����.
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

    /// ������ ����
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        /// ����,��,�������� ����� �����Ѵ�.
        SetupMatrices();

        /// ������ �ؽ��ĸ� 0�� �ؽ��� ���������� �ø���.
        /// �ؽ��� ���������� �������� �ؽ��Ŀ� ���������� ��� ����Ҷ� ���ȴ�.
        /// ���⼭�� �ؽ����� ����� ������ ���������� modulate�������� ��� ����Ѵ�.
        g_pd3dDevice->SetTexture( 0, g_pTexture );									/// 0�� �ؽ��� ���������� �ؽ��� ����
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );	/// MODULATE�������� ������ ����
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );	/// ù��° �������� �ؽ��� ��
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );	/// �ι�° �������� ���� ��
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );	/// alpha������ ������� ����

    #ifdef SHOW_HOW_TO_USE_TCI
    	/// D3D�� �ؽ��� ��ǥ ���� ����� ����ϴ� ���� �����ش�.
    	/// ���⼭�� ī�޶���ǥ�迡���� ���������� ����ؼ� �ؽ��� ��ǥ�� �����Ѵ�.
    	/// 4x4ũ���� �ؽ��� ��ȯ����� �ؽ�����ǥ�ε���(TCI=Texture Coord Index)�������ڷ� 
    	/// ����ؼ� x,y,z TCI��ǥ�� u,v�ؽ��� ��ǥ�� ��ȯ�Ѵ�.

    	/// ����� ���� �ܼ��� (-1.0 ~ +1.0) ���� (0.0 ~ 1.0) ������ ������ ��ȯ�ϴ� ����̴�.
    	/// world,view,projection��ȯ�� ��ģ ������ (-1.0 ~ +1.0)������ ���� ���� �ȴ�.
        //  tu =  0.5*x + 0.5
        //  tv = -0.5*y + 0.5
        D3DXMATRIXA16 mat;
        mat._11 = 0.25f; mat._12 = 0.00f; mat._13 = 0.00f; mat._14 = 0.00f;
        mat._21 = 0.00f; mat._22 =-0.25f; mat._23 = 0.00f; mat._24 = 0.00f;
        mat._31 = 0.00f; mat._32 = 0.00f; mat._33 = 1.00f; mat._34 = 0.00f;
        mat._41 = 0.50f; mat._42 = 0.50f; mat._43 = 0.00f; mat._44 = 1.00f;

        g_pd3dDevice->SetTransform( D3DTS_TEXTURE0, &mat );												/// �ؽ��� ��ȯ���
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 );			/// 2���� �ؽ��� ���
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// ī�޶� ��ǥ�� ��ȯ
    #endif

        /// ���������� ������ �׸���.
        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*50-2 );

        /// ������ ����
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
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
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
                      "D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    /// ������ ����
    HWND hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial 05: Textures",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

    /// Direct3D �ʱ�ȭ
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        /// �������� �ʱ�ȭ
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
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();
            }
        }
    }

    UnregisterClass( "D3D Tutorial", wc.hInstance );
    return 0;
}



