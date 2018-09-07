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
	HRESULT	InitIB();
	void SetMatrix();
	LPDIRECT3DVERTEXBUFFER9 m_pVB;	//	정점 버퍼
	LPDIRECT3DINDEXBUFFER9	m_pIB;	//	인덱스 버퍼
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------

};// class CMyGame :	public CDxCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================