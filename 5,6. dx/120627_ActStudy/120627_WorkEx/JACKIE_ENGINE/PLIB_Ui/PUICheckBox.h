#ifndef _JUICHECKBOX_H_
#define _JUICHECKBOX_H_
#pragma once

#include "PUIbutton.h"
#include "PUIDlg.h"

class CPUICheckBox :
	public CPUIButton
{
public:
	CPUICheckBox( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	void	InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual	void	OnHotKey()
	{
		if( m_pDlg->IsKeyboardInputEnable() )
			m_pDlg->RequestFocus( this );
		SetCheckedInternal( !m_bChecked, true );
	}

	virtual	BOOL	ContainsPoint( POINT pt );
	virtual void	UpdateRects();

	virtual	HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );


	bool	IsChecked()	{ return m_bChecked; }
	void	SetCheck( bool bCheck )	{ SetCheckedInternal( bCheck, false ); }


protected:
	virtual void	SetCheckedInternal( bool bChecked, bool bFromInput );

	bool	m_bChecked;
	RECT	m_rcButton;
	RECT	m_rcText;
};

#endif	//	_JUICHECKBOX_H_