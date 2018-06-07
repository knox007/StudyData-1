#ifndef _JUISLIDER_H_
#define _JUISLIDER_H_
#pragma once

#include "PUIctrl.h"
#include "PUIDlg.h"

class CPUISlider :
	public CPUICtrl
{
public:
	CPUISlider( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	void	InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual BOOL	ContainsPoint( POINT pt );
	virtual bool	HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );

	virtual void	UpdateRects();

	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );


	void	SetVal( int nVal )	{ SetValueInternal( nVal, false ); }
	int		GetVal()	const	{ return m_nVal; }

	void	GetRange( int &nMin, int &nMax )	const	{ nMin = m_nMin; nMin = m_nMax; }
	void	SetRange( int nMin, int nMax );

protected:
	void	SetValueInternal( int nVal, bool bFromInput );
	int		GetValFromPos( int nPosX );

	int		m_nVal;
	int		m_nMin;
	int		m_nMax;

	int		m_nDragX;
	int		m_nDragOffset;
	int		m_nButtonX;
	
	bool	m_bPressed;
	RECT	m_rcButton;
};

#endif	//	_JUISLIDER_H_