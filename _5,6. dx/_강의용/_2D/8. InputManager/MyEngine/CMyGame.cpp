//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()
{
	memset(m_tszMouseMsg, 0, sizeof(m_tszMouseMsg));
	memset(m_tszKbdMsg, 0, sizeof(m_tszKbdMsg));
	
}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	if (FAILED(m_dxTxtrTest.Create(m_pD3DDevice, "texture/myfamily.jpg")))
		return -1;

	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("궁서체"), 20, FW_BOLD)))
	//if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("굴림체"), 20, FW_LIGHT)))
		return E_FAIL;

	m_pInputManager = new CInputManager();

	m_pInputManager->Create(m_hWnd);
	
	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	RECT rt;
	//	이미지 영역
	m_dxTxtrTest.GetImageRect(&rt);
	LPDIRECT3DTEXTURE9 pTxTmp = m_dxTxtrTest.GetTexture();

	//	이미지 너비 & 높이
	D3DXVECTOR3	vcCenter((LONG)m_dxTxtrTest.GetImageWidth() * 0.5f, (LONG)m_dxTxtrTest.GetImageHeight() * 0.5f, 0);
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_pD3DSprite->Draw(pTxTmp, &rt, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));

	//	폰트 출력.
	m_dxFont.Draw(m_pD3DSprite, _T("우리 가족 입니다 ^^"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	if (m_pInputManager)
	{
		//	마우스 버튼
		memset(m_tszMouseMsg, 0, sizeof(m_tszMouseMsg));
		m_dxFont.Draw(m_pD3DSprite, _T("현재 클릭한 마우스 버튼 : "), 0, 50, 300, 50, D3DXCOLOR(0, 0, 0, 1), DT_LEFT);
		if (m_pInputManager->BtnPress(0))
		{
			sprintf(m_tszMouseMsg, "마우스 왼쪽 버튼 클릭!!");
			m_dxFont.Draw(m_pD3DSprite, m_tszMouseMsg, 280, 50, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
		}
		
		if (m_pInputManager->BtnPress(1))
		{
			sprintf(m_tszMouseMsg, "마우스 우측 버튼 클릭!!");
			m_dxFont.Draw(m_pD3DSprite, m_tszMouseMsg, 280, 50, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
		}

		if (m_pInputManager->BtnPress(2))
		{
			sprintf(m_tszMouseMsg, "마우스 가운데 버튼 클릭!!");
			m_dxFont.Draw(m_pD3DSprite, m_tszMouseMsg, 280, 50, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
		}
				
		//	키보드
		memset(m_tszKbdMsg, 0, sizeof(m_tszKbdMsg));
		int curIdx = 0;
		for (curIdx = 0; curIdx < 256; ++curIdx)
		{
			if (m_pInputManager->KeyDown(curIdx))
			{
				sprintf(m_tszKbdMsg, "Key Down : %c / %d", curIdx, curIdx);
				m_dxFont.Draw(m_pD3DSprite, m_tszKbdMsg, 280, 350, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			}
		}
		
		for (curIdx = 0; curIdx < 256; ++curIdx)
		{
			if (m_pInputManager->KeyUp(curIdx))
			{
				sprintf(m_tszKbdMsg, "Key Up : %c / %d", curIdx, curIdx);
				m_dxFont.Draw(m_pD3DSprite, m_tszKbdMsg, 280, 450, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			}
		}
		
		for (curIdx = 0; curIdx < 256; ++curIdx)
		{
			if (m_pInputManager->KeyPress(curIdx))
			{
				sprintf(m_tszKbdMsg, "Key Press : %c / %d", curIdx, curIdx);
				m_dxFont.Draw(m_pD3DSprite, m_tszKbdMsg, 280, 400, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			}
		}

		//	마우스 좌표		
		sprintf(m_tszMouseMsg, "마우스 좌표 x : %f, y : %f", m_pInputManager->GetMousePos().x, m_pInputManager->GetMousePos().y);
		m_dxFont.Draw(m_pD3DSprite, m_tszMouseMsg, 0, 100, 500, 50, D3DXCOLOR(1, 0, 1, 1),DT_LEFT);



		static RECT rc = { 0,200,500,130 };
		D3DXVECTOR3	vcEps = m_pInputManager->GetMouseEps();
		rc.top += long(vcEps.z / 40);
		rc.bottom = rc.top + 30;
		sprintf(m_tszMouseWheelMsg, "마우스 이동 옵셋(%.f, %.f, %.f), 휠: %d", vcEps.x, vcEps.y, vcEps.z, rc.top);

		m_dxFont.GetFont()->DrawText(m_pD3DSprite, m_tszMouseWheelMsg, -1, &rc, 0, D3DXCOLOR(0, 0, 1, 1));
		

	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		if (CInputManager::DBLCLK == m_pInputManager->BtnState(0))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("마우스 좌측 버튼 더블 클릭!!"));
			SetWindowText(m_hWnd, sMsg);
		}

		if (CInputManager::DBLCLK == m_pInputManager->BtnState(1))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("마우스 우측 버튼 따블 클릭!!"));
			SetWindowText(m_hWnd, sMsg);
		}

		if (CInputManager::DBLCLK == m_pInputManager->BtnState(2))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("마우스 가운데 버튼 따블 클릭!!"));
			SetWindowText(m_hWnd, sMsg);
		}


	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pInputManager);

	m_dxTxtrTest.Destroy();
	m_dxFont.Destroy();
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pInputManager)
		m_pInputManager->MsgProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
		case WM_PAINT:
		{
			break;
		}
	}

	return CDxCore::MsgProc(hWnd, msg, wParam, lParam);
}