//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
class CMyGame :	public CDxCore
{
public:
	CMyGame();
	virtual ~CMyGame();

	virtual INT		Init();
	virtual INT		Render();
	virtual INT		FrameMove();
	virtual void	Destroy();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	CDxTexture		m_dxTxtrTest;
	CDxFont			m_dxFont;

	TCHAR	Mouse_Pos[1024];
	TCHAR   Key_Text[1024];
	FLOAT	Mouse_Z;
};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================