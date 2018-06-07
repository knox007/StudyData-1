#include "StdAfx.h"
#include "PUIScrollBar.h"
#include "PUTCommon.h"
#include "PUICtrlMisc.h"
#include "PUTTimer.h"

//---------------------------------------------------------------------------------------
void	CPUIScrollBar::InitMembers()
{
	m_eCtrlType		=	eCTRLTYPE_SCROLLBAR;

	m_bShowthumb	=	true;
	m_bDrag			=	false;

	PUT_ZERO_MEMORY( m_rcPrevBttn );
	PUT_ZERO_MEMORY( m_rcNextBttn );
	PUT_ZERO_MEMORY( m_rcTrack );
	PUT_ZERO_MEMORY( m_rcThumbBttn );

	m_nPosVal	=	0;
	m_nPageSize	=	1;
	m_nStart	=	0;
	m_nEnd		=	1;
	m_ArrowBttnState	=	eARROWBUTTON_CLEAR;
	m_dArrowTimestamp	=	0.0;

}//	InitMembers
//---------------------------------------------------------------------------------------
void	CPUIScrollBar::UpdateRects()
{
	CPUICtrl::UpdateRects();

	SetRect(	&m_rcPrevBttn, 
				m_rcBoundBox.left,	m_rcBoundBox.top,
				m_rcBoundBox.right,	m_rcBoundBox.top + RectWidth( m_rcBoundBox )
			);

	SetRect(	&m_rcNextBttn,
				m_rcBoundBox.left,	m_rcBoundBox.bottom - RectWidth( m_rcBoundBox ),
				m_rcBoundBox.right,	m_rcBoundBox.bottom
			);

	SetRect(	&m_rcTrack,
				m_rcPrevBttn.left,	m_rcPrevBttn.bottom,
				m_rcNextBttn.right,	m_rcNextBttn.top );
	
	m_rcThumbBttn.left	=	m_rcPrevBttn.left;
	m_rcThumbBttn.right	=	m_rcPrevBttn.right;

	UpdateThumbRect();

}//	UpdateRects
//---------------------------------------------------------------------------------------
void	CPUIScrollBar::UpdateThumbRect()
{
	if( m_nEnd - m_nStart > m_nPageSize )
	{
		// 원본 코드는 페이지사이즈에 따라 변하지만. 텍스쳐가 늘어지면 이쁘지 않으므로 원본 크기를 유지한다.
		//	int nThumbHeight	=	__max( RectHeight( m_rcTrack ) * m_nPageSize / ( m_nEnd - m_nStart ), SCROLLBAR_MINTHUMBSIZE );

		// Thumb 의 높이는 Arrow 와 같다. ListBox 의 아이템 수 에 따라 변하지 않는다.
		int nThumbHeight	=	RectHeight( m_rcPrevBttn );

		int nMaxPos				=	m_nEnd - m_nStart - m_nPageSize;
		m_rcThumbBttn.top		=	m_rcTrack.top + ( m_nPosVal - m_nStart ) * ( RectHeight( m_rcTrack ) - nThumbHeight ) / nMaxPos;
		m_rcThumbBttn.bottom	=	m_rcThumbBttn.top + nThumbHeight;
		m_bShowthumb			=	true;
	}else
	{
		m_rcThumbBttn.bottom	=	m_rcThumbBttn.top;
		m_bShowthumb	=	false;
	}

}//	UpdateThumbRect
//---------------------------------------------------------------------------------------
void	CPUIScrollBar::Scroll( int nDelta )
{
	m_nPosVal	+=	nDelta;

	Cap();

	UpdateThumbRect();

}//	Scroll
//---------------------------------------------------------------------------------------
void	CPUIScrollBar::ShowItem( int nID )
{
	if( nID < 0 )
		nID	=	0;

	if( nID >= m_nEnd )
		nID	=	m_nEnd - 1;

	if( m_nPosVal > nID )
		m_nPosVal	=	nID;
	else
	if( m_nPosVal + m_nPageSize <= nID )
		m_nPosVal	=	nID - m_nPageSize + 1;

	UpdateThumbRect();

}//	ShowItem
//---------------------------------------------------------------------------------------
bool	CPUIScrollBar::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return false;

}//	HandleKeyboard
//---------------------------------------------------------------------------------------
bool	CPUIScrollBar::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	static int snThumbOffsetY;

	m_ptLastMouse	=	pt;

	switch( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			//	Previous Button
			if( PtInRect( &m_rcPrevBttn, pt ) )
			{
				SetCapture( hWnd );
				if( m_nPosVal > m_nStart )
					--m_nPosVal;

				UpdateThumbRect();

				m_ArrowBttnState	=	eARROWBUTTON_CLICK_PREV;
//				m_dArrowTimestamp	=	(double)gUtTimer->GetCurrentTime();	//	이 함수로 시간을 얻는게 괜찮을려나??
				m_dArrowTimestamp	=	(double)gUtTimer->GetAbsoluteTime();
				return true;
			}//	if( PtInRect( &m_rcPrevBttn, pt ) )


			//	Next Button
			if( PtInRect( &m_rcNextBttn, pt ) )
			{
				SetCapture( hWnd );
				if( m_nPosVal + m_nPageSize < m_nEnd )
					++m_nPosVal;

				UpdateThumbRect();

				m_ArrowBttnState	=	eARROWBUTTON_CLICK_NEXT;
//				m_dArrowTimestamp	=	(double)gUtTimer->GetCurrentTime();	//	이 함수로 시간을 얻는게 괜찮을려나??
				m_dArrowTimestamp	=	(double)gUtTimer->GetAbsoluteTime();
				return true;
			}//	if( PtInRect( &m_rcNextBttn, pt ) )


			//	Thumb Button
			if( PtInRect( &m_rcThumbBttn, pt ) )
			{
				SetCapture( hWnd );
				m_bDrag = true;
				snThumbOffsetY	=	pt.y - m_rcThumbBttn.top;
				return true;
			}//	if( PtInRect( &m_rcThumbBttn, pt ) )


			//	Track
			if( m_rcThumbBttn.left <= pt.x &&
				m_rcThumbBttn.right > pt.x )
			{
				SetCapture( hWnd );
				if( m_rcThumbBttn.top > pt.y &&
					m_rcTrack.top <= pt.y )
				{
					Scroll( -( m_nPageSize - 1 ) );
					return true;
				}else				
				if( m_rcThumbBttn.bottom <= pt.y && 
						m_rcTrack.bottom > pt.y )
					{
						Scroll( m_nPageSize - 1 );
						return true;
					}
			}//	if( m_rcThumbBttn.left <= pt.x && m_rcThumbBttn.right > pt.x )
		}//	case WM_LBUTTONDOWN: / 	case WM_LBUTTONDBLCLK:
		break;


	case WM_LBUTTONUP:
		{
			m_bDrag	=	false;
			ReleaseCapture();
			UpdateThumbRect();
			m_ArrowBttnState	=	eARROWBUTTON_CLEAR;
		}//	case WM_LBUTTONUP:
		break;

		
	case WM_MOUSEMOVE:
		{
			if( m_bDrag )
			{
				m_rcThumbBttn.bottom	+=	pt.y - snThumbOffsetY - m_rcThumbBttn.top;
				m_rcThumbBttn.top		=	pt.y - snThumbOffsetY;
				if( m_rcThumbBttn.top < m_rcTrack.top )
					OffsetRect( &m_rcThumbBttn, 0, m_rcTrack.top - m_rcThumbBttn.top );
				else
					if( m_rcThumbBttn.bottom > m_rcTrack.bottom )
						OffsetRect( &m_rcThumbBttn, 0, m_rcTrack.bottom - m_rcThumbBttn.bottom );

				int nMaxFirstItem	=	m_nEnd - m_nStart - m_nPageSize;
				int	nMaxThumb		=	RectHeight( m_rcTrack ) - RectHeight( m_rcThumbBttn );

				m_nPosVal = m_nStart + 
							( m_rcThumbBttn.top - m_rcTrack.top + ( nMaxThumb / ( nMaxFirstItem * 2 ) ) ) * 
							nMaxFirstItem / nMaxThumb;

				return true;
			}
		}//	case WM_MOUSEMOVE:
		break;

	}//	switch( uMsg )

	return false;
}//	HandleMouse
//---------------------------------------------------------------------------------------
bool	CPUIScrollBar::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_CAPTURECHANGED:
		{
			m_bDrag = false;
		}		
		return true;
	}
	return false;
}//	MsgProc
//---------------------------------------------------------------------------------------
void	CPUIScrollBar::Cap()
{
	if( m_nPosVal < m_nStart ||
		m_nEnd - m_nStart <= m_nPageSize )
	{
		m_nPosVal = m_nStart;
	}else
	if( m_nPosVal + m_nPageSize > m_nEnd )
		m_nPosVal = m_nEnd - m_nPageSize;
}//	Cap
//---------------------------------------------------------------------------------------
void	CPUIScrollBar::SetTrackRange( int nStart, int nEnd )
{
	m_nStart	=	nStart;
	m_nEnd		=	nEnd;
	Cap();
	UpdateThumbRect();
}//	SetTrackRange
//---------------------------------------------------------------------------------------
HRESULT	CPUIScrollBar::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	eCTRLSTATE_	eState	=	eCTRLSTATE_NORMAL;

	if( !m_bVisible )
		eState	=	eCTRLSTATE_HIDDEN;
	else
	if( !IsActive() )
		eState	=	eCTRLSTATE_DISABLED;
	else
	if( m_bMouseInRect )
		eState	=	eCTRLSTATE_MOUSEOVER;
	else
	if( IsFocus() )
		eState	=	eCTRLSTATE_FOCUS;

	//	PreBttn
	CPUIElement*	pPreBttnEle		=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_PREBTN_ACTIVE );
	//	NextBttn
	CPUIElement*	pNextBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_NEXTBTN_ACTIVE );
	//	ThumbBttn
	CPUIElement*	pThumbBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_THUMBBTN_ACTIVE );
	//	TrackBttn
	CPUIElement*	pTrackEle		=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_TRACKBAR );

	//	누르고 있지 않을때..
	if( m_ArrowBttnState == eARROWBUTTON_CLEAR )
	{
		if( PtInRect( &m_rcPrevBttn, m_ptLastMouse ) )
		{
			pPreBttnEle		=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_PREBTN_MOUSEOVER );
		}
		else
		if( PtInRect( &m_rcNextBttn, m_ptLastMouse ) )
		{
			pNextBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_NEXTBTN_MOUSEOVER );
		}
		else
		if( PtInRect( &m_rcThumbBttn, m_ptLastMouse ) )
		{
			pThumbBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_THUMBBTN_MOUSEOVER );
		}
	}//	if( m_ArrowBttnState = eARROWBUTTON_CLEAR )
	else
	//	누르고 있을때..
	{
//		double dCurrTime	=	(double)gUtTimer->GetCurrentTime();
		double dCurrTime	=	(double)gUtTimer->GetAbsoluteTime();		

		//	PrevBttn
		if( PtInRect( &m_rcPrevBttn, m_ptLastMouse ) )
		{
			switch( m_ArrowBttnState )
			{
			case eARROWBUTTON_CLICK_PREV:
				if( SCROLLBAR_ARROWCLICK_DELAY < dCurrTime - m_dArrowTimestamp )
				{
					Scroll( -1 );
					m_ArrowBttnState	=	eARROWBUTTON_HELD_PREV;
					m_dArrowTimestamp	=	dCurrTime;
				}				
				break;

			case eARROWBUTTON_HELD_PREV:
				if( SCROLLBAR_ARROWCLICK_REPEAT < dCurrTime - m_dArrowTimestamp )
				{
					Scroll( -1 );
					m_dArrowTimestamp	=	dCurrTime;
				}				
				break;
			}

			pPreBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_PREBTN_CLICKED );
		}
		else
		//	NextBttn
		if( PtInRect( &m_rcNextBttn, m_ptLastMouse ) )
		{
			switch ( m_ArrowBttnState )
			{
			case eARROWBUTTON_CLICK_NEXT:
				if( SCROLLBAR_ARROWCLICK_DELAY < dCurrTime - m_dArrowTimestamp )
				{
					Scroll( 1 );
					m_ArrowBttnState	=	eARROWBUTTON_HELD_NEXT;
					m_dArrowTimestamp	=	dCurrTime;
				}				
				break;

			case eARROWBUTTON_HELD_NEXT:
				if( SCROLLBAR_ARROWCLICK_REPEAT < dCurrTime - m_dArrowTimestamp )
				{
					Scroll( 1 );
					m_dArrowTimestamp	=	dCurrTime;
				}
				break;
			}
			pNextBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_NEXTBTN_CLICKED );
		}
	}//	~if( m_ArrowBttnState = eARROWBUTTON_CLEAR )


	if( m_bDrag )
		pThumbBttnEle	=	GetCustomSkinElement( eSKINTYPE_SCROLLBAR_THUMBBTN_CLICKED );

	pPreBttnEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pNextBttnEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pThumbBttnEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pTrackEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );

	//	Track
	m_pDlg->DrawSkinSprite( pTrackEle, &m_rcTrack );
	
	//	PrevBttn
	m_pDlg->DrawSkinSprite( pPreBttnEle, &m_rcPrevBttn );
	
	//	NextBttn
	m_pDlg->DrawSkinSprite( pNextBttnEle, &m_rcNextBttn );
	
	//	ThumbBttn
	if( m_bShowthumb )
		m_pDlg->DrawSkinSprite( pThumbBttnEle, &m_rcThumbBttn );

	return S_OK;
}//	Render
//---------------------------------------------------------------------------------------
//	EOF
