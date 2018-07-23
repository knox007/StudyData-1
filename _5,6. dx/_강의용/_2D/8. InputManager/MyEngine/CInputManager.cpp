//============================================================
// �ٸ��콺�� ������ �� ������ �ݵ�� �ʿ�.
#define _WIN32_WINNT 0x0400
//============================================================
#include "Global.h"
//============================================================
//------------------------------------
CInputManager::CInputManager()
{
	m_hWnd		= NULL; // for Mouse

	memset(m_kbdBttnOld, 0, sizeof(m_kbdBttnOld));
	memset(m_kbdBttnCur, 0, sizeof(m_kbdBttnCur));
	memset(m_kbdBttnMap, 0, sizeof(m_kbdBttnMap));

	memset(m_mouseBtttnCur, 0, sizeof(m_mouseBtttnCur));
	memset(m_mouseBtttnOld, 0, sizeof(m_mouseBtttnOld));
	memset(m_mouseBtttnMap, 0, sizeof(m_mouseBtttnMap));

	m_vcCur = D3DXVECTOR3( 0, 0, 0);
	m_vcOld = D3DXVECTOR3( 0, 0, 0);
	m_vcEps = D3DXVECTOR3( 0, 0, 0);
	
	m_dTimeDC	= 0;
	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	SetKeyboardState(m_kbdBttnCur);

}//	CInputManager::CInputManager()
//------------------------------------
CInputManager::~CInputManager()	{}
//------------------------------------
INT	CInputManager::Create(HWND hWnd)
{
	m_hWnd		= hWnd;

	memset(m_kbdBttnOld, 0, sizeof(m_kbdBttnOld));
	memset(m_kbdBttnCur, 0, sizeof(m_kbdBttnCur));
	memset(m_kbdBttnMap, 0, sizeof(m_kbdBttnMap));

	memset(m_mouseBtttnCur, 0, sizeof(m_mouseBtttnCur));
	memset(m_mouseBtttnOld, 0, sizeof(m_mouseBtttnOld));
	memset(m_mouseBtttnMap, 0, sizeof(m_mouseBtttnMap));

	m_vcCur = D3DXVECTOR3( 0, 0, 0);
	m_vcOld = D3DXVECTOR3( 0, 0, 0);
	m_vcEps = D3DXVECTOR3( 0, 0, 0);
	
	m_dTimeDC	= GetDoubleClickTime();

	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	m_dBtnBgn[0]	= GetTickCount();

	for(int i=1; i<MAX_INPUT_BTN; ++i)
		m_dBtnBgn[i]	= m_dBtnBgn[0];

	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	UINT ucNumLines=0;  // 3 is the default
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);

	return 0;

}//	INT	CInputManager::Create(HWND hWnd)
//------------------------------------
INT CInputManager::FrameMove()	// Mouse
{
	INT curIdx	= 0;

	// 1. current ���� old�� ����, ���� ���¸� �����Ѵ�.
	memcpy(m_kbdBttnOld, m_kbdBttnCur, sizeof(m_kbdBttnOld));			//	Ű����
	memcpy(m_mouseBtttnOld, m_mouseBtttnCur, sizeof(m_mouseBtttnOld));	//	���콺
	
	// 2. Current �� Map�� ���� 0���� �ʱ�ȭ
	memset(m_kbdBttnCur, 0, sizeof(m_kbdBttnCur));			//	Ű����
	memset(m_kbdBttnMap, 0, sizeof(m_kbdBttnMap));

	memset(m_mouseBtttnCur, 0, sizeof(m_mouseBtttnCur));	//	���콺
	memset(m_mouseBtttnMap, 0, sizeof(m_mouseBtttnMap));
	
	//3. current �̺�Ʈ �� ������
	/*
		1.	VK_LBUTTON ~ VK_OEM_CLEAR������ ���� Ű�ڵ� ���¸� ����.(vs 2017����)

		2.	256���� ������ ������� �ʴ� Ű�ڵ�� ����� Ű�ڵ尡 �־ 
			256���� ���� Ű�ڵ尡 �� ��ȿ���� �ʴ�.( winuser.h ���� )

		3.	��ȯ��.

					|	���� ������		|		ȣ�� ���� ������
			------------------------------------------------------
			0x00	|		X			|			X
			0x01	|		O			|			X
			0x80	|		X			|			O
			0x81	|		O			|			O
	*/
	GetKeyboardState(m_kbdBttnCur);
	
	// Keyboard �� ����
	for(curIdx = 0; curIdx < MAX_INPUT_KEY; ++curIdx)
	{	
		BYTE	vKey = m_kbdBttnCur[curIdx] & 0x80;		//	������ Ű���� ���¸� �о�´�.
															
		m_kbdBttnCur[curIdx] = (vKey)? 1: 0;			// Ű���� ���¸� 0�� 1�� ���Ѵ�.

		INT nOld = m_kbdBttnOld[curIdx];
		INT nCur = m_kbdBttnCur[curIdx];

		if		(0 == nOld && 1 ==nCur)
			m_kbdBttnMap[curIdx] = DOWN;	// Down
		else if (1 == nOld && 0 ==nCur)
			m_kbdBttnMap[curIdx] = UP;		// UP
		else if (1 == nOld && 1 ==nCur)
			m_kbdBttnMap[curIdx] = PRESS;	// PRESS
		else
			m_kbdBttnMap[curIdx] = NONE;	// NONE

	}//	for(curIdx = 0; curIdx < MAX_INPUT_KEY; ++curIdx)

	// Mouse button �� ����
	m_mouseBtttnCur[0] = m_kbdBttnCur[VK_LBUTTON];	// ���콺 ����
	m_mouseBtttnCur[1] = m_kbdBttnCur[VK_RBUTTON];	// ���콺 ������
	m_mouseBtttnCur[2] = m_kbdBttnCur[VK_MBUTTON];	// ���콺 ���

	for(curIdx = 0; curIdx < MAX_INPUT_BTN; ++curIdx)
	{
		INT nOld = m_mouseBtttnOld[curIdx];
		INT nCur = m_mouseBtttnCur[curIdx];

		if		(0 == nOld && 1 ==nCur) m_mouseBtttnMap[curIdx] = DOWN;	// Down
		else if (1 == nOld && 0 ==nCur) m_mouseBtttnMap[curIdx] = UP;	// UP
		else if (1 == nOld && 1 ==nCur) m_mouseBtttnMap[curIdx] = PRESS;	// PRESS
		else							m_mouseBtttnMap[curIdx] = NONE;	// NONE
	}

	// 4. Update Mouse Position
	POINT pt;
	GetCursorPos(&pt);				//	����ȭ����� ���콺 ��ǥ�� ����.
	ScreenToClient(m_hWnd, &pt);	//	m_hWnd�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ.

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;

	m_vcOld = m_vcCur;

	//5. Double Check
	DWORD dBtnCur = GetTickCount();	//	OS������ ������ ������ �ð��� msec ������ ����.

	for(curIdx = 0; curIdx < MAX_INPUT_BTN; ++curIdx)
	{
		//	��ư �ٿ� üũ.
		if(DOWN == m_mouseBtttnMap[curIdx])
		{
			//	���� �����ӿ��� �ѹ� ���ȴ�.
			if( 1== m_dBtnCnt[curIdx])
			{
				//	���� Ŭ�� ���͹� �ð��� �����°�?
				if( (dBtnCur - m_dBtnBgn[curIdx]) >= m_dTimeDC)
				{
					//	ī��Ʈ �ʱ�ȭ.
					m_dBtnCnt[curIdx] = 0;
				}
			}
			
			//	ī��Ʈ ����.
			++m_dBtnCnt[curIdx];

			//	1ȸ ���ȴ°�?
			if(1 == m_dBtnCnt[curIdx])
				m_dBtnBgn[curIdx]	= dBtnCur;	//	���� �ð��� �Ҵ�.

		}//	if(DOWN == m_mouseBtttnMap[curIdx])


		//	��ư �� üũ.
		if(UP == m_mouseBtttnMap[curIdx])
		{
			//	1ȸ ���ȴ°�?
			if( 1== m_dBtnCnt[curIdx])
			{
				//	��� �ð��� �����°�?
				if( (dBtnCur - m_dBtnBgn[curIdx]) >= m_dTimeDC)
					//	ī��Ʈ �ʱ�ȭ.
					m_dBtnCnt[curIdx] = 0;
			}
			//	2ȸ ���ȴ°�?
			else if( 2 == m_dBtnCnt[curIdx])
			{
				//	����ð��� ������ �ʾҴ°�?
				if( (dBtnCur- m_dBtnBgn[curIdx]) <= m_dTimeDC)
					//	���� Ŭ������ ó��.
					m_mouseBtttnMap[curIdx] = DBLCLK;

				//	ī��Ʈ �ʱ�ȭ.
				m_dBtnCnt[curIdx] =0;
			}

		}//	if(UP == m_mouseBtttnMap[curIdx])

	}//	for(curIdx = 0; curIdx < MAX_INPUT_BTN; ++curIdx)

	return 0;

}//	INT CInputManager::FrameMove()	// Mouse
//------------------------------------
BOOL CInputManager::KeyDown(INT nKey)		{ return m_kbdBttnMap[nKey] == DOWN; }
//------------------------------------
BOOL CInputManager::KeyUp(INT nKey)			{ return m_kbdBttnMap[nKey] == UP; }
//------------------------------------
BOOL CInputManager::KeyPress(INT nKey)		{ return m_kbdBttnMap[nKey] == PRESS; }
//------------------------------------
INT CInputManager::KeyState(INT nKey)		{ return m_kbdBttnMap[nKey]; }
//------------------------------------
// Mouse
//------------------------------------
BOOL CInputManager::BtnDown(INT nBtn)		{ return m_mouseBtttnMap[nBtn] == DOWN; }
//------------------------------------
BOOL CInputManager::BtnUp(INT nBtn)			{ return m_mouseBtttnMap[nBtn] == UP; }
//------------------------------------
BOOL CInputManager::BtnPress(INT nBtn)		{ return m_mouseBtttnMap[nBtn] == PRESS; }
//------------------------------------
INT CInputManager::BtnState(INT nBtn)		{ return m_mouseBtttnMap[nBtn]; }
//------------------------------------
D3DXVECTOR3 CInputManager::GetMousePos()	{ return m_vcCur;}
//------------------------------------
D3DXVECTOR3 CInputManager::GetMouseEps()	{ return m_vcEps; }
//------------------------------------
LRESULT CInputManager::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		//	#define _WIN32_WINNT 0x0400 ó�� �ʿ�.
		case WM_MOUSEWHEEL:
		{
			INT wheelOffset = HIWORD(wParam);			

			wheelOffset = short(wheelOffset);
			m_vcCur.z += FLOAT(wheelOffset);
			break;

		}//	case WM_MOUSEWHEEL:

	}//	switch( msg )

	return 0;

}//	LRESULT CInputManager::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
//------------------------------------