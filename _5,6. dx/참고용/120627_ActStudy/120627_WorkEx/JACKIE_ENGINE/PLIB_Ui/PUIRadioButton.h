#ifndef _JUIRADIOBUTTON_H_
#define _JUIRADIOBUTTON_H_
#pragma once

#include "PUIcheckbox.h"
#include "PUIDlg.h"

class CPUIRadioButton :
	public CPUICheckBox
{
public:
	CPUIRadioButton( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	void	InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual void	OnHotKey()
	{
		if( m_pDlg->IsKeyboardInputEnable() )
			m_pDlg->RequestFocus( this );
		SetCheckedInternal( true, true, true );
	}

	void	SetCheck( bool bCheck, bool bClearGroup = true )	{ SetCheckedInternal( bCheck, bClearGroup, false ); }
	void	SetButtonGroup( UINT unButtonGroupIDx )	{ m_unBttnGroupIDx = unButtonGroupIDx; }
	UINT	GetButtonGroup()	{ return m_unBttnGroupIDx; }

protected:
	virtual void	SetCheckedInternal( bool bChecked, bool bClearGroup, bool bFromInput );
	UINT			m_unBttnGroupIDx;
};

#endif	//	_JUIRADIOBUTTON_H_