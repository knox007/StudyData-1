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
	
	CDxTexture*		m_pDxTexture1;
	CDxTexture*		m_pDxTexture2;
	D3DXVECTOR3		m_vec3Pos1;
	D3DXVECTOR3		m_vec3Pos2;

	CDxFont			m_dxFont;

};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================