//============================================
#include "Global.h"
#define MOVEOFFSET 0.25f
//============================================
// ���� ����ü
struct SVtxD
{
	//-------------------------------
	D3DXVECTOR3 _pos;	// ���� ��ġ
	float _u, _v;		//	�ؽ��� ��ǥ.
	//-------------------------------
	SVtxD()	{ ZeroMemory(this, sizeof(this)); }
	//-------------------------------	
	SVtxD( D3DXVECTOR3 pos, float u, float v )
	{
		_pos = pos;
		_u = u;
		_v = v;
	}
	//-------------------------------
};
#define D3DFVF_CUSTOM ( D3DFVF_XYZ | D3DFVF_TEX1 )
//============================================
CMyGame::CMyGame()
{
	ZeroMemory(m_tszMessage, sizeof(m_tszMessage));
	m_pGrid = NULL;
	m_pTex = NULL;

}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT	CMyGame::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(m_pD3DDevice, "texture/myfamily.jpg", true);

	return S_OK;
}
//============================================
HRESULT	CMyGame::InitVB()
{
	SVtxD vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[0]._u = 0.0f;
	vtx[0]._v = 1.0f;

	vtx[1]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[1]._u = 0.0f;
	vtx[1]._v = 0.0f;

	vtx[2]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[2]._u = 1.0f;
	vtx[2]._v = 1.0f;
	
	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._u = 1.0f;
	vtx[3]._v = 0.0f;

	// �������۸� �����Ѵ�.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(4 * sizeof(SVtxD)
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
	
}//	HRESULT	CMyGame::InitVB()
//============================================
void CMyGame::SetMatrix()
{
	//---------------------------------
	// ���� ��ȯ
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY( &matWorld, timeGetTime()/500.0f );	// ȸ�����
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);			// ����̽��� ���� ����� �����Ѵ�.

}//	void CMyGame::SetMatrix()
//============================================
INT	CMyGame::Init()
{		
	if (FAILED(m_pDxFont->Create(m_pD3DDevice, _T("�ü�ü"), 20, FW_BOLD)))
		return E_FAIL;
	
	InitVB();

	InitTexture();

	m_pGrid = new CDxGrid();
	m_pGrid->Create(m_pD3DDevice);

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

	//	�׸��� ����.
	m_pGrid->FrameMove();
	m_pGrid->Render();
	
	//	
	SetMatrix();
	
	// ���� �������� ���� Ȯ��.
	DWORD dCullMode = 0;
	m_pD3DDevice->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// �������� ��Ȱ��ȭ
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	m_pD3DDevice->SetTexture(0, m_pTex->GetTexture());

	// ������ ����̽��� ����
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(SVtxD));
	// ���� ������ ����
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOM);
	// ������
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���� ���� ���� ����.
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, dCullMode);
	
	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		m_pDxCamera->FrameMove();
		
	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{	
	m_pDxFont->Destroy();

	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pTex);
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