//============================================
#include "Global.h"
#define MOVEOFFSET 0.25f
//============================================
CMyGame::CMyGame()
{
	ZeroMemory(m_tszMessage, sizeof(m_tszMessage));

}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	m_pDxTexture1 = new CDxTexture;
	if (FAILED(m_pDxTexture1->Create(m_pD3DDevice, "texture/myfamily.jpg", 0xFF000000, D3DFMT_A8R8G8B8)))
		return -1;

	//m_pDxTexture1->SetColor(0.0f, 1.0f, 0.0f);
	m_pDxTexture1->SetMono();

	m_pDxTexture2 = new CDxTexture;
	if (FAILED(m_pDxTexture2->Create(m_pD3DDevice, "texture/myfamily.jpg", 0xFF000000, D3DFMT_A1R5G5B5)))
		return -1;
	
		
	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("궁서체"), 20, FW_BOLD)))	
		return E_FAIL;
	
	m_vec3Pos1 = D3DXVECTOR2(150, 30);
	m_vec3Pos2 = D3DXVECTOR2(450, 30);

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	m_pDxSpriteManager->Begin();
	
	RECT	rc;

	m_pDxTexture1->GetImageRect(&rc);
	m_pDxSpriteManager->Draw(m_pDxTexture1->GetTexture(), &rc, NULL, NULL, 0, &m_vec3Pos1, D3DXCOLOR(1, 1, 1, 1));

	m_pDxTexture2->GetImageRect(&rc);
	m_pDxSpriteManager->Draw(m_pDxTexture2->GetTexture(), &rc, NULL, NULL, 0, &m_vec3Pos2, D3DXCOLOR(1, 1, 1, 1));

	//	폰트 출력.
	m_dxFont.Draw(m_pDxSpriteManager->GetSprite(), _T("fps 테스트"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	
	m_dxFont.Draw(m_pDxSpriteManager->GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	sprintf(m_tszMessage, _T("%d 바이트"), m_pDxTexture1->GetBytePerPixel());
	m_dxFont.Draw(m_pDxSpriteManager->GetSprite(), m_tszMessage, m_vec3Pos1.x, m_vec3Pos1.y + 450, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	sprintf(m_tszMessage, _T("%d 바이트"), m_pDxTexture2->GetBytePerPixel());
	m_dxFont.Draw(m_pDxSpriteManager->GetSprite(), m_tszMessage, m_vec3Pos2.x, m_vec3Pos2.y + 450, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	m_pDxSpriteManager->End();
	
	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();
		
		

	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pDxTexture1);
	SAFE_DELETE(m_pDxTexture2);

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