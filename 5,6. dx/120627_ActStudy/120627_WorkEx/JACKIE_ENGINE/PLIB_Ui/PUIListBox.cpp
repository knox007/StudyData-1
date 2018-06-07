#include "StdAfx.h"
#include "PUIListBox.h"
#include "PUTCommon.h"
#include "PUICtrlMisc.h"
#include "PUIDlgResourceMgr.h"
#include <strsafe.h>

//!	스크롤바 너비.
const	int LISTBOX_SCROLLBAR_WIDTH_DEFAULT = 16;
//!	아이템들이 출력될 영역. 
//	수치가 커질수록 가운데로 몰리며, 
//	아이템의 갯수도 줄어든다.
const	int	LISTBOX_BORDER_DEFAULT			=	10;	
//!	Left와의 여백
const	int LISTBOX_MARGIN_DEFAULT			=	5;	
//----------------------------------------------------------------------------------
void	CPUIListBox::InitMembers()
{
	m_eCtrlType	=	eCTRLTYPE_LISTBOX;

	m_eListBoxType		=	eLISTBOXTYPE_INVALID;
	m_nScrollBarWidth	=	LISTBOX_SCROLLBAR_WIDTH_DEFAULT;
	m_nSelectedIDx		=	-1;
	m_nSelectedStartIDx	=	0;
	m_bDrag				=	false;
	m_nBorder			=	LISTBOX_BORDER_DEFAULT;
	m_nMargin			=	-LISTBOX_MARGIN_DEFAULT;
	m_nTextHeight		=	0;
	m_pScrollBar		=	NULL;
}//	InitMembers
//----------------------------------------------------------------------------------
void	CPUIListBox::ClearMembers()
{
	RemoveAllItems();
	PUT_SAFE_DELETE( m_pScrollBar );
}//	ClearMembers
//----------------------------------------------------------------------------------
void	CPUIListBox::UpdateRects()
{
	CPUICtrl::UpdateRects();

	m_rcSelection		=	m_rcBoundBox;
	m_rcSelection.right	-=	m_nScrollBarWidth;
	InflateRect( &m_rcSelection, -m_nBorder, -m_nBorder );
	m_rcText			=	m_rcSelection;
	InflateRect( &m_rcText, m_nMargin, 0 );

	//	Update Scrollbar Rect
	if( m_pScrollBar )
	{
		m_pScrollBar->SetPos( m_rcBoundBox.right - m_nScrollBarWidth, m_rcBoundBox.top );
		m_pScrollBar->SetSize( m_nScrollBarWidth, m_nHeight );

		CPUIFontNode*	pFontNode	=	m_pDlg->GetResMgr()->GetFontNode( m_Elements.Find(0)->GetFontID() );
		if( pFontNode && pFontNode->m_unHeight )
		{
			m_pScrollBar->SetPageSize( RectHeight( m_rcText ) / pFontNode->m_unHeight );

			m_pScrollBar->ShowItem( m_nSelectedIDx );
		}
	}

}//	UpdateRects
//----------------------------------------------------------------------------------
HRESULT	CPUIListBox::AddItem( const WCHAR* ptszText, void *pData )
{
	CPUIListBoxItem*	pNewItem	=	new	CPUIListBoxItem;
	if( !pNewItem )
		return E_OUTOFMEMORY;

	StringCchCopyW( pNewItem->m_tszText, 256, ptszText );
	pNewItem->m_pData		=	pData;
	SetRect( &pNewItem->m_rcActive, 0, 0, 0, 0 );
	pNewItem->m_bSelected	=	false;

	m_Items.Add( pNewItem );
	
	if( m_pScrollBar )
		m_pScrollBar->SetTrackRange( 0, m_Items.GetSize() );

	return S_OK;

}//	AddItem
//----------------------------------------------------------------------------------
HRESULT	CPUIListBox::InsertItem( int nID, const WCHAR* ptszText, void* pData )
{
	CPUIListBoxItem*	pNewItem	=	NULL;
	PUTNEW( pNewItem, CPUIListBoxItem );

	if( !pNewItem )
		return E_OUTOFMEMORY;

	StringCchCopyW( pNewItem->m_tszText, 256, ptszText );
	pNewItem->m_pData		=	pData;
	SetRect( &pNewItem->m_rcActive, 0, 0, 0, 0 );
	pNewItem->m_bSelected	=	false;

	m_Items.Insert( nID, pNewItem );

	m_pScrollBar->SetTrackRange( 0, m_Items.GetSize() );

	return S_OK;

}//	InsertItem
//----------------------------------------------------------------------------------
void	CPUIListBox::RemoveItem( int nID )
{
	if( nID < 0 || (int)m_Items.GetSize() <= nID )
		return;

	m_Items.Delete( nID );

	m_pScrollBar->SetTrackRange( 0, m_Items.GetSize() );
	if( m_nSelectedIDx >= (int)m_Items.GetSize() )
		m_nSelectedIDx = (int)m_Items.GetSize() - 1;

	m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );

}//	RemoveItem
//----------------------------------------------------------------------------------
void	CPUIListBox::RemoveItemByText( const WCHAR* ptszText )
{

}//	RemoveItemByText
//----------------------------------------------------------------------------------
void	CPUIListBox::RemoveItemByData( void *pData )
{

}//	RemoveItemByData
//----------------------------------------------------------------------------------
void	CPUIListBox::RemoveAllItems()
{
	m_Items.DeleteAll();

	m_pScrollBar->SetTrackRange( 0, 1 );
}//	RemoveAllItems
//----------------------------------------------------------------------------------
CPUIListBoxItem*	CPUIListBox::GetItem( int nID )
{
	if( nID < 0 || nID >= (int)m_Items.GetSize() )
		return NULL;

	return m_Items.Find( nID );
}
//----------------------------------------------------------------------------------
int	CPUIListBox::GetSelectedIndex( int nPrevSelected /* = -1 */ )
{
	if( nPrevSelected < -1 )
		return -1;

	if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )
	{
		for( int nCur = nPrevSelected + 1; nCur < (int)m_Items.GetSize(); ++nCur )
		{
			CPUIListBoxItem*	pItem	=	m_Items.Find( nCur );

			if( pItem->m_bSelected )
				return nCur;
		}

		return -1;
	}else
	{
		return m_nSelectedIDx;
	}
}
//----------------------------------------------------------------------------------
void	CPUIListBox::SelectItem( int nID )
{
	if( m_Items.GetSize() == 0 )
		return;

	int nOldSelected	=	m_nSelectedIDx;
	m_nSelectedIDx		=	nID;

	if( m_nSelectedIDx < 0 )
		m_nSelectedIDx	=	0;
	if( m_nSelectedIDx >= (int)m_Items.GetSize() )
		m_nSelectedIDx	=	m_Items.GetSize() - 1;

	if( nOldSelected != m_nSelectedIDx )
	{
		if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )
		{
			m_Items.Find( m_nSelectedIDx )->m_bSelected	=	true;
		}

		m_nSelectedStartIDx	=	m_nSelectedIDx;

		m_pScrollBar->ShowItem( m_nSelectedIDx );
	}

	m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );
}
//----------------------------------------------------------------------------------
bool	CPUIListBox::HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	if( m_pScrollBar->HandleKeyboard( hWnd, uMsg, wParam, lParam ) )
		return true;

	switch ( uMsg )
	{
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_UP:
		case VK_DOWN:
		case VK_NEXT:
		case VK_PRIOR:
		case VK_HOME:
		case VK_END:
			{
				if( m_Items.GetSize() == 0 )
					return true;

				int nOldSelected	=	m_nSelectedIDx;

				switch( wParam )
				{
				case VK_UP:		--m_nSelectedIDx; break;
				case VK_DOWN:	++m_nSelectedIDx; break;
				case VK_NEXT:	m_nSelectedIDx += m_pScrollBar->GetPageSize() - 1; break;
				case VK_PRIOR:	m_nSelectedIDx -= m_pScrollBar->GetPageSize() - 1; break;
				case VK_HOME:	m_nSelectedIDx	= 0;	break;
				case VK_END:	m_nSelectedIDx	= m_Items.GetSize() - 1; break;
				}


				if( m_nSelectedIDx < 0 )
					m_nSelectedIDx = 0;
				if( m_nSelectedIDx >= (int)m_Items.GetSize() )
					m_nSelectedIDx = m_Items.GetSize() - 1;


				if( nOldSelected != m_nSelectedIDx )
				{
					if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )
					{
						for( int nCur = 0; nCur < (int)m_Items.GetSize(); ++nCur )
						{
							CPUIListBoxItem* pItem	=	m_Items.Find(nCur);
							pItem->m_bSelected = false;
						}

						if( GetKeyState( VK_SHIFT ) < 0 )
						{
							int nEnd = __max( m_nSelectedStartIDx, m_nSelectedIDx );

							for( int nCurIdx = __min( m_nSelectedStartIDx, m_nSelectedIDx ); nCurIdx < nEnd; ++nCurIdx )
								m_Items.Find(nCurIdx)->m_bSelected = true;
						}else
						{
							m_Items.Find(m_nSelectedIDx)->m_bSelected = true;
							m_nSelectedStartIDx		=	m_nSelectedIDx;
						}
					}//	if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )
				}//	if( nOldSelected != m_nSelectedIDx )
				else
					m_nSelectedStartIDx = m_nSelectedIDx;

				m_pScrollBar->ShowItem( m_nSelectedIDx );

				m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );
			}
			return true;


		case VK_SPACE:
			m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_ITEM_DBLCLK, true, this );
			return true;
		}//	case WM_KEYDOWN:
		break;
	}//	switch ( uMsg )

	return false;
}
//----------------------------------------------------------------------------------
bool CPUIListBox::HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !IsActive() )
		return false;

	if( WM_LBUTTONDOWN == uMsg )
		if( !IsFocus() )
			m_pDlg->RequestFocus( this );

	if( m_pScrollBar&& m_pScrollBar->HandleMouse( hWnd, uMsg, pt, wParam, lParam ) )
		return true;

	switch( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if( m_Items.GetSize() > 0 && PtInRect( &m_rcSelection, pt ) )
			{
				int nClicked = -1;
				if( m_nTextHeight )
					nClicked = m_pScrollBar->GetTrackPos() + ( pt.y - m_rcText.top ) / m_nTextHeight;

				if( nClicked >= m_pScrollBar->GetTrackPos() &&
					nClicked < (int)m_Items.GetSize() &&
					nClicked < m_pScrollBar->GetTrackPos() + m_pScrollBar->GetPageSize() )
				{
					SetCapture( hWnd );
					m_bDrag	=	true;

					if( uMsg == WM_LBUTTONDBLCLK )
					{
						m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_ITEM_DBLCLK, true, this );
						return true;
					}

					m_nSelectedIDx	=	nClicked;
					if( !( wParam & MK_SHIFT ) )
						m_nSelectedStartIDx	=	m_nSelectedIDx;

					if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )
					{
						CPUIListBoxItem*	pSelectedItem	=	m_Items.Find( m_nSelectedIDx );

						if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == MK_CONTROL )
						{
							pSelectedItem->m_bSelected	=	!pSelectedItem->m_bSelected;
						}else
							if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == MK_SHIFT )
							{
								int nBegin	=	__min( m_nSelectedStartIDx, m_nSelectedIDx );
								int nEnd	=	__max( m_nSelectedStartIDx, m_nSelectedIDx );

								int nCur = 0;
								for( nCur = 0; nCur < nBegin; ++nCur )
								{
									CPUIListBoxItem* pItem	=	m_Items.Find(nCur);
									pItem->m_bSelected	=	false;
								}

								for( nCur = nEnd + 1; nEnd < (int)m_Items.GetSize(); ++nCur )
								{
									CPUIListBoxItem* pItem	=	m_Items.Find(nCur);
									pItem->m_bSelected	=	false;
								}

								for( nCur = nBegin; nCur <= nEnd; ++nCur )
								{
									CPUIListBoxItem* pItem	=	m_Items.Find(nCur);
									pItem->m_bSelected	=	true;
								}
							}//	if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == MK_SHIFT )
							else
								if( ( wParam & ( MK_SHIFT | MK_CONTROL ) ) == ( MK_SHIFT | MK_CONTROL ) )
								{
									int nBegin	=	__min( m_nSelectedStartIDx, m_nSelectedIDx );
									int nEnd	=	__max( m_nSelectedStartIDx, m_nSelectedIDx );

									bool bLastSelected	=	m_Items.Find( m_nSelectedStartIDx )->m_bSelected;
									for( int nCur = nBegin + 1; nCur < nEnd; ++nCur )
									{
										CPUIListBoxItem* pItem	=	m_Items.Find(nCur);
										pItem->m_bSelected	=	bLastSelected;
									}

									pSelectedItem->m_bSelected	=	true;
									m_nSelectedIDx	=	m_nSelectedStartIDx;
								}else
								{
									for( int nCur = 0; nCur < (int)m_Items.GetSize(); ++nCur )
									{
										CPUIListBoxItem* pItem	=	m_Items.Find(nCur);
										pItem->m_bSelected	=	false;
									}

									pSelectedItem->m_bSelected	=	true;
								}
					}//	if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )

					m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );

				}//	if( nClicked >= m_pScrollBar->GetTrackPos() && nClicked < (int)m_Items.GetSize() && nClicked < m_pScrollBar->GetTrackPos() + m_pScrollBar->GetPageSize() )

				return true;
			}//	if( m_Items.GetSize() > 0 && PtInRect( &m_rcSelection, pt ) )
		}//	case WM_LBUTTONDOWN: / case WM_LBUTTONDBLCLK:
		break;


	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			m_bDrag	=	false;

			if( m_nSelectedIDx != -1 )
			{
				int nEnd	=	__max( m_nSelectedStartIDx, m_nSelectedIDx );

				for( int nCur = __min( m_nSelectedStartIDx, m_nSelectedIDx ) + 1; nCur < nEnd; ++nCur )
				{
					m_Items.Find(nCur)->m_bSelected	=	m_Items.Find(m_nSelectedStartIDx)->m_bSelected;
				}
				m_Items.Find( m_nSelectedIDx )->m_bSelected	=	m_Items.Find(m_nSelectedStartIDx)->m_bSelected;

				if( m_nSelectedStartIDx != m_nSelectedIDx )
					m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );

				m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION_END, true, this );
			}//	if( m_nSelectedIDx != -1 )
			return false;

		}//	case WM_LBUTTONUP:
		break;


	case WM_MOUSEMOVE:
		{
			if( m_bDrag )
			{
				int nItem = -1;
				if( m_nTextHeight )
					nItem	=	m_pScrollBar->GetTrackPos() + ( pt.y - m_rcText.top ) / m_nTextHeight;

				if( nItem >= (int)m_pScrollBar->GetTrackPos() &&
					nItem < (int)m_Items.GetSize() &&
					nItem < m_pScrollBar->GetTrackPos() + m_pScrollBar->GetPageSize() )
				{
					m_nSelectedIDx = nItem;
					m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );
				}else
					if( nItem < (int)m_pScrollBar->GetTrackPos() )
					{
						m_pScrollBar->Scroll( -1 );
						m_nSelectedIDx	=	m_pScrollBar->GetTrackPos();
						m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );
					}else 
						if( nItem >= m_pScrollBar->GetTrackPos() + m_pScrollBar->GetPageSize() )
						{
							m_pScrollBar->Scroll( 1 );
							m_nSelectedIDx	=	__min( (int)m_Items.GetSize(), m_pScrollBar->GetTrackPos() + m_pScrollBar->GetPageSize() ) -1;
							m_pDlg->SendEvent( eCTRLEVENT_LISTBOX_SELECTION, true, this );
						}

			}//	if( m_bDrag )

		}//	case WM_MOUSEMOVE:
		break;

	case WM_MOUSEWHEEL:
		{
			UINT unLines;
			SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &unLines, 0 );
			int nScrollAmount	=	int((short)HIWORD(wParam)) / WHEEL_DELTA * unLines;
			m_pScrollBar->Scroll( -nScrollAmount );
			return true;
		}//	case WM_MOUSEWHEEL:
		break;

	}//	switch( uMsg )

	return false;	

}//	HandleMouse
//----------------------------------------------------------------------------------
bool	CPUIListBox::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( WM_CAPTURECHANGED == uMsg )
		m_bDrag = false;

	return false;
}
//----------------------------------------------------------------------------------
HRESULT	CPUIListBox::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	if( !m_bVisible )	
		return E_FAIL;

	CPUIElement*	pBackEle	=	GetCustomSkinElement( eSKINTYPE_LISTBOX_BACKGROUND );
	pBackEle->GetTexColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, m_fSkinAlpha );
	pBackEle->GetFontColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, 0.0f );

	CPUIElement*	pSelEle		=	GetCustomSkinElement( eSKINTYPE_LISTBOX_SELECT );
	pSelEle->GetTexColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, m_fSkinAlpha );
	pSelEle->GetFontColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, 0.0f );

	m_pDlg->DrawSkinSprite( pBackEle, &m_rcBoundBox );

	if( m_Items.GetSize() > 0 )
	{
		RECT	rc		=	m_rcText;
		RECT	rcSel	=	m_rcSelection;

		rc.bottom	=	rc.top + m_pDlg->GetFontFromManager( pBackEle->GetFontID() )->m_unHeight;

		m_nTextHeight	=	RectHeight( rc );

		static bool sbScrollBarInit;
		if( !sbScrollBarInit )
		{
			if( m_nTextHeight )
				m_pScrollBar->SetPageSize( RectHeight( m_rcText ) / m_nTextHeight );
			else
				m_pScrollBar->SetPageSize( RectHeight( m_rcText ) );

			sbScrollBarInit = true;
		}

		rc.right	=	m_rcText.right;
		int nCur	=	m_pScrollBar->GetTrackPos();
		int jjj = 0;
		for( ; nCur < (int)m_Items.GetSize(); ++nCur )
		{
			if( rc.bottom > m_rcText.bottom )
				break;

			CPUIListBoxItem*	pItem	=	m_Items.Find(nCur);
			
			bool bSelectedStyle	=	false;

			if( !( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION ) && nCur == m_nSelectedIDx )
				bSelectedStyle	=	true;
			else
				if( m_eListBoxType & eLISTBOXTYPE_MULTISELECTION )
				{
					if(		m_bDrag &&
							( ( nCur >= m_nSelectedIDx && nCur < m_nSelectedStartIDx ) ||
							( nCur <= m_nSelectedIDx && nCur > m_nSelectedStartIDx ) ) )
							bSelectedStyle	=	m_Items.Find(m_nSelectedStartIDx)->m_bSelected;
					else
						if( pItem->m_bSelected )
							bSelectedStyle	=	true;
				}

				if( bSelectedStyle )
				{
					rcSel.top		=	rc.top;
					rcSel.bottom	=	rc.bottom;
					m_pDlg->DrawSkinSprite( pSelEle, &rcSel );
					m_pDlg->DrawSkinText( pItem->m_tszText, pSelEle, &rc );
				}else
					m_pDlg->DrawSkinText( pItem->m_tszText, pBackEle, &rc );

				OffsetRect( &rc, 0, m_nTextHeight );
		}//	for( int nCur = m_pScrollBar->GetTrackPos(); nCur < (int)m_Items.GetSize(); ++nCur )
	}//	if( m_Items.GetSize() > 0 )

	m_pScrollBar->OnRender( pDev, fElapsedTime );

	return S_OK;
}
//	Render
//----------------------------------------------------------------------------------
//	EOF