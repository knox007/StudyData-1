#ifndef _JUIEDITBOX_H_
#define _JUIEDITBOX_H_
#pragma once

#include "PUIctrl.h"
#include "PUIUniBuffer.h"

class CPUIDlg;

class CPUIEditBox :
	public CPUICtrl
{
public:
	CPUIEditBox( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	virtual ~CPUIEditBox(void)			{}
	void	InitMembers();	
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual	bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual	bool	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual void	UpdateRects();

	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	virtual void	OnFocusIn( HWND hWnd );

	
	//	Text	
	void			SetText( const WCHAR* ptszText, bool bSelected = false );
	void			SetTextFloatArray( const float* pfNumbers, int nCount );
	const WCHAR*	GetText()			{ return m_UniBuffer.GetBuffer(); }
	int				GetTextLength()		{ return m_UniBuffer.GetTextSize(); }
	HRESULT			GetTextCopy( const WCHAR* ptszDest, UINT unBufferCount );
	void			ClearText();

	
	//	Color
	virtual void	SeTextColor( D3DCOLOR col )				{ m_colText = col; }
	void			SetSelectedTextColor( D3DCOLOR col )	{ m_colSelectedText = col; }
	void			SetSelectedBackColor( D3DCOLOR col )	{ m_colSelectedBackground = col; }
	void			SetCaretColor( D3DCOLOR col )			{ m_colCaret = col; }

	//	Attribute
	void	SetBorderWidth( int nBorder )	{ m_nBorder = nBorder;		UpdateRects(); }
	void	SetSpace( int nSpacing )		{ m_nSpacing = nSpacing;	UpdateRects(); }
	void	ParseFloatArray( float* pfNumbers, int nCount );


protected:

	void	PlaceCaret( int nCP );
	void	DeleteSelectionText();
	void	ResetCaretBlink();
	void	CopyToClipboard();
	void	PasteFromClipboard();

	int				m_nBorder;
	int				m_nSpacing;
	RECT			m_rcText;
	RECT			m_rcRender[9];
	double			m_dfBlinkTime;
	double			m_dfLastBlinkTimestamp;	
	int				m_nCaretPos;	
	int				m_nSelectionStartPos;
	int				m_nFirstVisible;
	D3DCOLOR		m_colText;
	D3DCOLOR		m_colSelectedText;
	D3DCOLOR		m_colSelectedBackground;
	D3DCOLOR		m_colCaret;
	
	bool			m_bMouseDrag;
	bool			m_bCaretVisible;
	bool			m_bInsertModeFlag;		//	true - insert / false - overwrite
	static	bool	stt_bHideCaret;
		
	CPUIUniBuffer	m_UniBuffer;
};

#endif	//	_JUIEDITBOX_H_