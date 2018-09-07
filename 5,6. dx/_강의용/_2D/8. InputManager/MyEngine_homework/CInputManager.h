//=================================================================
#pragma once
//=================================================================
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
//=================================================================
#define MAX_INPUT_KEY	256
#define MAX_INPUT_BTN	8
//=================================================================
class CInputManager
{
public:
	enum eINPUTSTATE
	{
		NONE,
		DOWN,
		UP,
		PRESS,
		DBLCLK,
	};

protected:
	HWND		m_hWnd;

	BYTE		m_kbdBttnCur[MAX_INPUT_KEY];	// 키보드 현재 상태
	BYTE		m_kbdBttnOld[MAX_INPUT_KEY];	// 키보드 이전 상태
	BYTE		m_kbdBttnMap[MAX_INPUT_KEY];	// 키보드 맵

	BYTE		m_mouseBtttnCur[MAX_INPUT_BTN];	// 마우스 현재 상태
	BYTE		m_mouseBtttnOld[MAX_INPUT_BTN];	// 마우스 이전 상태
	BYTE		m_mouseBtttnMap[MAX_INPUT_BTN];	// 마우스 맵

	D3DXVECTOR3	m_vcCur;						// 휠 마우스
	D3DXVECTOR3 m_vcOld;
	D3DXVECTOR3 m_vcEps;

	DWORD		m_dTimeDC;					// Double Click Time Interval
	DWORD		m_dBtnBgn[MAX_INPUT_BTN];	// Double Click Start
	INT			m_dBtnCnt[MAX_INPUT_BTN];	// Double Click Count


public:
	CInputManager();
	virtual ~CInputManager();

	INT			Create(HWND	hWnd);
	INT			FrameMove();
	LRESULT		MsgProc(HWND,UINT, WPARAM, LPARAM);

	BOOL		KeyDown	(INT nKey);
	BOOL		KeyUp	(INT nKey);
	BOOL		KeyPress(INT nKey);
	INT			KeyState(INT nKey);

	BOOL		BtnDown	 (INT nBtn);
	BOOL		BtnUp	 (INT nBtn);
	BOOL		BtnPress (INT nBtn);
	INT			BtnState (INT nBtn);

	D3DXVECTOR3 GetMousePos();
	D3DXVECTOR3 GetMouseEps();

};//	class CInputManager
//=================================================================
#endif
//=================================================================