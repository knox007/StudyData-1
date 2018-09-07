#include "stdafx.h"
#include "DXUT.h"
#include "DXUTCamera.h"
#include "DXUTTest.h"

LPD3DXMESH			g_pMesh = NULL;
CModelViewerCamera	g_Camera;

HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{	
	// ī�޶� ����
	D3DXVECTOR3 vEye = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
	D3DXVECTOR3 vLookAt = D3DXVECTOR3( 0.0f, 0.0f, -0.0f );
	g_Camera.SetViewParams( &vEye, &vLookAt );

	// �������� ���̾�����������
	pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	return S_OK;
}	


void CALLBACK OnLostDevice( void* pUserContext )
{
	SAFE_RELEASE( g_pMesh );
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
	V_RETURN( D3DXCreateBox( pd3dDevice, 1.0f, 1.0f, 1.0f, &g_pMesh, 0 ) );

	return S_OK;
}

void CALLBACK OnDestroyDevice( void* pUserContext )
{
	SAFE_RELEASE( g_pMesh );
}

void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	g_Camera.FrameMove( fElapsedTime );
}

void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	HRESULT hr;

	// ����� Ŭ����
	V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0) );

	// ī�޶� ��� ����
	V( pd3dDevice->SetTransform( D3DTS_WORLD, g_Camera.GetWorldMatrix() ) );
	V( pd3dDevice->SetTransform( D3DTS_VIEW, g_Camera.GetViewMatrix() ) );

	// �޽� �׸���
	pd3dDevice->BeginScene();
	g_pMesh->DrawSubset( 0 );
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
