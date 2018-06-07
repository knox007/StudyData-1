#pragma once
#ifndef _PRINPUT_H_
#define _PRINPUT_H_

#define DIRECTINPUT_VERSION	0x0800
#define	DX_COUNTKEYS		256

#include <dinput.h>
#include "PUtSingleton.h"

#pragma comment(lib, "dinput8.lib")


class CPRInput : public CPUTSingleton<CPRInput>
{
public:

	//!	�Է� ��ġ.
	enum	eDEVINPUT_
	{
		eDEVINPUT_KEYBOARD,
		eDEVINPUT_MOUSE,
		eDEVINPUT_JOYSTICK,
		eDEVINPUT_MAX
	};

	//!	���콺 ��ư Ŭ��.
	enum	eMOUSEBTTNCLICK_
	{
		eMOUSEBTTNCLICK_LEFT,
		eMOUSEBTTNCLICK_RIGHT,
		eMOUSEBTTNCLICK_WHEEL
	};

	CPRInput(void)		{ InitMembers(); }
	~CPRInput(void)		{ ClearMembers(); }

	HRESULT	Init( HINSTANCE hInst, HWND hWnd );
	void	FrameMove();
	
	// Mouse ---------------------------------------------------------------------------------
	void	SetMouseSmooth( float fSmooth )				{ m_fMouseSmooth = fSmooth; }
	void	SetMousePos( float fX, float fY )			{ m_MousePos.x = fX; m_MousePos.y = fY; }
	const	D3DXVECTOR3*	GetMouseDelta() const		{ return &m_MouseDelta; }
	const	D3DXVECTOR2*	GetMousePos()	const		{ return &m_MousePos; }
	bool	IsMouseDown( eMOUSEBTTNCLICK_ eClick )		{ return ( m_CurMouseState.rgbButtons[eClick] & 0x80 ) ? true : false; }
	bool	IsMouseUp( eMOUSEBTTNCLICK_ eClick )		{ return ( m_CurMouseState.rgbButtons[eClick] & 0x80 ) ? false : true; }
	bool	IsMouseOneClick( eMOUSEBTTNCLICK_ eClick )	{ return ( m_CurMouseState.rgbButtons[eClick] & 0x80 ) && !(m_PrevMouseState.rgbButtons[eClick] & 0x80) ? true : false; }

	// Keyboard ------------------------------------------------------------------------------
	bool	IsKeyDown( DWORD dwKey )			{ return ( m_byCurKeyboardState[dwKey] & 0x80 ) ? true : false; }
	bool	IsKeyUp( DWORD dwKey )				{ return ( m_byCurKeyboardState[dwKey] & 0x80 ) ? false : true; }
	bool	IsKeyOneClick( DWORD dwKey )		{ return ( m_byCurKeyboardState[dwKey] & 0x80 ) && !( m_byPrevKeyboardState[dwKey] & 0x80 ) ? true : false; }



private:
	void	InitMembers();
	void	ClearMembers();

	LPDIRECTINPUT8			m_pInput;
	LPDIRECTINPUTDEVICE8	m_pDevInput[eDEVINPUT_MAX];	//	�Է� ����̽�.

	BYTE			m_byCurKeyboardState[DX_COUNTKEYS],	//	Ű���� ���°� _ ����
					m_byPrevKeyboardState[DX_COUNTKEYS];//				  _ ����

	DIMOUSESTATE	m_CurMouseState,		//	���콺 ���°� _ ����
					m_PrevMouseState;		//				  _ ����
	D3DXVECTOR2		m_MousePos;				//	���콺 ������ ��ġ.
	D3DXVECTOR3		m_MouseDelta;			//	���콺 �̵���.
	float			m_fMouseSmooth;			//	���콺 ����.
	float			m_fMouseZAxisSmooth;	//	���콺 Z�� ����.(�ٹ�ư)

};

#define gPRInput		CREATESINGLETON( CPRInput )
#define gPRInputDestroy	DESTROYSINGLETON( CPRInput )



#endif	//	_PRINPUT_H_