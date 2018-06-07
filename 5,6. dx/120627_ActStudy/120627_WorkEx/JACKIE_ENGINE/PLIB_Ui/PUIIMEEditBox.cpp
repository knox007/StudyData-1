#include "StdAfx.h"
#include "PUIIMEEditBox.h"
#include "PUIIMECommon.h"
#include "PUTCommon.h"
#include "PUIDlg.h"
#include "PUICtrlMisc.h"

#include <strsafe.h>

const WCHAR* IMM32_DLLNAME	=	L"\\imm32.dll";
const WCHAR* VER_DLLNAME	=	L"\\version.dll";

//--------------------------------------------------------------------------------------
// Function pointers
INPUTCONTEXT* (WINAPI * CPUIIMEEditBox::_ImmLockIMC)( HIMC ) = CPUIIMEEditBox::Dummy_ImmLockIMC;
BOOL (WINAPI * CPUIIMEEditBox::_ImmUnlockIMC)( HIMC ) = CPUIIMEEditBox::Dummy_ImmUnlockIMC;
LPVOID (WINAPI * CPUIIMEEditBox::_ImmLockIMCC)( HIMCC ) = CPUIIMEEditBox::Dummy_ImmLockIMCC;
BOOL (WINAPI * CPUIIMEEditBox::_ImmUnlockIMCC)( HIMCC ) = CPUIIMEEditBox::Dummy_ImmUnlockIMCC;
BOOL (WINAPI * CPUIIMEEditBox::_ImmDisableTextFrameService)( DWORD ) = CPUIIMEEditBox::Dummy_ImmDisableTextFrameService;
LONG (WINAPI * CPUIIMEEditBox::_ImmGetCompositionString)( HIMC, DWORD, LPVOID, DWORD ) = CPUIIMEEditBox::Dummy_ImmGetCompositionString;
DWORD (WINAPI * CPUIIMEEditBox::_ImmGetCandidateList)( HIMC, DWORD, LPCANDIDATELIST, DWORD ) = CPUIIMEEditBox::Dummy_ImmGetCandidateList;
HIMC (WINAPI * CPUIIMEEditBox::_ImmGetContext)( HWND ) = CPUIIMEEditBox::Dummy_ImmGetContext;
BOOL (WINAPI * CPUIIMEEditBox::_ImmReleaseContext)( HWND, HIMC ) = CPUIIMEEditBox::Dummy_ImmReleaseContext;
HIMC (WINAPI * CPUIIMEEditBox::_ImmAssociateContext)( HWND, HIMC ) = CPUIIMEEditBox::Dummy_ImmAssociateContext;
BOOL (WINAPI * CPUIIMEEditBox::_ImmGetOpenStatus)( HIMC ) = CPUIIMEEditBox::Dummy_ImmGetOpenStatus;
BOOL (WINAPI * CPUIIMEEditBox::_ImmSetOpenStatus)( HIMC, BOOL ) = CPUIIMEEditBox::Dummy_ImmSetOpenStatus;
BOOL (WINAPI * CPUIIMEEditBox::_ImmGetConversionStatus)( HIMC, LPDWORD, LPDWORD ) = CPUIIMEEditBox::Dummy_ImmGetConversionStatus;
HWND (WINAPI * CPUIIMEEditBox::_ImmGetDefaultIMEWnd)( HWND ) = CPUIIMEEditBox::Dummy_ImmGetDefaultIMEWnd;
UINT (WINAPI * CPUIIMEEditBox::_ImmGetIMEFileNameA)( HKL, LPSTR, UINT ) = CPUIIMEEditBox::Dummy_ImmGetIMEFileNameA;
UINT (WINAPI * CPUIIMEEditBox::_ImmGetVirtualKey)( HWND ) = CPUIIMEEditBox::Dummy_ImmGetVirtualKey;
BOOL (WINAPI * CPUIIMEEditBox::_ImmNotifyIME)( HIMC, DWORD, DWORD, DWORD ) = CPUIIMEEditBox::Dummy_ImmNotifyIME;
BOOL (WINAPI * CPUIIMEEditBox::_ImmSetConversionStatus)( HIMC, DWORD, DWORD ) = CPUIIMEEditBox::Dummy_ImmSetConversionStatus;
BOOL (WINAPI * CPUIIMEEditBox::_ImmSimulateHotKey)( HWND, DWORD ) = CPUIIMEEditBox::Dummy_ImmSimulateHotKey;
BOOL (WINAPI * CPUIIMEEditBox::_ImmIsIME)( HKL ) = CPUIIMEEditBox::Dummy_ImmIsIME;
UINT (WINAPI * CPUIIMEEditBox::_GetReadingString)( HIMC, UINT, LPWSTR, PINT, BOOL*, UINT* ) = CPUIIMEEditBox::Dummy_GetReadingString; // Traditional Chinese IME
BOOL (WINAPI * CPUIIMEEditBox::_ShowReadingWindow)( HIMC, BOOL ) = CPUIIMEEditBox::Dummy_ShowReadingWindow; // Traditional Chinese IME
BOOL (APIENTRY * CPUIIMEEditBox::_VerQueryValueA)( const LPVOID, LPSTR, LPVOID *, UINT* ) = CPUIIMEEditBox::Dummy_VerQueryValueA;
BOOL (APIENTRY * CPUIIMEEditBox::_GetFileVersionInfoA)( LPSTR, DWORD, DWORD, LPVOID )= CPUIIMEEditBox::Dummy_GetFileVersionInfoA;
DWORD (APIENTRY * CPUIIMEEditBox::_GetFileVersionInfoSizeA)( LPSTR, LPDWORD ) = CPUIIMEEditBox::Dummy_GetFileVersionInfoSizeA;

HINSTANCE CPUIIMEEditBox::stt_hDllImm32;					// IMM32 DLL handle
HINSTANCE CPUIIMEEditBox::stt_hDllVer;				    // Version DLL handle
HKL       CPUIIMEEditBox::stt_hKeyboardLayerCurrent;		// Current keyboard layout of the process
bool      CPUIIMEEditBox::stt_bVerticalCand;				// Indicates that the candidates are listed vertically

WCHAR     CPUIIMEEditBox::stt_tszIndicatorArr[5][3] =		// String to draw to indicate current input locale
{
	L"En",
	L"\x7B80",
	L"\x7E41",
	L"\xAC00",
	L"\x3042"
};
 

WCHAR*		CPUIIMEEditBox::stt_ptszCurrentIndicator = 
CPUIIMEEditBox::stt_tszIndicatorArr[0];										// Points to an indicator string that corresponds to current input locale
bool		CPUIIMEEditBox::stt_bInsertOnType;									// Insert the character as soon as a key is pressed (Korean behavior)
HINSTANCE CPUIIMEEditBox::stt_hDllIme;										// Instance handle of the current IME module
HIMC		CPUIIMEEditBox::stt_hImcDef;										// Default input context
CPUIIMEEditBox::eIMESTATE_  CPUIIMEEditBox::stt_eImeState = eIMESTATE_OFF;
bool		CPUIIMEEditBox::stt_bActiveImeSystem;								// Whether the IME system is active
POINT		CPUIIMEEditBox::stt_ptCompString;									// Composition string position. Updated every frame.
int			CPUIIMEEditBox::stt_nCompCaretPosition;
int			CPUIIMEEditBox::stt_nFirstTargetConv;								// Index of the first target converted char in comp string.  If none, -1.
CPUIUniBuffer CPUIIMEEditBox::stt_CompString = CPUIUniBuffer( 0 );
BYTE		CPUIIMEEditBox::stt_byCompStringAttrArr[MAX_COMPSTRING_SIZE];
DWORD		CPUIIMEEditBox::stt_dwCompStringClause[MAX_COMPSTRING_SIZE];
WCHAR		CPUIIMEEditBox::stt_tszReadingString[32];
CPUIIMEEditBox::sJUICandList CPUIIMEEditBox::stt_CandList;					// Data relevant to the candidate list
bool		CPUIIMEEditBox::stt_bVisibleReadingWindow;						// Indicates whether reading window is visible
bool		CPUIIMEEditBox::stt_bHorizReading;								// Indicates whether the reading window is vertical or horizontal
bool		CPUIIMEEditBox::stt_bChineseIME;
CPUTListMgrPt<CPUIIMEEditBox::sInputLocale>	CPUIIMEEditBox::stt_LocaleArr;	// Array of loaded keyboard layout on system
#if defined(DEBUG) || defined(_DEBUG)
bool		CPUIIMEEditBox::s_bIMEStaticMsgProcCalledForDBG = false;
#endif

