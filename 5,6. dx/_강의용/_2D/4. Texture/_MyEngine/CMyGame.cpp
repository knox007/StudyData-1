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
		,284
		,426
		//, D3DX_DEFAULT			//	����
									//	0 �̳� D3DX_DEFAULT �ϰ�� ������ �ش簪���� ū 2�� ���������� �����.
		//, D3DX_DEFAULT			//	����
		, 1							//	�Ӹ� ����*( ���� ���� )
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE			//	���͸�
		, D3DX_FILTER_NONE			//	�� ���͸�
		, 0							//	�÷�Ű
		, &m_d3DImageInfo			//	�ؽ��� ����
		, NULL
		, &m_pD3DTxtr
	)))
	{
		MessageBox(NULL, "myfamily.jpg file Could not be found", "Err", 0);
		m_pD3DTxtr = NULL;
		return -1;
	}

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{	
	RECT	rt1 = { 0, 0, (LONG)m_d3DImageInfo.Width, (LONG)m_d3DImageInfo.Height };
	D3DXVECTOR3	vcCenter((LONG)m_d3DImageInfo.Width * 0.5f, (LONG)m_d3DImageInfo.Height * 0.5f, 0);
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);

	/*
	m_pD3DTxtr	:	�ؽ���.

	rt1			:	����� �ҽ� ����.
					NULL�̸� ��ü ����.
	vcCenter	:	��������Ʈ�� �ǹ�(������) ����.
					NULL�̸� (0,0,0), �»���� ������
	pPosition	:	��������Ʈ�� ��ġ.
					vcCenter�� �������� �̵�.
					NULL�̸� vcCenter�� (0,0,0)���� �̵���Ŵ. 

	*/

	m_pD3DSprite->Draw(m_pD3DTxtr, &rt1, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));
	//	m_pD3DSprite->Draw(m_pD3DTxtr, NULL, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));		//	��¿��� NULL
	//	m_pD3DSprite->Draw(m_pD3DTxtr, NULL, NULL, &vcPos, D3DXCOLOR(1, 1, 1, 1));			//					�ǹ� NULL
	//	m_pD3DSprite->Draw(m_pD3DTxtr, NULL, NULL, NULL, D3DXCOLOR(1, 1, 1, 1));			//								��ġ NULL
	//	m_pD3DSprite->Draw(m_pD3DTxtr, &rt1, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 0.5f));	//											���� ����( ���İ� 0.5 ���� )

	return 0;
}
//============================================
INT		CMyGame::FrameMove()	{ return 0; }
//============================================
void	CMyGame::Destroy()
{
	SAFE_RELEASE(m_pD3DTxtr);

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