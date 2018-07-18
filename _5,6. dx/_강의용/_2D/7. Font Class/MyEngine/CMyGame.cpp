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

	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("����ü"), 20)))
		return E_FAIL;
	
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

	m_dxFont.DrawText(_T("��Ű¯"), 20, 20, 100, 30, D3DXCOLOR(1, 1, 0, 1));

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()	{ return 0; }
//============================================
void	CMyGame::Destroy()
{
	m_dxTxtrTest.Destroy();
	m_dxFont.Destroy();
}
//============================================