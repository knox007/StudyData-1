//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
//	���ؽ� ������ ����
struct CUSTOMVERTEX
{
	float x, y, z, rhw;	//	��ȯ�� �Ϸ�� ����.
	DWORD color;		//	������ ����.	
};
#define	D3DFVF_CUSTOMVERTEX	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
//============================================
class CMyGame :	public CDxCore
{
public:
	//-------------------------------------------
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
	//-------------------------------------------
	/*	���ؽ� ����.

		-	���� ������ ������ �ִ� �޸� ���.
		-	Lock() / Unlock()���� �����͸� ���ͼ� ���ؽ� ������ �����Ѵ�.
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB;	

	//	���ؽ� ���� ���� �� �ʱ�ȭ.
	HRESULT InitVB();

};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================