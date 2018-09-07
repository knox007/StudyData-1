#ifndef _JUIDLG_H_
#define _JUIDLG_H_
#pragma once

//#include "PUIDlgResourceMgr.h"
#include "PUTVecMgr.h"
#include "PUICtrl.h"


class CPUIStatic;
class CPUIButton;
class CPUICheckBox;
class CPUIRadioButton;
class CPUIComboBox;
class CPUISlider;
class CPUIEditBox;
class CPUIIMEEditBox;
class CPUIListBox;
class CPUIDlgResourceMgr;

typedef VOID (CALLBACK *PCALLBACKUIEVENT) ( UINT nEvent, int nControlID, CPUICtrl* pControl, void* pUserContext );

class CPUIDlg
{
	friend class CPUIDlgResourceMgr;

public:
	
	enum eMSGVAL_
	{
		eMSGVAL_NOTHANDLED = 1,
		eMSGVAL_HANDLED,
		eMSGVAL_MOUSE_IN,
		eMSGVAL_MAX
	};

	CPUIDlg()	{ InitMembers(); }
	CPUIDlg( const CPUIDlg &rhs );
	CPUIDlg&	operator=( const CPUIDlg &rhs );
	virtual ~CPUIDlg()	{ ClearMembers(); }
	virtual void		InitMembers();
	virtual void		ClearMembers();

	


	//	Init
	virtual void	Init( int nSkinID, bool bRegisterDlg = true );
	virtual void	Init( int nSkinID, bool bRegisterDlg, const WCHAR* ptszCtrlTextureFileName );
	virtual void	Init( int nSkinID, bool bRegisterDlg, const WCHAR* ptszCtrlTextureFileName, HMODULE hCtrlTextureResModule );



