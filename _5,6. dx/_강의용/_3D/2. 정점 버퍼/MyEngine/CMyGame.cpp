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
HRESULT CMyGame::InitVB()
{
	CUSTOMVERTEX vertices[] =
	{
		{ 150.0f, 50.0f, 0.5f, 1.0f, 0xffff0000,},	//	x, y, z, rhw, color
		{ 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
		{ 50.0f, 250.0f, 0.5f, 1.0f, 0xff0000ff, },
	};

	/*	���ؽ� ���� ����.		
		-	3���� ���ؽ� �����͸� ������ �޸� �Ҵ�.
		-	FVF�� �����Ͽ� �������� ������ ����.
	*/
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(
		3 * sizeof(CUSTOMVERTEX),	//	������ ���������� ũ��.
		0,							//	���ҽ� ����� ����.	
		D3DFVF_CUSTOMVERTEX,		//	���� ����( FVF )����.
		D3DPOOL_DEFAULT,			//	���� ���۰� ����� �޸� ��ġ( ���� ī��, �ý��� �޸� )�� ������� ����.
									//	D3DPOOL_DEFAULT		:	���� ������ �޸�Ǯ�� ����.
									//	D3DPOOL_MANAGED		:	���� ī��
									//	D3DPOOL_SYSTEMMEM	:	�ý��� �޸�
		/*
		���� �޸𸮿� �����Ǵ� ���.
		-	GPU�� ���� ���� ���̴�, T&L�� ������ �ϵ���� ������ ����� �� ����.
		-	���� ī�� ��ü�� �޸� �뷮�� ��� �� ����.

		�ý��� �޸𸮿� �����Ǵ� ���.
		-	�ϵ���� ���� ��� �Ұ�.
		-	�޸� �뷮�� ���� �޸𸮿� ���� ��������� ǳ����.
		*/


		&m_pVB,						//	��ȯ�� ��������.
		NULL)))						//	���ప, ����� NULL
		return E_FAIL;

	VOID* pVertices;

	//	���ؽ� ������ �޸𸮿� ���� ����(�ܺ� ���� ����)�� ���ؽ������� ������ ȹ��
	if (FAILED(m_pVB->Lock
	(
		0,					//	�����Ϸ��� ���� ������ �ɼ°�.
		sizeof(vertices),	//						������	->	���� ���� ��ü�� ��׷��� �ɼ°��� ����� ��� 0���� ����.
		(void**)&pVertices,	//	���ؽ� ������ �����͸� ��ȯ ���� ������
		0					//	������ �����Ϸ��� �÷���.
	)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();


	return S_OK;
}
//============================================
INT		CMyGame::Init()
{		
	if (FAILED(m_pDxFont->Create(m_pD3DDevice, _T("�ü�ü"), 20, FW_BOLD)))
		return E_FAIL;
	
	InitVB();

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	m_pDxSpriteManager->Begin();

	//	��Ʈ ���.
	m_pDxFont->Draw(m_pDxSpriteManager->GetSprite(), _T("fps �׽�Ʈ"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(m_pDxSpriteManager->GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	m_pDxSpriteManager->End();

	//	���� ���۸� ����̽��� ������ ��Ʈ��(�������� ������ �帧)�� ����.
	m_pD3DDevice->SetStreamSource(
		0,			//	���� ���۸� ������ ��Ʈ�� �ҽ� ����, ���߽�Ʈ���� �Ⱦ��Ÿ� 0���� �Ѵ�.
		m_pVB,		//	��Ʈ���� ������ ���� ������ ������
		0,			//	������ ������ �������� ������ ���� ������ �ɼ�, �Ϲ������� 0���� ��.
		sizeof(CUSTOMVERTEX)	//	���� ���� �ѵ���� ũ��.
	);
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLELIST,		//	�׸��� Ÿ�� ����
		0,						//	���� ���ؽ��� �ε���
		1						//	�������ϴ� �⺻ ������ ��.
	);

	
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
	SAFE_RELEASE(m_pVB);
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pInputManager)
		m_pInputManager->MsgProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case ID_TOGGLE_SCREEN:
			{
				Reset3D();
				return 0;
			}
		}
		break;
	}
		
	
	}//	switch (msg)

	return CDxCore::MsgProc(hWnd, msg, wParam, lParam);

}//	LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//============================================
HRESULT	CMyGame::Restore()
{
	return S_OK;

}//	HRESULT	CMyGame::Restore()
//============================================
void	CMyGame::Invalidate() {  }
//============================================