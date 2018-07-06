#ifndef _PUTCOMMONVERINTEGRATE_H_
#define _PUTCOMMONVERINTEGRATE_H_

void	PUT_Sprintf( TCHAR* ptszBuffer, const TCHAR* cptszFormat, ... );
void	PUT_VSprintf( TCHAR* ptszBuffer, size_t unNumberOfElements, const TCHAR* cptszFormat, va_list argPtr );
void	PUT_Strcpy( TCHAR *ptszDst, const TCHAR* ptszSrc );
void	PUT_StrNcpy( TCHAR *ptszDst, const TCHAR* ptszSrc, int nLen );
void	PUT_SplitPath( const TCHAR* cptszPath, TCHAR* ptszDrive, TCHAR* ptsdDir, TCHAR* ptszName, TCHAR* ptszExt );
void	PUT_Strdate( TCHAR* ptszBuffer, size_t unNumberOfElements );
#if defined( _MSC_VER ) && ( _MSC_VER > 1310 )
void	PUT_FOpen( FILE* pFile, const TCHAR* ptszFileName, const TCHAR* ptszMode );
#else
void	PUT_FOpen( FILE** ppFile, const TCHAR* ptszFileName, const TCHAR* ptszMode );
#endif
void	PUT_StrTime( TCHAR* ptszBuffer, size_t unSizeInBytes );
void	PUT_Assert( WCHAR* pwszErrMsg );


#endif
//	_PUTCOMMONVERINTEGRATE_H_