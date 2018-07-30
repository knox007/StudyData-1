//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
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
	
	Mouse_Pos[1024] = NULL;
	Key_Text[1024] = NULL;
	Mouse_Z = 0;

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
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f + Mouse_Z, 0);
	m_pD3DSprite->Draw(pTxTmp, &rt, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));

	//	폰트 출력.
	m_dxFont.Draw(m_pD3DSprite, _T("우리 가족 입니다 ^^"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_dxFont.Draw(m_pD3DSprite, _T(Mouse_Pos), m_pInputManager->GetMousePos().x + 10, m_pInputManager->GetMousePos().y + 10, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_dxFont.Draw(m_pD3DSprite, _T(Key_Text), 0, 50, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		for (int i = 0; i < MAX_INPUT_KEY; i++) {
			if (m_pInputManager->KeyDown(i)) {
				sprintf(Key_Text, "%c", i);
			}
		}
	
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

		sprintf(Mouse_Pos, _T("%f %f"), m_pInputManager->GetMousePos().x, m_pInputManager->GetMousePos().y);
		
		//Mouse_Z = m_pInputManager->GetMouseEps().z;
		D3DXVECTOR3	vcEps = m_pInputManager->GetMouseEps();
		Mouse_Z += vcEps.z / 10;
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