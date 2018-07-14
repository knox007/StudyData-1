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

	D3DXIMAGE_INFO		m_Img[256] = { 0 };		// �̹��� ����
	LPDIRECT3DTEXTURE9	m_Tex[256] = { 0 };		// �ؽ�ó ������

};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================