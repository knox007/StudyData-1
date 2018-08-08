//=================================================================
#pragma once
//=================================================================
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
//=================================================================
#define MAX_INPUT_KEY	256
#define MAX_INPUT_BTN	3
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

	BYTE		m_kbdBttnCur[MAX_INPUT_KEY];	//	키보드 현재 상태
	BYTE		m_kbdBttnOld[MAX_INPUT_KEY];	//	키보드 이전 상태
	BYTE		m_kbdBttnMap[MAX_INPUT_KEY];	//	키보드 맵
												//	m_kbdBttnCur, m_kbdBttnOld의 결과를 비교하여
												//	최종 결과를 적용하기 위한 버퍼.

	BYTE		m_mouseBtttnCur[MAX_INPUT_BTN];	// 마우스 현재 상태
	BYTE		m_mouseBtttnOld[MAX_INPUT_BTN];	// 마우스 이전 상태
	BYTE		m_mouseBtttnMap[MAX_INPUT_BTN];	// 마우스 맵

	D3DXVECTOR3	m_vcCur;						//	현재 프레임의 마우스 좌표및 휠의 옵셋 값.
	D3DXVECTOR3 m_vcOld;						//	이전
	D3DXVECTOR3 m_vcEps;						//	현재 프레임과 이전 프레임의 마우스 정보 변화량.

	DWORD		m_dTimeDC;						//	시스템상의 마우스 더블클릭 인식유효 시간.
	DWORD		m_dBtnBgn[MAX_INPUT_BTN];		//	각 마우스 버튼의 클릭 시간.
	


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

	INT			m_dBtnCnt[MAX_INPUT_BTN];	// Double Click Count

};//	class CInputManager
//=================================================================
#endif
//=================================================================