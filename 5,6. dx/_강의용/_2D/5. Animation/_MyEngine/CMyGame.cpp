//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{ 
	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pD3DDevice				//	����̽� ������
		, "texture/myfamily.jpg"	//	�ؽ��� ���
		
		, D3DX_DEFAULT				//	����, 0 �̳� D3DX_DEFAULT �ϰ�� �ؽ��� ����� ����.
		, D3DX_DEFAULT				//	����
		, 1							//	�Ӹ� ����*( ���� ���� )
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE			//	���͸�
		, D3DX_FILTER_NONE			//	�� ���͸�
		, 0							//	�÷�Ű
		, &m_tInfoBG.m_imageInfo			//	�ؽ��� ����
		, NULL
		, &m_tInfoBG.m_d3dTxtr
	)))
	{
		MessageBox(NULL, "myfamily.jpg file Could not be found", "Err", 0);
		m_tInfoBG.m_d3dTxtr = NULL;
		return -1;
	}
	
	SetRect(&m_tInfoBG.m_rcImage, 0, 0, m_tInfoBG.m_imageInfo.Width, m_tInfoBG.m_imageInfo.Height);


	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pD3DDevice				//	����̽� ������
		, "Texture/animate.bmp"

		, D3DX_DEFAULT				//	����, 0 �̳� D3DX_DEFAULT �ϰ�� �ؽ��� ����� ����.
		, D3DX_DEFAULT				//	����
		, 1							//	�Ӹ� ����*( ���� ���� )
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE			//	���͸�
		, D3DX_FILTER_NONE			//	�� ���͸�
		, 0xFF000000							//	�÷�Ű
		, &m_tInfoAni.m_imageInfo			//	�ؽ��� ����
		, NULL
		, &m_tInfoAni.m_d3dTxtr
	)))
	{
		MessageBox(NULL, "animate.bmp file Could not be found", "Err", 0);
		m_tInfoAni.m_d3dTxtr = NULL;
		return -1;
	}

	SetRect(&m_tInfoAni.m_rcImage, 0, 0, 0, 32);

	m_dwBeginTime = timeGetTime();	//	�ü���� ���۵��� ����� �ð�.

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::FrameMove()
{
	m_dwEndTime = timeGetTime();

	if ((m_dwEndTime - m_dwBeginTime) > FRAME_REFRESH_TIME)
	{
		m_tInfoAni.m_rcImage.left += 32;

		if (m_tInfoAni.m_rcImage.left + 32 >= 960)
			m_tInfoAni.m_rcImage.left = 0;

		m_tInfoAni.m_rcImage.right = m_tInfoAni.m_rcImage.left + 32;

		m_dwBeginTime = m_dwEndTime;
	
	}//	if ((m_dwEndTime - m_dwBeginTime) > FRAME_REFRESH_TIME)

	m_vecAniPos = D3DXVECTOR3( cosf(D3DX_PI*m_dwBeginTime*0.0001f), sinf(D3DX_PI*m_dwBeginTime*0.0003f), 0.0F );

	m_vecAniPos *= 100.0f;

	m_vecAniPos += D3DXVECTOR3(300, 300, 0.F);
	
	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
INT		CMyGame::Render()
{
	m_pD3DSprite->Draw(m_tInfoBG.m_d3dTxtr, &m_tInfoBG.m_rcImage, &D3DXVECTOR3(m_tInfoBG.m_imageInfo.Width*0.5f, m_tInfoBG.m_imageInfo.Height*0.5f, 0), &D3DXVECTOR3(m_dwScrWidth*0.5f, m_dwScrHeight*0.5f, 0), D3DXCOLOR(1, 1, 1, 1));
	m_pD3DSprite->Draw(m_tInfoAni.m_d3dTxtr, &m_tInfoAni.m_rcImage, NULL, &m_vecAniPos, D3DXCOLOR(1, 1, 1, 1));

	return 0;

}//	INT		CMyGame::Render()
//============================================
void	CMyGame::Destroy()
{
	SAFE_RELEASE(m_tInfoBG.m_d3dTxtr);
	SAFE_RELEASE(m_tInfoAni.m_d3dTxtr);

}//	void	CMyGame::Destroy()
//============================================
//*
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_PAINT:		
		{			
			break;
		}
	}

	return CDxCore::MsgProc(hWnd, msg, wParam, lParam);
}
//*/
//============================================