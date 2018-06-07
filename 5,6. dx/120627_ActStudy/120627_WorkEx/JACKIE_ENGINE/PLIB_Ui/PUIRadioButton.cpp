#include "StdAfx.h"
#include "PUIRadioButton.h"
//----------------------------------------------------------------------------------
void	CPUIRadioButton::InitMembers()
{
	m_eCtrlType	=	eCTRLTYPE_RADIOBUTTON;
}//	InitMembers
//----------------------------------------------------------------------------------
bool	CPUIRadioButton::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
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
				if( m_bPressed )
				{
					m_bPressed = false;

					m_pDlg->ClearRadioButtonGroup( m_unBttnGroupIDx );
					m_bChecked = !m_bChecked;

					m_pDlg->SendEvent( eCTRLEVENT_RADIOBUTTON_CHANGED, true, this );
				}
				return true;
			}
		}
		break;
	}
	return false;
}//	HandleKeyboard
//----------------------------------------------------------------------------------
bool	CPUIRadioButton::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	switch( uMsg )
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
				{
					m_pDlg->ClearRadioButtonGroup( m_unBttnGroupIDx );
					m_bChecked = !m_bChecked;

					m_pDlg->SendEvent( eCTRLEVENT_RADIOBUTTON_CHANGED, true, this );
				}

				return true;
			}
		}
		break;
	}

	return false;
}//	HandleMouse
//----------------------------------------------------------------------------------
void	CPUIRadioButton::SetCheckedInternal( bool bChecked, bool bClearGroup, bool bFromInput )
{
	if( bChecked && bClearGroup )
		m_pDlg->ClearRadioButtonGroup( m_unBttnGroupIDx );

	m_bChecked = bChecked;
	m_pDlg->SendEvent( eCTRLEVENT_RADIOBUTTON_CHANGED, bFromInput, this );
}//	SetCheckedInternal
//----------------------------------------------------------------------------------
//	EOF