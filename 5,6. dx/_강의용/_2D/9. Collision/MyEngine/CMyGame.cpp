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
	m_pDxTexture1 = new CDxTexture;
	if (FAILED(m_pDxTexture1->Create(m_pD3DDevice, "texture/A.png")))
		return -1;

	m_pDxTexture2 = new CDxTexture;
	if (FAILED(m_pDxTexture2->Create(m_pD3DDevice, "texture/B.png")))
		return -1;
	
	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	m_vec3Pos1 = D3DXVECTOR3(150, 30, 0);
	m_vec3Pos2 = D3DXVECTOR3(400, 300,0);
	
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

	//	폰트 출력.
	m_dxFont.Draw(m_pD3DSprite, _T("박스충돌 테스트"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		D3DXVECTOR3 tmpPos = m_vec3Pos1;

		//--------------------------------------
		//	컨트롤
		if (m_pInputManager->KeyPress(VK_RIGHT))
			tmpPos.x += MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_LEFT))
			tmpPos.x -= MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_UP))
			tmpPos.y -= MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_DOWN))
			tmpPos.y += MOVEOFFSET;

		//--------------------------------------
		//	충돌영역 설정
		RECT rcCol1;
		SetRect(&rcCol1, INT(tmpPos.x)
			, INT(tmpPos.y)
			, INT(tmpPos.x) + m_pDxTexture1->GetImageWidth()
			, INT(tmpPos.y) + m_pDxTexture1->GetImageHeight()
		);

		RECT rcCol2;
		SetRect(&rcCol2, INT(m_vec3Pos2.x)
			, INT(m_vec3Pos2.y)
			, INT(m_vec3Pos2.x) + m_pDxTexture2->GetImageWidth()
			, INT(m_vec3Pos2.y) + m_pDxTexture2->GetImageHeight()
		);
		
		//--------------------------------------
		//	충돌 체크
		bool isCollision = false;
		
		if (rcCol1.left <= rcCol2.right &&
			rcCol1.right >= rcCol2.left  &&

			rcCol1.top <= rcCol2.bottom &&
			rcCol1.bottom >= rcCol2.top)
		{
			isCollision = true;
			SetWindowText(m_hWnd, "충돌!!!");
		}

		//--------------------------------------
		//	충돌 결과에 따른 동작설정.
		if (!isCollision)
		{
			SetWindowText(m_hWnd, "방향키를 누르면 박스가 움직입니다.");
			m_vec3Pos1 = tmpPos;
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