	//	Proc
	int		MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );


	//	Ctrl
	HRESULT	InitCtrl(	CPUICtrl* pCtrl );
	
	HRESULT	AddCtrl(	CPUICtrl* pCtrl, int nSkinID );

	HRESULT	AddStatic(	int nID, const WCHAR* ptszText, 
						int nPosX, int nPosY, int nWid, int nHei,
						int nSkinID = -1, bool bIsDefault = false, 
						CPUIStatic** ppCreated = NULL );
	
	HRESULT	AddButton(	int nID, 
						const WCHAR* ptszText, 
						int nPosX, int nPosY,
						int nWid, int nHei,
						int nSkinID = -1, UINT unHotKey = 0, 
						bool bIsDefault = false,	
						CPUIButton** ppCreated = NULL );

	HRESULT	AddCheckBox(	int nID, const WCHAR* ptszText, 
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1, bool bChecked = false,
							UINT unHotKey = 0, bool bIsDefault = false, 
							CPUICheckBox** ppCreated = NULL );

	HRESULT	AddRadioButton(	int nID, UINT unButtonGroup,
							const WCHAR* ptszText,
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1, bool bChecked = false,
							UINT unHotKey = 0, bool bIsDefault = false,
							CPUIRadioButton** ppCreated = NULL );
	
	HRESULT	AddComboBox(	int nID, 
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1, int nScrollBarSkinID = -1,
							UINT unHotKey = 0, bool bIsDefault = false, 
							CPUIComboBox** ppCreated = NULL );	
	
	HRESULT	AddSlider(		int nID,
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1,
							int nVal = 50, bool bIsDefault = false, 
							CPUISlider** ppCreated = NULL );
	
	HRESULT	AddEditBox(		int nID, const WCHAR* ptszText,
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1, bool bIsDefault = false,
							CPUIEditBox** ppCreated = NULL );
	
	HRESULT	AddIMEEditBox(	int nID, const WCHAR* ptszText,
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1, bool bIsDefault = false, 
							CPUIIMEEditBox** ppCreated = NULL );

	HRESULT	AddListBox(		int nID, 
							int nPosX, int nPosY, int nWid, int nHei,
							int nSkinID = -1, int nScrollBarSkinID = -1, DWORD dwStyle = 0, 
							CPUIListBox** ppCreated = NULL );

	

	CPUIStatic*			GetStatic( int nID )		{ return (CPUIStatic*)GetCtrl( nID, eCTRLTYPE_STATIC ); }
	CPUIButton*			GetButton( int nID )		{ return (CPUIButton*)GetCtrl( nID, eCTRLTYPE_BUTTON ); }
	CPUICheckBox*		GetCheckBox( int nID )		{ return (CPUICheckBox*)GetCtrl( nID, eCTRLTYPE_CHECKBOX ); }
	CPUIRadioButton*	GetRadioButton( int nID )	{ return (CPUIRadioButton*)GetCtrl( nID, eCTRLTYPE_RADIOBUTTON ); }
	CPUIComboBox*		GetComboBox( int nID )		{ return (CPUIComboBox*)GetCtrl( nID, eCTRLTYPE_COMBOBOX ); }
	CPUISlider*			GetSlider( int nID )		{ return (CPUISlider*)GetCtrl( nID, eCTRLTYPE_SLIDER ); }
	CPUIEditBox*		GetEditBox( int nID )		{ return (CPUIEditBox*)GetCtrl( nID, eCTRLTYPE_EDITBOX ); }
	CPUIIMEEditBox*		GetIMEEditBox( int nID )	{ return (CPUIIMEEditBox*)GetCtrl( nID, eCTRLTYPE_IMEEDITBOX ); }
	CPUIListBox*		GetListBox( int nID )		{ return (CPUIListBox*)GetCtrl( nID, eCTRLTYPE_LISTBOX ); }
	static	CPUICtrl*	GetNextCtrl( CPUICtrl* pCtrl );
	static	CPUICtrl*	GetPrevCtrl( CPUICtrl* pCtrl );
	


	//	Ctrls
	size_t		GetCtrlSize()			{ return m_Ctrls.GetSize(); }
	void		RemoveCtrl( int nID );
	void		RemoveAllCtrls();
	CPUICtrl*	GetCtrl( int nID );
	CPUICtrl*	GetCtrl( int nID, eCTRLTYPE_ eType );
	CPUICtrl*	GetCtrlAtPoint( POINT pt );
	bool		GetCtrlEnabled( int nID );
	void		SetCtrlEnabled( int nID, bool bEnable );


	//	Ctrl Enable Check
	bool		IsCtrlEnable( int nID );
	void		CheckCtrlEnable( int nID, bool bEnable );
	

	//	Clear Ctrl
	void		ClearRadioButtonGroup( UINT unGroup );
	void		ClearComboBox( int nID );


	//	Element
	HRESULT			SetDefaultElement( UINT unCtrlType, UINT unElement, CPUIElement* pElement );
	HRESULT			SetSkinElement( UINT unElement, CPUIElement* pElement );
	CPUIElement*	GetDefaultElement( UINT unCtrlType, UINT unElement );	
	CPUIElement*	GetSkinElement( UINT unElement )	{ return m_SkinElements.Find(unElement); }


	//	Event
	void	SendEvent( UINT unEvent, bool bTriggeredByUser, CPUICtrl* pCtrl );


	//! CPUIDlg 클래스는 상속을 받아 사용할 것이며	
	void	SetCallBack( PCALLBACKUIEVENT pCallBack, void* pUserContext = NULL );	
	void	CheckNonUserEvents( bool bEnable )	{ m_bNonUserEvents	= bEnable; }
	void	CheckKeyboardInput( bool bEnable )	{ m_bKeyboardInput	= bEnable; }
	void	CheckMouseInput( bool bEnable )		{ m_bMouseInput		= bEnable; }
	bool	IsKeyboardInputEnable()		const	{ return m_bKeyboardInput; }


	//	Focus
	void			RequestFocus( CPUICtrl* pCtrl );
	static	void	ClearFocus();
	void			FocusDefaultCtrl();


	//	Helpers
	HRESULT		DrawRect( RECT* pRect, D3DCOLOR col );
	HRESULT		DrawPolyLine( POINT* pPoints, UINT unNumPts, D3DCOLOR col );
	HRESULT		DrawSprite( CPUIElement* pElement, RECT* prcDest );
	HRESULT		DrawSkinSprite( CPUIElement* pElement, RECT* prcDest );
	HRESULT		CalcTextRect( const WCHAR* ptszText, CPUIElement* pElement, RECT* prcDest, int nCount = -1 );
	HRESULT		DrawText( const WCHAR* ptszText, CPUIElement* pElement, RECT* prcDest, bool bShadow = false, int nCount = -1 );
	HRESULT		DrawSkinText( const WCHAR* ptszText, CPUIElement* pElement, RECT* prcDest, bool bShadow = false, int nCount = -1 );


	//	Attributes
	void		SetPos( int nX, int nY )		{ m_nPosX = nX; m_nPosY = nY;}
	void		GetPos( POINT &pt )				{ pt.x = m_nPosX; pt.y = m_nPosY; }
	void		SetSize( int nWid, int nHei )	{ m_nWidth = nWid; m_nHeight = nHei; }
	int			GetWidth()	{ return m_nWidth; }
	int			GetHeight()	{ return m_nHeight; }
	bool		IsVisible()						{ return m_bVisible; }
	void		CheckVisible( bool bVisible )	{ m_bVisible = bVisible; }
	bool		IsShowDlgRect()					{ return m_bShowDlgRect; }
	void		CheckDlgRectDraw( bool bFlag )	{ m_bShowDlgRect = bFlag; }
	void		SetBackgroundColors( D3DCOLOR colTL, D3DCOLOR colTR, D3DCOLOR colBL, D3DCOLOR colBR );
	void		SetBackgroundColors( D3DCOLOR col )	{ SetBackgroundColors( col, col, col, col ); }


	//	Refresh
	static	void	SetRefreshTime( float fTime )	{ stt_dRefreshTime = fTime; }	
	void			Refresh();


	//	Render
	HRESULT			OnRender( LPDIRECT3DDEVICE9 pDef, float fElapsedTime );

	
	//	Font
	HRESULT			SetFont( UINT unID, const WCHAR* ptszFaceName, long lHeight, long lWeight );
	CPUIFontNode*	GetFont( UINT unID );
	CPUIFontNode*	GetFontFromManager( UINT unID );


	//	Texture
	HRESULT			SetTex( UINT unID, const WCHAR* ptszFileName );
	HRESULT			SetTex( UINT unID, const WCHAR* ptszResName, HMODULE hResourceModule );
	CPUITexNode*	GetTex( UINT unID );


	//	ResourceMgr	
	void				SetResMgr( CPUIDlgResourceMgr* pMgr )	{ m_pResMgr = pMgr; }
	CPUIDlgResourceMgr*	GetResMgr()								{ return m_pResMgr; }
	


