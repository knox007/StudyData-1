#ifndef _JUIIMEEDITBOX_H_
#define	_JUIIMEEDITBOX_H_

#pragma once
#include "PUIeditbox.h"
#include "PUIUniBuffer.h"
#include <dimm.h>
#include <PUTListMgr.h>

class CPUIDlg;

const int	MAX_CANDLIST		=	10;
const int	MAX_COMPSTRING_SIZE	=	256;



class CPUIIMEEditBox :
	public CPUIEditBox
{
protected:
	// Empty implementation of the IMM32 API
	static INPUTCONTEXT* WINAPI Dummy_ImmLockIMC( HIMC ) { return NULL; }
	static BOOL WINAPI Dummy_ImmUnlockIMC( HIMC ) { return FALSE; }
	static LPVOID WINAPI Dummy_ImmLockIMCC( HIMCC ) { return NULL; }
	static BOOL WINAPI Dummy_ImmUnlockIMCC( HIMCC ) { return FALSE; }
	static BOOL WINAPI Dummy_ImmDisableTextFrameService( DWORD ) { return TRUE; }
	static LONG WINAPI Dummy_ImmGetCompositionString( HIMC, DWORD, LPVOID, DWORD ) { return IMM_ERROR_GENERAL; }
	static DWORD WINAPI Dummy_ImmGetCandidateList( HIMC, DWORD, LPCANDIDATELIST, DWORD ) { return 0; }
	static HIMC WINAPI Dummy_ImmGetContext( HWND ) { return NULL; }
	static BOOL WINAPI Dummy_ImmReleaseContext( HWND, HIMC ) { return FALSE; }
	static HIMC WINAPI Dummy_ImmAssociateContext( HWND, HIMC ) { return NULL; }
	static BOOL WINAPI Dummy_ImmGetOpenStatus( HIMC ) { return 0; }
	static BOOL WINAPI Dummy_ImmSetOpenStatus( HIMC, BOOL ) { return 0; }
	static BOOL WINAPI Dummy_ImmGetConversionStatus( HIMC, LPDWORD, LPDWORD ) { return 0; }
	static HWND WINAPI Dummy_ImmGetDefaultIMEWnd( HWND ) { return NULL; }
	static UINT WINAPI Dummy_ImmGetIMEFileNameA( HKL, LPSTR, UINT ) { return 0; }
	static UINT WINAPI Dummy_ImmGetVirtualKey( HWND ) { return 0; }
	static BOOL WINAPI Dummy_ImmNotifyIME( HIMC, DWORD, DWORD, DWORD ) { return FALSE; }
	static BOOL WINAPI Dummy_ImmSetConversionStatus( HIMC, DWORD, DWORD ) { return FALSE; }
	static BOOL WINAPI Dummy_ImmSimulateHotKey( HWND, DWORD ) { return FALSE; }
	static BOOL WINAPI Dummy_ImmIsIME( HKL ) { return FALSE; }

	// Traditional Chinese IME
	static UINT WINAPI Dummy_GetReadingString( HIMC, UINT, WCHAR*, PINT, BOOL*, PUINT ) { return 0; }
	static BOOL WINAPI Dummy_ShowReadingWindow( HIMC, BOOL ) { return FALSE; }

	// Verion library imports
	static BOOL APIENTRY Dummy_VerQueryValueA( const LPVOID, LPSTR, LPVOID *, PUINT ) { return 0; }
	static BOOL APIENTRY Dummy_GetFileVersionInfoA( LPSTR, DWORD, DWORD, LPVOID ) { return 0; }
	static DWORD APIENTRY Dummy_GetFileVersionInfoSizeA( LPSTR, LPDWORD ) { return 0; }

	// Function pointers: IMM32
	static INPUTCONTEXT* (WINAPI * _ImmLockIMC)( HIMC );
	static BOOL (WINAPI * _ImmUnlockIMC)( HIMC );
	static LPVOID (WINAPI * _ImmLockIMCC)( HIMCC );
	static BOOL (WINAPI * _ImmUnlockIMCC)( HIMCC );
	static BOOL (WINAPI * _ImmDisableTextFrameService)( DWORD );
	static LONG (WINAPI * _ImmGetCompositionString)( HIMC, DWORD, LPVOID, DWORD );
	static DWORD (WINAPI * _ImmGetCandidateList)( HIMC, DWORD, LPCANDIDATELIST, DWORD );
	static HIMC (WINAPI * _ImmGetContext)( HWND );
	static BOOL (WINAPI * _ImmReleaseContext)( HWND, HIMC );
	static HIMC (WINAPI * _ImmAssociateContext)( HWND, HIMC );
	static BOOL (WINAPI * _ImmGetOpenStatus)( HIMC );
	static BOOL (WINAPI * _ImmSetOpenStatus)( HIMC, BOOL );
	static BOOL (WINAPI * _ImmGetConversionStatus)( HIMC, LPDWORD, LPDWORD );
	static HWND (WINAPI * _ImmGetDefaultIMEWnd)( HWND );
	static UINT (WINAPI * _ImmGetIMEFileNameA)( HKL, LPSTR, UINT );
	static UINT (WINAPI * _ImmGetVirtualKey)( HWND );
	static BOOL (WINAPI * _ImmNotifyIME)( HIMC, DWORD, DWORD, DWORD );
	static BOOL (WINAPI * _ImmSetConversionStatus)( HIMC, DWORD, DWORD );
	static BOOL (WINAPI * _ImmSimulateHotKey)( HWND, DWORD );
	static BOOL (WINAPI * _ImmIsIME)( HKL );

	// Function pointers: Traditional Chinese IME
	static UINT (WINAPI * _GetReadingString)( HIMC, UINT, WCHAR*, PINT, BOOL*, UINT* );
	static BOOL (WINAPI * _ShowReadingWindow)( HIMC, BOOL );

	// Function pointers: Verion library imports
	static BOOL (APIENTRY * _VerQueryValueA)( const LPVOID, LPSTR, LPVOID *, PUINT );
	static BOOL (APIENTRY * _GetFileVersionInfoA)( LPSTR, DWORD, DWORD, LPVOID );
	static DWORD (APIENTRY * _GetFileVersionInfoSizeA)( LPSTR, LPDWORD );



public:
	CPUIIMEEditBox( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	virtual ~CPUIIMEEditBox()				{ ClearMembers(); }
	void	InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }
	virtual void ClearMembers()				{ stt_LocaleArr.DeleteAll(); }

	static void	Initialize();
	static void	UnInitialize();

	static HRESULT	StaticOnCreateDevice( HWND hWnd );
	static void		EnableIMESystem( bool bEnable )	{ stt_bActiveImeSystem = bEnable; }
	virtual void	UpdateRects();

	//	MsgProc
	static	bool	StaticMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual	bool	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual	bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	void			PumpMsg();

	//	Render
	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	virtual HRESULT	RenderCandidateReadingWindow( LPDIRECT3DDEVICE9 pDev, float fElapsedTime, bool bReading );
	virtual	HRESULT	RenderComposition( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	virtual HRESULT	RenderIndicator( LPDIRECT3DDEVICE9 pDev, float fElpasedTime );

	//	Focus
	virtual	void	OnFocusIn( HWND hWnd );
	virtual	void	OnFocusOut( HWND hWnd );


protected:
	static	WORD	GetLanguage()				{ return LOWORD( stt_hKeyboardLayerCurrent ); }
	static	WORD	GetPrimaryLanguage()		{ return PRIMARYLANGID( GetLanguage() ); }
	static	WORD	GetSubLanguage()			{ return SUBLANGID( GetLanguage() );}
	static	void	SendKey( BYTE byVirtKey );
	static	DWORD	GetIMEId( UINT unIdx = 0 );
	static	void	CheckInputLocale();
	static	void	CheckToggleState( HWND hWnd );
	static	void	SetupIMEAPI();
	static	void	ResetCompositionString();
	static	void	GetReadingWindowOrientation( DWORD dwID );
	static	void	GetPrivateReadingString( HWND hWnd );
	void			TruncateCompString( HWND hWnd, bool bUseBackSpace = true, int nNewStrLen = 0 );
	void			FinalizeString( HWND hWnd, bool bSend );	
	void			SendCompString( HWND hWnd );



protected:
	enum eINDICATOR_
	{
		eINDICATOR_NONE,
		eINDICATOR_CHS,
		eINDICATOR_CHT,
		eINDICATOR_KOREAN,
		eINDICATOR_JAPANESE,

		eINDICATOR_MAX
	};//	eINDICATOR_

	enum eIMESTATE_
	{
		eIMESTATE_OFF,
		eIMESTATE_ON,
		eIMESTATE_ENGLISH,

		eIMESTATE_MAX
	};//	eIMESTATE_

	struct sJUICandList
	{
		WCHAR			_tszCandidate[MAX_CANDLIST][MAX_COMPSTRING_SIZE];
		CPUIUniBuffer	_HoriCand;
		int				_nFirstSelected;
		int				_nHoriSelectedLen;
		DWORD			_dwCount;
		DWORD			_dwSelection;
		DWORD			_dwPageSize;
		int				_nReadingError;
		bool			_bShowWindow;
		RECT			_rcCandidate;
	};

	struct sInputLocale
	{
		HKL		_hKeyboardLayout;
		WCHAR	_tszLangAbbreviation[3];
		WCHAR	_tszLocalLanguageName[64];
	};

	//	Handle
	static	HINSTANCE				stt_hDllImm32;
	static	HINSTANCE				stt_hDllVer;
	static	HIMC					stt_hImcDef;
	static	HKL						stt_hKeyboardLayerCurrent;
	static	HINSTANCE				stt_hDllIme;
	

	//	Attribute	
	static	CPUTListMgrPt<sInputLocale>	stt_LocaleArr;

	static	bool						stt_bVerticalCand;
	static	WCHAR*						stt_ptszCurrentIndicator;
	static	WCHAR						stt_tszIndicatorArr[eINDICATOR_MAX][eIMESTATE_MAX];
	static	bool						stt_bInsertOnType;		//	키가 눌리자 마자 글자가 입력되는지 여부( 한국어 특성 )
	static	eIMESTATE_					stt_eImeState;
	static	bool						stt_bActiveImeSystem;	//	Ime시스템이 활성화 되었는가?
	static	POINT						stt_ptCompString;			//	구성 문자열의 위치. 매프레임마다 갱신.
	static	int							stt_nCompCaretPosition;
	static	int							stt_nFirstTargetConv;
	static	CPUIUniBuffer				stt_CompString;
	static	BYTE						stt_byCompStringAttrArr[MAX_COMPSTRING_SIZE];
	static	DWORD						stt_dwCompStringClause[MAX_COMPSTRING_SIZE];
	static	WCHAR						stt_tszReadingString[32];
	static	sJUICandList				stt_CandList;
	static	bool						stt_bVisibleReadingWindow;
	static	bool						stt_bHorizReading;
	static	bool						stt_bChineseIME;
	
	int		m_nIndicatorWidth;
	RECT	m_rcIndicator;
	
	
	//	color
	enum eIMECOLOR_
	{
		eIMECOLOR_READING,
		eIMECOLOR_READING_WINDOW,
		eIMECOLOR_READING_SELECTED,
		eIMECOLOR_READING_SELECTEDBACKGROUND,

		eIMECOLOR_CANDIDATE,
		eIMECOLOR_CANDIDATE_WINDOW,
		eIMECOLOR_CANDIDATE_SELECTED,
		eIMECOLOR_CANDIDATE_SELECTEDBACKGROUND,

		eIMECOLOR_COMP,
		eIMECOLOR_COMP_WINDOW,
		eIMECOLOR_COMP_CARET,
		eIMECOLOR_COMP_TARGET,
		eIMECOLOR_COMP_TARGETBACKGROUND,
		eIMECOLOR_COMP_TARGETNONE,
		eIMECOLOR_COMP_TARGETNONEBACKGROUND,

		eIMECOLOR_INDICATOR_IME,
		eIMECOLOR_INDICATOR_ENG,
		eIMECOLOR_INDICATOR_BACKGROUND,

		eIMECOLOR_MAX
	};
	void	SetIMEColor( eIMECOLOR_ eIdx, D3DCOLOR col )
	{ m_colIME[ eIdx ] = col; }
	D3DCOLOR	GetIMEColor( eIMECOLOR_ eIdx )
	{ return m_colIME[eIdx]; }

	D3DCOLOR	m_colIME[eIMECOLOR_MAX];

#if defined(DEBUG) || defined(_DEBUG)
	static bool	s_bIMEStaticMsgProcCalledForDBG;
#endif
};

#endif	//_JUIIMEEDITBOX_H_