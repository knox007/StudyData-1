#include "StdAfx.h"
#include "PUIComboBox.h"
#include "PUTcommon.h"
#include "PUICtrlMisc.h"
#include "PUIDlgResourceMgr.h"
#include <strsafe.h>
//----------------------------------------------------------------------------------

//!	콤보박스 클릭시 드롭다운될 아이템의 영역 설정.
const	int DEFAULT_DROPHEIGHT		=	100;

//!	스크롤바 너비.
const	int COMBOBOX_SCROLLBAR_WIDTH_DEFAULT = 20;

//!	아이템들이 출력될 영역. 
//	수치가 커질수록 가운데로 몰리며, 
//	아이템의 갯수도 줄어든다.
const	int COMBOBOX_BORDER_DEFAULT	=	4;

//!	콤보박스 커서의 높이값
const	int	COMBOBOX_CURSOR_OFFSET	=	2;
//----------------------------------------------------------------------------------
void	CPUIComboBoxItem::InitMembers()
{
	PUT_ZERO_MEMORY(m_tszText);
	m_pData = NULL;

	PUT_ZERO_MEMORY(m_rcActive);
	m_bVisible = false;

}//	InitMembers
//----------------------------------------------------------------------------------






//----------------------------------------------------------------------------------
void	CPUIComboBox::InitMembers()
{
	m_eCtrlType		=	eCTRLTYPE_COMBOBOX;
	m_nDropHeight	=	DEFAULT_DROPHEIGHT;
	m_bOpened		=	false;
	m_nSelectedID	=	-1;
	m_nFocusedID	=	-1;
	m_pScrollBar	=	NULL;

	m_nScrollBarWidth	=	COMBOBOX_SCROLLBAR_WIDTH_DEFAULT;

}//	InitMembers
//----------------------------------------------------------------------------------
void	CPUIComboBox::ClearMembers()
{
	RemoveAllItems();
	PUT_SAFE_DELETE( m_pScrollBar );

}//	ClearMembers
//----------------------------------------------------------------------------------
void	CPUIComboBox::SetTextColor( D3DCOLOR col )
{
	CPUIElement* pEle = m_Elements.Find(0);

	if( pEle )
		pEle->GetFontColor().SetStateColor( eCTRLSTATE_NORMAL, col );

	pEle = m_Elements.Find(2);
	if( pEle )
		pEle->GetFontColor().SetStateColor( eCTRLSTATE_NORMAL, col );

}//	SetTextColor
//----------------------------------------------------------------------------------
void	CPUIComboBox::UpdateRects()
{
	CPUIButton::UpdateRects();

	m_rcButton			=	m_rcBoundBox;
	m_rcButton.left		=	m_rcButton.right - RectHeight( m_rcButton );

	m_rcText			=	m_rcBoundBox;
	m_rcText.right		=	m_rcButton.left;

	m_rcDropDown		=	m_rcText;
	OffsetRect( &m_rcDropDown, 0, (int)(0.9f * RectHeight( m_rcText ) ) );
	m_rcDropDown.bottom	+=	m_nDropHeight;
//	m_rcDropDown.right	-=	m_nScrollBarWidth;

	m_rcDropDownText	=	m_rcDropDown;
	
	/*
	m_rcDropDownText.left += (int) (0.1f * RectWidth( m_rcDropDown ));
	m_rcDropDownText.right -= (int) (0.1f * RectWidth( m_rcDropDown ));
	m_rcDropDownText.top += (int) (0.1f * RectHeight( m_rcDropDown ));
	m_rcDropDownText.bottom -= (int) (0.1f * RectHeight( m_rcDropDown ));
	*/

	m_rcDropDownText.left	+=	COMBOBOX_BORDER_DEFAULT;
	m_rcDropDownText.right	-=	COMBOBOX_BORDER_DEFAULT;
	m_rcDropDownText.top	+=	COMBOBOX_BORDER_DEFAULT;
	m_rcDropDownText.bottom	-=	COMBOBOX_BORDER_DEFAULT;

	if( !m_pScrollBar )
		return;
	m_pScrollBar->SetPos( m_rcDropDown.right, m_rcDropDown.top + COMBOBOX_CURSOR_OFFSET );
	m_pScrollBar->SetSize( m_nScrollBarWidth, RectHeight( m_rcDropDown ) - COMBOBOX_CURSOR_OFFSET );
//	CPUIFontNode*	pFontNode	=	m_pDlg->GetResMgr()->GetFontNode( m_Elements[2].GetFontID() );
	CPUIFontNode*	pFontNode	=	m_pDlg->GetResMgr()->GetFontNode( m_Elements.Find(0)->GetFontID() );
	if( pFontNode && pFontNode->m_unHeight )
	{
		m_pScrollBar->SetPageSize( RectHeight( m_rcDropDownText ) / pFontNode->m_unHeight );
		m_pScrollBar->ShowItem( m_nSelectedID );
	}

}//	UpdateRects
//----------------------------------------------------------------------------------
void	CPUIComboBox::OnFocusOut( HWND hWnd )
{
	CPUIButton::OnFocusOut( hWnd );
	m_bOpened	=	false;

}//	OnFocusOut
//----------------------------------------------------------------------------------
bool	CPUIComboBox::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	const DWORD	dwRepeat_mask =	(0x40000000);

	if( !IsActive() )
		return false;

	if( m_pScrollBar->HandleKeyboard( hWnd, uMsg, wParam, lParam ) )
		return true;

	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			switch ( wParam )
			{
			// case VK_RETURN: -----------------------------------------------
			case VK_RETURN:
				if( m_bOpened )
				{
					if( m_nSelectedID != m_nFocusedID )
					{
						m_nSelectedID = m_nFocusedID;
						m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
					}
					m_bOpened = false;

					if( !m_pDlg->IsKeyboardInputEnable() )
						m_pDlg->ClearFocus();

					return true;
				}
				break;
			// ------------------------------------------ case VK_RETURN: ---

			// case VK_F4: --------------------------------------------------
			case VK_F4:
				{
					if( lParam & dwRepeat_mask )
						return true;

					m_bOpened = !m_bOpened;

					if( !m_bOpened )
					{
						m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );

						if( !m_pDlg->IsKeyboardInputEnable() )
							m_pDlg->ClearFocus();
					}
					return true;
				}
				break;
			// ----------------------------------------------- case VK_F4: ---

			// case VK_LEFT: case VK_UP: -------------------------------------
			case VK_LEFT:
			case VK_UP:
				{
					if( m_nFocusedID > 0 )
					{
						--m_nFocusedID;
						m_nSelectedID = m_nFocusedID;

						if( !m_bOpened )
							m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
					}
					return true;
				}
				break;
			// --------------------------------- case VK_LEFT: case VK_UP: ---

			// case VK_RIGHT: case VK_DOWN: ----------------------------------
			case VK_RIGHT:
			case VK_DOWN:
				{
					if( m_nFocusedID + 1 < (int)GetNumItems() )
					{
						++m_nFocusedID;
						m_nSelectedID = m_nFocusedID;

						if( !m_bOpened )
							m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
					}
					return true;
				}
				break;
			// ------------------------------ case VK_RIGHT: case VK_DOWN: ---				
			}
		}
		break;
	}
	return false;
}//	HandleKeyboard
//----------------------------------------------------------------------------------
bool	CPUIComboBox::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	if( m_pScrollBar->HandleMouse( hWnd, uMsg, pt, wParam, lParam ) )
		return true;

	switch( uMsg )
	{
	// case WM_MOUSEMOVE: ------------------------------------------------
	case WM_MOUSEMOVE:
		{
			if( m_bOpened && PtInRect( &m_rcDropDown, pt ) )
			{
				for( size_t nCur = 0; nCur < m_Items.GetSize(); ++nCur )
				{
					CPUIComboBoxItem* pItem = m_Items.Find(nCur);

					if( pItem->m_bVisible &&
						PtInRect( &pItem->m_rcActive, pt ) )
					{
						m_nFocusedID = nCur;
					}
				}

				return true;
			}
		}
		break;
	// -------------------------------------------- case WM_MOUSEMOVE: ---


	// case WM_LBUTTONDOWN:	case WM_LBUTTONDBLCLK: -----------------------
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if( ContainsPoint( pt ) )
			{
				m_bPressed = true;
				SetCapture( hWnd );

				if( !m_bFocus )
					m_pDlg->RequestFocus( this );

				if( m_bFocus )
				{
					m_bOpened = !m_bOpened;

					if( !m_bOpened )
					{
						if( !m_pDlg->IsKeyboardInputEnable() )
							m_pDlg->ClearFocus();
					}
				}
				return true;
			}//	if( ContainsPoint( pt ) )


			if( m_bOpened && PtInRect( &m_rcDropDown, pt ) )
			{
				for( size_t nCur = m_pScrollBar->GetTrackPos(); nCur < m_Items.GetSize(); ++nCur )
				{
					CPUIComboBoxItem* pItem = m_Items.Find(nCur);
					if( pItem->m_bVisible &&
						PtInRect( &pItem->m_rcActive, pt ) )
					{
						m_nFocusedID = m_nSelectedID = nCur;
						m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
						m_bOpened = false;

						if( !m_pDlg->IsKeyboardInputEnable() )
							m_pDlg->ClearFocus();

						break;
					}
				}
				return true;
			}//	if( m_bOpened && PtInRect( &m_rcDropDown, pt ) )


			if( m_bOpened )
			{
				m_nFocusedID = m_nSelectedID;
				m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
				m_bOpened = false;
			}

			m_bPressed = false;

			if( !m_pDlg->IsKeyboardInputEnable() )
				m_pDlg->ClearFocus();
		}
		break;
	// ------------------- case WM_LBUTTONDOWN:	case WM_LBUTTONDBLCLK: ---


	// case WM_LBUTTONUP: ------------------------------------------------
	case WM_LBUTTONUP:
		{
			if( m_bPressed && ContainsPoint( pt ) )
			{
				m_bPressed = false;
				ReleaseCapture();
				return true;
			}
		}
		break;
	// -------------------------------------------- case WM_LBUTTONUP: ---


	// case WM_MOUSEWHEEL: -----------------------------------------------
	case WM_MOUSEWHEEL:
		{
			int nDelta = (short)HIWORD( wParam ) / WHEEL_DELTA;
			if( m_bOpened )
			{
				UINT	unLines;
				SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &unLines, 0 );
				int nScrollAmount	=	int((short)HIWORD(wParam)) / WHEEL_DELTA * unLines;
				m_pScrollBar->Scroll( -nScrollAmount );
				m_pScrollBar->SetTextColor( -nDelta * unLines );
			}else
			{
				if( nDelta > 0 )
				{
					if( m_nFocusedID > 0 )
					{
						--m_nFocusedID;
						m_nSelectedID = m_nFocusedID;

						if( !m_bOpened )
							m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
					}
				}else
				{
					if( m_nFocusedID + 1 < (int)GetNumItems() )
					{
						++m_nFocusedID;
						m_nSelectedID = m_nFocusedID;

						if( !m_bOpened )
							m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
					}
				}
			}
			return true;
		}
		break;
	// ------------------------------------------- case WM_MOUSEWHEEL: ---
	}

	return false;
}//	HandleMouse
//----------------------------------------------------------------------------------
void	CPUIComboBox::OnHotKey()
{
	if( m_bOpened )
		return;

	if( m_nSelectedID == -1 )
		return;

	if( m_pDlg->IsKeyboardInputEnable() )
		m_pDlg->RequestFocus( this );

	++m_nSelectedID;

	if( m_nSelectedID >= (int)m_Items.GetSize() )
		m_nSelectedID = 0;

	m_nFocusedID = m_nSelectedID;
	m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, true, this );
}//	OnHotKey
//----------------------------------------------------------------------------------
HRESULT	CPUIComboBox::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	eCTRLSTATE_	eState	=	eCTRLSTATE_NORMAL;

	if( !m_bOpened )
		eState	=	eCTRLSTATE_HIDDEN;

	//	Dropdown box
	CPUIElement*	pDropDownEle	=	GetCustomSkinElement( eSKINTYPE_COMBOBOX_DROPDOWNBOX );

	//	Scroll bar
	static bool bScrollBarInit = false;
	if( !bScrollBarInit )
	{
		if( m_pDlg->GetFontFromManager( pDropDownEle->GetFontID() )->m_unHeight )
			m_pScrollBar->SetPageSize(	RectHeight( m_rcDropDownText ) / 
										m_pDlg->GetFontFromManager( pDropDownEle->GetFontID() )->m_unHeight );
		else
			m_pScrollBar->SetPageSize(	RectHeight( m_rcDropDownText ) );

		bScrollBarInit	=	true;
	}

	if( m_bOpened )
		m_pScrollBar->OnRender( pDev, fElapsedTime );

	//	Blend current color
	pDropDownEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pDropDownEle->GetFontColor().Blend( eState, fElapsedTime, 0.0f );

	if( m_bOpened )
		m_pDlg->DrawSkinSprite( pDropDownEle, &m_rcDropDown );

	//	Selection Outline
	CPUIElement*	pSelectionEle = GetCustomSkinElement( eSKINTYPE_COMBOBOX_SELECTION );
	pSelectionEle->GetTexColor().SetCurrentColor( pDropDownEle->GetTexColor().GetCurrentColor() );
	pSelectionEle->GetFontColor().SetCurrentColor( pDropDownEle->GetFontColor().GetStateColor( eCTRLSTATE_NORMAL ) );

	CPUIFontNode*	pFontNode	=	m_pDlg->GetFontFromManager( pDropDownEle->GetFontID() );
	if( pFontNode )
	{
		int nCurY			=	m_rcDropDownText.top;
		int nRemainHeight	=	RectHeight( m_rcDropDownText );

		for( size_t nCur = m_pScrollBar->GetTrackPos(); nCur < m_Items.GetSize(); ++nCur )
		{
			CPUIComboBoxItem* pItem	=	m_Items.Find(nCur);

			nRemainHeight	-=	pFontNode->m_unHeight;
			if( nRemainHeight < 0 )
			{
				pItem->m_bVisible = false;
				continue;
			}

			SetRect(	&pItem->m_rcActive, 
						m_rcDropDownText.left,	nCurY, 
						m_rcDropDownText.right,	nCurY + pFontNode->m_unHeight 
					);
			nCurY	+=	pFontNode->m_unHeight;

			pItem->m_bVisible = true;

			if( m_bOpened )
			{
				if( (int)nCur == m_nFocusedID )
				{
					RECT	rc;
					SetRect(	&rc, 
								m_rcDropDown.left,
								pItem->m_rcActive.top - COMBOBOX_CURSOR_OFFSET,
								m_rcDropDown.right,
								pItem->m_rcActive.bottom + COMBOBOX_CURSOR_OFFSET );
					m_pDlg->DrawSkinSprite( pSelectionEle, &rc );
					m_pDlg->DrawSkinText( pItem->m_tszText, pSelectionEle, &pItem->m_rcActive );
				}
				else
				{
					m_pDlg->DrawSkinText( pItem->m_tszText, pDropDownEle, &pItem->m_rcActive );
				}
			}
		}
	}

	CPUIElement*	pBttnEle	=	GetCustomSkinElement( eSKINTYPE_COMBOBOX_ACTIVEBTN );
	eState	=	eCTRLSTATE_NORMAL;

	if( !m_bVisible )
		eState	=	eCTRLSTATE_HIDDEN;
	else
	if( !m_bEnable )
		eState	=	eCTRLSTATE_DISABLED;
	else
	if( m_bPressed )
	{
		eState	=	eCTRLSTATE_MOUSEOVER;
		pBttnEle	=	GetCustomSkinElement( eSKINTYPE_COMBOBOX_MOUSEOVERBTN );
	}
	else
	if( m_bFocus )
		eState	=	eCTRLSTATE_FOCUS;

	

	//	Draw ComboBox Button	
	pBttnEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	RECT	rcWindow	=	m_rcButton;
	m_pDlg->DrawSkinSprite( pBttnEle, &rcWindow );

	
	//	Main TextBox
	if( m_bOpened )
		eState	=	eCTRLSTATE_PRESSED;
	CPUIElement*	pTextBoxEle	=	GetCustomSkinElement( eSKINTYPE_COMBOBOX_EDITBOX );
	pTextBoxEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pTextBoxEle->GetFontColor().Blend( eState, fElapsedTime, 0.0f );
	m_pDlg->DrawSkinSprite( pTextBoxEle, &m_rcText );

	if( 0 <= m_nSelectedID && m_nSelectedID < (int)m_Items.GetSize() )
	{
		CPUIComboBoxItem*	pItem = m_Items.Find(m_nSelectedID);
		if( pItem )
			m_pDlg->DrawSkinText( pItem->m_tszText, pTextBoxEle, &m_rcText );
	}

	return S_OK;
}//	Render
//----------------------------------------------------------------------------------
HRESULT	CPUIComboBox::AddItem( const WCHAR* ptszText, void* pData )
{
	if( !ptszText )
		return E_INVALIDARG;

	CPUIComboBoxItem*	pItem	=	NULL;
	PUTNEW( pItem, CPUIComboBoxItem );
	if( !pItem )
		return E_FAIL;

	PUT_ZERO_MEMORY_PTR( pItem );
	StringCchCopyW( pItem->m_tszText, 256, ptszText );
	pItem->m_pData	=	pData;

	m_Items.Add( pItem );

	if( m_pScrollBar )
		m_pScrollBar->SetTrackRange( 0, (int)m_Items.GetSize() );

	if( GetNumItems() == 1 )
	{
		m_nSelectedID = 0;
		m_nFocusedID = 0;
		m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, false, this );
	}

	return S_OK;
}//	AddItem
//----------------------------------------------------------------------------------
void	CPUIComboBox::RemoveItem( UINT unID )
{
	m_Items.Delete( (int)unID );
	if( m_pScrollBar )
		m_pScrollBar->SetTrackRange( 0, m_Items.GetSize() );
	if( m_nSelectedID >= (int)m_Items.GetSize() )
		m_nSelectedID = m_Items.GetSize() - 1;
}//	RemoveItem
//----------------------------------------------------------------------------------
void	CPUIComboBox::RemoveAllItems()
{
	m_Items.DeleteAll();
	if( m_pScrollBar )
		m_pScrollBar->SetTrackRange( 0, 1 );
	m_nFocusedID	=	m_nSelectedID	=	-1;
}//	RemoveAllItems
//----------------------------------------------------------------------------------
int		CPUIComboBox::FindItem( const WCHAR* ptszText, UINT unStart /* = 0 */ )
{
	if( !ptszText )
		return -1;

	for( int nCur = 0; nCur < (int)m_Items.GetSize(); ++nCur )
	{
		CPUIComboBoxItem* pItem	=	m_Items.Find( nCur );

		if( wcscmp( pItem->m_tszText, ptszText ) == 0 )
		{
			return nCur;
		}
	}

	return -1;
}//	FindItem
//----------------------------------------------------------------------------------
bool	CPUIComboBox::ContainsItem( const WCHAR* ptszText, UINT unStart )
{
	return ( FindItem( ptszText, unStart ) != -1 );
}//	ContainsItem
//----------------------------------------------------------------------------------
void*	CPUIComboBox::GetSelectedData()
{
	if( m_nSelectedID < 0 )
		return NULL;

	CPUIComboBoxItem*	pItem	=	m_Items.Find( m_nSelectedID );
	return pItem->m_pData;
}//	GetSelectedData
//----------------------------------------------------------------------------------
CPUIComboBoxItem*	CPUIComboBox::GetSelectedItem()
{
	if( m_nSelectedID < 0 )
		return NULL;

	return m_Items.Find( m_nSelectedID );
}//	GetSelectedItem
//----------------------------------------------------------------------------------
void*	CPUIComboBox::GetItemData( const WCHAR* ptszText )
{
	int nIdx	=	FindItem( ptszText );
	if( nIdx == -1 )
		return NULL;

	CPUIComboBoxItem*	pItem	=	m_Items.Find( nIdx );
	if( !pItem )
		return NULL;

	return pItem->m_pData;
}//	GetItemData

