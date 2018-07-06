#ifndef _PUTCOMMONSTR_H_
#define	_PUTCOMMONSTR_H_
#pragma once
//------------------------------------------------------------------------------------------------
void	PUT_GetStrInQuot( TCHAR* ptszDst, const TCHAR* ptszSrc );
//------------------------------------------------------------------------------------------------
void	PUT_Trim( TCHAR *ptszBuff );
//------------------------------------------------------------------------------------------------
void	PUT_GetStrOneLineInFile( TCHAR* ptszDst, int nMaxLine, FILE* pf );
//------------------------------------------------------------------------------------------------
inline	void	PUT_ClearStr( TCHAR *pszTmp )	
{
	pszTmp[0]	=	0;

}//	ClearStr
//------------------------------------------------------------------------------------------------
inline	void	PUT_ClearStrPt( TCHAR *pszTmp )	
{
	pszTmp	=	0;

}//	ClearStrPt
//------------------------------------------------------------------------------------------------
inline bool	PUT_IsEmptyStr( TCHAR *psz )
{
	if( psz )
		return ( strlen( psz ) > 0 ) ? (false) : (true);

	return false;

}//	IsEmptyStr
//------------------------------------------------------------------------------------------------
inline bool	PUT_StrCmp( const TCHAR *psz1, const TCHAR *psz2 )
{
	return (strcmp( psz1, psz2 ) == 0) ? ( true ) : ( false );

}//	PUT_StrCmp
//------------------------------------------------------------------------------------------------
inline bool	PUT_StrNiCmp( const TCHAR *psz1, const TCHAR *psz2 )
{
	return (strnicmp( psz1, psz2, strlen(psz2) ) == 0) ? ( true ) : ( false );

}//	PUT_StrNiCmp
//------------------------------------------------------------------------------------------------
inline void	PUT_SetFMultiByteTWideChar( char *pMulti, WCHAR *pWide )
{
	MultiByteToWideChar( CP_ACP, 0, pMulti, -1, pWide, (int)strlen(pMulti) );

}//	SetFMultiByteTWideChar
//------------------------------------------------------------------------------------------------
inline void	PUT_SetFWideCharTMultiByte( WCHAR *pszWide, char *pMulti, int nSizeMulti )
{
	WideCharToMultiByte( CP_ACP, 0, pszWide, -1, pMulti, nSizeMulti, 0, 0 );

}//	SetFWideCharTMultiByte
//------------------------------------------------------------------------------------------------
#endif	//	_PUTCOMMONSTR_H_