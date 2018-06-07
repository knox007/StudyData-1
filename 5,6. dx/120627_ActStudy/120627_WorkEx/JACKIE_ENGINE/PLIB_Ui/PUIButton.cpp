#include "StdAfx.h"
#include "PUIButton.h"
#include "PUICtrlMisc.h"
#include "PUIDlg.h"
//-------------------------------------------------------------------------
void	CPUIButton::InitMembers()
{
	m_eCtrlType	=	eCTRLTYPE_BUTTON;

	m_bPressed	=	false;
	m_unHotkey	=	0;
}//	InitMembers
//-------------------------------------------------------------------------
bool	CPUIButton::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			switch ( wParam )
			{
			case VK_SPACE:
				m_bPressed = true;
				return true;
			}
		}
		return true;

	case WM_KEYUP:
		{
			switch( wParam )
			{
			case VK_SPACE:
				if( m_bPressed )
				{
					m_bPressed = false;
					m_pDlg->SendEvent( eCTRLEVENT_BUTTON_CLICKED, true, this );
				}
				return true;
			}
		}
		return true;
	}
	return false;
}//	HandleKeyboard
//-------------------------------------------------------------------------
bool	CPUIButton::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
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

				if( !m_pDlg->IsKeyboardInputEnable() )
					m_pDlg->ClearFocus();

				if( ContainsPoint( pt ) )
					m_pDlg->SendEvent( eCTRLEVENT_BUTTON_CLICKED, true, this );

				return true;
			}
		}
		break;
	}
	return false;
}//	HandleMouse
//-------------------------------------------------------------------------
HRESULT	CPUIButton::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	eCTRLSTATE_	eState = eCTRLSTATE_NORMAL;

	CPUIElement* pEle = NULL;

	//	활성화 버튼
	pEle	=	GetCustomSkinElement( eSKINTYPE_BUTTON_ACTIVE );

	if( !m_bVisible )
		eState	=	eCTRLSTATE_HIDDEN;
	else
	if( !m_bEnable )
	{
		eState	=	eCTRLSTATE_DISABLED;
		pEle	=	GetCustomSkinElement( eSKINTYPE_BUTTON_UNACTIVE );
	}
	else
	if( m_bPressed )
	{
		eState	=	eCTRLSTATE_PRESSED;
		pEle	=	GetCustomSkinElement( eSKINTYPE_BUTTON_CLICKED );
	}
	else
	if( m_bMouseInRect )
	{
		eState	=	eCTRLSTATE_MOUSEOVER;
		pEle	=	GetCustomSkinElement( eSKINTYPE_BUTTON_MOUSEOVER );
	}
	else
	if( m_bFocus )
	{
		eState	=	eCTRLSTATE_FOCUS;
		pEle	=	GetCustomSkinElement( eSKINTYPE_BUTTON_ACTIVE );
	}

	if( pEle )
	{
		RECT	rcWindow	=	m_rcBoundBox;
		pEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
		pEle->GetFontColor().Blend( eState, fElapsedTime, 0.0f );
		m_pDlg->DrawSkinSprite( pEle, &rcWindow );
		m_pDlg->DrawSkinText( GetText(), pEle, &rcWindow );
	}

	return S_OK;
}//	Render
//-------------------------------------------------------------------------
//	EOF