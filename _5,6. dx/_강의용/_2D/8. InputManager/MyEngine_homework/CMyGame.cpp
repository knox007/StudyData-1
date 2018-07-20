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

	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("�ü�ü"), 20, FW_BOLD)))
	//if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("����ü"), 20, FW_LIGHT)))
		return E_FAIL;

	m_pInputManager = new CInputManager();

	m_pInputManager->Create(m_hWnd);
	
	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	RECT rt;
	//	�̹��� ����
	m_dxTxtrTest.GetImageRect(&rt);
	LPDIRECT3DTEXTURE9 pTxTmp = m_dxTxtrTest.GetTexture();

	//	�̹��� �ʺ� & ����
	D3DXVECTOR3	vcCenter((LONG)m_dxTxtrTest.GetImageWidth() * 0.5f, (LONG)m_dxTxtrTest.GetImageHeight() * 0.5f, 0);
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_pD3DSprite->Draw(pTxTmp, &rt, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));

	//	��Ʈ ���.
	m_dxFont.Draw(m_pD3DSprite, _T("�츮 ���� �Դϴ� ^^"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

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
			sprintf(sMsg, _T("���콺 ���� ��ư ���� Ŭ��!!"));
			SetWindowText(m_hWnd, sMsg);
		}

		if (CInputManager::DBLCLK == m_pInputManager->BtnState(1))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("���콺 ���� ��ư ���� Ŭ��!!"));
			SetWindowText(m_hWnd, sMsg);
		}

		if (CInputManager::DBLCLK == m_pInputManager->BtnState(2))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("���콺 ��� ��ư ���� Ŭ��!!"));
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