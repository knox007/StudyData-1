#ifndef _PUTCOMMONFPATH_H_
#define _PUTCOMMONFPATH_H_

#pragma once

#include<string>

//!	���� ��� ���.
void	PUT_GetFilePath( char *pszFileName, char *pszFileOut, bool bDirCur = false );

//!	���� �۾� ��� ���.
void	PUT_GetCurrentWorkFolder( char *pszWorkFolder );

//!	���� Ȯ���� ���.
void	PUT_GetFileExe( char* pszFile, char* pszOutExe );

//!	���ϸ� ���.
void	PUT_GetFileName( char* pszFile, char* pszOutName );

//!	���ϰ�� ���� ���.
void	PUT_SplitPath(const std::string& inputPath, std::string* pathOnly, std::string* filenameOnly);

//!	���� ��ΰ� �����ϴ°�?
bool	PUT_IsFilePathExist( const char *pszFilePath );

//!	�б����� �����ΰ�?
bool	PUT_IsReadOnlyFile( const char* pszFilePath );

//!	�б����� �Ӽ� ����.
bool	PUT_RemoveAttrReadOnly( const char* pszFilePath );

//!	Ȯ���� �ٲٱ�
void	PUT_ChangeExt( TCHAR* ptszFName, TCHAR* ptszDstName, const TCHAR* ptszExe );

#endif
//	_PUTCOMMONFPATH_H_
