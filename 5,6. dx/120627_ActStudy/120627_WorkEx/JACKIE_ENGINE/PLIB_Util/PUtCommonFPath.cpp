#include "stdafx.h"
#include "PUtCommonFPath.h"
#include <algorithm>
#include <io.h>
#include "PUtCommonStr.h"
#include "PreDef_UT.h"
#include "PUTCommonVerIntegrate.h"

#pragma warning(disable:4996)

//---------------------------------------------------------------------------------------
//!	파일 경로 얻기.
void	PUT_GetFilePath( char *pszFileName, char *pszFileOut, bool bDirCur )
{
	if( bDirCur )
	{
		char	szBuff[MAX_PATH]	=	{0,};
		GetCurrentDirectory( MAX_PATH, szBuff );
#ifndef _ENGCLI_VS2003_VS2008_
		sprintf_s( pszFileOut, sizeof(pszFileOut), "%s\\%s", szBuff, pszFileName );
#else
		PUT_Sprintf( pszFileOut, "%s\\%s", szBuff, pszFileName );
#endif
		
	}
	else
	{
#ifndef _ENGCLI_VS2003_VS2008_
		sprintf_s( pszFileOut, sizeof(pszFileOut), "%s", pszFileName );
#else
		PUT_Sprintf( pszFileOut, "%s", pszFileName );
#endif
	}

}//	GetFilePath
//---------------------------------------------------------------------------------------
//!	현재 작업 경로 얻기.
void	PUT_GetCurrentWorkFolder( char *pszWorkFolder )
{
	char szCurExePath[256];
	GetModuleFileName( NULL, szCurExePath, 256 );
	char *findpp = strrchr( szCurExePath,'\\' );
	strset( findpp + 1, '\0' );
	PUT_Strcpy( pszWorkFolder, szCurExePath );

}//	GetCurrentWorkFolder
//---------------------------------------------------------------------------------------
//!	파일 확장자 얻기.
void	PUT_GetFileExe( char* pszFile, char* pszOutExe )
{
	size_t nSizeFPath = strlen( pszFile );

	size_t nPosExe = 0;
	for( size_t nCur = nSizeFPath - 1; nCur > 0; --nCur ){
		if( pszFile[nCur] == '.' )
		{
			nPosExe = nCur;
			break;
		}
	}

	PUT_Strcpy( pszOutExe, &pszFile[ nPosExe + 1 ] );

}//	GetFileExe
//---------------------------------------------------------------------------------------
//!	파일명만 얻기.
void	PUT_GetFileName( char* pszFile, char* pszOutName )
{
	size_t nSizeFPath = strlen( pszFile );

	size_t nPosName = 0;
	for( size_t nCur = nSizeFPath - 1; nCur > 0; --nCur ){
		if( pszFile[nCur] == '\\' )
		{
			nPosName = nCur;
			break;
		}
	}

	PUT_Strcpy( pszOutName, &pszFile[ nPosName + 1 ] );

}//	GetFileName
//---------------------------------------------------------------------------------------
//!	파일경로 별로 얻기.
void	PUT_SplitPath(const std::string& inputPath, std::string* pathOnly, std::string* filenameOnly)
{
	std::string fullPath(inputPath);
	std::replace(fullPath.begin(),fullPath.end(),'\\','/');

	std::string::size_type lastSlashPos=fullPath.find_last_of('/');

	// check for there being no path element in the input
	if (lastSlashPos==std::string::npos)
	{
		*pathOnly="";
		*filenameOnly=fullPath;
	}
	else // do the split
	{
		if (pathOnly)
			*pathOnly=fullPath.substr(0,lastSlashPos);

		if (filenameOnly)
			*filenameOnly=fullPath.substr(lastSlashPos+1,fullPath.size()-lastSlashPos-1);
	}

}//	SplitPath
//---------------------------------------------------------------------------------------
//!	파일 경로가 존재하는가?
bool	PUT_IsFilePathExist( const char *pszFilePath )
{
	int nRet = access( pszFilePath, 0 );
	if( nRet == 0 )
		return true;

	return false;

}//	IsFilePathExist
//---------------------------------------------------------------------------------------
//!	읽기전용 파일인가?
bool	PUT_IsReadOnlyFile( const char* pszFilePath )
{
	DWORD	dwAttrs = GetFileAttributes( pszFilePath );

	if( dwAttrs != INVALID_FILE_ATTRIBUTES )
	{
		if( dwAttrs & FILE_ATTRIBUTE_READONLY )
			return true;
	}

	return false;

}//	IsReadOnlyFile
//---------------------------------------------------------------------------------------
//!	읽기전용 속성 제거.
bool	PUT_RemoveAttrReadOnly( const char* pszFilePath )
{
	if( PUT_IsReadOnlyFile( pszFilePath ) )
	{
		DWORD dwAttrs = GetFileAttributes( pszFilePath );

		if( SetFileAttributes( pszFilePath, dwAttrs & ~FILE_ATTRIBUTE_READONLY ) )
			return true;
	}

	return false;

}//	RemoveAttrReadOnly
//---------------------------------------------------------------------------------------
void	PUT_ChangeExt( TCHAR* ptszFName, TCHAR* ptszDstName, const TCHAR* ptszExe )
{
	TCHAR	tszDst[256]		=	{0};
	PUT_Strcpy( tszDst, ptszFName );
	TCHAR* ptszTmpFName	=	strchr( tszDst, _T('.') );
	*ptszTmpFName		=	_T('\0');
	strcat( tszDst, ptszExe );

	PUT_Strcpy( ptszDstName, tszDst );

}//	PUT_ChangeExt
//---------------------------------------------------------------------------------------
//	EOF