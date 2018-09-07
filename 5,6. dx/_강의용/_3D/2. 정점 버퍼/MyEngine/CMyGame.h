//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
//	버텍스 데이터 형식
struct CUSTOMVERTEX
{
	float x, y, z, rhw;	//	변환이 완료된 정점.
	DWORD color;		//	정점의 색깔.	
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
	/*	버텍스 버퍼.

		-	정점 정보를 가지고 있는 메모리 블록.
		-	Lock() / Unlock()으로 포인터를 얻어와서 버텍스 정보를 설정한다.
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB;	

	//	버텍스 버퍼 생성 및 초기화.
	HRESULT InitVB();

};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================