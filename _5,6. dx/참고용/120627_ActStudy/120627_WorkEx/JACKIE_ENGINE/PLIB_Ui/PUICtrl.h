#ifndef	_JUICTRL_H_
#define _JUICTRL_H_
#pragma once

#include "PUICtrlCommon.h"
#include "PUTVecMgr.h"

class CPUIDlg;
class CPUIElement;
const int MAX_ELEMENT = 9;

class CPUICtrl
{
public:
	CPUICtrl( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	virtual ~CPUICtrl()					{ ClearMembers(); }
	virtual	void	InitMembers();
	virtual	void	InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }
	virtual	void	ClearMembers();

	virtual HRESULT	Init()				{ return S_OK; }
	virtual	void	Refresh();
	
	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )			{ return S_OK; }

	//	Message Procedure & Handle InputDevice
	virtual bool	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )					{ return false; }
	virtual bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )			{ return false; }
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )		{ return false; }

	//	ID
	int		GetID()		const	{ return m_nID; }
	void	SetID( int nID )	{ m_nID = nID; }
	bool	IsSameID( int nID )	{ return ( GetID() == nID );}

	//	Position & Size
	void	SetPos( int nX, int nY )		{ m_nPosX = nX; m_nPosY = nY;			UpdateRects(); }
	void	SetSize( int nWid, int nHei )	{ m_nWidth = nWid; m_nHeight = nHei;	UpdateRects(); }

	//	Is Mouse In Rect?
	virtual BOOL ContainsPoint( POINT pt ) { return PtInRect( &m_rcBoundBox, pt ); }

	//	Check Default
	void	SetDefaultEnable( bool bDef )		{ m_bDefault = bDef; }
	bool	IsDefaultEnable()					{ return m_bDefault; }

	//	Check Visible
	void	SetVisible( bool bVis )		{ m_bVisible = bVis; }
	bool	IsVisible()					{ return m_bVisible; }
	
	//	Check Mouse Position
	void	SetMouseInRect( bool bIn )	{ m_bMouseInRect = bIn; }
	bool	IsMouseInRect()				{ return m_bMouseInRect; }
	
	//	Check Focus	
	void	OnFocusIn( HWND hWnd = NULL )		{ m_bFocus = true; }
	void	OnFocusOut( HWND hWnd = NULL )		{ m_bFocus = false; }	
	bool	IsFocus()					{ return m_bFocus; }	//	jackie 110908 Really Need??
	bool	IsActive()					{ return ( IsVisible() && IsEnable() ); }
	
	//	Check Enable
	void	SetEnable( bool bEnabled )	{ m_bEnable = bEnabled; }
	bool	IsEnable()					{ return m_bEnable; }

	//	Type
	UINT	GetType()					{ return m_eCtrlType; }
	bool	IsSameType( eCTRLTYPE_ eType)	{ return (GetType() == eType);}

	//	Hotkey
	void	SetHotkey( UINT unHotkey )	{ m_unHotkey = unHotkey; }
	UINT	GetHotkey()					{ return m_unHotkey; }
	virtual void OnHotKey()				{}

	//	UserData
	void	SetUserData( void* pUserData )	{ m_pUserData = pUserData; }
	void*	GetUserData()					{ return m_pUserData; }

	//	Element
	HRESULT			SetElement( UINT unElement, CPUIElement* pEle );	
	HRESULT			SetCustomSkinElement( UINT unElement, CPUIElement* pEle );
	CPUIElement*	GetElement( UINT unElement );
	CPUIElement*	GetCustomSkinElement( UINT unElement );


	//	TextColor & Alpha
	virtual void	SetTextColor( D3DCOLOR col );
	void			SetSkinAlpha( float fAlpha )			{ m_fSkinAlpha = fAlpha; }

	//	Dlg	
	CPUIDlg*		GetDlg()					{ return m_pDlg; }
	void			SetDlg( CPUIDlg* pDlg )		{ m_pDlg = pDlg; }
	bool			IsSameDlg( CPUIDlg* pDlg )	{ return (GetDlg() == pDlg);}

 
protected:
	virtual void UpdateRects();

	CPUIDlg*	m_pDlg;
	UINT		m_unCtrlID;

	int			m_nID;
	eCTRLTYPE_	m_eCtrlType;

	int		m_nPosX;
	int		m_nPosY;
	int		m_nWidth;
	int		m_nHeight;
	RECT	m_rcBoundBox;
 	bool	m_bVisible;
	bool	m_bMouseInRect;
	bool	m_bFocus;	//	jackie 110908 Really Need??
	bool	m_bDefault;
	bool	m_bEnable;
	
	UINT	m_unHotkey;
	void*	m_pUserData;	
	float	m_fSkinAlpha;

	CPUTVecMgrPt<CPUIElement>	m_Elements;	
	CPUTVecMgrPt<CPUIElement>	m_CustomSkinElements;
	
};

#endif	//	_JUICTRL_H_