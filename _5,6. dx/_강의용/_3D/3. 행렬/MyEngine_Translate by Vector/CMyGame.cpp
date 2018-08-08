//============================================
#include "Global.h"
#define MOVEOFFSET 0.25f
//============================================
// ���� ����ü
struct SVtxRHWD
{
	//-------------------------------
	D3DXVECTOR3	_pos;		// ��ġ
	float	_rhw;			// reciprocal homogeneous w
	DWORD	_color;			// ����
	//-------------------------------
	SVtxRHWD() {}
	SVtxRHWD(float X, float Y, float Z, float RHW, DWORD COLOR)
	{
		_pos.x = X;
		_pos.y = Y;
		_pos.z = Z;

		_rhw = RHW;
		_color = COLOR;
	}
	//-------------------------------
	SVtxRHWD(D3DXVECTOR3 P, float RHW, DWORD COLOR)
	{
		_pos = P;
		_rhw = RHW;
		_color = COLOR;
	}
	//-------------------------------
};
#define D3DFVF_CUSTOM (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
//============================================
CMyGame::CMyGame()
{
	ZeroMemory(m_tszMessage, sizeof(m_tszMessage));

}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT	CMyGame::InitVB()
{
	// �� ������ ����� ���ÿ� ����
	SVtxRHWD vtx[3];

	vtx[0] = SVtxRHWD(250.0f, 50.0f, 0.5f, 1.0f, 0xffff0000);
	vtx[1] = SVtxRHWD(350.0f, 250.0f, 0.5f, 1.0f, 0xff0000ff);
	vtx[2] = SVtxRHWD(150.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00);


	// �������۸� �����Ѵ�.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(3 * sizeof(SVtxRHWD)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// ���������͸� ä���.
	// Lock�� ������ ������ ����
	void* pvtx;
	if (FAILED(m_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	m_pVB->Unlock();

	return S_OK;

}//	HRESULT	CMyGame::InitVB()
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


	// ������ ����̽��� ����
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(SVtxRHWD));
	// ���� ������ ����
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOM);
	// ������
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	
	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();
		
		D3DXVECTOR3 dirLeft(-0.5f, 0, 0);
		D3DXVECTOR3	dirRight(0.5f, 0, 0);
		D3DXVECTOR3	dirUp(0, -0.5f, 0);
		D3DXVECTOR3	dirDown(0, 0.5f, 0);

		if (m_pInputManager->KeyPress(VK_RIGHT))
		{
			SVtxRHWD* pvtx;
			// Lock���� �ι�°�� 0�����ϸ� ������ ���θ� �������� �ȴ�.
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirRight;
			pvtx[1]._pos += dirRight;
			pvtx[2]._pos += dirRight;			

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_LEFT))
		{
			SVtxRHWD* pvtx;
			// Lock���� �ι�°�� 0�����ϸ� ������ ���θ� �������� �ȴ�.
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirLeft;
			pvtx[1]._pos += dirLeft;
			pvtx[2]._pos += dirLeft;
			
			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_UP))
		{
			SVtxRHWD* pvtx;
			// Lock���� �ι�°�� 0�����ϸ� ������ ���θ� �������� �ȴ�.
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirUp;
			pvtx[1]._pos += dirUp;
			pvtx[2]._pos += dirUp;
			
			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_DOWN))
		{
			SVtxRHWD* pvtx;
			// Lock���� �ι�°�� 0�����ϸ� ������ ���θ� �������� �ȴ�.
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirDown;
			pvtx[1]._pos += dirDown;
			pvtx[2]._pos += dirDown;
			
			m_pVB->Unlock();
		}

	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{	
	m_pDxFont->Destroy();
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