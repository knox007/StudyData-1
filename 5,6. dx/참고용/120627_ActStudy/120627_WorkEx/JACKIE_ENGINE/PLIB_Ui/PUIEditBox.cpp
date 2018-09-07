
#include "StdAfx.h"
#include "PUICtrlMisc.h"
#include "PUIEditBox.h"
#include "PUIDlg.h"
#include "PUTTimer.h"
#include "PUTCommon.h"
#include <strsafe.h>
#pragma warning( disable : 4995 ) // disable deprecated warning 

const	int	EDITBOX_SCROLLEXTENT	=	4;
const	int	EDITBOX_DEFAULT_WIDTH	=	5;
const	int	EDITBOX_DEFAULT_SPACING	=	4;

enum eVK_CTRL
{
	eVK_CTRL_A = 1,
	eVK_CTRL_B,
	eVK_CTRL_C,
	eVK_CTRL_D,
	eVK_CTRL_E,
	eVK_CTRL_F,
	eVK_CTRL_G,
	eVK_CTRL_H,
	eVK_CTRL_I,
	eVK_CTRL_J,
	eVK_CTRL_K,
	eVK_CTRL_L,
	eVK_CTRL_M,
	eVK_CTRL_N,
	eVK_CTRL_O,
	eVK_CTRL_P,
	eVK_CTRL_Q,
	eVK_CTRL_R,
	eVK_CTRL_S,
	eVK_CTRL_T,
	eVK_CTRL_U,
	eVK_CTRL_V,
	eVK_CTRL_W,
	eVK_CTRL_X,
	eVK_CTRL_Y,
	eVK_CTRL_Z,
	eVK_CTRL_LBIGBLANK,	/*	[	*/
	eVK_CTRL_WONMARK,	/*	\	*/
	eVK_CTRL_RBIGBLANK,	/*	]	*/
	eVK_CTRL_SIZE
};

