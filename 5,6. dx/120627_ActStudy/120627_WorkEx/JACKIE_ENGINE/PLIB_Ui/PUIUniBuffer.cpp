#include "StdAfx.h"
#include "PUICtrlCommon.h"
#include "PUIUniBuffer.h"
#include "PUTCommon.h"
#include <strsafe.h>

const WCHAR* UNISCRIBE_DLLNAME = L"\\usp10.dll";

//----------------------------------------------------------------------------------
HINSTANCE CPUIUniBuffer::s_hDll = NULL;
HRESULT		(WINAPI *CPUIUniBuffer::_ScriptApplyDigitSubstitution)( const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*, SCRIPT_STATE* )
= Dummy_ScriptApplyDigitSubstitution;
HRESULT		(WINAPI *CPUIUniBuffer::_ScriptStringAnalyse)( HDC, const void *, int, int, int, DWORD, int, SCRIPT_CONTROL*, SCRIPT_STATE*, const int*, SCRIPT_TABDEF*, const BYTE*, SCRIPT_STRING_ANALYSIS* )
= Dummy_ScriptStringAnalyse;
HRESULT		(WINAPI *CPUIUniBuffer::_ScriptStringCPtoX)( SCRIPT_STRING_ANALYSIS, int, BOOL, int* )
= Dummy_ScriptStringCPtoX;
HRESULT		(WINAPI *CPUIUniBuffer::_ScriptStringXtoCP)( SCRIPT_STRING_ANALYSIS, int, int*, int* )
= Dummy_ScriptStringXtoCP;
HRESULT		(WINAPI *CPUIUniBuffer::_ScriptStringFree)( SCRIPT_STRING_ANALYSIS* )
= Dummy_ScriptStringFree;
const int*	(WINAPI *CPUIUniBuffer::_ScriptString_pcOutChars)( SCRIPT_STRING_ANALYSIS )
= Dummy_ScriptString_pcOutChars;
const SCRIPT_LOGATTR* (WINAPI *CPUIUniBuffer::_ScriptString_pLogAttr)( SCRIPT_STRING_ANALYSIS )
= Dummy_ScriptString_pLogAttr;
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::InitMembers()
{
	Initialize();

	m_nBufferSize		=	0;
	m_ptszBuffer		=	NULL;
	m_bAnalyseRequired	=	true;
	m_Analysis			=	NULL;
	m_pFontNode			=	NULL;
}//	InitMembers
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::ClearMembers()
{
	delete[] m_ptszBuffer;
	if( m_Analysis )
		_ScriptStringFree( &m_Analysis );
}//	ClearMembers
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::Initialize()
{
	if( s_hDll )
		return;

	WCHAR	tszPath[ MAX_PATH + 1 ] = {0,};
	if( !GetSystemDirectoryW( tszPath, MAX_PATH + 1 ) )
		return;

	int nLen1	=	lstrlenW( tszPath );
	int nLen2	=	lstrlenW( UNISCRIBE_DLLNAME );
	if( nLen1 + nLen2 > MAX_PATH )
		return;

	StringCchCatW( tszPath, MAX_PATH, UNISCRIBE_DLLNAME );

	s_hDll	=	LoadLibraryW( tszPath );
	if( s_hDll )
	{
		FARPROC		Temp;

		GETPROCADDRESS( s_hDll, ScriptApplyDigitSubstitution, Temp );
		GETPROCADDRESS( s_hDll, ScriptStringAnalyse, Temp );
		GETPROCADDRESS( s_hDll, ScriptStringCPtoX, Temp );
		GETPROCADDRESS( s_hDll, ScriptStringXtoCP, Temp );
		GETPROCADDRESS( s_hDll, ScriptStringFree, Temp );
		GETPROCADDRESS( s_hDll, ScriptString_pLogAttr, Temp );
		GETPROCADDRESS( s_hDll, ScriptString_pcOutChars, Temp );
	}
}//	Initialize
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::UnInitialize()
{
	if( s_hDll )
	{
		PLACEHOLDERPROC( ScriptApplyDigitSubstitution );
		PLACEHOLDERPROC( ScriptStringAnalyse );
		PLACEHOLDERPROC( ScriptStringCPtoX );
		PLACEHOLDERPROC( ScriptStringXtoCP );
		PLACEHOLDERPROC( ScriptStringFree );
		PLACEHOLDERPROC( ScriptString_pLogAttr );
		PLACEHOLDERPROC( ScriptString_pcOutChars );

		FreeLibrary( s_hDll );
		s_hDll	=	NULL;
	}
}//	UnInitialize
//----------------------------------------------------------------------------------
bool	CPUIUniBuffer::SetBufferSize( int nNewSize )
{
	if( m_nBufferSize == JUI_MAX_EDITBOXLENGTH )
		return false;

	int nAllocSize =	( nNewSize == -1 || nNewSize < m_nBufferSize * 2 ) ?
						( m_nBufferSize ? m_nBufferSize * 2 : 256 ) : nNewSize * 2;
	if( nAllocSize > JUI_MAX_EDITBOXLENGTH )
		nAllocSize = JUI_MAX_EDITBOXLENGTH;

	WCHAR	*ptszTempBuff	=	NULL;
	PUTNEW( ptszTempBuff, WCHAR[nAllocSize] );

	if( !ptszTempBuff )
		return false;

	if( m_ptszBuffer )
	{
		CopyMemory( ptszTempBuff, m_ptszBuffer, m_nBufferSize * sizeof( WCHAR ) );
		delete[] m_ptszBuffer;
	}else
	{
		PUT_ZERO_MEMORY_PTR( ptszTempBuff );
	}

	m_ptszBuffer	=	ptszTempBuff;
	m_nBufferSize	=	nAllocSize;
	
	return true;
}//	SetBufferSize
//----------------------------------------------------------------------------------
HRESULT		CPUIUniBuffer::Analyse()
{
	if( m_Analysis )
		_ScriptStringFree( &m_Analysis );

	SCRIPT_CONTROL	ScriptCtrl;
	SCRIPT_STATE	ScriptState;
	PUT_ZERO_MEMORY( ScriptCtrl );
	PUT_ZERO_MEMORY( ScriptState );
	_ScriptApplyDigitSubstitution( NULL, &ScriptCtrl, &ScriptState );

	if( !m_pFontNode )
		return E_FAIL;

	HRESULT	hr	=	_ScriptStringAnalyse(	m_pFontNode->m_pFont ? m_pFontNode->m_pFont->GetDC() : NULL,
		m_ptszBuffer,
		lstrlenW( m_ptszBuffer ) + 1,
		lstrlenW( m_ptszBuffer ) * 3 / 2 + 16,
		-1, 
		SSA_BREAK | SSA_GLYPHS | SSA_FALLBACK | SSA_LINK,
		0,
		&ScriptCtrl,
		&ScriptState,
		NULL,
		NULL,
		NULL,
		&m_Analysis );

	if( SUCCEEDED( hr ) )
		m_bAnalyseRequired	=	false;

	return hr;
}//	Analyse
//----------------------------------------------------------------------------------
WCHAR&	CPUIUniBuffer::operator []( int n )
{
	m_bAnalyseRequired	=	true;
	return m_ptszBuffer[n];
}//	operator []
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::Clear()
{
	m_ptszBuffer = NULL;
	m_bAnalyseRequired	=	true;
}//	Clear
//----------------------------------------------------------------------------------
bool	CPUIUniBuffer::InsertChar( int nID, WCHAR tChar )
{
	assert( nID >= 0 );

	if( nID < 0 || nID > lstrlenW( m_ptszBuffer ) )
		return false;
	
	if( GetTextSize() + 1 >= JUI_MAX_EDITBOXLENGTH )
		return false;

	if( lstrlenW( m_ptszBuffer ) + 1 >= m_nBufferSize )
		if( !SetBufferSize( -1 ) )
			return false;

	assert( m_nBufferSize >= 2 );

	WCHAR	*pDest	=	m_ptszBuffer + lstrlenW( m_ptszBuffer ) + 1;
	WCHAR	*pStop	=	m_ptszBuffer + nID;
	WCHAR	*pSrc	=	pDest - 1;

	while( pDest > pStop )
	{
		*pDest-- = *pSrc--;
	}

	m_ptszBuffer[ nID ]	=	tChar;
	m_bAnalyseRequired	=	true;

	return true;	
}//	InsertChar
//----------------------------------------------------------------------------------
bool	CPUIUniBuffer::RemoveChar( int nID )
{
	if( !lstrlenW( m_ptszBuffer ) || nID < 0 || nID >= lstrlenW( m_ptszBuffer ) )
		return false;

	MoveMemory( m_ptszBuffer + nID, m_ptszBuffer + nID + 1, sizeof( WCHAR ) * ( lstrlenW( m_ptszBuffer ) - nID ) );

	m_bAnalyseRequired	=	true;
	return true;
}//	RemoveChar
//----------------------------------------------------------------------------------
bool	CPUIUniBuffer::InsertString( int nID, const WCHAR* ptszText, int nCount /* = -1 */ )
{
	assert( nID >= 0 );

	if( nID > lstrlenW( m_ptszBuffer ) )
		return false;

	if( nCount == -1 )
		nCount = lstrlenW( ptszText );

	if( GetTextSize() + nCount > JUI_MAX_EDITBOXLENGTH )
		return false;

	if( lstrlenW( m_ptszBuffer ) + nCount >= m_nBufferSize )
		if( !SetBufferSize( lstrlenW( m_ptszBuffer ) + nCount + 1 ) )
			return false;

	MoveMemory( m_ptszBuffer + nID + nCount, m_ptszBuffer + nID, sizeof( WCHAR ) * ( lstrlenW( m_ptszBuffer ) - nID + 1 ) );
	CopyMemory( m_ptszBuffer + nID, ptszText, nCount * sizeof( WCHAR ) );

	m_bAnalyseRequired = true;

	return true;
}//	InsertString
//----------------------------------------------------------------------------------
bool	CPUIUniBuffer::SetText( const WCHAR* ptszText )
{
	assert( ptszText != NULL );

	int nRequired = int( wcslen( ptszText ) + 1 );

	if( nRequired >= JUI_MAX_EDITBOXLENGTH )
		return false;

	while( GetBufferSize() < nRequired )
		if( !SetBufferSize( -1 ) )
			break;

	if( GetBufferSize() >= nRequired )
	{
		StringCchCopyW( m_ptszBuffer, GetBufferSize(), ptszText );
		m_bAnalyseRequired	=	true;
		return true;
	}else
		return false;
}//	SetText
//----------------------------------------------------------------------------------
HRESULT		CPUIUniBuffer::CPtoX( int nCP, BOOL bTrail, int* pnX )
{
	assert( pnX );
	*pnX	=	0;

	HRESULT	hr	=	S_OK;
	if( m_bAnalyseRequired )
		hr = Analyse();

	if( SUCCEEDED( hr ) )
		hr = _ScriptStringCPtoX( m_Analysis, nCP, bTrail, pnX );

	return hr;
}//	CPtoX
//----------------------------------------------------------------------------------
HRESULT		CPUIUniBuffer::XtoCP( int nX, int* pnCP, int* pnTrail )
{
	assert( pnCP && pnTrail );
	*pnCP		=	0;
	*pnTrail	=	FALSE;

	HRESULT	hr	=	S_OK;
	if( m_bAnalyseRequired )
		hr	=	Analyse();

	if( SUCCEEDED( hr ) )
		hr	=	_ScriptStringXtoCP( m_Analysis, nX, pnCP, pnTrail );

	if( *pnCP == -1 && *pnTrail == TRUE )
	{
		*pnCP		=	0;
		*pnTrail	=	FALSE;
	}else	
		if( *pnCP > lstrlenW( m_ptszBuffer ) && *pnTrail == FALSE )
		{
			*pnCP		=	lstrlenW( m_ptszBuffer );		
			*pnTrail	=	TRUE;
		}

		return hr;	
}//	XtoCP
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::GetPriorItemPos( int nCP, int* pnPrior )
{
	*pnPrior	=	nCP;

	if( m_bAnalyseRequired )
		if( FAILED( Analyse() ) )
			return;

	const SCRIPT_LOGATTR *pLogAttr = _ScriptString_pLogAttr( m_Analysis );
	if( !pLogAttr )
		return;

	if( !_ScriptString_pcOutChars( m_Analysis ) )
		return;

	int nInitial	=	*_ScriptString_pcOutChars( m_Analysis );
	if( nCP - 1 < nInitial )
		nInitial = nCP - 1;

	for( int nIdx = nInitial; nIdx > 0; --nIdx )
	{
		if(	pLogAttr[nIdx].fWordStop ||
			( !pLogAttr[nIdx].fWhiteSpace &&
			  pLogAttr[nIdx - 1].fWhiteSpace ) )
		{
			*pnPrior = nIdx;
			return;
		}
	}

	*pnPrior = 0;

}//	GetPriorItemPos
//----------------------------------------------------------------------------------
void	CPUIUniBuffer::GetNextItemPos( int nCP, int* pnPrior )
{
	*pnPrior	=	nCP;

	HRESULT	hr = S_OK;

	if( m_bAnalyseRequired )
		hr = Analyse();

	if( FAILED( hr ) )
		return;

	const SCRIPT_LOGATTR *pLogAttr	=	_ScriptString_pLogAttr( m_Analysis );
	if( !pLogAttr )
		return;

	if( !_ScriptString_pcOutChars( m_Analysis ) )
		return;

	int nInitial	=	*_ScriptString_pcOutChars( m_Analysis );
	if( nCP + 1 < nInitial )
		nInitial = nCP + 1;

	for( int nIdx = nInitial; nIdx < *_ScriptString_pcOutChars( m_Analysis ) - 1; ++nIdx )
	{
		if( pLogAttr[nIdx].fWordStop )
		{
			*pnPrior	=	nIdx;
			return;
		}else
			if( pLogAttr[nIdx].fWhiteSpace &&
				!pLogAttr[nIdx+1].fWhiteSpace )
			{
				*pnPrior	=	nIdx + 1;
				return;
			}
	}

	*pnPrior	=	*_ScriptString_pcOutChars( m_Analysis ) - 1;
}//	GetNextItemPos
//----------------------------------------------------------------------------------
//	EOF