private:

	void	InitDefaultElements();	
	void	OnMouseMove( POINT pt );	

	void	SetNextDlg( CPUIDlg* pNextDialog );	
	bool	OnCycleFocus( bool bForward );

	int		m_nDefaultCtrlID;

	int		m_nPosX;
	int		m_nPosY;
	int		m_nWidth;
	int		m_nHeight;

	bool	m_bVisible;
	bool	m_bDrag;

	static double				stt_dRefreshTime;
	double						m_dLastRefreshTime;
	
	static CPUICtrl*			stt_pCtrlFocus;
	static CPUICtrl*			stt_pCtrlPressed;
	CPUICtrl*					m_pCtrlMouseIn;

	D3DCOLOR	m_colLT;
	D3DCOLOR	m_colRT;
	D3DCOLOR	m_colLB;
	D3DCOLOR	m_colRB;

	CPUIDlgResourceMgr*			m_pResMgr;
	PCALLBACKUIEVENT			m_pCallbackEvent;
	void*						m_pCallbackEventUserContext;

	CPUTVecMgr<int>				m_TexIDs;
	CPUTVecMgr<int>				m_FontIDs;

	CPUTVecMgrPt<CPUICtrl>			m_Ctrls;	
	CPUTVecMgrPt<CPUIElementHolder>	m_DefaultElements;
	size_t	GetDefEleSize()			{ return m_DefaultElements.GetSize(); }

	bool								m_bShowDlgRect;
	CPUTVecMgrPt<CPUIElement>			m_SkinElements;

	CPUIDlg*	m_pPrevDlg;
	CPUIDlg*	m_pNextDlg;

	bool	m_bNonUserEvents;
	bool	m_bKeyboardInput;
	bool	m_bMouseInput;
};

#endif	//	_JUIDLG_H_