//============================================
#include "Global.h"
#define MOVEOFFSET 0.25f
//============================================
// ���� ����ü
struct SVtxD
{
	//-------------------------------
	D3DXVECTOR3	_pos;		// ��ġ
	DWORD	_color;			// ����
	//-------------------------------
	SVtxD()
	{
		_pos = D3DXVECTOR3(0, 0, 0);
		_color = 0xffffffff;
	}
	//-------------------------------
	SVtxD(float X, float Y, float Z, DWORD COLOR)
	{
		_pos.x = X;
		_pos.y = Y;
		_pos.z = Z;

		_color = COLOR;
	}
	//-------------------------------
	SVtxD(D3DXVECTOR3 P, DWORD COLOR)
	{
		_pos = P;
		_color = COLOR;
	}
	//-------------------------------
};
#define D3DFVF_CUSTOM (D3DFVF_XYZ|D3DFVF_DIFFUSE)
//============================================
CMyGame::CMyGame()
{
	ZeroMemory(m_tszMessage, sizeof(m_tszMessage));

	_scale = 1.0f;
	_rotY = 0.0f;
	_pos = D3DXVECTOR3(0, 0, 0);

}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT	CMyGame::InitVB()
{
	// �� ������ ����� ���ÿ� ����
	SVtxD vtx[3];

	vtx[0] = SVtxD(-1.0f, -1.0f, 0.0f, 0xffff0000);
	vtx[1] = SVtxD(1.0f, -1.0f, 0.0f, 0xff0000ff);
	vtx[2] = SVtxD(0.0f, 1.0f, 0.0f, 0xff00ff00);


	// �������۸� �����Ѵ�.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(3 * sizeof(SVtxD)
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


	//	�ø��� ����.
	//	D3DCULL_CW			:	�ð������ �ø�
	//	D3DCULL_CCW(����Ʈ)	:	�ð� �ݴ� ������ �ø�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//	�������� ����.
	//	��� ���Ͱ� �־�� ������ �ȴ�.( D3DFVF_NORMAL )
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ������ ����̽��� ����
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(SVtxD));
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
		
#if 1
		D3DXVECTOR3 dirLeft(-0.01f, 0, 0);
		D3DXVECTOR3	dirRight(0.01f, 0, 0);
		D3DXVECTOR3	dirUp(0, -0.01f, 0);
		D3DXVECTOR3	dirDown(0, 0.01f, 0);

		if (m_pInputManager->KeyPress(VK_RIGHT))
		{
			SVtxD* pvtx;
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
			SVtxD* pvtx;
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
			SVtxD* pvtx;
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
			SVtxD* pvtx;
			// Lock���� �ι�°�� 0�����ϸ� ������ ���θ� �������� �ȴ�.
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirDown;
			pvtx[1]._pos += dirDown;
			pvtx[2]._pos += dirDown;

			m_pVB->Unlock();
		}
		
		
#else
		//---------------------------------
		//	���� ��ȯ.
		//---------------------------------
		//	������ ��ȯ.
		if (m_pInputManager->KeyPress('q') || m_pInputManager->KeyPress('Q'))
		{
			if (_scale <= 5.0f)
				_scale += 0.01f;
		}
		else if (m_pInputManager->KeyPress('e') || m_pInputManager->KeyPress('E'))
		{
			if (_scale >= 0.05f)
				_scale -= 0.01f;
		}

		D3DXVECTOR3	vcS(_scale, _scale, _scale);
		D3DXMATRIX	mtScl;	// ������ ���
		D3DXMatrixScaling(&mtScl, vcS.x, vcS.y, vcS.z);

		//	ȸ�� ��ȯ.
		//	Degree ������ �־����� Radian���� �ٲ۴�.
		if (m_pInputManager->KeyPress('1'))
			_rotY += 0.05f;
		else if (m_pInputManager->KeyPress('2'))
			_rotY += 0.05f;

		//	dx�� Radian ���� ȸ�� ó��.
		float fRadian = D3DXToRadian(_rotY);
		//	Y�࿡ ���� ȸ�� ����� ���Ѵ�.
		D3DXMATRIX mtRot;	// ȸ�� ���
		D3DXMatrixRotationY(&mtRot, fRadian);


		D3DXMATRIX mtTrn;	// �̵� ���
		if (m_pInputManager->KeyPress(VK_RIGHT))
			_pos.x += 0.01f;
		else if (m_pInputManager->KeyPress(VK_LEFT))
			_pos.x -= 0.01f;

		if (m_pInputManager->KeyPress(VK_UP))
			_pos.y += 0.01f;
		else if (m_pInputManager->KeyPress(VK_DOWN))
			_pos.y -= 0.01f;

		D3DXMatrixTranslation(&mtTrn, _pos.x, _pos.y, _pos.z);


		D3DXMATRIX mtWld;	// ���� ���� ���
		mtWld = mtScl * mtRot * mtTrn;

		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtWld);
		//---------------------------------
#endif
		//---------------------------------
		// �� ��ȯ
		//---------------------------------		
		D3DXMATRIX mtViw;
		D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);						// ī�޶��� ��ġ
		D3DXVECTOR3 vLookAt(0.0f, 0.0f, 0.0f);						// ī�޶� ���� �ִ� ����
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);						// ī�޶��� �� ����
		D3DXMatrixLookAtLH(&mtViw, &vEyePt, &vLookAt, &vUpVec);		// �� ��� �����

		m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtViw);				// ����̽��� �� ��� ����



		//---------------------------------
		// ���� ��ȯ
		//---------------------------------
		D3DXMATRIX m_mtPrj;
		FLOAT	fScreenW = (FLOAT)800;
		FLOAT	fScreenH = (FLOAT)600;
		FLOAT	fFOV = D3DX_PI / 4.0f;	//	fov�� Ŀ����
										//	-	ȭ�鿡 ǥ���Ǵ� ������Ʈ�� ����( ��ȷ���, ����� �� )
										//	-	�������� ������ ������.

										//	fov�� ������
										//	-	ȭ�鿡 ǥ���Ǵ� ������Ʈ�� �پ��.
										//	-	�������� ������ ������.

		FLOAT	fAspect = fScreenW / fScreenH;
		FLOAT	fNear = 1.f;
		FLOAT	fFar = 5000.f;

		D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);	// ���� ��� �����
		m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_mtPrj);				// ����̽��� ���� ����� ����


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