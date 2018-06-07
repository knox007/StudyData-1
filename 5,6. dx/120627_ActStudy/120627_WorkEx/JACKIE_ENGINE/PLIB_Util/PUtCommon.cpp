#include "stdafx.h"
#include "PUtCommon.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"
#include "PreDef_UT.h"


//------------------------------------------------------------------------
void	PUTSHOWERR( TCHAR *ptszMsg )
{
#if defined(_DEBUG) || defined(DEBUG)
	TCHAR tszBuf[1024];
#ifndef _ENGCLI_VS2003_VS2008_
	sprintf_s( tszBuf, sizeof(tszBuf), PUT_CSTR_TCHAR("File: %s\nLine: %d\n%s"),__FILE__,__LINE__,ptszMsg );
#else
	PUT_Sprintf( tszBuf, PUT_CSTR_TCHAR("File: %s\nLine: %d\n%s"),__FILE__,__LINE__,ptszMsg );
#endif
	MessageBox( 0, tszBuf, "Error", MB_ICONWARNING );
#else

#endif
};//PUTSHOWERR
//-----------------------------------------------------------------------------------------------
void Trace( const TCHAR *ptszFormat, ... )
{
	TCHAR szBuff[1024];

	va_list argList;
	va_start( argList, ptszFormat );
#ifndef _ENGCLI_VS2003_VS2008_
	vsprintf_s( szBuff, ptszFormat, argList );
#else
	PUT_VSprintf( szBuff, 1024, ptszFormat, argList );
#endif
	va_end( argList );

	OutputDebugString( szBuff );
}//	Trace
//-----------------------------------------------------------------------------------------------
void	IsFailed( HRESULT hr )
{
	PUT_IsFailed(hr)
	{
		PUT_ERROR;
		exit(0);
	}	

}//	IsFailed
//-----------------------------------------------------------------------------------------------
void	IsFailed( HRESULT hr, TCHAR *ptszErr )
{
	PUT_IsFailed(hr)
	{
		PUT_ERROR_MSZ(ptszErr);
		exit(0);
	}

}//	IsFailed( HRESULT hr, WCHAR *ptszErr )
//-----------------------------------------------------------------------------------------------
void	PUTShowErrCode()
{
#if defined(_DEBUG) || defined(DEBUG)
	DWORD dwErr = GetLastError();
	char szErrMsg[1024] = {0};

	switch( dwErr )
	{
	case ERROR_INVALID_FUNCTION:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( szErrMsg, sizeof(szErrMsg), "Incorrect Function." );
#else
		PUT_Strcpy( szErrMsg, "Incorrect Function." );
#endif

		break;

	case ERROR_FILE_NOT_FOUND:
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( szErrMsg, sizeof(szErrMsg), "File Not Found." );
#else
		PUT_Strcpy( szErrMsg, "File Not Found." );
#endif
		break;
	}

	if( dwErr != ERROR_SUCCESS )
	{
		PUT_ERROR_MSZ(szErrMsg);		
	}
#else
	(__noop);
#endif

}//	PUTShowErrCode
//-----------------------------------------------------------------------------------------------

void	PUT_ERROR_MSZ( TCHAR* ptszMsg )
{
#if defined(_DEBUG) || defined(DEBUG)
	WCHAR wszErrMsg[1024] = {0};

	PUT_SetFMultiByteTWideChar( ptszMsg, wszErrMsg );
	PUT_Assert( wszErrMsg );

#else
	(__noop);
#endif

}//	PUT_ERROR_MSZ
//-----------------------------------------------------------------------------------------------
//	EOF