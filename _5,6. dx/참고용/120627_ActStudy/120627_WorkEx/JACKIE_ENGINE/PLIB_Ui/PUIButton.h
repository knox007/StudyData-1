#ifndef	_JUIBUTTON_H_
#define _JUIBUTTON_H_

#pragma once
#include "PUIstatic.h"
#include "PUIDlg.h"


class CPUIButton :
	public CPUIStatic
{
public:
	CPUIButton( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	virtual void InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual	bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual void	OnHotKey()
	{
		if( m_pDlg->IsKeyboardInputEnable() )
			m_pDlg->RequestFocus( this );
		m_pDlg->SendEvent( eCTRLEVENT_BUTTON_CLICKED, true, this );
	}

	virtual BOOL ContainsPoint( POINT pt )	{ return PtInRect( &m_rcBoundBox, pt ); }
	
	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	
protected:
	bool	m_bPressed;

};

#endif	//	_JUIBUTTON_H_