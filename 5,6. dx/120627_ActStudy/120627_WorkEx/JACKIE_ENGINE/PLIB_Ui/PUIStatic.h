#ifndef _JUISTATIC_H_
#define _JUISTATIC_H_
#pragma once

#include "PUIctrl.h"

class CPUIDlg;

class CPUIStatic :
	public CPUICtrl
{
public:
	CPUIStatic( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	void	InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual HRESULT OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );

	HRESULT			GetTextCopy( WCHAR* ptszDest, UINT unBufferCnt );
	const WCHAR*	GetText()	{ return m_tszText; }
	HRESULT			SetText( const WCHAR* ptszText );

private:
	WCHAR	m_tszText[MAX_PATH];

};

#endif	//	_JUISTATIC_H_