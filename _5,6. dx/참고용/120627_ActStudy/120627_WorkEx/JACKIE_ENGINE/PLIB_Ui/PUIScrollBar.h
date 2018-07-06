#ifndef _JUISCROLLBAR_H_
#define _JUISCROLLBAR_H_
#pragma once

#include "PUIctrl.h"
#include "PUIDlg.h"

const int SCROLLBAR_MINTHUMBSIZE	=	8;
const float SCROLLBAR_ARROWCLICK_DELAY	=	0.33f;
const float SCROLLBAR_ARROWCLICK_REPEAT =	0.05f;

class CPUIScrollBar :
	public CPUICtrl
{
public:
	CPUIScrollBar( CPUIDlg* pDlg = NULL )	{ InitMembers(pDlg); }
	void			InitMembers();
	virtual void InitMembers( CPUIDlg *pDlg )	{ InitMembers(); m_pDlg = pDlg; }

	virtual	bool	HandleKeyboard( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool	HandleMouse( HWND hWnd, UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
	virtual bool	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	virtual void	UpdateRects();

	//	Track
	void	SetTrackRange( int nStart, int nEnd );
	void	SetTrackPos( int nPos )	
			{ m_nPosVal = nPos; Cap(); UpdateThumbRect(); }
	int		GetTrackPos()	
			{ return m_nPosVal; }	
	void	SetPageSize( int nPageSize )	
			{ m_nPageSize = nPageSize; Cap(); UpdateThumbRect(); }
	int		GetPageSize()	
			{ return m_nPageSize; }


	void	Scroll( int nDelta );
	void	ShowItem( int nID );

	
protected:
	enum eARROWBUTTON_
	{
		eARROWBUTTON_CLEAR,			//	NO ARROW BUTTON IS DOWNED.

		eARROWBUTTON_CLICK_PREV,	//	PREV BUTTON IS CLICKED.
		eARROWBUTTON_CLICK_NEXT,	//	NEXT BUTTON IS CLICKED.
		eARROWBUTTON_HELD_PREV,		//	PREV BUTTON IS HELD DOWN.
		eARROWBUTTON_HELD_NEXT,		//	NEXT BUTTON IS HELD DOWN.

		eARROWBUTTON_MAX
	};

	void	UpdateThumbRect();
	void	Cap();

	bool	m_bShowthumb;
	bool	m_bDrag;
	
	RECT	m_rcPrevBttn;
	RECT	m_rcNextBttn;
	RECT	m_rcThumbBttn;
	RECT	m_rcTrack;

	int		m_nPosVal;
	int		m_nPageSize;
	int		m_nStart;
	int		m_nEnd;

	POINT	m_ptLastMouse;
	eARROWBUTTON_	m_ArrowBttnState;
	double	m_dArrowTimestamp;

};

#endif	//	_JUISCROLLBAR_H_