#define		LCID_INVARIANT		MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ), SORT_DEFAULT )
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::InitMembers()
{
	CPUIIMEEditBox::Initialize();
	_ImmDisableTextFrameService( (DWORD) - 1 );

	m_eCtrlType	=	eCTRLTYPE_IMEEDITBOX;

	stt_bActiveImeSystem	=	true;
	m_nIndicatorWidth		=	0;

	SetIMEColor( eIMECOLOR_READING,								D3DCOLOR_ARGB( 188,		255,	255,	255 ) );
	SetIMEColor( eIMECOLOR_READING_WINDOW,						D3DCOLOR_ARGB( 128,		0,		0,		0 ) );
	SetIMEColor( eIMECOLOR_READING_SELECTED,					D3DCOLOR_ARGB( 255,		255,	0,		0 ) );
	SetIMEColor( eIMECOLOR_READING_SELECTEDBACKGROUND,			D3DCOLOR_ARGB( 128,		80,		80,		80 ) );

	SetIMEColor( eIMECOLOR_CANDIDATE,							D3DCOLOR_ARGB( 255,		200,	200,	200 ) );
	SetIMEColor( eIMECOLOR_CANDIDATE_WINDOW,					D3DCOLOR_ARGB( 128,		0,		0,		0 ) );
	SetIMEColor( eIMECOLOR_CANDIDATE_SELECTED,					D3DCOLOR_ARGB( 255,		255,	255,	255 ) );
	SetIMEColor( eIMECOLOR_CANDIDATE_SELECTEDBACKGROUND,		D3DCOLOR_ARGB( 128,		158,	158,	158 ) );
	
	SetIMEColor( eIMECOLOR_COMP,								D3DCOLOR_ARGB( 255,		200,	200,	255 ) );
	SetIMEColor( eIMECOLOR_COMP_WINDOW,							D3DCOLOR_ARGB( 198,		0,		0,		0 ) );
	SetIMEColor( eIMECOLOR_COMP_CARET,							D3DCOLOR_ARGB( 255,		255,	255,	255 ) );
	SetIMEColor( eIMECOLOR_COMP_TARGET,							D3DCOLOR_ARGB( 255,		255,	255,	255 ) );
	SetIMEColor( eIMECOLOR_COMP_TARGETBACKGROUND,				D3DCOLOR_ARGB( 255,		150,	150,	150 ) );
	SetIMEColor( eIMECOLOR_COMP_TARGETNONE,						D3DCOLOR_ARGB( 255,		255,	255,	0 ) );
	SetIMEColor( eIMECOLOR_COMP_TARGETNONEBACKGROUND,			D3DCOLOR_ARGB( 255,		150,	150,	150 ) );

	SetIMEColor( eIMECOLOR_INDICATOR_IME,						D3DCOLOR_ARGB( 255,		255,	255,	255 ) );
	SetIMEColor( eIMECOLOR_INDICATOR_ENG,						D3DCOLOR_ARGB( 255,		0,		0,		0 ) );
	SetIMEColor( eIMECOLOR_INDICATOR_BACKGROUND,				D3DCOLOR_ARGB( 255,		128,	128,	128 ) );
}//	InitMembers
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::Initialize()
{
	if( stt_hDllImm32 )	//!	한번만 실행되어야 함.
		return;

	FARPROC Temp;

	stt_CompString.SetBufferSize( MAX_COMPSTRING_SIZE );
	
	WCHAR tszPath[MAX_PATH + 1];
	if( !::GetSystemDirectoryW( tszPath, MAX_PATH + 1 ) )
		return;

	StringCchCatW( tszPath, MAX_PATH, IMM32_DLLNAME );
	stt_hDllImm32	=	LoadLibraryW( tszPath );

	if( stt_hDllImm32 )
	{
		GETPROCADDRESS( stt_hDllImm32, ImmLockIMC,		Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmUnlockIMC,	Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmLockIMCC,		Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmUnlockIMCC,	Temp );

		GETPROCADDRESS( stt_hDllImm32, ImmDisableTextFrameService,	Temp );

		GETPROCADDRESS( stt_hDllImm32, ImmGetCompositionString,		Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetCandidateList,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetContext,				Temp );

		GETPROCADDRESS( stt_hDllImm32, ImmReleaseContext,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmAssociateContext,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetOpenStatus,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmSetOpenStatus,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetConversionStatus,		Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetDefaultIMEWnd,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetIMEFileNameA,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmGetVirtualKey,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmNotifyIME,				Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmSetConversionStatus,		Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmSimulateHotKey,			Temp );
		GETPROCADDRESS( stt_hDllImm32, ImmIsIME,					Temp );

	}//	if( stt_hDllImm32 )

	if( !::GetSystemDirectoryW( tszPath, MAX_PATH + 1 ) )
		return;

	StringCchCatW( tszPath, MAX_PATH, VER_DLLNAME );

	stt_hDllVer	=	LoadLibraryW( tszPath );

	if( stt_hDllVer )
	{
		GETPROCADDRESS( stt_hDllVer, VerQueryValueA,				Temp );
		GETPROCADDRESS( stt_hDllVer, GetFileVersionInfoA,		Temp );
		GETPROCADDRESS( stt_hDllVer, GetFileVersionInfoSizeA,	Temp );
	}
}//	Initialize
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::UnInitialize()
{
	if( stt_hDllImm32 )
	{
		PLACEHOLDERPROC( ImmLockIMC );
		PLACEHOLDERPROC( ImmUnlockIMC );
		PLACEHOLDERPROC( ImmLockIMCC );
		PLACEHOLDERPROC( ImmUnlockIMCC );
		PLACEHOLDERPROC( ImmDisableTextFrameService );
		PLACEHOLDERPROC( ImmGetCompositionString );
		PLACEHOLDERPROC( ImmGetCandidateList );
		PLACEHOLDERPROC( ImmGetContext );
		PLACEHOLDERPROC( ImmReleaseContext );
		PLACEHOLDERPROC( ImmAssociateContext );
		PLACEHOLDERPROC( ImmGetOpenStatus );
		PLACEHOLDERPROC( ImmSetOpenStatus );
		PLACEHOLDERPROC( ImmGetConversionStatus );
		PLACEHOLDERPROC( ImmGetDefaultIMEWnd );
		PLACEHOLDERPROC( ImmGetIMEFileNameA );
		PLACEHOLDERPROC( ImmGetVirtualKey );
		PLACEHOLDERPROC( ImmNotifyIME );
		PLACEHOLDERPROC( ImmSetConversionStatus );
		PLACEHOLDERPROC( ImmSimulateHotKey );
		PLACEHOLDERPROC( ImmIsIME );

		FreeLibrary( stt_hDllImm32 );
		stt_hDllImm32	=	NULL;
	}

	if( stt_hDllIme )
	{
		PLACEHOLDERPROC( GetReadingString );
		PLACEHOLDERPROC( ShowReadingWindow );

		FreeLibrary( stt_hDllIme );
		stt_hDllIme		=	NULL;
	}

	if( stt_hDllVer )
	{
		PLACEHOLDERPROC( VerQueryValueA );
		PLACEHOLDERPROC( GetFileVersionInfoA );
		PLACEHOLDERPROC( GetFileVersionInfoSizeA );

		FreeLibrary( stt_hDllVer );
		stt_hDllVer		=	NULL;
	}

}//	UnInitialize
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::SendKey( BYTE byVirtKey )
{
	keybd_event( byVirtKey, 0,		0,					0 );
	keybd_event( byVirtKey, 0,		KEYEVENTF_KEYUP,	0 );
}//	SendKey
//--------------------------------------------------------------------------------------
HRESULT	CPUIIMEEditBox::StaticOnCreateDevice( HWND hWnd )
{
	stt_hImcDef	=	_ImmGetContext( hWnd );
	assert( !stt_hImcDef );
	_ImmReleaseContext( hWnd, stt_hImcDef );

	return S_OK;
}//	StaticOnCreateDevice
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::UpdateRects()
{
	int nWidth	=	m_nWidth;
	m_nWidth	-=	m_nIndicatorWidth + m_nBorder * 2;
	CPUIEditBox::UpdateRects();
	m_nWidth	=	nWidth;

	SetRect( &m_rcIndicator, m_rcBoundBox.right, m_rcBoundBox.top, m_nPosX + m_nWidth, m_rcBoundBox.bottom );
	m_rcBoundBox.right	=	m_rcBoundBox.left + m_nWidth;
}//	UpdateRects
//--------------------------------------------------------------------------------------
DWORD	CPUIIMEEditBox::GetIMEId( UINT unIdx /* = 0 */ )
{
	static	HKL		hklPrev	=	0;
	static	DWORD	dwID[2]	=	{ 0, 0 };

	DWORD	dwVerSize;
	DWORD	dwVerHandle;
	LPVOID	lpVerBuffer;
	LPVOID	lpVerData;
	UINT	unVerData;
	char	tszTmp[1024];

	if( unIdx >= sizeof( dwID ) / sizeof( dwID[0] ) )
		return 0;

	if( hklPrev == stt_hKeyboardLayerCurrent )
		return dwID[unIdx];

	hklPrev	=	stt_hKeyboardLayerCurrent;

	if( !( ( stt_hKeyboardLayerCurrent == _CHT_HKL ) || ( stt_hKeyboardLayerCurrent == _CHT_HKL2 ) || ( stt_hKeyboardLayerCurrent == _CHT_HKL ) ) )
	{
		dwID[0]	=	dwID[1]	=	0;
		return dwID[unIdx];
	}

	if( !_GetReadingString )
	{
		if( ( CompareString( LCID_INVARIANT, NORM_IGNORECASE, tszTmp, -1, CHT_IMEFILENAME1, -1 ) != CSTR_EQUAL ) &&
			( CompareString( LCID_INVARIANT, NORM_IGNORECASE, tszTmp, -1, CHT_IMEFILENAME2, -1 ) != CSTR_EQUAL ) &&
			( CompareString( LCID_INVARIANT, NORM_IGNORECASE, tszTmp, -1, CHT_IMEFILENAME3, -1 ) != CSTR_EQUAL ) &&
			( CompareString( LCID_INVARIANT, NORM_IGNORECASE, tszTmp, -1, CHS_IMEFILENAME1, -1 ) != CSTR_EQUAL ) &&
			( CompareString( LCID_INVARIANT, NORM_IGNORECASE, tszTmp, -1, CHS_IMEFILENAME2, -1 ) != CSTR_EQUAL ) )
		{
			dwID[0] = dwID[1] = 0;
			return dwID[unIdx];
		}			
	}

	dwVerSize	=	_GetFileVersionInfoSizeA( tszTmp, &dwVerHandle );
	if( dwVerSize )
	{
		lpVerBuffer	=	HeapAlloc( GetProcessHeap(), 0, dwVerSize );
		if( lpVerBuffer )
		{
			if( _GetFileVersionInfoA( tszTmp, dwVerHandle, dwVerSize, lpVerBuffer ) )
			{
				if( _VerQueryValueA( lpVerBuffer, "\\", &lpVerData, &unVerData ) )
				{
					DWORD	dwVer	=	( ( VS_FIXEDFILEINFO*)lpVerData )->dwFileVersionMS;
					dwVer	=	( dwVer & 0x00ff0000 ) << 8 | ( dwVer & 0x000000ff ) << 16;

					if( _GetReadingString
						||
						( GetLanguage() == LANG_CHT &&
						(	dwVer == MAKEIMEVERSION(4, 2)	||
							dwVer == MAKEIMEVERSION(4, 3)	||
							dwVer == MAKEIMEVERSION(4, 4)	||

							dwVer == MAKEIMEVERSION(5, 0)	||
							dwVer == MAKEIMEVERSION(5, 1)	||
							dwVer == MAKEIMEVERSION(5, 2)	||

							dwVer == MAKEIMEVERSION(6, 0) ) )
							||
						( GetLanguage() == LANG_CHS &&
						(	dwVer == MAKEIMEVERSION(4, 1)	||
							dwVer == MAKEIMEVERSION(4, 2)	||
							dwVer == MAKEIMEVERSION(5, 3) ) )
					)
					{
						dwID[0]	=	dwVer | GetLanguage();
						dwID[1]	=	( ( VS_FIXEDFILEINFO*)lpVerData )->dwFileVersionLS;
					}
				}//	if( _VerQueryValueA( lpVerBuffer, "\\", &lpVerData, &unVerData ) )

			}//	if( _GetFileVersionInfoA( tszTmp, dwVerHandle, dwVerSize, lpVerBuffer ) )

			HeapFree( GetProcessHeap(), 0, lpVerBuffer );

		}//	if( lpVerBuffer )

	}//	if( dwVerSize )

	return dwID[unIdx];
}//	GetIMEId
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::CheckInputLocale()
{
	static	HKL	hklPrev	=	0;

	stt_hKeyboardLayerCurrent	=	GetKeyboardLayout( 0 );
	if( hklPrev == stt_hKeyboardLayerCurrent )
		return;

	hklPrev	=	stt_hKeyboardLayerCurrent;
	switch( GetPrimaryLanguage() )
	{
	case LANG_CHINESE:
		{
			stt_bVerticalCand	=	true;
			switch( GetSubLanguage() )
			{
			case SUBLANG_CHINESE_SIMPLIFIED:
				stt_ptszCurrentIndicator	=	stt_tszIndicatorArr[eINDICATOR_CHS];
				stt_bVerticalCand	=	GetIMEId()	==	0;
				break;

			case SUBLANG_CHINESE_TRADITIONAL:
				stt_ptszCurrentIndicator		=	stt_tszIndicatorArr[eINDICATOR_CHT];
				break;

			default:
				stt_ptszCurrentIndicator		=	stt_tszIndicatorArr[eINDICATOR_NONE];
				break;
			}
		}
		break;//	LANG_CHINESE

	case LANG_KOREAN:
		stt_ptszCurrentIndicator		=	stt_tszIndicatorArr[eINDICATOR_KOREAN];
		stt_bVerticalCand	=	false;
		break;//	LANG_KOREAN

	case LANG_JAPANESE:
		stt_ptszCurrentIndicator		=	stt_tszIndicatorArr[eINDICATOR_JAPANESE];
		stt_bVerticalCand	=	true;
		break;

	default:
		stt_ptszCurrentIndicator		=	stt_tszIndicatorArr[eINDICATOR_NONE];
		break;
	}//	switch( GetPrimaryLanguage() )

	if( stt_ptszCurrentIndicator	 == stt_tszIndicatorArr[eINDICATOR_NONE] )
	{
		WCHAR	tszLang[5];
		GetLocaleInfoW( MAKELCID( LOWORD( stt_hKeyboardLayerCurrent ), SORT_DEFAULT ), LOCALE_SABBREVLANGNAME, tszLang, 5 );
		stt_ptszCurrentIndicator	[0]	=	tszLang[0];
		stt_ptszCurrentIndicator	[1]	=	_totlower( tszLang[1] );
	}
}//	CheckInputLocale
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::CheckToggleState( HWND hWnd )
{
	CheckInputLocale();
	bool bIme			=	_ImmIsIME( stt_hKeyboardLayerCurrent ) != 0;
	stt_bChineseIME	=	( GetPrimaryLanguage() == LANG_CHINESE ) && bIme;

	HIMC	hImc;
	if( NULL != ( hImc = _ImmGetContext( hWnd ) ) )
	{
		if( stt_bChineseIME )
		{
			DWORD	dwConvMode, dwSentMode;
			_ImmGetConversionStatus( hImc, &dwConvMode, &dwSentMode );
			stt_eImeState	=	( dwConvMode & IME_CMODE_NATIVE ) ? eIMESTATE_ON : eIMESTATE_ENGLISH;
		}else
		{
			stt_eImeState	=	( bIme && _ImmGetOpenStatus( hImc ) != 0 ) ? eIMESTATE_ON : eIMESTATE_OFF;
		}

		_ImmReleaseContext( hWnd, hImc );
	}//	if( NULL != ( hImc = _ImmGetContext( hWnd ) ) )
	else
		stt_eImeState	=	eIMESTATE_OFF;
}//	CheckToggleState
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::SetupIMEAPI()
{
	char	tszImeFile[MAX_PATH + 1];

	_GetReadingString	=	NULL;
	_ShowReadingWindow	=	NULL;
	if( _ImmGetIMEFileNameA(	stt_hKeyboardLayerCurrent, 
								tszImeFile, 
								sizeof( tszImeFile )/sizeof( tszImeFile[0] ) - 1 ) == 0 )
		return;

	if( stt_hDllIme )
		FreeLibrary( stt_hDllIme );
	stt_hDllIme	=	LoadLibraryA( tszImeFile );
	if( !stt_hDllIme )
		return;

	_GetReadingString	=	( UINT (WINAPI*)( HIMC, UINT, LPWSTR, PINT, BOOL*, UINT* ) )
		( GetProcAddress( stt_hDllIme, "GetReadingString" ) );
	_ShowReadingWindow	=	( BOOL (WINAPI*)( HIMC, BOOL ) )
		( GetProcAddress( stt_hDllIme, "ShowReadingWindow" ) );	
}//	SetupIMEAPI
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::ResetCompositionString()
{
	stt_nCompCaretPosition	=	0;
	stt_CompString.SetText( L"" );
	PUT_ZERO_MEMORY( stt_byCompStringAttrArr );

//	PUTOutputDebugStr( PUT_CSTR_TCHAR("ResetCompString : %s \n") , stt_CompString.GetBuffer() );	
}//	ResetCompositionString
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::TruncateCompString( HWND hWnd, bool bUseBackSpace /* = true */, int nNewStrLen /* = 0 */ )
{
	if( !stt_bInsertOnType )
		return;

	int nCompStrLen	=	(int)wcslen( stt_CompString.GetBuffer() );
	assert( nNewStrLen == 0 || nNewStrLen >= nCompStrLen );

	int nCur = 0;
	for( nCur = 0; nCur < nCompStrLen - stt_nCompCaretPosition; ++nCur )
		SendMessage( hWnd, WM_KEYDOWN, VK_RIGHT, 0 );
	SendMessage( hWnd, WM_KEYUP, VK_RIGHT, 0 );

	if( bUseBackSpace || m_bInsertModeFlag )
		nNewStrLen	=	0;

	if( nNewStrLen < nCompStrLen )
	{
		for( nCur = 0; nCur < nCompStrLen - nNewStrLen; ++nCur )
		{
			SendMessage( hWnd, WM_KEYDOWN, VK_BACK, 0 );
			SendMessage( hWnd, WM_CHAR, VK_BACK, 0 );
		}
		SendMessage( hWnd, WM_KEYUP, VK_BACK, 0 );
	}else
		nNewStrLen	=	nCompStrLen;

	for( nCur = 0; nCur < nNewStrLen; ++nCur )
		SendMessage( hWnd, WM_KEYDOWN, VK_LEFT, 0 );
	SendMessage( hWnd, WM_KEYUP, VK_LEFT, 0 );

}//	TruncateCompString
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::SendCompString( HWND hWnd )
{
	for( int nCur = 0; nCur < lstrlenW( stt_CompString.GetBuffer() ); ++nCur )
	{
		MsgProc( hWnd, WM_CHAR, (WPARAM)stt_CompString[nCur], 0 );
//		PUTOutputDebugStr( PUT_CSTR_TCHAR("SendCompString : %c\n"), stt_CompString[nCur] );
	}
}//	SendCompString
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::FinalizeString( HWND hWnd, bool bSend )
{
	HIMC	hImc;
	if( NULL == ( hImc = _ImmGetContext( hWnd ) ) )
		return;

	static bool bProcessing	=	false;
	if( bProcessing )
	{
//		PUTOutputDebugStr(PUT_CSTR_TCHAR("CPUIIMEEditBox::FinalizeString: Reentrant detected!\n") );
		_ImmReleaseContext( hWnd, hImc );
		return;
	}

	bProcessing = true;

	if( !stt_bInsertOnType && bSend )
	{
		long lLength = lstrlenW( stt_CompString.GetBuffer() );
		if( GetLanguage() == LANG_CHT&&
			stt_CompString[lLength - 1] == 0x3000 )
		{
			stt_CompString[lLength - 1] = 0;
		}
//		SendCompString();
	}

	ResetCompositionString();
	_ImmNotifyIME( hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0 );
	_ImmNotifyIME( hImc, NI_CLOSECANDIDATE, 0, 0 );
	_ImmReleaseContext( hWnd, hImc );
	bProcessing = false;
}//	FinalizeString
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::GetReadingWindowOrientation( DWORD dwID )
{
	stt_bHorizReading =	( stt_hKeyboardLayerCurrent == _CHS_HKL )		|| 
						( stt_hKeyboardLayerCurrent == _CHT_HKL2 )	||
						( dwID == 0 );

	if( !stt_bHorizReading &&
		( dwID & 0x0000ffff ) == LANG_CHT )
	{
		WCHAR	tszRegPath[MAX_PATH];
		HKEY	hKey;
		DWORD	dwVer	=	dwID & 0xffff0000;
		StringCchCopyW( tszRegPath, MAX_PATH, L"software\\microsoft\\windows\\currentversion\\" );
		StringCchCatW( tszRegPath, MAX_PATH, ( dwVer >= MAKEIMEVERSION( 5, 1 ) ) ? L"MSTCIPH" : L"TINTLGNT" );
		long	lRc	=	RegOpenKeyExW( HKEY_CURRENT_USER, tszRegPath, 0, KEY_READ, &hKey );
		if( lRc == ERROR_SUCCESS )
		{
			DWORD dwSize = sizeof(DWORD), dwMapping, dwType;
			lRc = RegQueryValueEx( hKey, PUT_CSTR_TCHAR("Keyboard Mapping"), NULL, &dwType, (BYTE*)&dwMapping, &dwSize );

			if( lRc == ERROR_SUCCESS )
			{
				if( ( dwVer <= MAKEIMEVERSION(5, 0) &&
					( (BYTE)dwMapping == 0x22 || (BYTE)dwMapping == 0x23 ) ) ||
					( (dwVer == MAKEIMEVERSION(5,1) || dwVer == MAKEIMEVERSION(5,2) ) &&
					(BYTE)dwMapping >= 0x22 && (BYTE)dwMapping <= 0x24 )
				)
				{
					stt_bHorizReading = true;
				}
			}//	if( lRc == ERROR_SUCCESS )
			RegCloseKey( hKey );
		
		}//	if( lRc == ERROR_SUCCESS )

	}//	if( !stt_bHorizReading &&	( dwID & 0x0000ffff ) == LANG_CHT )

}//	GetReadingWindowOrientation
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::GetPrivateReadingString( HWND hWnd )
{
	DWORD	dwId = GetIMEId();
	if( !dwId )
	{
		stt_bVisibleReadingWindow = false;
		return;
	}

	HIMC	hImc;
	hImc	=	_ImmGetContext( hWnd );
	if( !hImc )
	{
		stt_bVisibleReadingWindow = false;
		return;
	}

	DWORD			dwReadingStrLen = 0;
	DWORD			dwErr = 0;
	WCHAR			*ptszReadingStrBuffer = NULL;
	WCHAR			*ptszStr = 0;
	bool			bUnicodeIme = false;
	INPUTCONTEXT	*pIC = NULL;

	if( _GetReadingString )
	{
		UINT	unMaxUiLen;
		BOOL	bVertical;
		dwReadingStrLen	=	_GetReadingString( hImc, 0, NULL, (int*)&dwErr, &bVertical, &unMaxUiLen );
		if( dwReadingStrLen )
		{
			ptszStr = ptszReadingStrBuffer = (LPWSTR)HeapAlloc( GetProcessHeap(), 0, sizeof(WCHAR) * dwReadingStrLen );
			if( !ptszReadingStrBuffer )
			{
				_ImmReleaseContext( hWnd, hImc );
				return;
			}//	if( !ptszReadingStrBuffer )

			dwReadingStrLen	=	_GetReadingString( hImc, dwReadingStrLen, ptszStr, (int*)&dwErr, &bVertical, &unMaxUiLen );
		}//	if( dwReadingStrLen )

		stt_bHorizReading	=	!bVertical;
		bUnicodeIme		=	true;
	}//	if( _GetReadingString )
	else
	{
		pIC	=	_ImmLockIMC( hImc );

		LPBYTE	pbyTmp = NULL;
		switch ( dwId )
		{
		case IMEID_CHT_VER42: // New(Phonetic/ChanJie)IME98  : 4.2.x.x // Win98
		case IMEID_CHT_VER43: // New(Phonetic/ChanJie)IME98a : 4.3.x.x // WinMe, Win2k
		case IMEID_CHT_VER44: // New ChanJie IME98b          : 4.4.x.x // WinXP
			{
				pbyTmp	=	*(LPBYTE*)((LPBYTE)_ImmLockIMCC( pIC->hPrivate ) + 24 );
				if( !pbyTmp )
					break;
				dwReadingStrLen	=	*(DWORD*)( pbyTmp + 7 * 4 + 32 * 4 );
				dwErr			=	*(DWORD*)( pbyTmp + 8 * 4 + 32 * 4 );
				ptszStr			=	(WCHAR*)( pbyTmp + 56 );
				bUnicodeIme		=	true;
			}
			break;

		case IMEID_CHT_VER50:
			{
				pbyTmp	=	*(LPBYTE*)( (LPBYTE)_ImmLockIMCC( pIC->hPrivate ) + 3 * 4 );
				if( !pbyTmp )
					break;
				pbyTmp	=	*(LPBYTE*)( (LPBYTE)pbyTmp + 1*4 + 5*4 + 4*2 );
				if( !pbyTmp )
					break;

				dwReadingStrLen	=	*(DWORD*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 + 16 );
				dwErr			=	*(DWORD*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 + 16 + 1*4 );
				ptszStr			=	(WCHAR*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 );
				bUnicodeIme		=	false;
			}
			break;

		case IMEID_CHT_VER51:
		case IMEID_CHT_VER52:
		case IMEID_CHS_VER53:
			{
				pbyTmp	=	*(LPBYTE*)((LPBYTE)_ImmLockIMCC( pIC->hPrivate ) + 4 );
				if( !pbyTmp )
					break;
				pbyTmp	=	*(LPBYTE*)((LPBYTE)pbyTmp + 1*4 + 5*4 );
				if( !pbyTmp )
					break;

				dwReadingStrLen	=	*(DWORD*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 + 16 * 2 );
				dwErr			=	*(DWORD*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 + 16 * 2 + 1*4 );
				ptszStr			=	(WCHAR*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 );
				bUnicodeIme		=	true;
			}
			break;

		case IMEID_CHS_VER41:
			{
				int nOffset = 0;
				nOffset	=	(GetIMEId(1) >= 0x00000002 ) ? 8 : 7;

				pbyTmp = *(LPBYTE*)( (LPBYTE)_ImmLockIMCC( pIC->hPrivate ) + nOffset * 4 );
				if( !pbyTmp )
					break;
				dwReadingStrLen	=	*(DWORD*)(pbyTmp + 7*4 + 16*2*4);
				dwErr	=	*(DWORD*)(pbyTmp + 8*4 + 16*2*4);
				dwErr	=	__min( dwErr, dwReadingStrLen );
				ptszStr	=	(WCHAR*)(pbyTmp + 6*4 + 16*2*1);
				bUnicodeIme	=	true;
			}
			break;

		case IMEID_CHS_VER42:
			{
				OSVERSIONINFO	osi;
				osi.dwOSVersionInfoSize	=	sizeof(OSVERSIONINFO);
				GetVersionEx( &osi );

				int nTcharSize = ( osi.dwPlatformId == VER_PLATFORM_WIN32_NT ) ? sizeof(WCHAR) : sizeof(char);
				pbyTmp	=	*(LPBYTE*)((LPBYTE)_ImmLockIMCC( pIC->hPrivate ) + 1*4 + 1*4 + 6*4 );
				if( !pbyTmp )
					break;
				dwReadingStrLen	=	*(DWORD*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 + 16 * nTcharSize );
				dwErr	=	*(DWORD*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 + 16 * nTcharSize + 1*4 );
				ptszStr	=	(WCHAR*)(pbyTmp + 1*4 + (16*2+2*4) + 5*4 );
				bUnicodeIme	=	(osi.dwPlatformId == VER_PLATFORM_WIN32_NT ) ? true : false;
			}
			break;

		}//	switch ( dwId )
		
	}//	~if( _GetReadingString )

	stt_CandList._tszCandidate[0][0]	=	0;
	stt_CandList._tszCandidate[1][0]	=	0;
	stt_CandList._tszCandidate[2][0]	=	0;
	stt_CandList._tszCandidate[3][0]	=	0;

	stt_CandList._dwCount		=	dwReadingStrLen;
	stt_CandList._dwSelection	=	(DWORD) - 1;

	if( bUnicodeIme )
	{
		UINT unCur;
		for( unCur = 0; unCur < dwReadingStrLen; ++unCur )
		{
			if( dwErr <= unCur && stt_CandList._dwSelection == (DWORD) - 1 )
			{
				stt_CandList._dwSelection	=	unCur;
			}

			stt_CandList._tszCandidate[unCur][0]	=	ptszStr[unCur];
			stt_CandList._tszCandidate[unCur][1]	=	0;
		}
		stt_CandList._tszCandidate[unCur][0]	=	0;
	}//	if( bUnicodeIme )
	else
	{
		char *p	=	(char*)ptszStr;
		DWORD dwI, dwJ;
		for( dwI = 0, dwJ = 0; dwI < dwReadingStrLen; ++dwI, ++dwJ )
		{
			if( dwErr <= dwI && stt_CandList._dwSelection == (DWORD) - 1 )
			{
				stt_CandList._dwSelection = dwJ;
			}
			
			WCHAR	tszCodePage[8];
			UINT	unCodePage	=	CP_ACP;
			if( GetLocaleInfoW( MAKELCID( GetLanguage(), SORT_DEFAULT ),
				LOCALE_IDEFAULTANSICODEPAGE,
				tszCodePage,
				sizeof( tszCodePage )/ sizeof(tszCodePage[0]) ) )
			{
				unCodePage	=	wcstoul( tszCodePage, NULL, 0 );
			}
			MultiByteToWideChar(	unCodePage, 
									0, 
									p + dwI,
									IsDBCSLeadByteEx( unCodePage, p[dwI] ) ? 2 : 1,
									(WCHAR*)stt_CandList._tszCandidate[dwJ],
									1
								);
			if( IsDBCSLeadByteEx( unCodePage, p[dwI] ) )
				++dwI;
		}//	for( dwI = 0, dwJ = 0; dwI < dwReadingStrLen; ++dwI, ++dwJ )
		stt_CandList._tszCandidate[dwJ][0]	=	0;
		stt_CandList._dwCount					=	dwJ;
	}//	~if( bUnicodeIme )

	if( !_GetReadingString )
	{
		_ImmUnlockIMCC( pIC->hPrivate );
		_ImmUnlockIMC( hImc );
		GetReadingWindowOrientation( dwId );
	}
	_ImmReleaseContext( hWnd, hImc );

	if( ptszReadingStrBuffer )
		HeapFree( GetProcessHeap(), 0, ptszReadingStrBuffer );

	if( stt_CandList._dwCount > 0 )
		stt_bVisibleReadingWindow = true;
	else
		stt_bVisibleReadingWindow = false;

	if( stt_bHorizReading )
	{
		stt_CandList._nReadingError	=	-1;
		stt_tszReadingString[0]		=	0;
		for( UINT unCur = 0; unCur < stt_CandList._dwCount; ++unCur )
		{
			if( stt_CandList._dwSelection == unCur )
				stt_CandList._nReadingError = lstrlenW( stt_tszReadingString );
			StringCchCatW( stt_tszReadingString, 32, stt_CandList._tszCandidate[unCur] );
		}
	}//	if( stt_bHorizReading )

	stt_CandList._dwPageSize	=	MAX_CANDLIST;

}//	GetPrivateReadingString
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::PumpMsg()
{
	MSG msg;

	while ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
		if( !GetMessage( &msg, NULL, 0, 0 ) )
		{
			PostQuitMessage( (int)msg.wParam );
			return;
		}
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}//	PumpMsg
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::OnFocusIn( HWND hWnd )
{
	CPUIEditBox::OnFocusIn( hWnd );

	if( stt_bActiveImeSystem )
	{
		_ImmAssociateContext( hWnd, stt_hImcDef );
		CheckToggleState( hWnd );
	}else
		_ImmAssociateContext( hWnd, NULL );

	HIMC	hImc;
	if( NULL != ( hImc = _ImmGetContext( hWnd) ) )
	{
		if( !stt_bActiveImeSystem )
			stt_eImeState	=	eIMESTATE_OFF;

		_ImmReleaseContext( hWnd, hImc );
		CheckToggleState( hWnd );
	}
}//	OnFocusIn
//--------------------------------------------------------------------------------------
void	CPUIIMEEditBox::OnFocusOut( HWND hWnd )
{
	CPUIEditBox::OnFocusOut( hWnd );

	FinalizeString( hWnd, false );

	_ImmAssociateContext( hWnd, NULL );
}//	OnFocusOut
//--------------------------------------------------------------------------------------
bool	CPUIIMEEditBox::StaticMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HIMC	hImc;

	if( !stt_bActiveImeSystem )
		return false;

