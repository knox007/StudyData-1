//============================================
#include "Global.h"
//============================================
//#define USE_IDXBUFFER
//============================================
CMyGame::CMyGame()
{
	ZeroMemory(m_tszMessage, sizeof(m_tszMessage));
	m_pGrid = NULL;

}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT	CMyGame::InitVB()
{
#ifndef USE_IDXBUFFER
	SVtxDiffuse vtx[6];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[0]._color = 0xff00ff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[2]._color = 0xff00ff00;
	
	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._color = 0xff0000ff;

	vtx[4]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[4]._color = 0xff0000ff;

	vtx[5]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[5]._color = 0xff0000ff;

	// �������۸� �����Ѵ�.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(6 * sizeof(SVtxDiffuse)
		, 0
		, D3DFVF_XYZDIFFUSE
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
#else
	SVtxDiffuse vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[0]._color = 0xff00ff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[2]._color = 0xff00ff00;

	vtx[3]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[3]._color = 0xff0000ff;

	// �������۸� �����Ѵ�.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(4 * sizeof(SVtxDiffuse)
		, 0
		, D3DFVF_XYZDIFFUSE
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

#endif
}//	HRESULT	CMyGame::InitVB()
//============================================
HRESULT	CMyGame::InitIB()
{
	SIdx indices[] =
	{
		{ 0,1,2 },{ 1,3,2 }
	};

	if (FAILED(m_pD3DDevice->CreateIndexBuffer(
		2*sizeof(SIdx),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIB,
		NULL
	)))
	{
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(m_pIB->Lock(
		0,
		sizeof(SIdx),
		(void**)&pIndices,
		0)))
		return E_FAIL;

	memcpy(pIndices, indices, sizeof(indices));

	m_pIB->Unlock();

	return S_OK;

}//	HRESULT	CMyGame::InitIB()
 //============================================
void CMyGame::SetMatrix()
{
	//---------------------------------
	// ���� ��ȯ
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixRotationY( &matWorld, timeGetTime()/500.0f );	// ȸ�����
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);			// ����̽��� ���� ����� �����Ѵ�.

}//	void CMyGame::SetMatrix()
//============================================
INT	CMyGame::Init()
{		
	if (FAILED(m_pDxFont->Create(m_pD3DDevice, _T("�ü�ü"), 20, FW_BOLD)))
		return E_FAIL;
	
	InitVB();
	InitIB();

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
	
	// ������ ����̽��� ����
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(SVtxDiffuse));
	// ���� ������ ����
	m_pD3DDevice->SetFVF(D3DFVF_XYZDIFFUSE);


#ifndef USE_IDXBUFFER
	// ������
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// ���� ���� ���� ����.
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, dCullMode);
#else
	m_pD3DDevice->SetIndices(m_pIB);
	// ������
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
#endif
	
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
	
	SAFE_RELEASE(m_pIB);
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