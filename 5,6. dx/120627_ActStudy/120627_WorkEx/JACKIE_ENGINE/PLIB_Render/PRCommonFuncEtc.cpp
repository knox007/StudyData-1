#include "stdafx.h"
#include "PRCommonFunc.h"
#include "PUtCommon.h"
#include "PUtCommonStr.h"
#include "PreDef_Render.h"
#include "PUTCommonVerIntegrate.h"
#include <string>


//--------------------------------------------------------------------------------
HRESULT	devSetMtrl( PRLPD3DDEV9 pDev, PRDMTRL9* pMtrl )
{
	return pDev->SetMaterial( pMtrl );

}//	devSetMtrl
//--------------------------------------------------------------------------------
HRESULT	devSetLight( PRLPD3DDEV9 pDev, DWORD dwIdx, D3DLIGHT9* pLight )
{
	return pDev->SetLight( dwIdx, pLight );

}//	devSetLight
//--------------------------------------------------------------------------------
HRESULT	devSetTxtr( PRLPD3DDEV9 pDev, DWORD dwState, LPDIRECT3DBASETEXTURE9 pTex )
{
	return pDev->SetTexture( dwState, pTex );

}//	devSetTex
//--------------------------------------------------------------------------------
HRESULT	devLightEnable( PRLPD3DDEV9 pDev, DWORD dwIdx, BOOL bEnable )
{
	return pDev->LightEnable( dwIdx, bEnable );

}//	devLightEnable
//--------------------------------------------------------------------------------
HRESULT	devSetSmpS( PRLPD3DDEV9 pDev, DWORD dwSampler, D3DSAMPLERSTATETYPE eType, DWORD dwVal )
{
	return pDev->SetSamplerState( dwSampler, eType, dwVal );

}//	devSetSmplState
//--------------------------------------------------------------------------------
HRESULT	devSetSmpSMINFilter( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal )
{	
	return devSetSmpS( pDev, dwSampler, D3DSAMP_MINFILTER, dwVal );

}//	devSetSmpSMINFilter
//--------------------------------------------------------------------------------
HRESULT	devSetSmpSMAGFilter( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal )
{
	return devSetSmpS( pDev, dwSampler, D3DSAMP_MAGFILTER, dwVal );

}//	devSetSmpSMAGFilter
//--------------------------------------------------------------------------------
HRESULT	devSetSmpSMIPFilter( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal )
{
	return devSetSmpS( pDev, dwSampler, D3DSAMP_MIPFILTER, dwVal );

}//	devSetSmpSMIPFilter
//--------------------------------------------------------------------------------
HRESULT	devSetSmpSFilters( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal )
{
	devSetSmpSMINFilter( pDev, dwSampler, dwVal );
	devSetSmpSMIPFilter( pDev, dwSampler, dwVal );
	devSetSmpSMAGFilter( pDev, dwSampler, dwVal );

	return S_OK;

}//	devSetSmpSFilters
//--------------------------------------------------------------------------------
void	PRCheckError( HRESULT hr )	//	DXGetErrorString9
{
	TCHAR tszMsg[MAX_PATH] = {0,};

#if defined(_DEBUG) || defined(DEBUG)
	switch( hr )
	{
//	case D3D_OK:
//		break;

	case D3DOK_NOAUTOGEN:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DOK_NOAUTOGEN\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DOK_NOAUTOGEN\n") );
#endif
		
		break;

	case D3DERR_CONFLICTINGRENDERSTATE:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_CONFLICTINGRENDERSTATE\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_CONFLICTINGRENDERSTATE\n") );
#endif
		break;

	case D3DERR_CONFLICTINGTEXTUREFILTER:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_CONFLICTINGTEXTUREFILTER\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_CONFLICTINGTEXTUREFILTER\n") );
#endif
		break;

	case D3DERR_CONFLICTINGTEXTUREPALETTE:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_CONFLICTINGTEXTUREPALETTE\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_CONFLICTINGTEXTUREPALETTE\n") );
#endif
		break;

	case D3DERR_DEVICELOST:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_DEVICELOST\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_DEVICELOST\n") );
#endif
		break;

	case D3DERR_DEVICENOTRESET:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_DEVICENOTRESET\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_DEVICENOTRESET\n") );
#endif
		break;

	case D3DERR_DRIVERINTERNALERROR:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_DRIVERINTERNALERROR\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_DRIVERINTERNALERROR\n") );
#endif
		break;

	case D3DERR_INVALIDCALL:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_INVALIDCALL\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_INVALIDCALL\n") );
#endif
		break;

	case D3DERR_INVALIDDEVICE:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_INVALIDDEVICE\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_INVALIDDEVICE\n") );
#endif
		break;

	case D3DERR_MOREDATA:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_MOREDATA\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_MOREDATA\n") );
#endif
		break;

	case D3DERR_NOTAVAILABLE:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_NOTAVAILABLE\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_NOTAVAILABLE\n") );
#endif
		break;

	case D3DERR_NOTFOUND:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_NOTFOUND\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_NOTFOUND\n") );
#endif
		break;

	case D3DERR_OUTOFVIDEOMEMORY:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_OUTOFVIDEOMEMORY\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_OUTOFVIDEOMEMORY\n") );
#endif
		break;

	case D3DERR_TOOMANYOPERATIONS:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_TOOMANYOPERATIONS\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_TOOMANYOPERATIONS\n") );
#endif
		break;

	case D3DERR_UNSUPPORTEDALPHAARG:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDALPHAARG\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDALPHAARG\n") );
#endif
		break;

	case D3DERR_UNSUPPORTEDALPHAOPERATION:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDALPHAOPERATION\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDALPHAOPERATION\n") );
#endif
		break;

	case D3DERR_UNSUPPORTEDCOLORARG:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDCOLORARG\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDCOLORARG\n") );
#endif
		break;

	case D3DERR_UNSUPPORTEDCOLOROPERATION:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDCOLOROPERATION\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDCOLOROPERATION\n") );
#endif
		break;

	case D3DERR_UNSUPPORTEDFACTORVALUE:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDFACTORVALUE\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDFACTORVALUE\n") );
#endif
		break;

	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDTEXTUREFILTER\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_UNSUPPORTEDTEXTUREFILTER\n") );
#endif
		break;

	case D3DERR_WRONGTEXTUREFORMAT:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("D3DERR_WRONGTEXTUREFORMAT\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("D3DERR_WRONGTEXTUREFORMAT\n") );
#endif
		break;

	case E_FAIL:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("E_FAIL\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("E_FAIL\n") );
#endif
		break;

	case E_INVALIDARG:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("E_INVALIDARG\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("E_INVALIDARG\n") );
#endif
		break;

	case E_OUTOFMEMORY:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( tszMsg, sizeof(tszMsg), PUT_CSTR_TCHAR("E_OUTOFMEMORY\n") );
#else
		PUT_Strcpy( tszMsg, PUT_CSTR_TCHAR("E_OUTOFMEMORY\n") );
#endif
		break;	
	}

	PUT_IsFailed( hr )
		PUTOutputDebugStr( tszMsg );

#else
	(__noop);
#endif

}//	PRCheckError
//--------------------------------------------------------------------------------
//	EOF