#if defined(DEBUG) || defined(_DEBUG)
	s_bIMEStaticMsgProcCalledForDBG = true;
#endif

	switch( uMsg )
	{
	case WM_ACTIVATEAPP:
		{
			if( wParam )
			{
				UINT	unKeyboardLayer = GetKeyboardLayoutList( 0, NULL );
				stt_LocaleArr.DeleteAll();

				HKL	*phKeyboardLayer = NULL;
				PUTNEW( phKeyboardLayer, HKL[unKeyboardLayer] );
				if( phKeyboardLayer )
				{
					GetKeyboardLayoutList( unKeyboardLayer, phKeyboardLayer );


					for( UINT unCurLayer = 0; unCurLayer < unKeyboardLayer; ++unCurLayer )
					{
						sInputLocale	*pLocale = NULL;
						PUTNEW( pLocale, sInputLocale );

						if( ( PRIMARYLANGID( LOWORD( phKeyboardLayer[ unCurLayer ] ) ) == LANG_CHINESE ||
							PRIMARYLANGID( LOWORD( phKeyboardLayer[ unCurLayer ] ) ) == LANG_JAPANESE ||
							PRIMARYLANGID( LOWORD( phKeyboardLayer[ unCurLayer ] ) ) == LANG_KOREAN ) &&
							!_ImmIsIME( phKeyboardLayer[unCurLayer] ) )
						{
							PUT_SAFE_DELETE( pLocale );
							continue;
						}

						bool bBreak	=	false;

						for( size_t nCurLocale = 0; nCurLocale < stt_LocaleArr.GetSize(); ++nCurLocale )
						{
							if( LOWORD( stt_LocaleArr.Find( nCurLocale )->_hKeyboardLayout ) ==
								LOWORD( phKeyboardLayer[nCurLocale] ) )
							{
								bBreak	=	true;
								break;
							}
						}//	for( int nCurLocale = 0; nCurLocale < s_LocaleArr.GetSize(); ++nCurLocale )

						if( bBreak )
						{
							PUT_SAFE_DELETE( pLocale );
							break;
						}

						pLocale->_hKeyboardLayout	=	phKeyboardLayer[unCurLayer];

						WCHAR	tszDesc[128]	=	L"";

						switch( PRIMARYLANGID( LOWORD( phKeyboardLayer[unCurLayer] ) ) )
						{
						case LANG_CHINESE:
							{
								switch ( SUBLANGID( LOWORD(phKeyboardLayer[unCurLayer] ) ) )
								{
								case SUBLANG_CHINESE_SIMPLIFIED:
									StringCchCopyW( pLocale->_tszLangAbbreviation, 3, stt_tszIndicatorArr[ eINDICATOR_CHS ] );
									break;

								case SUBLANG_CHINESE_TRADITIONAL:
									StringCchCopyW( pLocale->_tszLangAbbreviation, 3, stt_tszIndicatorArr[ eINDICATOR_CHT ] );
									break;

								default:
									{
										GetLocaleInfoW( MAKELCID( LOWORD( phKeyboardLayer[ unCurLayer ] ), SORT_DEFAULT ), LOCALE_SABBREVLANGNAME, tszDesc, 128 );
										pLocale->_tszLangAbbreviation[0]	=	tszDesc[0];
										pLocale->_tszLangAbbreviation[1]	=	tolower( tszDesc[1] );
										pLocale->_tszLangAbbreviation[2]	=	_T('\0');
									}//	default:
									break;
								}//	switch ( SUBLANGID( LOWORD(phKeyboardLayer[unCurLayer] ) ) )
							}//	case LANG_CHINESE:
							break;

						case LANG_KOREAN:
							StringCchCopyW( pLocale->_tszLangAbbreviation, 3, stt_tszIndicatorArr[ eINDICATOR_KOREAN ] );
							break;

						case LANG_JAPANESE:
							StringCchCopyW( pLocale->_tszLangAbbreviation, 3, stt_tszIndicatorArr[ eINDICATOR_JAPANESE ] );
							break;

						default:
							{
								GetLocaleInfoW( MAKELCID( LOWORD( phKeyboardLayer[ unCurLayer ] ), SORT_DEFAULT ), LOCALE_SABBREVLANGNAME, tszDesc, 128 );
								pLocale->_tszLangAbbreviation[0]	=	tszDesc[0];
								pLocale->_tszLangAbbreviation[1]	=	tolower( tszDesc[1] );
								pLocale->_tszLangAbbreviation[2]	=	_T('\0');
							}//	default:
							break;

						}//	switch( PRIMARYLANGID( LOWORD( phKeyboardLayer[unCurLayer] ) ) )

						GetLocaleInfoW( MAKELCID( LOWORD( phKeyboardLayer[unCurLayer] ), SORT_DEFAULT ), LOCALE_SLANGUAGE, tszDesc, 128 );
						StringCchCopyW( pLocale->_tszLangAbbreviation, 64, tszDesc );
						stt_LocaleArr.Add( pLocale );

					}//	for( UINT unCurLayer = 0; unCurLayer < unKeyboardLayer; ++unCurLayer )
					
					PUT_SAFE_DELETE_ARRAY( phKeyboardLayer );					

				}//	if( phKeyboardLayer )

			}//	if( wParam )

		}//	case WM_ACTIVATEAPP:
		break;



	case WM_INPUTLANGCHANGE:
		{
//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_INPUTLANGCHANGE\n") );

			UINT	uLang	=	GetPrimaryLanguage();
			CheckToggleState( hWnd );

			if( uLang != GetPrimaryLanguage() )
				stt_bInsertOnType	=	( GetPrimaryLanguage() == LANG_KOREAN );

			SetupIMEAPI();
			if( _ShowReadingWindow )
			{
				if( NULL != ( hImc = _ImmGetContext( hWnd ) ) )
				{
					_ShowReadingWindow( hImc, false );
					_ImmReleaseContext( hWnd, hImc );
				}
			}
		}//	case WM_INPUTLANGCHANGE:
		return true;


	case WM_IME_SETCONTEXT:
		{
//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_IME_SETCONTEXT\n") );
			lParam	=	0;
		}//	case WM_IME_SETCONTEXT
		return false;


	case WM_IME_STARTCOMPOSITION:
		{
//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_IME_STARTCOMPOSITION\n") );
			ResetCompositionString();
			stt_bHideCaret	=	true;
		}
		return true;


	case WM_IME_COMPOSITION:
		{
//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_IME_COMPOSITION\n") );
		}
		return false;
	}//	switch( uMsg )

	return false;
}//	StaticMsgProc
//--------------------------------------------------------------------------------------
bool	CPUIIMEEditBox::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			CPUIFontNode* pFont	=	m_pDlg->GetFont( m_Elements.Find(0)->GetFontID() );

			int nCompStrWidth = 0;
			stt_CompString.CPtoX( stt_CompString.GetTextSize(), FALSE, &nCompStrWidth );

			if( stt_ptCompString.x <= pt.x &&
				stt_ptCompString.y <= pt.y &&
				stt_ptCompString.x + nCompStrWidth > pt.x &&
				stt_ptCompString.y + (long)pFont->m_unHeight > pt.y )
			{
				int nCharBodyHit, nCharHit;
				int nTrail;

				stt_CompString.XtoCP( pt.x - stt_ptCompString.x, &nCharBodyHit, &nTrail );
				if( nTrail && nCharBodyHit < stt_CompString.GetTextSize() )
					nCharHit	=	nCharBodyHit + 1;
				else
					nCharHit	=	nCharBodyHit;


				HIMC	hImc	=	_ImmGetContext( hWnd );
				if( !hImc )
					return true;

				_ImmNotifyIME( hImc, NI_CLOSECANDIDATE, 0, 0 );
				_ImmReleaseContext( hWnd, hImc );

				switch( GetPrimaryLanguage() )
				{
				case LANG_JAPANESE:
					{
						if( stt_nFirstTargetConv != -1 )
						{
							int nClauseClicked = 0;

							while( (int)stt_dwCompStringClause[nClauseClicked + 1] <= nCharBodyHit )
								++nClauseClicked;

							int nClauseSelected = 0;
							while( (int)stt_dwCompStringClause[nClauseSelected + 1] <= stt_nFirstTargetConv )
								++nClauseSelected;

							BYTE	byVirtKey = nClauseClicked > nClauseSelected ? VK_RIGHT : VK_LEFT;
							int		nSendCount = abs( nClauseClicked - nClauseSelected );
							while( nSendCount-- > 0 )
								SendKey( byVirtKey );

							return true;
						}//	if( stt_nFirstTargetConv != -1 )
					}//	case LANG_JAPANESE:
					break;

				case LANG_CHINESE:
					{
						BYTE	byVirtKey	=	nCharHit > stt_nCompCaretPosition ? VK_RIGHT : VK_LEFT;
						int		nSendCount	=	abs( nCharHit - stt_nCompCaretPosition );
						while( nSendCount-- > 0 )
						{
							SendKey( byVirtKey );
						}
					}
					break;
				}//	switch( GetPrimaryLanguage() )

				return true;

			}/*	if( stt_ptCompString.x <= pt.x &&
				stt_ptCompString.y <= pt.y &&
				stt_ptCompString.x + nCompStrWidth > pt.x &&
				stt_ptCompString.y + pFont->m_unHeight > pt.y ) */

			if( stt_CandList._bShowWindow && PtInRect( &stt_CandList._rcCandidate, pt ) )
			{
				if( stt_bVerticalCand )
				{
					int nRow	=	( pt.y - stt_CandList._rcCandidate.top ) / pFont->m_unHeight;

					if( nRow < (int)stt_CandList._dwCount )
					{
						switch( GetPrimaryLanguage() )
						{
						case LANG_CHINESE:
						case LANG_KOREAN:
							{
								SendKey( (BYTE)('0' + nRow + 1 ) );
							}//	case LANG_CHINESE:
							 //	case LANG_KOREAN:
							break;

						case LANG_JAPANESE:
							{
								BYTE	byVirtKey;
								if( nRow > (int)stt_CandList._dwSelection )
									byVirtKey = VK_DOWN;
								else
									byVirtKey = VK_UP;

								int nNumToHit = abs( int( nRow - stt_CandList._dwSelection ) );
								
								for( int nStrike = 0; nStrike < nNumToHit; ++nStrike )
									SendKey( byVirtKey );

								SendKey( VK_RIGHT );
								SendKey( VK_LEFT );
							}//	case LANG_JAPANESE:
							break;
						}//	switch( GetPrimaryLanguage() )
					}//	if( nRow < (int)stt_CandList._dwCount )
					else
					{
						int nCharHit	=	0;
						int nTrail		=	0;
						stt_CandList._HoriCand.XtoCP( pt.x - stt_CandList._rcCandidate.left, &nCharHit, &nTrail );

						int nCandidate	=	stt_CandList._dwCount - 1;
						int nEntryStart	=	0;

						for( UINT unCur = 0; unCur < stt_CandList._dwCount; ++unCur )
						{
							if( nCharHit >= nEntryStart )
							{
								nEntryStart += lstrlenW( stt_CandList._tszCandidate[unCur] ) + 1;
							}else
							{
								nCandidate = unCur - 1;
								break;
							}
						}//	for( UINT unCur = 0; unCur < stt_CandList._dwCount; ++unCur )


						switch( GetPrimaryLanguage() )
						{
						case LANG_CHINESE:
						case LANG_KOREAN:
							SendKey( (BYTE)( '0' + nCandidate + 1 ) );
							break;
						}

					}//	~if( nRow < (int)stt_CandList._dwCount )					
				
				}//	if( stt_bVerticalCand )

				return true;

			}//	if( stt_CandList._bShowWindow && PtInRect( &stt_CandList._rcCandidate, pt ) )				

		}//	case WM_LBUTTONDOWN:
		 //	case WM_LBUTTONDBLCLK:		
		break;
	}//	switch( uMsg )

	return CPUIEditBox::HandleMouse( hWnd, uMsg, pt, wParam, lParam );
}//	HandleMouse
//--------------------------------------------------------------------------------------
bool	CPUIIMEEditBox::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

