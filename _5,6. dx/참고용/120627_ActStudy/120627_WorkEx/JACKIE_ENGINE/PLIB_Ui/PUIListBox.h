#ifndef _JUILISTBOX_H_
#define _JUILISTBOX_H_
#pragma once

#include "PUIctrl.h"
#include "PUIDlg.h"
#include "PUIScrollBar.h"
#include "PUTListMgr.h"

//------------------------------------------------------------------------
class CPUIListBoxItem 
{
public:
	CPUIListBoxItem()	{ /* InitMembers(); */ }
	~CPUIListBoxItem()	{ /* ClearMembers(); */ }
//	void	InitMembers();
//	void	ClearMembers();

	WCHAR	m_tszText[256];
	void*	m_pData;
	RECT	m_rcActive;
	bool	m_bSelected;
};
//------------------------------------------------------------------------
class CPUIListBox :
	public CPUICtrl
{
public:
	CPUIListBox( CPUIDlg* pDlg = NULL ) { InitMembers(pDlg); }
	virtual ~CPUIListBox()				{ ClearMembers(); }
	virtual void	InitMembers();
	virtual void	InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }
	void	ClearMembers();

	enum	eLISTBOXTYPE_
	{
		eLISTBOXTYPE_INVALID,
		eLISTBOXTYPE_MULTISELECTION,

		eLISTBOXTYPE_MAX
	};

	virtual	HRESULT	Init()	
	{
		if( !m_pScrollBar )		
			PUTNEW( m_pScrollBar, CPUIScrollBar( m_pDlg ) );	

		return m_pDlg->InitCtrl( m_pScrollBar );
	}

	virtual	bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual bool	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );

	virtual void	UpdateRects();

	//	Attribute
	size_t	GetSize()	{ return m_Items.GetSize(); }

	eLISTBOXTYPE_	GetStyle()	const	
					{ return m_eListBoxType; }
	void			SetStyle( eLISTBOXTYPE_ eStyle )	
					{ m_eListBoxType = eStyle;}
	int				GetScrollBarWidth()	const		
					{ return m_nScrollBarWidth; }
	void			SetScrollBarWidth( int nWid )	
					{ m_nScrollBarWidth = nWid; UpdateRects(); }
	CPUIScrollBar*	GetScrollBar()	
					{ return m_pScrollBar; }
	void			SetBorder( int nBorder, int nMargin )	
					{ m_nBorder = nBorder; m_nMargin = nMargin; }

	//	Item
	HRESULT	AddItem( const WCHAR* ptszText, void *pData );
	HRESULT	InsertItem( int nID, const WCHAR* ptszText, void* pData );
	void	RemoveItem( int nID );
	void	RemoveItemByText( const WCHAR* ptszText );
	void	RemoveItemByData( void *pData );
	void	RemoveAllItems();

	CPUIListBoxItem*	GetItem( int nID );
	int		GetSelectedIndex( int nPrevSelected = -1 );
	CPUIListBoxItem*	GetSelectedItem( int nPrevSelected = -1 )
						{ return GetItem( GetSelectedIndex( nPrevSelected ) ); }
	void	SelectItem( int nID );
	

protected:	
	CPUTListMgrPt<CPUIListBoxItem>	m_Items;

	RECT	m_rcText;
	RECT	m_rcSelection;
	CPUIScrollBar*	m_pScrollBar;

	int		m_nScrollBarWidth;
	int		m_nBorder;
	int		m_nMargin;
	int		m_nTextHeight;
	
	eLISTBOXTYPE_	m_eListBoxType;

	int		m_nSelectedIDx;
	int		m_nSelectedStartIDx;
	bool	m_bDrag;
	
};//	CPUIListBox

#endif	//	_JUILISTBOX_H_