bool CPUIEditBox::stt_bHideCaret = false;
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::InitMembers()
{
	m_eCtrlType				=	eCTRLTYPE_EDITBOX;

	m_nBorder				=	EDITBOX_DEFAULT_WIDTH;
	m_nSpacing				=	EDITBOX_DEFAULT_SPACING;

	m_bCaretVisible			=	true;
	m_dfBlinkTime			=	GetCaretBlinkTime() * 0.001f;
	m_dfLastBlinkTimestamp	=	gUtTimer->GetAbsoluteTime();
	stt_bHideCaret			=	false;
	m_nFirstVisible			=	0;

	// jackie_notice : 에디트 박스의 글자 색
	m_colText				=	D3DCOLOR_ARGB( 255, 16, 16, 16 );
	m_colSelectedText		=	D3DCOLOR_ARGB( 255, 255, 255, 255 );
	m_colSelectedBackground	=	D3DCOLOR_ARGB( 255, 40, 50, 92 );
	m_colCaret				=	D3DCOLOR_ARGB( 255, 0, 0, 0 );

	m_nCaretPos				=	m_nSelectionStartPos	=	0;
	m_bInsertModeFlag		=	true;
	m_bMouseDrag			=	false;
}//	InitMembers
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::PlaceCaret( int nCP )
{
	assert( nCP >= 0 && nCP <= m_UniBuffer.GetTextSize() );
	m_nCaretPos	=	nCP;

	int nX1st, nX, nX2;
	m_UniBuffer.CPtoX( m_nFirstVisible, FALSE, &nX1st );
	m_UniBuffer.CPtoX( nCP, FALSE, &nX );

	if( nCP == m_UniBuffer.GetTextSize() )
		nX2 = nX;
	else
		m_UniBuffer.CPtoX( nCP, TRUE, &nX2 );

	if( nX < nX1st )
		m_nFirstVisible = nCP;
	else
		if( nX2 > nX1st + RectWidth( m_rcText ) )
		{
			int nXNewLeft = nX2 - RectWidth( m_rcText);

			int nCPNew1st, nNewTrail;
			m_UniBuffer.XtoCP( nXNewLeft, &nCPNew1st, &nNewTrail );

			int nXNew1st;
			m_UniBuffer.CPtoX( nCPNew1st, FALSE, &nXNew1st );
			if( nXNew1st < nXNewLeft )
				++nCPNew1st;

			m_nFirstVisible	= nCPNew1st;
		}
}//	PlaceCaret
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::ClearText()
{
	m_UniBuffer.Clear();
	PlaceCaret( 0 );
	m_nFirstVisible			=	0;	
	m_nSelectionStartPos	=	0;
}//	ClearText
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::SetText( const WCHAR* ptszText, bool bSelected /* = false */ )
{
	assert( ptszText != NULL );

	m_UniBuffer.SetText( ptszText );
	m_nFirstVisible	=	0;
	PlaceCaret( m_UniBuffer.GetTextSize() );
	m_nSelectionStartPos = bSelected ? 0 : m_nCaretPos;
}//	SetText
//-------------------------------------------------------------------------------------------
HRESULT		CPUIEditBox::GetTextCopy( const WCHAR* ptszDest, UINT unBufferCount )
{
	assert( ptszDest );

	StringCchCopyW( (WCHAR*)ptszDest, unBufferCount, m_UniBuffer.GetBuffer() );

	return S_OK;
}//	GetTextCopy
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::DeleteSelectionText()
{
	int nFirst	=	__min( m_nCaretPos, m_nSelectionStartPos );
	int nLast	=	__max( m_nCaretPos, m_nSelectionStartPos );

	PlaceCaret( nFirst );

	m_nSelectionStartPos	=	m_nCaretPos;

	for( int nCur = nFirst; nCur < nLast; ++nCur )
		m_UniBuffer.RemoveChar( nFirst );
}//	DeleteSelectionText
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::UpdateRects()
{
	CPUICtrl::UpdateRects();

	m_rcText	=	m_rcBoundBox;

	InflateRect( &m_rcText, -m_nBorder, -m_nBorder );

	m_rcRender[0]	=	m_rcText;

	SetRect( &m_rcRender[1],	m_rcBoundBox.left,	m_rcBoundBox.top,	m_rcText.left,			m_rcText.top );
	SetRect( &m_rcRender[2],	m_rcText.left,		m_rcBoundBox.top,	m_rcText.right,			m_rcText.top );
	SetRect( &m_rcRender[3],	m_rcText.right,		m_rcBoundBox.top,	m_rcBoundBox.right,		m_rcText.top );
	SetRect( &m_rcRender[4],	m_rcBoundBox.left,	m_rcText.top,		m_rcText.left,			m_rcText.bottom );

	SetRect( &m_rcRender[5],	m_rcBoundBox.left,	m_rcBoundBox.top,	m_rcText.left,	m_rcText.top );
	SetRect( &m_rcRender[6],	m_rcBoundBox.left,	m_rcBoundBox.top,	m_rcText.left,	m_rcText.top );
	SetRect( &m_rcRender[7],	m_rcBoundBox.left,	m_rcBoundBox.top,	m_rcText.left,	m_rcText.top );
	SetRect( &m_rcRender[8],	m_rcBoundBox.left,	m_rcBoundBox.top,	m_rcText.left,	m_rcText.top );

	InflateRect( &m_rcText, -m_nSpacing, -m_nSpacing );
}//	UpdateRects
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::CopyToClipboard()
{
	if( m_nCaretPos != m_nSelectionStartPos && OpenClipboard( NULL ) )
	{
		EmptyClipboard();

		HGLOBAL	hBlock	=	GlobalAlloc( GMEM_MOVEABLE, sizeof(WCHAR) * ( m_UniBuffer.GetTextSize() + 1 ) );
		if( hBlock )
		{
			WCHAR* ptszText	=	( WCHAR* )GlobalLock( hBlock );
			if( ptszText )
			{
				int nFirst	=	__min( m_nCaretPos, m_nSelectionStartPos );
				int nLast	=	__max( m_nCaretPos, m_nSelectionStartPos );
				if( nLast - nFirst > 0 )
					CopyMemory( ptszText, m_UniBuffer.GetBuffer() + nFirst, ( nLast - nFirst ) * sizeof(WCHAR) );
				ptszText[nLast - nFirst] = _T('\0');
				GlobalUnlock( hBlock );
			}
			SetClipboardData( CF_UNICODETEXT, hBlock );
		}
		CloseClipboard();

		if( hBlock )
			GlobalFree( hBlock );
	}
}//	CopyToClipboard
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::PasteFromClipboard()
{
	DeleteSelectionText();

	if( OpenClipboard( NULL ) )
	{
		HANDLE hHandle = GetClipboardData( CF_UNICODETEXT );
		if( hHandle )
		{
			WCHAR* ptszText		=	(WCHAR*)GlobalLock( hHandle );
			if( ptszText )
			{
				if( m_UniBuffer.InsertString( m_nCaretPos, ptszText ) )
					PlaceCaret( m_nCaretPos + lstrlenW( ptszText ) );
				m_nSelectionStartPos = m_nCaretPos;
				GlobalUnlock( hHandle );
			}
		}
		CloseClipboard();
	}
}//	PasteFromClipboard
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::OnFocusIn( HWND hWnd )
{
	CPUICtrl::OnFocusIn( hWnd );

	ResetCaretBlink();
}//	OnFocusIn
//-------------------------------------------------------------------------------------------
bool	CPUIEditBox::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive())
		return false;

	bool bHandle	=	false;

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		{
			switch ( wParam )
			{
			case VK_TAB:
				break;

			case VK_HOME:
				{
					PlaceCaret( 0 );
					if( GetKeyState( VK_SHIFT ) >= 0 )
						m_nSelectionStartPos = m_nCaretPos;
					ResetCaretBlink();
					bHandle = true;
				}//	VK_HOME
				break;

			case VK_END:
				{
					PlaceCaret( m_UniBuffer.GetTextSize() );
					if( GetKeyState( VK_SHIFT ) >= 0 )
						m_nSelectionStartPos = m_nCaretPos;
					ResetCaretBlink();
					bHandle = true;
				}//	VK_END
				break;

			case VK_INSERT:
				{
					if( GetKeyState( VK_CONTROL ) )
					{
						CopyToClipboard();
					}else
						if( GetKeyState( VK_SHIFT ) )
						{
							PasteFromClipboard();
						}else
						{
							m_bInsertModeFlag = !m_bInsertModeFlag;
						}
				}//	VK_INSERT
				break;

			case VK_DELETE:
				{
					if( m_nCaretPos != m_nSelectionStartPos )
					{
						DeleteSelectionText();
						m_pDlg->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
					}
					else
					{
						if( m_UniBuffer.RemoveChar( m_nCaretPos ) )
							m_pDlg->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
					}
					ResetCaretBlink();
					bHandle = true;
				}//	VK_DELETE
				break;

			case VK_LEFT:
				{
					if( GetKeyState( VK_CONTROL ) < 0 )
					{
						m_UniBuffer.GetPriorItemPos( m_nCaretPos, &m_nCaretPos );
						PlaceCaret( m_nCaretPos );
					}else
						if( m_nCaretPos > 0 )
							PlaceCaret( m_nCaretPos - 1 );
					
					if( GetKeyState( VK_SHIFT ) >= 0 )
						m_nSelectionStartPos = m_nCaretPos;
					ResetCaretBlink();
					bHandle = true;
				}//	VK_LEFT
				break;

			case VK_RIGHT:
				{
					if( GetKeyState( VK_CONTROL ) < 0 )
					{
						m_UniBuffer.GetNextItemPos( m_nCaretPos, &m_nCaretPos );
						PlaceCaret( m_nCaretPos );
					}else
						if( m_nCaretPos < m_UniBuffer.GetTextSize() )
							PlaceCaret( m_nCaretPos + 1 );
					
					if( GetKeyState( VK_SHIFT ) >= 0 )
						m_nSelectionStartPos = m_nCaretPos;
					ResetCaretBlink();
					bHandle = true;
				}//	VK_RIGHT
				break;

			case VK_UP:
			case VK_DOWN:
				bHandle = true;
				break;//	VK_UP / VK_DOWN

			default:
				bHandle = wParam != VK_ESCAPE;
				break;//	default
			}
		}//	case WM_KEYDOWN:
		break;
	}//	switch ( uMsg )

	return bHandle;
}//	HandleKeyboard
//-------------------------------------------------------------------------------------------
bool	CPUIEditBox::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !m_bEnable || !m_bVisible )
		return false;

	switch( uMsg )
	{
	case WM_CHAR:
		{
			switch( (WCHAR)wParam )
			{
			case VK_BACK:
				{
					if( m_nCaretPos != m_nSelectionStartPos )
					{
						DeleteSelectionText();
						GetDlg()->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
					}else
						if( m_nCaretPos > 0 )
						{
							PlaceCaret( m_nCaretPos - 1 );
							m_nSelectionStartPos = m_nCaretPos;
							m_UniBuffer.RemoveChar( m_nCaretPos );
							GetDlg()->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
						}
						ResetCaretBlink();
				}//	case VK_BACK:
				break;



			case eVK_CTRL_X:
			case VK_CANCEL:
				{
					CopyToClipboard();

					if( (WCHAR)wParam == eVK_CTRL_X )
					{
						DeleteSelectionText();
						GetDlg()->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
					}
				}//	case eVK_CTRL_X: / VK_CANCEL:
				break;


			case eVK_CTRL_V:
				{
					PasteFromClipboard();
					GetDlg()->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
				}//	case eVK_CTRL_V:
				break;

			case eVK_CTRL_A:
				{
					if( m_nSelectionStartPos == m_nCaretPos )
					{
						m_nSelectionStartPos = 0;
						PlaceCaret( m_UniBuffer.GetTextSize() );
					}
				}//	case eVK_CTRL_A:
				break;

			case VK_RETURN:
				GetDlg()->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );
				break;

			// 문자열내에 필요없는 필요없는 문자들.
			case eVK_CTRL_Z:
			case eVK_CTRL_B:
			case eVK_CTRL_N:
			case eVK_CTRL_S:
			case eVK_CTRL_D:
			case eVK_CTRL_F:
			case eVK_CTRL_G:
			case eVK_CTRL_J:
			case eVK_CTRL_K:
			case eVK_CTRL_L:
			case eVK_CTRL_Q:
			case eVK_CTRL_W:
			case eVK_CTRL_E:
			case eVK_CTRL_R:
			case eVK_CTRL_T:
			case eVK_CTRL_Y:
			case eVK_CTRL_U:
			case eVK_CTRL_I:
			case eVK_CTRL_O:
			case eVK_CTRL_P:
			case eVK_CTRL_LBIGBLANK:
			case eVK_CTRL_RBIGBLANK:
			case eVK_CTRL_WONMARK:
				break;

			default:
				{
					if( m_nCaretPos != m_nSelectionStartPos )
						DeleteSelectionText();

					if( !m_bInsertModeFlag &&
						m_nCaretPos < m_UniBuffer.GetTextSize() )
					{
						m_UniBuffer[m_nCaretPos]	=	(WCHAR)wParam;
						PlaceCaret( m_nCaretPos + 1 );
						m_nSelectionStartPos	=	m_nCaretPos;
					}else
					{
						if( m_UniBuffer.InsertChar( m_nCaretPos, (WCHAR)wParam ) )
						{
							PlaceCaret( m_nCaretPos + 1 );
							m_nSelectionStartPos	=	m_nCaretPos;
//							PUTOutputDebugStr( PUT_CSTR_TCHAR("InsertChar : %c\n") ,wParam );
						}
					}
					ResetCaretBlink();

					GetDlg()->SendEvent( eCTRLEVENT_EDITBOX_CHANGED, true, this );

				}//	default:
				break;
			}
		}//	case WM_CHAR
		return true;

	}//	switch( uMsg )

	return false;
}//	MsgProc
//-------------------------------------------------------------------------------------------
bool	CPUIEditBox::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch ( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if( !IsFocus() )
				GetDlg()->RequestFocus( this );

			if( !ContainsPoint( pt ) )
				return false;
			
			m_bMouseDrag = true;
			SetCapture( hWnd );

			int nCP, nTrail, nX1st;

			m_UniBuffer.CPtoX( m_nFirstVisible, FALSE, &nX1st );

			if( SUCCEEDED( m_UniBuffer.XtoCP( pt.x - m_rcText.left + nX1st, &nCP, &nTrail ) ) )
			{
				if( nTrail && nCP < m_UniBuffer.GetTextSize() )
					PlaceCaret( nCP + 1 );
				else
					PlaceCaret( nCP );

				m_nSelectionStartPos = m_nCaretPos;

				ResetCaretBlink();					

			}//	if( SUCCEEDED( m_UniBuffer.XtoCP( pt.x - m_rcText.left + nX1st, &nCP, &nTrail ) ) )

			return true;
		}		
		break;
		//	case WM_LBUTTONDOWN:
		//	case WM_LBUTTONDBLCLK:


	case WM_LBUTTONUP:
		ReleaseCapture();
		m_bMouseDrag = false;
		break;


	case WM_MOUSEMOVE:
		if( m_bMouseDrag )
		{
			int nCP, nTrail, nX1st;

			m_UniBuffer.CPtoX( m_nFirstVisible, FALSE, &nX1st );
			if( SUCCEEDED( m_UniBuffer.XtoCP( pt.x - m_rcText.left + nX1st, &nCP, &nTrail ) ) )
			{
				if( nTrail && nCP < m_UniBuffer.GetTextSize() )
					PlaceCaret( nCP + 1 );
				else
					PlaceCaret( nCP );
			}
		}		
		break;
		//	case WM_MOUSEMOVE:

	}//	switch ( uMsg )

	return false;

}//	HandleMouse
//-------------------------------------------------------------------------------------------
#define IN_FLOAT_CHARSET( c )\
	( (c) == _T('-') || (c) == _T('.') || ( _T('0') <= (c) && (c) <= _T('9') ) )
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::ParseFloatArray( float* pfNumbers, int nCount )
{
	int		nWritten = 0;
	const	WCHAR *pToken, *pEnd;
	WCHAR	tszToken[60];

	pToken = m_UniBuffer.GetBuffer();

	while( nWritten < nCount && *pToken != _T('\0') )
	{
		while ( *pToken == _T(' ') )
			++pToken;

		if( *pToken == _T('\0') )
			break;

		pEnd	=	pToken;
		while( IN_FLOAT_CHARSET( *pEnd ) )
			++pEnd;

		int nTokenLen	=	__min( sizeof( tszToken )/sizeof(tszToken[0]) - 1, int( pEnd - pToken ) );
		StringCchCopyW( tszToken, nTokenLen, pToken );
		*pfNumbers	=	(float)wcstod( tszToken, NULL );
		++nWritten;
		++pfNumbers;
		pToken = pEnd;
	}//	while( nWritten < nCount && *pToken != _T('\0') )
}//	ParseFloatArray
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::SetTextFloatArray( const float* pfNumbers, int nCount )
{
	WCHAR	tszBuffer[512] = {0,};
	WCHAR	tszTmp[64];

	if( pfNumbers == NULL )
		return;

	for( int nCur = 0; nCur < nCount; ++nCur )
	{
		StringCchPrintfW( tszTmp,	64,		L"%.4f",		pfNumbers[nCur] );
		StringCchCatW(	tszBuffer,	512,	tszTmp );
	}

	if( nCount > 0 && wcslen( tszBuffer ) > 0 )
		tszBuffer[ wcslen( tszBuffer ) - 1 ] = 0;

	SetText( tszBuffer );
}
//-------------------------------------------------------------------------------------------
void	CPUIEditBox::ResetCaretBlink()
{
	m_bCaretVisible		=	true;
	m_dfLastBlinkTimestamp	=	gUtTimer->GetAbsoluteTime();
}
//-------------------------------------------------------------------------------------------
HRESULT	CPUIEditBox::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	if( !m_bVisible )
		return S_OK;

	HRESULT	hr;
	int nSelStartX = 0, nCaretX = 0;

	CPUIElement *pElement	=	GetCustomSkinElement( eSKINTYPE_EDITBOX_BACKGROUND );
	if( pElement )
	{
		m_UniBuffer.SetFontNode( m_pDlg->GetFontFromManager( pElement->GetFontID() ) );
		PlaceCaret( m_nCaretPos );
	}

	pElement->GetTexColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, 0.0f );
	m_pDlg->DrawSkinSprite( pElement, &m_rcBoundBox );

	int nXFirst;
	m_UniBuffer.CPtoX( m_nFirstVisible, FALSE, &nXFirst );

	hr = m_UniBuffer.CPtoX( m_nCaretPos, FALSE, &nCaretX );
	if( m_nCaretPos != m_nSelectionStartPos )
		hr = m_UniBuffer.CPtoX( m_nSelectionStartPos, FALSE, &nSelStartX );
	else
		nSelStartX = nCaretX;

	RECT	rcSelection;
	if( m_nCaretPos != m_nSelectionStartPos )
	{
		int nSelLeftX = nCaretX, nSelRightX = nSelStartX;
		if( nSelLeftX > nSelRightX )
		{
			int nTmp	=	nSelLeftX;
			nSelLeftX	=	nSelRightX;
			nSelRightX	=	m_rcText.bottom;
		}

		SetRect( &rcSelection, nSelLeftX, m_rcText.top, nSelRightX, m_rcText.bottom );
		OffsetRect( &rcSelection, m_rcText.left - nXFirst, 0 );
		IntersectRect( &rcSelection, &m_rcText, &rcSelection );
		m_pDlg->DrawRect( &rcSelection, m_colSelectedBackground );
	}

	pElement->GetFontColor().SetCurrentColor( m_colText );
	m_pDlg->DrawSkinText( m_UniBuffer.GetBuffer() + m_nFirstVisible, pElement, &m_rcText );

	if( m_nCaretPos != m_nSelectionStartPos )
	{
		int nFirstToRender		=	__max( m_nFirstVisible, __min( m_nSelectionStartPos, m_nCaretPos ) );
		int nNumChatToRender	=	__max( m_nSelectionStartPos, m_nCaretPos ) - nFirstToRender;
		m_Elements.Find(0)->GetFontColor().SetCurrentColor( m_colSelectedText );
		m_pDlg->DrawSkinText(	m_UniBuffer.GetBuffer() + nFirstToRender,
								pElement,
								&rcSelection,
								false,
								nNumChatToRender );
	}

	if( gUtTimer->GetAbsoluteTime() -  m_dfLastBlinkTimestamp >= m_dfBlinkTime )
	{
		m_bCaretVisible		=	!m_bCaretVisible;
		m_dfLastBlinkTimestamp	=	gUtTimer->GetAbsoluteTime();
	}

	if( m_bFocus && m_bCaretVisible && !stt_bHideCaret )
	{
		RECT rcCaret = {	m_rcText.left - nXFirst + nCaretX - 1, 
							m_rcText.top,
							m_rcText.left - nXFirst + nCaretX + 1,
							m_rcText.bottom };

		if( !m_bInsertModeFlag )
		{
			int nRightEdgeX;
			m_UniBuffer.CPtoX( m_nCaretPos, TRUE, &nRightEdgeX );
			rcCaret.right	=	m_rcText.left - nXFirst + nRightEdgeX;
		}

		m_pDlg->DrawRect( &rcCaret, m_colCaret );
	}

	return S_OK;
}//	Render
//-------------------------------------------------------------------------------------------
//	EOF