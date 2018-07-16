//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
struct STextureInto
{
	D3DXIMAGE_INFO		m_imageInfo;
	LPDIRECT3DTEXTURE9	m_d3dTxtr;
	RECT				m_rcImage;

};// struct STextureInto	
//============================================
#define FRAME_REFRESH_TIME	10 
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

	//	���.
	STextureInto m_tInfoBG;
	//	�ִϸ��̼�.
	STextureInto m_tInfoAni;
	//	�ִϸ��̼� ��ġ
	D3DXVECTOR3			m_vecAniPos;

	// ���� Ÿ��
	DWORD				m_dwBeginTime;
	// �� Ÿ��
	DWORD				m_dwEndTime;

};// class CMyGame :	public CDxCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================