#if defined(DEBUG) || defined(_DEBUG)
	assert( s_bIMEStaticMsgProcCalledForDBG && PUT_CSTR_TCHAR("To fix, call CPUIDlgResourceMgr::MsgProc() first\n ") );
#endif

	bool	bTrappedData	= false;
	bool	*pbTrapped		= &bTrappedData;

	HIMC	hImc;
	static	LPARAM	sttlParamAlt = 0x80000000, sttlParamCtrl = 0x80000000, sttlParamShift = 0x80000000;

	*pbTrapped	=	false;
	if( !stt_bActiveImeSystem )
		return CPUIEditBox::MsgProc( hWnd, uMsg, wParam, lParam );

	switch( uMsg )
	{
		case WM_IME_COMPOSITION:
			{
				//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_IME_COMPOSITION\n") );

				long	lRet;
				WCHAR	tszCompStr[MAX_COMPSTRING_SIZE];

				*pbTrapped	=	true;
				if( NULL == ( hImc = _ImmGetContext( hWnd ) ) )
					break;

				if( lParam & GCS_CURSORPOS )
				{
					stt_nCompCaretPosition	=	_ImmGetCompositionString( hImc, GCS_CURSORPOS, NULL, 0 );
					if( stt_nCompCaretPosition < 0 )
						stt_nCompCaretPosition = 0;
				}

				if( lParam & GCS_RESULTSTR )
				{
					//			PUTOutputDebugStr( PUT_CSTR_TCHAR("GCS_RESULTSTR\n") );
					lRet	=	_ImmGetCompositionString( hImc, GCS_RESULTSTR, tszCompStr, sizeof( tszCompStr ) );

					if( lRet > 0 )
					{
						lRet /= sizeof( WCHAR );
						tszCompStr[lRet] = 0;
						TruncateCompString( hWnd, false, (int)wcslen( tszCompStr ) );
						stt_CompString.SetText( tszCompStr );
						SendCompString( hWnd );
						ResetCompositionString();
					}//	if( lRet > 0 )

				}//	if( lParam & GCS_RESULTSTR )


				if( lParam & GCS_COMPSTR )
				{
					//			PUTOutputDebugStr( PUT_CSTR_TCHAR("GCS_COMPSTR\n") );

					lRet	=	_ImmGetCompositionString( hImc, GCS_COMPSTR, tszCompStr, sizeof( tszCompStr ) );

					if( lRet > 0 )
					{
						lRet /= sizeof(WCHAR);
						tszCompStr[lRet]	=	0;

						TruncateCompString( hWnd, false, (int)wcslen( tszCompStr ) );

						stt_CompString.SetText( tszCompStr );

						if( GetLanguage() == LANG_CHT && !GetIMEId() )
						{
							if( lstrlenW( stt_CompString.GetBuffer() ) )
							{
								stt_CandList._dwCount		=	4;
								stt_CandList._dwSelection	=	(DWORD) - 1;

								for( int nCur = 3; nCur >= 0; --nCur )
								{
									if( nCur > lstrlenW( stt_CompString.GetBuffer() ) - 1 )
										stt_CandList._tszCandidate[nCur][0]	=	0;
									else
									{
										stt_CandList._tszCandidate[nCur][0]	=	stt_CompString[nCur];
										stt_CandList._tszCandidate[nCur][1]	=	0;
									}

								}//	for( int nCur = 3; nCur >= 0; --nCur )

								stt_CandList._dwPageSize	=	MAX_CANDLIST;

								ZeroMemory( (void*)stt_CompString.GetBuffer(), 4 * sizeof(WCHAR) );
								stt_bVisibleReadingWindow	=	true;
								GetReadingWindowOrientation( 0 );

								if( stt_bHorizReading )
								{
									stt_CandList._nReadingError	=	-1;
									stt_tszReadingString[0]		=	0;

									for( UINT unCur = 0; unCur < stt_CandList._dwCount; ++unCur )
									{
										if( stt_CandList._dwSelection == unCur )
											stt_CandList._nReadingError	=	lstrlenW( stt_tszReadingString );
										StringCchCatW( stt_tszReadingString, 32, stt_CandList._tszCandidate[unCur] );
									}

								}//	if( stt_bHorizReading )

							}//	if( strlen( stt_CompString.GetBuffer() ) )
							else
							{
								stt_CandList._dwCount		=	0;
								stt_bVisibleReadingWindow	=	false;
							}//	~if( strlen( stt_CompString.GetBuffer() ) )

						}//	if( GetLanguage() == LANG_CHT && !GetIMEId() )

						if( stt_bInsertOnType )
						{
							SendCompString( hWnd );

							int nCount	=	lstrlenW( stt_CompString.GetBuffer() + stt_nCompCaretPosition );

							for( int nCur = 0; nCur < nCount; ++nCur )
								SendMessage( hWnd, WM_KEYDOWN, VK_LEFT, 0 );
							SendMessage( hWnd, WM_KEYUP, VK_LEFT, 0 );
						}

					}//	if( lRet > 0 )

					ResetCaretBlink();

				}//	if( lParam & GCS_COMPSTR )

				if( lParam & GCS_COMPATTR )
				{
					lRet	=	_ImmGetCompositionString( hImc, GCS_COMPATTR, stt_byCompStringAttrArr, sizeof(stt_byCompStringAttrArr) );
					if( lRet > 0 )
						stt_byCompStringAttrArr[lRet]	=	0;
				}

				if( lParam & GCS_COMPCLAUSE )
				{
					lRet	=	_ImmGetCompositionString( hImc, GCS_COMPCLAUSE, stt_dwCompStringClause, sizeof(stt_dwCompStringClause) );
					stt_dwCompStringClause[lRet / sizeof(DWORD)]	=	0;
				}

				_ImmReleaseContext( hWnd, hImc );
			}//	case WM_IME_COMPOSITION:
			break;


		case WM_IME_ENDCOMPOSITION:
			{
				//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_IME_ENDCOMPOSITION\n") );
				TruncateCompString( hWnd );
				ResetCompositionString();
				stt_bHideCaret	=	false;
			}//	case WM_IME_ENDCOMPOSITION:
			break;


		case WM_IME_NOTIFY:
			{
				//			PUTOutputDebugStr( PUT_CSTR_TCHAR("WM_IME_NOTIFY %u\n"), wParam );
				switch( wParam )
				{
				case IMN_SETCONVERSIONMODE:
					//			PUTOutputDebugStr(PUT_CSTR_TCHAR("IMN_SETCONVERSIONMODE\n"));
					break;

				case IMN_SETOPENSTATUS:
					//			PUTOutputDebugStr(PUT_CSTR_TCHAR("IMN_SETCONVERSIONMODE\n"));
					CheckToggleState( hWnd );
					break;

				case IMN_OPENCANDIDATE:
				case IMN_CHANGECANDIDATE:
					{
						//			PUTOutputDebugStr( wParam == IMN_CHANGECANDIDATE ? PUT_CSTR_TCHAR("IMN_CHANGECANDIDATE\n") : PUT_CSTR_TCHAR("IMN_OPENCANDIDATE\n") );

						stt_CandList._bShowWindow	=	true;
						*pbTrapped	=	true;
						if( NULL == ( hImc = _ImmGetContext( hWnd ) ) )
							break;

						LPCANDIDATELIST	lpCandList	=	NULL;
						DWORD			dwLenRequired;

						stt_bVisibleReadingWindow	=	false;
						dwLenRequired	=	_ImmGetCandidateList( hImc, 0, NULL, 0 );

						if( dwLenRequired )
						{
							lpCandList		=	(LPCANDIDATELIST)HeapAlloc( GetProcessHeap(), 0, dwLenRequired );
							dwLenRequired	=	_ImmGetCandidateList( hImc, 0, lpCandList, dwLenRequired );
						}

						if( lpCandList )
						{
							stt_CandList._dwSelection	=	lpCandList->dwSelection;
							stt_CandList._dwSelection	=	lpCandList->dwCount;

							int nPageTopIdx	=	0;
							stt_CandList._dwPageSize	=	__min( lpCandList->dwPageSize, MAX_CANDLIST );
							
							if( GetPrimaryLanguage() == LANG_JAPANESE )							
								nPageTopIdx	=	( stt_CandList._dwSelection / stt_CandList._dwPageSize ) * stt_CandList._dwPageSize;
							else
								nPageTopIdx	=	lpCandList->dwPageStart;

							stt_CandList._dwSelection	=	(GetLanguage() == LANG_CHS && !GetIMEId() ) ? (DWORD) - 1
															:	stt_CandList._dwSelection - nPageTopIdx;


							PUT_ZERO_MEMORY( stt_CandList._tszCandidate );

							for(	UINT unCurIdx = nPageTopIdx, unCur = 0;
									(DWORD)unCur < lpCandList->dwCount && unCur < stt_CandList._dwPageSize;
									++unCurIdx, ++unCur )
							{
								WCHAR* ptszCand	=	stt_CandList._tszCandidate[unCur];

								*ptszCand++	=	(WCHAR)( _T('0') + ( ( unCur + 1 ) % 10 ) );
								if( stt_bVerticalCand )
									*ptszCand++	=	_T(' ');

								WCHAR* ptszNewCand	=	(WCHAR*)( (BYTE*)lpCandList + lpCandList->dwOffset[unCur] );
								while( *ptszNewCand )
									*ptszCand++ = *ptszNewCand++;
								if( !stt_bVerticalCand )
									*ptszCand++ = _T(' ');
								*ptszCand	=	0;
							
							}//	for(	UINT unCurIdx = nPageTopIdx, unCur = 0;
							 //	(DWORD)unCur < lpCandList->dwCount && unCur < stt_CandList._dwPageSize;
							 //	++unCurIdx, ++unCur )

							stt_CandList._dwCount	=	lpCandList->dwCount - lpCandList->dwPageStart;
							if( stt_CandList._dwCount > lpCandList->dwPageSize )
								stt_CandList._dwCount	=	lpCandList->dwPageSize;

							HeapFree( GetProcessHeap(), 0, lpCandList );
							_ImmReleaseContext( hWnd, hImc );

							if( GetPrimaryLanguage() == LANG_KOREAN ||
								GetLanguage() == LANG_CHT && !GetIMEId() )
								stt_CandList._dwSelection	=	(DWORD)-1;

							if( !stt_bVerticalCand )
							{
								WCHAR	tszCand[256]	=	L"";

								stt_CandList._nFirstSelected	=	0;
								stt_CandList._nHoriSelectedLen	=	0;

								for( UINT unCur = 0; unCur < MAX_CANDLIST; ++unCur )
								{
									if( stt_CandList._tszCandidate[unCur][0] == L'\0' )
										break;

									WCHAR	tszEntry[32];
									StringCchPrintfW( tszEntry, 32, L"%s ", stt_CandList._tszCandidate[unCur] );

									if( stt_CandList._dwSelection == unCur )
									{
										stt_CandList._nFirstSelected		=	lstrlenW( tszCand );
										stt_CandList._nHoriSelectedLen		=	lstrlenW( tszEntry ) - 1;

									}//	if( stt_CandList._dwSelection == unCur )

									StringCchCatW( tszCand, 256, tszEntry );

								}//	for( UINT unCur = 0; unCur < MAX_CANDLIST; ++unCur )
								
								tszCand[lstrlenW(tszCand) - 1]	=	_T('\0');
								stt_CandList._HoriCand.SetText( tszCand );

							}//	if( !stt_bVerticalCand )							

						}//	if( lpCandList )

					}//	case IMN_OPENCANDIDATE:
					 //	case IMN_CHANGECANDIDATE:
					break;



				case IMN_CLOSECANDIDATE:
					{
						//			PUTOutputDebugStr( PUT_CSTR_TCHAR("IMN_CLOSECANDIDATE\n") );
						stt_CandList._bShowWindow	=	false;
						if( !stt_bVisibleReadingWindow )
						{
							stt_CandList._dwCount	=	0;
							PUT_ZERO_MEMORY( stt_CandList._tszCandidate );
						}

						*pbTrapped	=	true;
					}//	case IMN_CLOSECANDIDATE:
					break;


				case IMN_PRIVATE:
					{
						//			PUTOutputDebugStr( PUT_CSTR_TCHAR("IMN_PRIVATE\n") );
						if( !stt_CandList._bShowWindow )
							GetPrivateReadingString( hWnd );

						DWORD dwID	=	GetIMEId();
						switch( dwID )
						{
						case IMEID_CHT_VER42:
						case IMEID_CHT_VER43:
						case IMEID_CHT_VER44:
						case IMEID_CHS_VER41:
						case IMEID_CHS_VER42:
							{
								if( (lParam == 1) || (lParam == 2) )
									*pbTrapped	=	true;
							}
							break;

						case IMEID_CHT_VER50:
						case IMEID_CHT_VER51:
						case IMEID_CHT_VER52:
						case IMEID_CHT_VER60:
						case IMEID_CHS_VER53:
							{
								if( (lParam == 16) || (lParam == 17) ||
									(lParam == 26) || (lParam == 27) ||
									(lParam == 28) )
									*pbTrapped	=	true;
							}
							break;

						}//	switch( dwID )

					}//	case IMN_PRIVATE:
					break;

				default:
					*pbTrapped	=	true;
					break;

				}//	switch( wParam )

			}//	case WM_IME_NOTIFY:
			break;


		case WM_KEYUP:
		case WM_SYSKEYUP:
			{
				if( !( sttlParamAlt & 0x80000000 ) && 
					wParam != VK_MENU &&
					( GetAsyncKeyState( VK_MENU ) & 0x8000 ) == 0 )
				{
					PostMessage( GetFocus(), WM_KEYUP, (WPARAM)VK_MENU, (sttlParamAlt & 0x01ff0000) | 0xC0000001 );
				}else 
					if( !( sttlParamCtrl & 0x80000000 ) &&
						wParam != VK_CONTROL &&
						( GetAsyncKeyState( VK_CONTROL ) & 0x8000 ) == 0 )
					{
						PostMessage( GetFocus(), WM_KEYUP, (WPARAM)VK_CONTROL, (sttlParamCtrl & 0x01ff0000) | 0xC0000001 );
					}else
						if( !( sttlParamShift & 0x80000000 ) &&
							wParam != VK_SHIFT &&
							( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) == 0 )
						{
							PostMessage( GetFocus(), WM_KEYUP, (WPARAM)VK_SHIFT, (sttlParamShift & 0x01ff0000) | 0xC0000001 );
						}
			}//	case WM_KEYUP:
			 //case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			{
				switch( wParam )
				{
				case VK_MENU:
					sttlParamAlt	=	lParam;
					break;

				case VK_SHIFT:
					sttlParamShift	=	lParam;
					break;

				case VK_CONTROL:
					sttlParamCtrl	=	lParam;
					break;
				}//	switch( wParam )

			}//	case WM_KEYDOWN:
			 //	case WM_SYSKEYDOWN:
			break;

		default:
			return CPUIEditBox::MsgProc( hWnd, uMsg, wParam, lParam );

	}//	switch( uMsg )

	return *pbTrapped;		
}//	MsgProc
//--------------------------------------------------------------------------------------
HRESULT	CPUIIMEEditBox::RenderCandidateReadingWindow(LPDIRECT3DDEVICE9 pDev, float fElapsedTime, bool bReading)
{
	RECT		rc;
	UINT		unNumEntries	=	bReading ? 4 : MAX_CANDLIST;
	D3DCOLOR	colText, colTextBk, colSelectText, colSelectBk;
	int			nX, nXFirst, nXComp;
	m_UniBuffer.CPtoX( m_nCaretPos,		FALSE,	&nX );
	m_UniBuffer.CPtoX( m_nFirstVisible, FALSE,	&nXFirst );

	if( bReading )
	{
		colText			=	GetIMEColor(eIMECOLOR_READING);
		colTextBk		=	GetIMEColor(eIMECOLOR_READING_WINDOW);
		colSelectText	=	GetIMEColor(eIMECOLOR_READING_SELECTED);
		colSelectBk		=	GetIMEColor(eIMECOLOR_READING_SELECTEDBACKGROUND);
	}//	if( bReading )
	else
	{
		colText			=	GetIMEColor(eIMECOLOR_CANDIDATE);
		colTextBk		=	GetIMEColor(eIMECOLOR_CANDIDATE_WINDOW);
		colSelectText	=	GetIMEColor(eIMECOLOR_CANDIDATE_SELECTED);
		colSelectBk		=	GetIMEColor(eIMECOLOR_CANDIDATE_SELECTEDBACKGROUND);
	}//	~if( bReading )
	

	if( GetLanguage() == LANG_CHT && !GetIMEId() )
		nXComp	=	0;
	else
		if( GetPrimaryLanguage() == LANG_JAPANESE )
			stt_CompString.CPtoX( stt_nFirstTargetConv,	FALSE, &nXComp );
		else
			stt_CompString.CPtoX( stt_nCompCaretPosition, FALSE, &nXComp );

	int	nWidthRequired		=	0;
	int	nHeightRequired		=	0;
	int	nSingleLineHeight	=	0;

	if( ( stt_bVerticalCand && !bReading ) ||
		( !stt_bHorizReading && bReading ) )
	{
		for( UINT unCur = 0; unCur < unNumEntries; ++unCur )
		{
			if( stt_CandList._tszCandidate[unCur][0] == _T('\0') )
				break;
			SetRect( &rc, 0, 0, 0, 0 );
			m_pDlg->CalcTextRect( stt_CandList._tszCandidate[unCur], m_Elements.Find(1), &rc );
			nWidthRequired		=	__max( nWidthRequired,		rc.right - rc.left );
			nSingleLineHeight	=	__max( nSingleLineHeight,	rc.bottom - rc.top );
		}//	for( UINT unCur = 0; unCur < unNumEntries; ++unCur )

		nHeightRequired	=	nSingleLineHeight * unNumEntries;

	}//	if( ( stt_bVerticalCand && !bReading ) ||
	 //	( !stt_bHorizReading && bReading ) )
	else
	{
		SetRect( &rc, 0, 0, 0, 0 );
		
		if( bReading )
			m_pDlg->CalcTextRect( stt_tszReadingString, m_Elements.Find(1), &rc );
		else
			m_pDlg->CalcTextRect( stt_CandList._HoriCand.GetBuffer(), m_Elements.Find(1), &rc );
		nWidthRequired		=	rc.right - rc.left;
		nSingleLineHeight	=	nHeightRequired	=	rc.bottom - rc.top;

	}//	~if( ( stt_bVerticalCand && !bReading ) ||
	 //	( !stt_bHorizReading && bReading ) )

	bool bHasPosition	=	false;

	// Bottom -----------------------------------------------
	SetRect( &rc,	stt_ptCompString.x + nXComp,
					stt_ptCompString.y + m_rcText.bottom - m_rcText.top,
					stt_ptCompString.x + nXComp + nWidthRequired,
					stt_ptCompString.y + m_rcText.bottom - m_rcText.top + nHeightRequired );

	if( rc.right > m_pDlg->GetWidth() )
	{
		rc.left		-=	rc.right - m_pDlg->GetWidth();
		rc.right	=	m_pDlg->GetWidth();
	}

	if( rc.bottom <= m_pDlg->GetHeight() )
		bHasPosition	=	true;
	//-------------------------------------------------------
	
	
	// Top --------------------------------------------------
	if( !bHasPosition )
	{
		SetRect( &rc,	stt_ptCompString.x + nXComp, 
						stt_ptCompString.y + nHeightRequired,
						stt_ptCompString.x + nXComp,
						stt_ptCompString.y );

		if( rc.right > m_pDlg->GetWidth() )
		{
			rc.left		-=	rc.right - m_pDlg->GetWidth();
			rc.right	=	m_pDlg->GetWidth();
		}
		if( rc.top >= 0 )
			bHasPosition	=	true;
	}//	if( !bHasPosition )
	//-------------------------------------------------------


	// Right ------------------------------------------------
	if( !bHasPosition )
	{
		int nXCompTrail = 0;
		stt_CompString.CPtoX( stt_nCompCaretPosition, TRUE, &nXCompTrail );
		SetRect( &rc,	stt_ptCompString.x + nXCompTrail,
						0,
						stt_ptCompString.x + nXCompTrail + nWidthRequired,
						nHeightRequired );

		if( rc.right <= m_pDlg->GetWidth() )
			bHasPosition	=	true;
	}//	if( !bHasPosition )
	//-------------------------------------------------------


	// Left -------------------------------------------------
	if( !bHasPosition )
	{
		SetRect( &rc,	stt_ptCompString.x + nXComp - nWidthRequired,
						0,
						stt_ptCompString.x + nXComp,
						nHeightRequired );

		if( rc.right >= 0 )
			bHasPosition	=	true;
	}//	if( !bHasPosition )
	//-------------------------------------------------------

	if( !bHasPosition )
	{
		rc.left		=	0;
		rc.right	=	nWidthRequired;
	}

	if( !bReading )
		stt_CandList._rcCandidate	=	rc;

	m_pDlg->DrawRect( &rc, colTextBk );

	if( ( stt_bVerticalCand && !bReading ) ||
		( !stt_bHorizReading && bReading ) )
	{
		for( UINT unCur = 0; unCur < unNumEntries; ++unCur )
		{
			rc.bottom	=	rc.top + nSingleLineHeight;

			if( stt_CandList._dwSelection == unCur )
			{
				m_pDlg->DrawRect( &rc, colSelectBk );
				m_Elements.Find(1)->GetFontColor().SetCurrentColor( colSelectText );
			}else
				m_Elements.Find(1)->GetFontColor().SetCurrentColor( colText );

			m_pDlg->DrawText( stt_CandList._tszCandidate[unCur], m_Elements.Find(1), &rc );

			rc.top	+=	nSingleLineHeight;

		}//	for( UINT unCur = 0; unCur < unNumEntries; ++unCur )

	}//	if( ( stt_bVerticalCand && !bReading ) ||
	 //		( !stt_bHorizReading && bReading ) )
	else
	{
		m_Elements.Find(1)->GetFontColor().SetCurrentColor( colText );

		if( bReading )
			m_pDlg->DrawText( stt_tszReadingString, m_Elements.Find(1), &rc );
		else
			m_pDlg->DrawText( stt_CandList._HoriCand.GetBuffer(), m_Elements.Find(1), &rc );

		if( !bReading )
		{
			int nXLeft, nXRight;
			stt_CandList._HoriCand.CPtoX( stt_CandList._nFirstSelected, FALSE, &nXLeft );
			stt_CandList._HoriCand.CPtoX( stt_CandList._nFirstSelected + stt_CandList._nHoriSelectedLen, FALSE, &nXRight );

			rc.right	=	rc.left + nXRight;
			rc.left		+=	nXLeft;
			m_pDlg->DrawRect( &rc, colSelectBk );
			m_Elements.Find(1)->GetFontColor().SetCurrentColor( colSelectText );
			m_pDlg->DrawText(	stt_CandList._HoriCand.GetBuffer() + stt_CandList._nFirstSelected,
								m_Elements.Find(1), 
								&rc, 
								false, 
								stt_CandList._nHoriSelectedLen 
								);
		}//	if( !bReading )

	}//	~if( ( stt_bVerticalCand && !bReading ) ||
	 //		( !stt_bHorizReading && bReading ) )

	return S_OK;
}//	RenderCandidateReadingWindow
//--------------------------------------------------------------------------------------
HRESULT		CPUIIMEEditBox::RenderComposition( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	RECT	rcCaret	=	{ 0, 0, 0, 0 };
	int		nX, nXFirst;
	m_UniBuffer.CPtoX( m_nCaretPos,		FALSE, &nX );
	m_UniBuffer.CPtoX( m_nFirstVisible,	FALSE, &nXFirst );
	CPUIElement	*pElement = m_Elements.Find(0);

	RECT	rc	=	{	m_rcText.left + nX - nXFirst,
						m_rcText.top,
						m_rcText.left + nX - nXFirst,
						m_rcText.bottom 
					};
	m_pDlg->CalcTextRect( stt_CompString.GetBuffer(), pElement, &rc );

	if( rc.right > m_rcText.right )
		OffsetRect( &rc, m_rcText.left - rc.left, rc.bottom - rc.top );

	RECT	rcFirst	=	rc;

	stt_ptCompString.x	=	rc.left;
	stt_ptCompString.y	=	rc.top;

	D3DCOLOR	colText	=	m_colIME[eIMECOLOR_COMP];

	pElement->GetFontColor().SetCurrentColor( colText );
	const WCHAR	*ptszComp	=	stt_CompString.GetBuffer();
	int nCharLeft			=	stt_CompString.GetTextSize();

	for( ; ; )
	{
		int nLastLine = 0;
		int nTrail = 0;
		stt_CompString.XtoCP(	m_rcText.right - rc.left,
								&nLastLine,
								&nTrail
							);
		int nNumCharToDraw	=	__min( nCharLeft, nLastLine );
		m_pDlg->CalcTextRect( ptszComp, pElement, &rc, nNumCharToDraw );

		if( GetPrimaryLanguage() == LANG_KOREAN )
		{
			if( m_bCaretVisible )
			{
				m_pDlg->DrawRect( &rc, GetIMEColor(eIMECOLOR_COMP_WINDOW) );
			}else
			{
				colText	=	m_Elements.Find(0)->GetFontColor().GetStateColor(eCTRLSTATE_NORMAL);
			}

		}//	if( GetPrimaryLanguage() == LANG_KOREAN )
		else
		{
			m_pDlg->DrawRect( &rc, GetIMEColor(eIMECOLOR_COMP_WINDOW) );
		}//	~if( GetPrimaryLanguage() == LANG_KOREAN )

		pElement->GetFontColor().SetCurrentColor( colText );
		m_pDlg->DrawText( ptszComp, pElement, &rc, false, nNumCharToDraw );

		nCharLeft	-=	nNumCharToDraw;
		ptszComp	+=	nNumCharToDraw;
		if( nCharLeft <= 0 )
			break;

		OffsetRect( &rc, m_rcText.left - rc.left, rc.bottom - rc.top );
	}//	for( ; ; )

	rc	=	rcFirst;

	int nCharFirst				=	0;
	nXFirst						=	0;
	stt_nFirstTargetConv		=	-1;
	BYTE	*pbyAttr			=	NULL;
	const WCHAR *ptszCompCur	=	NULL;

	for(	ptszCompCur = stt_CompString.GetBuffer(), pbyAttr = stt_byCompStringAttrArr;
			*ptszCompCur != L'\0';
			++ptszCompCur, ++pbyAttr )
	{
		
		D3DCOLOR	colBk;
		int			nXLeft = 0, nXRight = 0;
		stt_CompString.CPtoX( int( ptszCompCur - stt_CompString.GetBuffer() ), FALSE, &nXLeft );
		stt_CompString.CPtoX( int( ptszCompCur - stt_CompString.GetBuffer() ), TRUE, &nXRight );

		if( nXRight - nXFirst > m_rcText.right - rc.left )
		{
			OffsetRect( &rc, m_rcText.left - rc.left, rc.bottom - rc.top );

			nCharFirst	=	int( ptszCompCur - stt_CompString.GetBuffer() );
			stt_CompString.CPtoX( nCharFirst, FALSE, &nXFirst );
		}//	if( nXRight - nXFirst > m_rcText.right - rc.left )

		if( stt_nCompCaretPosition == int( ptszCompCur - stt_CompString.GetBuffer() ) )
		{
			rcCaret			=	rc;
			rcCaret.left	+=	nXLeft - nXFirst - 1;
			rcCaret.right	=	rcCaret.left + 2;
		}//	if( stt_nCompCaretPosition == int( ptszCompCur - stt_CompString.GetBuffer() ) )
		
		if( *pbyAttr == ATTR_TARGET_CONVERTED )
		{
			pElement->GetFontColor().SetCurrentColor( GetIMEColor( eIMECOLOR_COMP_TARGETNONE ) );
			colBk	=	GetIMEColor( eIMECOLOR_COMP_TARGETNONEBACKGROUND );
		}else
			if( *pbyAttr == ATTR_TARGET_NOTCONVERTED )
			{
				pElement->GetFontColor().SetCurrentColor( GetIMEColor(eIMECOLOR_COMP_TARGET) );
				colBk	=	GetIMEColor(eIMECOLOR_COMP_TARGETNONEBACKGROUND);
			}else
				continue;

			RECT	rcTarget	=	{	rc.left + nXLeft - nXFirst,
										rc.top,
										rc.left + nXRight - nXFirst,
										rc.bottom };
			m_pDlg->DrawRect( &rcTarget, colBk );
			m_pDlg->DrawText( ptszCompCur, pElement, &rcTarget, false, 1 );

			if( -1 == stt_nFirstTargetConv )
				stt_nFirstTargetConv	=	int(pbyAttr - stt_byCompStringAttrArr );

	}//	for(	ptszCompCur = stt_CompString.GetBuffer(), pbyAttr = stt_byCompStringAttrArr;
	 //	*ptszCompCur != _T('\0');
	 //	++ptszCompCur, ++pbyAttr )

	if( m_bCaretVisible )
	{
		if( stt_nCompCaretPosition == stt_CompString.GetTextSize() )
		{
			stt_CompString.CPtoX( stt_nCompCaretPosition, FALSE, &nX );
			rcCaret	=	rc;
			rcCaret.left	+=	nX- nXFirst - 1;
			rcCaret.right	=	rc.left + 2;
		}//	if( stt_nCompCaretPosition == stt_CompString.GetTextSize() )

		m_pDlg->DrawRect( &rcCaret, GetIMEColor(eIMECOLOR_COMP_CARET) );

	}//	if( m_bCaretVisible )

	return S_OK;
}//	RenderComposition
//--------------------------------------------------------------------------------------
HRESULT	CPUIIMEEditBox::RenderIndicator( LPDIRECT3DDEVICE9 pDev, float fElpasedTime )
{
	CPUIElement	*pElement	=	m_Elements.Find(9);
	pElement->GetTexColor().Blend( eCTRLSTATE_NORMAL, fElpasedTime );

	m_pDlg->DrawSprite( pElement, &m_rcIndicator );
	RECT	rc	=	m_rcIndicator;
	InflateRect( &rc, -m_nSpacing, -m_nSpacing );
	D3DCOLOR col =	stt_eImeState == eIMESTATE_ON && stt_bActiveImeSystem ? 
					GetIMEColor(eIMECOLOR_INDICATOR_IME) : GetIMEColor(eIMECOLOR_INDICATOR_ENG);

	pElement->GetFontColor().SetCurrentColor( col );

	RECT	rcCalc			=	{0, 0, 0, 0};
	WCHAR	*ptszIndicator	=	stt_bActiveImeSystem ? stt_ptszCurrentIndicator : stt_tszIndicatorArr[0];

	m_pDlg->CalcTextRect( ptszIndicator, pElement, &rcCalc );
	m_pDlg->DrawText( ptszIndicator, pElement, &rc );

	return S_OK;
}//	RenderIndicator
//--------------------------------------------------------------------------------------
HRESULT	CPUIIMEEditBox::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	if( m_bVisible == false )
		return S_OK;

	CPUIEditBox::OnRender( pDev, fElapsedTime );

	CPUIElement	*pElement	=	GetCustomSkinElement( eSKINTYPE_EDITBOX_BACKGROUND );

	if( pElement )
	{
		stt_CompString.SetFontNode( m_pDlg->GetFontFromManager( pElement->GetFontID() ) );
		stt_CandList._HoriCand.SetFontNode( m_pDlg->GetFontFromManager( pElement->GetFontID() ) );
	}

	if( m_bFocus )
	{
		RenderComposition( pDev, fElapsedTime );

		if( stt_bVisibleReadingWindow )
			RenderCandidateReadingWindow( pDev, fElapsedTime, true );
		else
			if( stt_CandList._bShowWindow )
				RenderCandidateReadingWindow( pDev, fElapsedTime, false );

	}//	if( m_bFocus )

	return S_OK;
}//	Render
//--------------------------------------------------------------------------------------
//	EOF