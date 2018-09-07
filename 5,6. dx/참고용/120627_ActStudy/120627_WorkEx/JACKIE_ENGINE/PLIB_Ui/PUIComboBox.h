#ifndef _JUICOMBOBOX_H_
#define _JUICOMBOBOX_H_
#pragma once

#include "PUIbutton.h"
#include "PUIDlg.h"
#include "PUIScrollBar.h"
#include "PUTListMgr.h"


//------------------------------------------------------------------------
class CPUIComboBoxItem
{
public:
	CPUIComboBoxItem()	{ InitMembers(); }
	~CPUIComboBoxItem()	{}

	void	InitMembers();
	

	WCHAR	m_tszText[256];
	void*	m_pData;

	RECT	m_rcActive;
	bool	m_bVisible;
};
//------------------------------------------------------------------------
typedef std::list<CPUIComboBoxItem*>	LISTCOMBOITEM;
typedef LISTCOMBOITEM::iterator			LISTCOMBOITEMITER;
class CPUIComboBox :
	public CPUIButton
{
public:
	CPUIComboBox( CPUIDlg* pDlg = NULL )	{ InitMembers( pDlg ); }
	virtual ~CPUIComboBox()					{ ClearMembers(); }
	void	InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }
	void	ClearMembers();
	
	virtual HRESULT	Init()	
	{		
		if( !m_pScrollBar )		
			PUTNEW( m_pScrollBar, CPUIScrollBar );
		return m_pDlg->InitCtrl( m_pScrollBar );
	}

	virtual	bool		HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool		HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual void		OnHotKey();
	
	virtual	void		OnFocusOut( HWND hWnd );
	
	virtual	HRESULT		OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );

	virtual void		UpdateRects();
	
	//	Item
	HRESULT				AddItem( const WCHAR* ptszText, void* pData );
	void				RemoveAllItems();
	void				RemoveItem( UINT unID );
	bool				ContainsItem( const WCHAR* ptszText, UINT unStart = 0 );
	int					FindItem( const WCHAR* ptszText, UINT unStart = 0 );
	void*				GetItemData( const WCHAR* ptszText );
	void*				GetItemData( int nID );
	void*				GetSelectedData();
	CPUIComboBoxItem*	GetSelectedItem();
	UINT				GetNumItems()			{ return m_Items.GetSize(); }
	CPUIComboBoxItem*	GetItem( UINT unID )	{ return m_Items.Find( unID ); }
	HRESULT				SetSelectedByIndex( UINT unID );
	HRESULT				SetSelectedByText( const WCHAR* ptszText );
	HRESULT				SetSelectedByData( void* pData );
	
	//	ScrollBar
	CPUIScrollBar*		GetScrollBar()			{ return m_pScrollBar; }

	//	Attribute
	void				SetDropHeight( UINT unHeight )	{ m_nDropHeight = unHeight; UpdateRects(); }
	int					GetScrollBarWidth()	const		{ return m_nScrollBarWidth; }
	void				SetScrollBarWidth( int nWid )	{ m_nScrollBarWidth = nWid; }
	virtual	void		SetTextColor( D3DCOLOR col );


protected:
	CPUTListMgrPt<CPUIComboBoxItem>	m_Items;

	int				m_nSelectedID;
	int				m_nFocusedID;
	int				m_nDropHeight;
	CPUIScrollBar	*m_pScrollBar;
	int				m_nScrollBarWidth;

	bool			m_bOpened;

	RECT			m_rcText;
	RECT			m_rcButton;
	RECT			m_rcDropDown;
	RECT			m_rcDropDownText;
};

#endif	//	_JUICOMBOBOX_H_