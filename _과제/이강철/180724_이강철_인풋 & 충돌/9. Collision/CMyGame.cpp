//============================================
#include "Global.h"
//============================================
#define MOVEOFFSET	2.25F
//============================================
CMyGame::CMyGame()
{
	
}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	srand((unsigned)time(NULL));

	m_pDxTexture1 = new CDxTexture;
	if (FAILED(m_pDxTexture1->Create(m_pD3DDevice, "texture/A2.png")))
		return -1;

	m_pDxTexture2 = new CDxTexture;
	if (FAILED(m_pDxTexture2->Create(m_pD3DDevice, "texture/B2.png")))
		return -1;

	m_pDxTexture3 = new CDxTexture;
	if (FAILED(m_pDxTexture3->Create(m_pD3DDevice, "texture/C2.png")))
		return -1;
	
	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	m_vec3Pos1 = D3DXVECTOR3(50, 50, 0);
	m_vec3Pos2 = D3DXVECTOR3(150, 150,0);
	m_vec3Pos3 = D3DXVECTOR3(300, 300, 0);
	
	m_pInputManager = new CInputManager();
	m_pInputManager->Create(m_hWnd);
	
	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	RECT	rc;

	m_pDxTexture1->GetImageRect(&rc);	
	m_pD3DSprite->Draw(m_pDxTexture1->GetTexture(), &rc, NULL, &m_vec3Pos1, D3DXCOLOR(1, 1, 1, 1));

	m_pDxTexture2->GetImageRect(&rc);
	m_pD3DSprite->Draw(m_pDxTexture2->GetTexture(), &rc, NULL, &m_vec3Pos2, D3DXCOLOR(1, 1, 1, 1));

	m_pDxTexture3->GetImageRect(&rc);
	m_pD3DSprite->Draw(m_pDxTexture3->GetTexture(), &rc, NULL, &m_vec3Pos3, D3DXCOLOR(1, 1, 1, 1));

	//	폰트 출력.
	m_dxFont.Draw(m_pD3DSprite, _T("박스충돌 테스트"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return 0;

}//	INT		CMyGame::Render()
//============================================

BOOL GAME_FLAG = FALSE;

INT		CMyGame::FrameMove()
{
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();
		//--------------------------------------
		//	컨트롤
		if (m_pInputManager->KeyPress(VK_RIGHT)) 
			m_vec3Pos1.x += MOVEOFFSET;
		
		if (m_pInputManager->KeyPress(VK_LEFT)) 
			m_vec3Pos1.x -= MOVEOFFSET;
	
		if (m_pInputManager->KeyPress(VK_UP)) 
			m_vec3Pos1.y -= MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_DOWN)) 
			m_vec3Pos1.y += MOVEOFFSET;
		//--------------------------------------
		//	충돌영역 설정
		RECT rcTemp;
		RECT rcCol1;
		SetRect(&rcCol1, INT(m_vec3Pos1.x)
			, INT(m_vec3Pos1.y)
			, INT(m_vec3Pos1.x) + m_pDxTexture1->GetImageWidth()
			, INT(m_vec3Pos1.y) + m_pDxTexture1->GetImageHeight()
		);

		RECT rcCol2;
		SetRect(&rcCol2, INT(m_vec3Pos2.x)
			, INT(m_vec3Pos2.y)
			, INT(m_vec3Pos2.x) + m_pDxTexture2->GetImageWidth()
			, INT(m_vec3Pos2.y) + m_pDxTexture2->GetImageHeight()
		);

		RECT rcCol3;
		SetRect(&rcCol3, INT(m_vec3Pos3.x)
			, INT(m_vec3Pos3.y)
			, INT(m_vec3Pos3.x) + m_pDxTexture3->GetImageWidth()
			, INT(m_vec3Pos3.y) + m_pDxTexture3->GetImageHeight()
		);
		
		if (IntersectRect(&rcTemp, &rcCol1, &rcCol2)) {
			SetWindowText(m_hWnd, "충돌!!!");
			int rcTemp_W = rcTemp.right - rcTemp.left;
			int rcTemp_H = rcTemp.bottom - rcTemp.top;
			if (rcTemp_W > rcTemp_H) {
				if (rcTemp.top == rcCol2.top) {
					m_vec3Pos2.y += MOVEOFFSET;
				} else if (rcTemp.bottom == rcCol2.bottom) {
					m_vec3Pos2.y -= MOVEOFFSET;
				}
			} else {
				if (rcTemp.right == rcCol2.right) {
					m_vec3Pos2.x -= MOVEOFFSET;
				} else if (rcTemp.left == rcCol2.left) {
					m_vec3Pos2.x += MOVEOFFSET;
				}
			}
		} else {
			SetWindowText(m_hWnd, "방향키를 누르면 박스가 움직입니다.");
		}

		if (IntersectRect(&rcTemp, &rcCol2, &rcCol3)) {
			m_vec3Pos3.x = (rand() % 500);
			m_vec3Pos3.y = (rand() % 500);
		}
	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pDxTexture1);
	SAFE_DELETE(m_pDxTexture2);

	SAFE_DELETE(m_pInputManager);

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