//----------------------------------------------------------------------------------
void*	CPUIComboBox::GetItemData( int nIDx )
{
	if( nIDx < 0 || nIDx >= (int)m_Items.GetSize() )
		return NULL;

	return m_Items.Find( nIDx )->m_pData;
}//	GetItemData
//----------------------------------------------------------------------------------
HRESULT	CPUIComboBox::SetSelectedByIndex( UINT unID )
{
	if( unID >= GetNumItems() )
		return E_INVALIDARG;

	m_nFocusedID	=	m_nSelectedID	=	unID;
	m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, false, this );

	return S_OK;
}//	SetSelectedByIndex
//----------------------------------------------------------------------------------
HRESULT	CPUIComboBox::SetSelectedByText( const WCHAR* ptszText )
{
	if( ptszText != NULL )
		return E_INVALIDARG;

	int nIDx	=	FindItem( ptszText );
	if( nIDx == -1 )
		return E_FAIL;

	m_nFocusedID	=	m_nSelectedID	=	nIDx;
	m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, false, this );

	return S_OK;
}
//----------------------------------------------------------------------------------
HRESULT	CPUIComboBox::SetSelectedByData( void* pData )
{
	for( int nCur = 0; nCur < (int)m_Items.GetSize(); ++nCur )
	{
		CPUIComboBoxItem* pItem	=	m_Items.Find( nCur );
		if( pItem->m_pData == pData )
		{
			m_nFocusedID	=	m_nSelectedID	=	nCur;
			m_pDlg->SendEvent( eCTRLEVENT_COMBOBOX_SELECTION_CHANGED, false, this );
			return S_OK;
		}
	}

	return E_FAIL;
}//	SetSelectedByText
//----------------------------------------------------------------------------------
//	EOF