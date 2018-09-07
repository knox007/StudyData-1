//============================================
#include "Global.h"
#define MOVEOFFSET 0.25f
//============================================
// 정점 구조체
struct SVtxD
{
	//-------------------------------
	D3DXVECTOR3	_pos;		// 위치
	DWORD	_color;			// 색상
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
	// 세 정점을 선언과 동시에 정의
	SVtxD vtx[3];

	vtx[0] = SVtxD(-1.0f, -1.0f, 0.0f, 0xffff0000);
	vtx[1] = SVtxD(1.0f, -1.0f, 0.0f, 0xff0000ff);
	vtx[2] = SVtxD(0.0f, 1.0f, 0.0f, 0xff00ff00);


	// 정점버퍼를 생성한다.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(3 * sizeof(SVtxD)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// 정점데이터를 채운다.
	// Lock은 현재의 독점을 유지
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
	if (FAILED(m_pDxFont->Create(m_pD3DDevice, _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;
	
	InitVB();

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	m_pDxSpriteManager->Begin();

	//	폰트 출력.
	m_pDxFont->Draw(m_pDxSpriteManager->GetSprite(), _T("fps 테스트"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(m_pDxSpriteManager->GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	m_pDxSpriteManager->End();


	//	컬링을 끈다.
	//	D3DCULL_CW			:	시계방향을 컬링
	//	D3DCULL_CCW(디폴트)	:	시계 반대 방향을 컬링
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//	라이팅을 끈다.
	//	노멀 벡터가 있어야 연산이 된다.( D3DFVF_NORMAL )
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 정점을 디바이스에 연결
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(SVtxD));
	// 정점 포멧을 설정
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOM);
	// 렌더링
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
			// Lock에서 두번째를 0으로하면 데이터 전부를 가져오게 된다.
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
			// Lock에서 두번째를 0으로하면 데이터 전부를 가져오게 된다.
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
			// Lock에서 두번째를 0으로하면 데이터 전부를 가져오게 된다.
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
			// Lock에서 두번째를 0으로하면 데이터 전부를 가져오게 된다.
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirDown;
			pvtx[1]._pos += dirDown;
			pvtx[2]._pos += dirDown;

			m_pVB->Unlock();
		}
		
		
#else
		//---------------------------------
		//	월드 변환.
		//---------------------------------
		//	스케일 변환.
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
		D3DXMATRIX	mtScl;	// 스케일 행렬
		D3DXMatrixScaling(&mtScl, vcS.x, vcS.y, vcS.z);

		//	회전 변환.
		//	Degree 값으로 주어지면 Radian으로 바꾼다.
		if (m_pInputManager->KeyPress('1'))
			_rotY += 0.05f;
		else if (m_pInputManager->KeyPress('2'))
			_rotY += 0.05f;

		//	dx는 Radian 으로 회전 처리.
		float fRadian = D3DXToRadian(_rotY);
		//	Y축에 대한 회전 행렬을 구한다.
		D3DXMATRIX mtRot;	// 회전 행렬
		D3DXMatrixRotationY(&mtRot, fRadian);


		D3DXMATRIX mtTrn;	// 이동 행렬
		if (m_pInputManager->KeyPress(VK_RIGHT))
			_pos.x += 0.01f;
		else if (m_pInputManager->KeyPress(VK_LEFT))
			_pos.x -= 0.01f;

		if (m_pInputManager->KeyPress(VK_UP))
			_pos.y += 0.01f;
		else if (m_pInputManager->KeyPress(VK_DOWN))
			_pos.y -= 0.01f;

		D3DXMatrixTranslation(&mtTrn, _pos.x, _pos.y, _pos.z);


		D3DXMATRIX mtWld;	// 최종 월드 행렬
		mtWld = mtScl * mtRot * mtTrn;

		m_pD3DDevice->SetTransform(D3DTS_WORLD, &mtWld);
		//---------------------------------
#endif
		//---------------------------------
		// 뷰 변환
		//---------------------------------		
		D3DXMATRIX mtViw;
		D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);						// 카메라의 위치
		D3DXVECTOR3 vLookAt(0.0f, 0.0f, 0.0f);						// 카메라가 보고 있는 지점
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);						// 카메라의 업 벡터
		D3DXMatrixLookAtLH(&mtViw, &vEyePt, &vLookAt, &vUpVec);		// 뷰 행렬 만들기

		m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtViw);				// 디바이스의 뷰 행렬 설정



		//---------------------------------
		// 투영 변환
		//---------------------------------
		D3DXMATRIX m_mtPrj;
		FLOAT	fScreenW = (FLOAT)800;
		FLOAT	fScreenH = (FLOAT)600;
		FLOAT	fFOV = D3DX_PI / 4.0f;	//	fov가 커지면
										//	-	화면에 표현되는 오브젝트수 증가( 어안렌즈, 물고기 눈 )
										//	-	어지러움 정도가 심해짐.

										//	fov가 작으면
										//	-	화면에 표현되는 오브젝트수 줄어듬.
										//	-	어지러움 정도가 적어짐.

		FLOAT	fAspect = fScreenW / fScreenH;
		FLOAT	fNear = 1.f;
		FLOAT	fFar = 5000.f;

		D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);	// 투영 행렬 만들기
		m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_mtPrj);				// 디바이스의 투영 행렬을 설정


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