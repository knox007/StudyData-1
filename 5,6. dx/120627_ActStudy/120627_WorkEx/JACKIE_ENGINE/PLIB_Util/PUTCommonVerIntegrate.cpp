#include "stdafx.h"
#include <assert.h>
#include <crtdbg.h>
#include <errno.h>
#include "PUTCommonVerIntegrate.h"


#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )
#define PUTSplitpath	_splitpath
#define PUTVSprintf		vsprintf
#define PUTStrcpy		strcpy
#define PUTStrdate		_strdate
#define PUTASSERT		assert
#define PUTSTRTIME		_strtime
#define PUTFOPEN		fopen
#define PUTStrNcpy		strncpy
#else
#define PUTSplitpath	_splitpath_s
#define PUTVSprintf		vsprintf_s
#define PUTStrcpy		strcpy_s
#define PUTStrdate		_strdate_s
#define PUTASSERT		_ASSERT_EXPR
#define PUTSTRTIME		_strtime_s
#define PUTFOPEN		fopen_s
#define PUTStrNcpy		strncpy_s
#endif


#if defined( _MSC_VER ) && ( _MSC_VER > 1310 )
void	PUT_FOpen( FILE* pFile, const TCHAR* ptszFileName, const TCHAR* ptszMode )
{
	 PUTFOPEN( pFile, ptszFileName, ptszMode );
}
//----------------------------------------------------------------------------------------
#else
void	PUT_FOpen( FILE** ppFile, const TCHAR* ptszFileName, const TCHAR* ptszMode )
{
	*ppFile = fopen( ptszFileName, ptszMode );
}
#endif
//----------------------------------------------------------------------------------------
void	PUT_SplitPath( const TCHAR* cptszPath, TCHAR* ptszDrive, TCHAR* ptszDir, TCHAR* ptszName, TCHAR* ptszExt )
{
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )
	PUTSplitpath( cptszPath, ptszDrive, ptszDir, ptszName, ptszExt );
#else
	PUTSplitpath(	cptszPath, 
					ptszDrive, sizeof( ptszDrive ), 
					ptszDir, sizeof(ptszDir), 
					ptszName, sizeof(ptszName), 
					ptszExt, sizeof(ptszExt) );
#endif

}//	PUT_SplitPath
//----------------------------------------------------------------------------------------
void	PUT_Sprintf( TCHAR* ptszBuffer, const TCHAR* cptszFormat, ... )
{
	TCHAR	tszBuff[1024] = {0};

	va_list argList;
	va_start( argList, cptszFormat );
	PUT_VSprintf( tszBuff, sizeof(tszBuff), cptszFormat, argList );
	va_end( argList );
	
	PUT_Strcpy( ptszBuffer, tszBuff );

}//	PUT_Sprintf
//----------------------------------------------------------------------------------------
void	PUT_VSprintf( TCHAR* ptszBuffer, size_t unNumberOfElements, const TCHAR* cptszFormat, va_list argPtr )
{
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )
	PUTVSprintf( ptszBuffer, cptszFormat, argPtr );
#else
	PUTVSprintf( ptszBuffer, unNumberOfElements, cptszFormat, argPtr );
#endif

}//	PUT_VSprintf
//----------------------------------------------------------------------------------------
void	PUT_Strcpy( TCHAR *ptszDst, const TCHAR* ptszSrc )
{
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )
	PUTStrcpy( ptszDst, ptszSrc );
#else	
	PUTStrcpy( ptszDst, MAX_PATH, ptszSrc );
#endif

}//	PUT_Strcpy
//----------------------------------------------------------------------------------------
void	PUT_StrNcpy( TCHAR *ptszDst, const TCHAR* ptszSrc, int nLen )
{
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )
	PUTStrNcpy( ptszDst, ptszSrc, nLen );
#else
	PUTStrNcpy( ptszDst, MAX_PATH, ptszSrc, nLen );
#endif
}
//----------------------------------------------------------------------------------------
void	PUT_Strdate( TCHAR* ptszBuffer, size_t unNumberOfElements )
{
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )	
	PUTStrdate( ptszBuffer );	
#else
	PUTStrdate( ptszBuffer, unNumberOfElements );
#endif

}//	PUT_Strdate
//----------------------------------------------------------------------------------------
void	PUT_StrTime( TCHAR* ptszBuffer, size_t unSizeInBytes )
{
#if defined( _MSC_VER ) && ( _MSC_VER <= 1310 )
	PUTSTRTIME( ptszBuffer );
#else
	PUTSTRTIME( ptszBuffer, unSizeInBytes );
#endif

}//	PUT_StrTime
//----------------------------------------------------------------------------------------
void	PUT_Assert( WCHAR* pwszErrMsg )
{
#if defined(_MSC_VER) && (_MSC_VER <= 1310 )
	PUTASSERT( 0 );
#else
	PUTASSERT( 0, pwszErrMsg );
#endif

}//	PUT_Assert
//----------------------------------------------------------------------------------------
//	EOF