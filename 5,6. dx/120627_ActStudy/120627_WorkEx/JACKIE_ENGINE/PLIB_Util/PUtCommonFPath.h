#ifndef _PUTCOMMONFPATH_H_
#define _PUTCOMMONFPATH_H_

#pragma once

#include<string>

//!	파일 경로 얻기.
void	PUT_GetFilePath( char *pszFileName, char *pszFileOut, bool bDirCur = false );

//!	현재 작업 경로 얻기.
void	PUT_GetCurrentWorkFolder( char *pszWorkFolder );

//!	파일 확장자 얻기.
void	PUT_GetFileExe( char* pszFile, char* pszOutExe );

//!	파일명만 얻기.
void	PUT_GetFileName( char* pszFile, char* pszOutName );

//!	파일경로 별로 얻기.
void	PUT_SplitPath(const std::string& inputPath, std::string* pathOnly, std::string* filenameOnly);

//!	파일 경로가 존재하는가?
bool	PUT_IsFilePathExist( const char *pszFilePath );

//!	읽기전용 파일인가?
bool	PUT_IsReadOnlyFile( const char* pszFilePath );

//!	읽기전용 속성 제거.
bool	PUT_RemoveAttrReadOnly( const char* pszFilePath );

//!	확장자 바꾸기
void	PUT_ChangeExt( TCHAR* ptszFName, TCHAR* ptszDstName, const TCHAR* ptszExe );

#endif
//	_PUTCOMMONFPATH_H_
