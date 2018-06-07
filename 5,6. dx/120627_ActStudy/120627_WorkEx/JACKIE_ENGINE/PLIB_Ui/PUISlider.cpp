#include "StdAfx.h"
#include "PUISlider.h"
#include "PUTCommon.h"
#include "PUICtrlMisc.h"
//------------------------------------------------------------------
void	CPUISlider::InitMembers()
{
	m_eCtrlType	=	eCTRLTYPE_SLIDER;

	m_nMin	=	0;
	m_nMax	=	100;
	m_nVal	=	50;

	m_bPressed	=	false;
}//	InitMembers
//------------------------------------------------------------------
BOOL	CPUISlider::ContainsPoint( POINT pt )
{
	return (	PtInRect( &m_rcBoundBox, pt ) ||
				PtInRect( &m_rcButton, pt ) );
}//	ContainsPoint
//------------------------------------------------------------------
void	CPUISlider::UpdateRects()
{
	CPUICtrl::UpdateRects();

	m_rcButton			=	m_rcBoundBox;
	m_rcButton.right	=	m_rcButton.left + RectHeight( m_rcButton );
	OffsetRect( &m_rcButton, -RectWidth( m_rcButton ) / 2, 0 );

	m_nButtonX	=	(int)
					( (m_nVal - m_nMin) * (float)RectWidth(m_rcBoundBox) 
					/ ( m_nMax - m_nMin ) );

	OffsetRect( &m_rcButton, m_nButtonX, 0 );

}//	UpdateRects
//------------------------------------------------------------------
int		CPUISlider::GetValFromPos( int nPosX )
{
	float fValPerPixel	=	(float)( m_nMax - m_nMin ) / RectWidth( m_rcBoundBox );
	return (int) ( 0.5f + m_nMin + fValPerPixel * ( nPosX - m_rcBoundBox.left) );
}//	GetValFromPos
//------------------------------------------------------------------
bool	CPUISlider::HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_HOME:
				SetValueInternal(	m_nMin, true );
				return true;

			case VK_END:
				SetValueInternal(	m_nMax, true );
				return true;

			case VK_LEFT:
			case VK_DOWN:
				SetValueInternal(	m_nVal - 1, true );
				return true;

			case VK_RIGHT:
			case VK_UP:
				SetValueInternal(	m_nVal + 1, true );
				return true;

			case VK_NEXT:
				SetValueInternal(	m_nVal - ( 10 > ( m_nMax - m_nMin ) / 10
									? 10 : ( m_nMax - m_nMin ) / 10 ),
									true );
				return true;

			case VK_PRIOR:
				SetValueInternal(	m_nVal + ( 10 > ( m_nMax - m_nMin ) / 10
									? 10 : ( m_nMax - m_nMin ) / 10 ),
									true );
				return true;
			}//	switch( wParam )
			break;
		}//	case WM_KEYDOWN:
	}//	switch( uMsg )

	return false;
}//	HandleKeyboard
//------------------------------------------------------------------
bool	CPUISlider::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;
	
	switch( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			//	button rect
			if( PtInRect( &m_rcButton, pt ) )
			{				
				m_bPressed	=	true;
				SetCapture( hWnd );

				m_nDragX		=	pt.x;
				m_nDragOffset	=	m_nButtonX - m_nDragX;

				if( !m_bFocus )
					m_pDlg->RequestFocus( this );

				return true;
			}//	if( PtInRect( &m_rcButton, pt ) )

			//	bound rect
			if( PtInRect( &m_rcBoundBox, pt ) )
			{
				PUTOutputDebugStr(PUT_CSTR_TCHAR("WM_LBUTTONDOWN\n"));
				m_nDragX		=	pt.x;
				m_nDragOffset	=	0;
				m_bPressed		=	true;

				if( !m_bFocus )
					m_pDlg->RequestFocus( this );

				if( pt.x > m_nButtonX + m_nPosX )
				{
//					SetValueInternal( m_nVal + 1, true );
					SetValueInternal( pt.x - m_nPosX, true );
					return true;
				}

				if( pt.x < m_nButtonX + m_nPosX )
				{
//					SetValueInternal( m_nVal - 1, true );
					SetValueInternal( pt.x - m_nPosX, true );
					return true;
				}
			}//	if( PtInRect( &m_rcBoundBox, pt ) )
		}//	case WM_LBUTTONDOWN: / 	case WM_LBUTTONDBLCLK:
		break;

	case WM_LBUTTONUP:
		{
			if( m_bPressed )
			{
				m_bPressed = false;
				ReleaseCapture();
				m_pDlg->SendEvent( eCTRLEVENT_SLIDER_VALUE_CHANGED, true, this );
				return true;
			}
		}//	case WM_LBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		{
			if( m_bPressed )
			{
				SetValueInternal( GetValFromPos( m_nPosX + pt.x + m_nDragOffset ), true );
				return true;
			}
		}//	case WM_MOUSEMOVE:
		break;

	case WM_MOUSEWHEEL:
		{
			int nScrollStep	=	int( (short)HIWORD( wParam ) )/ WHEEL_DELTA;
			SetValueInternal( m_nVal - nScrollStep, true );
			return true;
		}//	case WM_MOUSEWHEEL:
		break;
	}//	switch( uMsg )

	return false;
}//	HandleMouse
//------------------------------------------------------------------
void	CPUISlider::SetRange( int nMin, int nMax )
{
	m_nMin	=	nMin;
	m_nMax	=	nMax;

	SetValueInternal( m_nVal, false );
}//	SetRange
//------------------------------------------------------------------
void	CPUISlider::SetValueInternal( int nVal, bool bFromInput )
{
	nVal	=	__max( m_nMin, nVal );
	nVal	=	__min( m_nMax, nVal );

	if( nVal == m_nVal )
		return;

	m_nVal	=	nVal;
	UpdateRects();

	m_pDlg->SendEvent( eCTRLEVENT_SLIDER_VALUE_CHANGED, bFromInput, this );
}//	SetValueInternal
//------------------------------------------------------------------
HRESULT	CPUISlider::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	eCTRLSTATE_	eState	=	eCTRLSTATE_NORMAL;

	CPUIElement*	pBttnEle	=	GetCustomSkinElement( eSKINTYPE_SLIDER_BTN_ACTIVE );
	if( !m_bVisible )
	{
		eState		=	eCTRLSTATE_HIDDEN;
		pBttnEle	=	GetCustomSkinElement( eSKINTYPE_SLIDER_BTN_ACTIVE );
	}else
	if( !m_bEnable )
	{
		eState		=	eCTRLSTATE_DISABLED;
		pBttnEle	=	GetCustomSkinElement( eSKINTYPE_SLIDER_BTN_UNACTIVE );
	}else
	if( m_bPressed )
	{
		eState		=	eCTRLSTATE_PRESSED;
		pBttnEle	=	GetCustomSkinElement( eSKINTYPE_BUTTON_CLICKED );
	}else
	if( m_bMouseInRect )
	{
		eState		=	eCTRLSTATE_MOUSEOVER;
		pBttnEle	=	GetCustomSkinElement( eSKINTYPE_SLIDER_BTN_MOUSEOVER );
	}
	else
	if( m_bFocus )
	{
		eState		=	eCTRLSTATE_FOCUS;
		pBttnEle	=	GetCustomSkinElement( eSKINTYPE_SLIDER_BTN_ACTIVE );
	}

	CPUIElement*	pTrackEle	=	GetCustomSkinElement( eSKINTYPE_SLIDER_TRACK );
	pTrackEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	m_pDlg->DrawSkinSprite( pTrackEle, &m_rcBoundBox );

	pBttnEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	m_pDlg->DrawSkinSprite( pBttnEle, &m_rcButton );

	return S_OK;
}//	Render
//------------------------------------------------------------------
//	EOF