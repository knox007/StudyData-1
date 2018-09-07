#include "StdAfx.h"
#include "PRCore.h"
#include "PUTCommon.h"
#include "PRLight.h"
#include "PreDef_Render.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"
//----------------------------------------------------------------------------
void CPRCore::InitMembers()
{
	//	Device
	m_pD3D		=	NULL;
	m_pDevice	=	NULL;	

	//	Device::Clear
	m_pClearRectsArr	=	NULL;
	m_dwClearRectCnt	=	0;
	
	m_dwClearFlag	=	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
	m_fZ			=	1.0f;
	m_dwStencil		=	0;	
	
	m_dColorBackScreen = D3DCOLOR_XRGB( 0, 128, 128 );
}//	InitMembers
//---------------------------------------------------------------------------
void CPRCore::ClearMembers()
{
	PUT_SAFE_DELETE( m_pLight );
	PUT_SAFE_RELEASE( m_pDevice );
	PUT_SAFE_RELEASE( m_pD3D );	
}//	ClearMembers
//---------------------------------------------------------------------------
bool CPRCore::Init( HWND hWnd, bool bWindowMode )
{
	m_bWindowMode	=	bWindowMode;
	m_hWnd			=	hWnd;
	
	PUT_SAFE_RELEASE( m_pDevice );
	PUT_SAFE_RELEASE( m_pD3D );

	m_pD3D	=	Direct3DCreate9( D3D_SDK_VERSION );
	if( !m_pD3D )
	{
		PUTSHOWERR( PUT_CSTR_TCHAR("CPRCore::Init") );
		return FALSE;
	}

	m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_DisplayMode );
	m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_Caps );

	DWORD	dwVertexProcessing = 0;
	if( m_Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		dwVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

		if( m_Caps.DevCaps & D3DDEVCAPS_PUREDEVICE )
		{
			dwVertexProcessing |= D3DCREATE_PUREDEVICE;
		}
	}else
		dwVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if( !BuildPresentParam() )
	{
		PUT_SAFE_RELEASE( m_pD3D );
		return FALSE;
	}

	HRESULT hResult = 0;
	hResult = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
									m_hWnd, dwVertexProcessing,
									&m_Param, &m_pDevice );
	if( FAILED( hResult ) )
	{
		PUT_SAFE_RELEASE( m_pD3D );
		PUTSHOWERR( PUT_CSTR_TCHAR("CPRCore::Init") );
		return FALSE;
	}

	//	Α¶Έν
	PUTNEW( m_pLight, CPRLight );
	m_pLight->Init( GetDevice(),
		0,
		D3DXVECTOR3(0,0,1)
		);

	return TRUE;
}//	Init
//---------------------------------------------------------------------------
bool CPRCore::BuildPresentParam()
{
	ZeroMemory( &m_Param, sizeof( m_Param ) );

	D3DFORMAT	dwAdapterFormat = ( m_bWindowMode ) ? 
								m_DisplayMode.Format :
								D3DFMT_X8R8G8B8;

	if( SUCCEEDED( m_pD3D->CheckDeviceFormat(	D3DADAPTER_DEFAULT,
												D3DDEVTYPE_HAL,
												dwAdapterFormat,
												D3DUSAGE_DEPTHSTENCIL,
												D3DRTYPE_SURFACE,
												D3DFMT_D24S8) ) )
	{
		m_Param.AutoDepthStencilFormat	=	D3DFMT_D24S8;
	}else
		if( SUCCEEDED( m_pD3D->CheckDeviceFormat(	D3DADAPTER_DEFAULT,
													D3DDEVTYPE_HAL,
													dwAdapterFormat,
													D3DUSAGE_DEPTHSTENCIL,
													D3DRTYPE_SURFACE,
													D3DFMT_D24X8) ) )
		{
			m_Param.AutoDepthStencilFormat	=	D3DFMT_D24X8;
		}else
			if( SUCCEEDED( m_pD3D->CheckDeviceFormat(	D3DADAPTER_DEFAULT,
														D3DDEVTYPE_HAL,
														dwAdapterFormat,
														D3DUSAGE_DEPTHSTENCIL,
														D3DRTYPE_SURFACE,
														D3DFMT_D16 ) ) )
			{
				m_Param.AutoDepthStencilFormat	=	D3DFMT_D16;
			}else
			{
				PUTSHOWERR( PUT_CSTR_TCHAR("Unable to find valid depth format") );
				return FALSE;
			}

			m_Param.BackBufferWidth				=	( m_bWindowMode ) ? 0 : m_DisplayMode.Width;
			m_Param.BackBufferHeight			=	( m_bWindowMode ) ? 0 : m_DisplayMode.Height;
			m_Param.BackBufferFormat			=	dwAdapterFormat;
			m_Param.BackBufferCount				=	1;
			m_Param.MultiSampleType				=	D3DMULTISAMPLE_NONE;
			m_Param.MultiSampleQuality			=	0;
			m_Param.SwapEffect					=	D3DSWAPEFFECT_DISCARD;
			m_Param.hDeviceWindow				=	m_hWnd;
			m_Param.Windowed					=	m_bWindowMode;
			m_Param.EnableAutoDepthStencil		=	TRUE;			
			m_Param.FullScreen_RefreshRateInHz	=	( m_bWindowMode ) ? 0 : m_DisplayMode.RefreshRate;
			m_Param.PresentationInterval		=	D3DPRESENT_INTERVAL_IMMEDIATE;
			m_Param.FullScreen_RefreshRateInHz	=	( m_bWindowMode ) ? 0 : m_DisplayMode.RefreshRate;			

			return TRUE;
}//	BuildPresentParam
//---------------------------------------------------------------------------
BOOL CPRCore::Reset()
{
	if( m_pDevice )
	{
		if( !BuildPresentParam() )
			return FALSE;

		m_pDevice->Reset( &m_Param );
	}
	return TRUE;
}//	Reset
//---------------------------------------------------------------------------
DWORD CPRCore::devGetFillMode()
{
	DWORD dwState; 
	HRESULT hr = devGetRState( m_pDevice, D3DRS_CULLMODE, &dwState );	
	return dwState;

}//	devGetFillMode
//---------------------------------------------------------------------------
HRESULT	CPRCore::SetTransformWorld( D3DMATRIX* pMat )
{
	return devSetTrsformWorld( m_pDevice, pMat );

}//	SetTransformWorld
//---------------------------------------------------------------------------
HRESULT	CPRCore::SetTransformView( D3DMATRIX* pMat )
{
	return devSetTrsformView( m_pDevice, pMat );	

}//	devSetTransformView
//---------------------------------------------------------------------------
HRESULT	CPRCore::SetTransformProjection( D3DMATRIX* pMat )
{
	return devSetTrsformProjection( m_pDevice, pMat );

}//	SetTransformProjection
//---------------------------------------------------------------------------
void	CPRCore::SaveScreenShot( char *pszFileName )
{
	if( GetDevice() )
	{
		LPDIRECT3DSURFACE9 pBackBuffer;

		GetDevice()->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );

		if( pBackBuffer )
		{
			SYSTEMTIME	  time;
			GetLocalTime(&time);

			char szCurDir[MAX_PATH] = {0,};
			GetCurrentDirectory(MAX_PATH, szCurDir);


			char szFPath[ MAX_PATH ] = {0,}; 			
			char szDrive[_MAX_DRIVE] = {0,}; 			
			char szDirect[ MAX_PATH ] = {0,};			
			char szLFile[ MAX_PATH ] = {0,}; 
			char szExe[ _MAX_EXT ] = {0,};

#ifndef _ENGCLI_VS2003_VS2008_
			_splitpath_s( szCurDir, szDrive, szDirect, szLFile, szExe );
#else
			PUT_SplitPath( szCurDir, szDrive, szDirect, szLFile, szExe );
#endif
			

#ifndef _ENGCLI_VS2003_VS2008_
			sprintf_s( szFPath, sizeof(szFPath), "%s%s%s/%s", szDrive, szDirect,szLFile, "ScreenShot" );
#else
			PUT_Sprintf( szFPath, "%s%s%s/%s", szDrive, szDirect,szLFile, "ScreenShot" );
#endif

			

			if( _access( szFPath, 0 ) == -1 )
				_mkdir( szFPath );

			SetCurrentDirectory( szFPath );

			char szFile[MAX_PATH] = {0,}; 

#ifndef _ENGCLI_VS2003_VS2008_
			sprintf_s(	szFile, sizeof(szFile), "%s_%04d_%02d_%02d_%02d_%02d_%02d.bmp",	pszFileName, 
				time.wYear, time.wMonth, 
				time.wDay, time.wHour,
				time.wMinute, time.wSecond );
#else
			PUT_Sprintf(	szFile, "%s_%04d_%02d_%02d_%02d_%02d_%02d.bmp",	pszFileName, 
				time.wYear, time.wMonth, 
				time.wDay, time.wHour,
				time.wMinute, time.wSecond );
#endif
			

			D3DXSaveSurfaceToFile( szFile, D3DXIFF_BMP, pBackBuffer, NULL, NULL );

			pBackBuffer->Release();

			SetCurrentDirectory( szCurDir );

		}//	if( pBackBuffer )

	}//	if( GetDevice() )

}//	SaveScreenShot
//---------------------------------------------------------------------------
//	EOF
