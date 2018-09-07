#include "StdAfx.h"
#include "PRInput.h"
#include "PUtCommon.h"


void CPRInput::InitMembers()
{
	m_pInput	=	NULL;
	for( int nCur = 0; nCur < eDEVINPUT_MAX; ++nCur )
	{
		m_pDevInput[nCur]	=	NULL;
	}
	
	PUT_ZERO_MEMORY( m_byCurKeyboardState );
	PUT_ZERO_MEMORY( m_byPrevKeyboardState );

	PUT_ZERO_MEMORY( m_CurMouseState );
	PUT_ZERO_MEMORY( m_PrevMouseState );

	PUT_ZERO_MEMORY( m_MousePos );
	PUT_ZERO_MEMORY( m_MouseDelta );

	m_fMouseSmooth		=	5.0f;
	m_fMouseZAxisSmooth	=	120.0f;


}//	InitMembers
//--------------------------------------------------------------------------------
void CPRInput::ClearMembers()
{
	for( int nCur = 0; nCur < eDEVINPUT_MAX; ++nCur )
	{
		if( m_pDevInput[nCur] )
		{
			m_pDevInput[nCur]->Unacquire();
			PUT_SAFE_RELEASE( m_pDevInput[nCur] );
		}
	}

	PUT_SAFE_RELEASE( m_pInput );

}//	ClearMembers
//--------------------------------------------------------------------------------
HRESULT	CPRInput::Init( HINSTANCE hInst, HWND hWnd )
{
	//!	Ű���� ���� -------------------

	//!	DirectInput ��ü ����.
	if( DirectInput8Create( hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pInput, NULL ) != DI_OK )
		return E_FAIL;

	//!	Ű���� �Է� ����̽� ����.
	if( m_pInput->CreateDevice( GUID_SysKeyboard, &m_pDevInput[eDEVINPUT_KEYBOARD], NULL) != DI_OK )
		return E_FAIL;

	//!	Ű���� ����̽��� ���� ���� ����.
	if( m_pDevInput[eDEVINPUT_KEYBOARD]->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) != DI_OK )
		return E_FAIL;

	//!	����̽��� ������ ���� ����.
	if( m_pDevInput[eDEVINPUT_KEYBOARD]->SetDataFormat( &c_dfDIKeyboard ) != DI_OK )
		return E_FAIL;

	//����̽� ���� ����� ���.
	if( m_pDevInput[eDEVINPUT_KEYBOARD]->Acquire() != DI_OK )
		return E_FAIL;

	
	//! ���콺 ���� -------------------

	//!	���콺 �Է� ����̽� ����.
	if( m_pInput->CreateDevice( GUID_SysMouse, &m_pDevInput[eDEVINPUT_MOUSE], NULL) != DI_OK )
		return E_FAIL;

	//!	���콺 ����̽��� ���� ���� ����.
	if( m_pDevInput[eDEVINPUT_MOUSE]->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) != DI_OK )
		return E_FAIL;

	//!	����̽��� ������ ���� ����.
	if( m_pDevInput[eDEVINPUT_MOUSE]->SetDataFormat( &c_dfDIMouse ) != DI_OK )
		return E_FAIL;

	//����̽� ���� ����� ���.
	if( m_pDevInput[eDEVINPUT_MOUSE]->Acquire() != DI_OK )
		return E_FAIL;

	return S_OK;

}//	Init
//--------------------------------------------------------------------------------
void	CPRInput::FrameMove()
{
	//! Ű���� ���� ����.
	memcpy( m_byPrevKeyboardState, m_byCurKeyboardState, sizeof(BYTE) * DX_COUNTKEYS );
	if( m_pDevInput[eDEVINPUT_KEYBOARD] && 
		m_pDevInput[eDEVINPUT_KEYBOARD]->GetDeviceState( DX_COUNTKEYS, (LPVOID)m_byCurKeyboardState ) )
	{
		memset( m_byCurKeyboardState, 0, sizeof(BYTE) * DX_COUNTKEYS );
		m_pDevInput[eDEVINPUT_KEYBOARD]->Acquire();
	}

	//! ���콺 ���� ����.
	memcpy( &m_PrevMouseState, &m_CurMouseState, sizeof(DIMOUSESTATE) );
	if( m_pDevInput[eDEVINPUT_MOUSE] &&
		m_pDevInput[eDEVINPUT_MOUSE]->GetDeviceState( sizeof(DIMOUSESTATE), (LPVOID)&m_CurMouseState ) )
	{
		memset( &m_CurMouseState, 0, sizeof(DIMOUSESTATE) );
		m_pDevInput[eDEVINPUT_MOUSE]->Acquire();
	}

	//!	���콺 �̵���.
	D3DXVECTOR3	CurMouseDelta	=	D3DXVECTOR3( (float)m_CurMouseState.lX, 
												 (float)m_CurMouseState.lY, 
												 (float)m_CurMouseState.lZ / m_fMouseZAxisSmooth );
//	PUTOutputDebugStr("CurMouseDelta lX = %f, lY = %f, lZ = %f\n", CurMouseDelta.x, CurMouseDelta.y, CurMouseDelta.z );

	float	fRevMouseSmooth		=	1.0f / m_fMouseSmooth;

	if( IsMouseDown( eMOUSEBTTNCLICK_LEFT ) ||
		IsMouseDown( eMOUSEBTTNCLICK_RIGHT ) ||
		IsMouseDown( eMOUSEBTTNCLICK_WHEEL ) )
		m_MouseDelta	=	m_MouseDelta * ( 1.0f - fRevMouseSmooth ) + CurMouseDelta * fRevMouseSmooth;
	else
		m_MouseDelta	=	CurMouseDelta;

}//	FrameMove
//--------------------------------------------------------------------------------