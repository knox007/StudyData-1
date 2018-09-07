/**-----------------------------------------------------------------------------
 * \brief ����̽� ����
 * ����: CreateDevice.cpp
 *
 * ����: D3D ����̽��� �����ϰ�, �̸� ����ؼ� ȭ���� ����� ����� ���ؼ�
 *       �����ϰ� �ȴ�.
 *
 **-----------------------------------------------------------------------------
 */
/// Direct3D9�� ����ϱ� ���� ���
#include <d3d9.h>




/**-----------------------------------------------------------------------------
 * ��������
 *------------------------------------------------------------------------------
 */
LPDIRECT3D9             g_pD3D       = NULL; /// D3D ����̽��� ������ D3D��ü����
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; /// �������� ���� D3D����̽�




/**-----------------------------------------------------------------------------
 * Direct3D �ʱ�ȭ
 *------------------------------------------------------------------------------
 */
HRESULT InitD3D( HWND hWnd )
{
    /// ����̽��� �����ϱ����� D3D��ü ����
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;                /// ����̽� ������ ���� ����ü
    ZeroMemory( &d3dpp, sizeof(d3dpp) );        /// �ݵ�� ZeroMemory()�Լ��� �̸� ����ü�� ������ ������ �Ѵ�.
    d3dpp.Windowed = TRUE;                      /// â���� ����
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   /// ���� ȿ������ SWAPȿ��
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;    /// ���� ����ȭ�� ��忡 ���缭 �ĸ���۸� ����

    /// ����̽��� ������ ���� �������� �����Ѵ�.
    /// 1. ����Ʈ ����ī�带 ���(��κ��� ����ī�尡 1�� �̴�.)
    /// 2. HAL����̽��� �����Ѵ�.(HW������ġ�� ����ϰڴٴ� �ǹ�)
    /// 3. ����ó���� ��� ī�忡�� �����ϴ� SWó���� �����Ѵ�.(HW�� �����Ұ�� ���� ���� ������ ����.)
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    /// ����̽� ���������� ó���Ұ�� ���⿡�� �Ѵ�.

    return S_OK;
}


/**-----------------------------------------------------------------------------
 * �ʱ�ȭ�� ��ü���� �Ұ��Ѵ�.
 *------------------------------------------------------------------------------
 */
VOID Cleanup()
{
    if( g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL)
        g_pD3D->Release();
}



/**-----------------------------------------------------------------------------
 * ȭ���� �׸���.
 *------------------------------------------------------------------------------
 */
VOID Render()
{
    if( NULL == g_pd3dDevice )
        return;

    /// �ĸ���۸� �Ķ���(0,0,255)���� �����.
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
    
    /// ������ ����
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        /// ���� ������ ��ɵ��� ������ ��
    
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

        case WM_PAINT:
            Render();
            ValidateRect( hWnd, NULL );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




/**-----------------------------------------------------------------------------
 * �� ���α׷��� ������
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
    HWND hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial 01: CreateDevice", 
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

    /// Direct3D �ʱ�ȭ
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    { 
        /// ������ ���
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        /// �޽��� ����
        MSG msg; 
        while( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    /// ��ϵ� Ŭ���� �Ұ�
    UnregisterClass( "D3D Tutorial", wc.hInstance );
    return 0;
}



