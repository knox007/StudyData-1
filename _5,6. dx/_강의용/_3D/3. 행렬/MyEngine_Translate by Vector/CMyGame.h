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
	//------------------------------------------
public:
	CMyGame();
	virtual ~CMyGame();

	virtual INT		Init();
	virtual INT		Render();
	virtual INT		FrameMove();
	virtual void	Destroy();

	virtual HRESULT	Restore();
	virtual void	Invalidate();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	
	
	TCHAR			m_tszMessage[256];

	//------------------------------------------
	HRESULT	InitVB();

	LPDIRECT3DVERTEXBUFFER9 m_pVB;	// 정점 버버



};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================