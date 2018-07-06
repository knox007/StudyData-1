#include "StdAfx.h"
#include "PUICheckBox.h"
#include "PUICtrlMisc.h"
#include "PUTCommon.h"

//--------------------------------------------------------------------------------
void	CPUICheckBox::InitMembers()
{
	m_eCtrlType = eCTRLTYPE_CHECKBOX;

	m_bChecked	=	false;
}//	InitMembers
//--------------------------------------------------------------------------------
bool	CPUICheckBox::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_SPACE:
				m_bPressed = true;
				return true;
			}
		}
		break;

	case WM_KEYUP:
		{
			switch( wParam )
			{
			case VK_SPACE:
				{
					if( m_bPressed )
					{
						m_bPressed = false;
						SetCheckedInternal( !m_bChecked, true );
					}
				}
				return true;
			}
		}
		break;
	}
	return false;
}//	HandleKeyboard
//--------------------------------------------------------------------------------
bool	CPUICheckBox::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch ( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if( ContainsPoint( pt ) )
			{
				m_bPressed = true;
				SetCapture( hWnd );

				if( !m_bFocus )
					m_pDlg->RequestFocus( this );

				return true;
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			if( m_bPressed )
			{
				m_bPressed = false;
				ReleaseCapture();

				if( ContainsPoint( pt ) )
					SetCheckedInternal( !m_bChecked, true );

				return true;
			}
		}
		break;

	}
	return false;
}//	HandleMouse
//--------------------------------------------------------------------------------
void	CPUICheckBox::SetCheckedInternal( bool bChecked, bool bFromInput )
{
	m_bChecked = bChecked;
	m_pDlg->SendEvent( eCTRLEVENT_CHECKBOX_CHANGED, bFromInput, this );
}//	SetCheckedInternal
//--------------------------------------------------------------------------------
BOOL	CPUICheckBox::ContainsPoint( POINT pt )
{
	return (	PtInRect( &m_rcBoundBox, pt ) ||
				PtInRect( &m_rcButton, pt ) );
}//	ContainsPoint
//--------------------------------------------------------------------------------
void	CPUICheckBox::UpdateRects()
{
	CPUIButton::UpdateRects();

	m_rcButton			=	m_rcBoundBox;
	m_rcButton.right	=	m_rcButton.left + RectHeight( m_rcButton );

	m_rcText			=	m_rcBoundBox;
	m_rcText.left	+=	(int)( 1.25f * RectWidth( m_rcButton ) );
}//	UpdateRects
//--------------------------------------------------------------------------------
HRESULT	CPUICheckBox::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	eCTRLSTATE_	eState	=	eCTRLSTATE_NORMAL;

	CPUIElement*	pEle	=	NULL;

	if( m_bChecked )
	{
		pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_CHCK_ACTIVE );

		if( m_bMouseInRect )
			pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_CHCK_MOUSEOVER );
		else
		if( m_bPressed )
			pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_CHCK_CLICKED );
		else
		if( !m_bEnable )
			pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_CHCK_UNACTIVE );
	}else
	{
		pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_UNCHCK_ACTIVE );

		if( m_bMouseInRect )
			pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_UNCHCK_MOUSEOVER );
		else
		if( m_bPressed )
			pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_UNCHCK_CLICKED );
		else
		if( !m_bEnable )
			pEle = GetCustomSkinElement( eSKINTYPE_CHECKBOX_UNCHCK_UNACTIVE );
	}

	if( !m_bVisible )
		eState	=	eCTRLSTATE_HIDDEN;
	else
	if( !m_bEnable )
		eState	=	eCTRLSTATE_DISABLED;
	else
	if( m_bPressed )
		eState	=	eCTRLSTATE_PRESSED;
	else
	if( m_bMouseInRect )
		eState	=	eCTRLSTATE_MOUSEOVER;
	else
	if( m_bFocus )
		eState	=	eCTRLSTATE_FOCUS;

	pEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pEle->GetFontColor().Blend( eState, fElapsedTime, 0.0f );
	m_pDlg->DrawSkinSprite( pEle, &m_rcButton );
	m_pDlg->DrawSkinText( GetText(), pEle, &m_rcText, true );

	return S_OK;
}//	Render
//--------------------------------------------------------------------------------
//	EOF