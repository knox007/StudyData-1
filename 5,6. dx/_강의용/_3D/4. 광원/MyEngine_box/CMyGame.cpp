//============================================
#include "Global.h"
#define MOVEOFFSET 0.25f
//============================================
// 정점 구조체
struct SVtxNor
{
	//-------------------------------
	D3DXVECTOR3 _pos;	// 정점 위치
	D3DXVECTOR3 _nor;	// 라이팅이 적용되기 위해서는 법선벡터는 필수.
	//-------------------------------
	SVtxNor()	{ _pos = _nor = D3DXVECTOR3(0, 0, 0); }
	//-------------------------------	
	SVtxNor( D3DXVECTOR3 pos, D3DXVECTOR3 nor )
	{
		_pos = pos;
		_nor = nor;
	}
	//-------------------------------
};
#define D3DFVF_CUSTOM ( D3DFVF_XYZ | D3DFVF_NORMAL )
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
	SVtxNor vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[0]._nor = D3DXVECTOR3(0, 0, -1);

	vtx[1]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[1]._nor = D3DXVECTOR3(0, 0, -1);

	vtx[2]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[2]._nor = D3DXVECTOR3(0, 0, -1);
	
	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._nor = D3DXVECTOR3(0, 0, -1);

	// 정점버퍼를 생성한다.
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(4 * sizeof(SVtxNor)
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

	
}
/*
HRESULT	CMyGame::InitVB()
{
	// 정점버퍼를 생성한다.	
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(50*2 * sizeof(SVtxNor)
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
	SVtxNor* pVtxNor;
	if (FAILED(m_pVB->Lock(0, 0, (void**)&pVtxNor, 0)))
		return E_FAIL;

	for (int cur = 0; cur<50; cur++)
	{
		FLOAT theta = (2 * D3DX_PI*cur) / (50 - 1);
		pVtxNor[2 * cur + 0]._pos = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));
		pVtxNor[2 * cur + 0]._nor = D3DXVECTOR3(sinf(theta), 0.0f, cosf(theta));

		pVtxNor[2 * cur + 1]._pos = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));
		pVtxNor[2 * cur + 1]._nor = D3DXVECTOR3(sinf(theta), 0.0f, cosf(theta));
	}


	m_pVB->Unlock();

	return S_OK;

}//	HRESULT	CMyGame::InitVB()
*/
//============================================
void CMyGame::SetMatrix()
{
	//---------------------------------
	// 월드 변환
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY( &matWorld, timeGetTime()/500.0f );	// 회전행렬
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);			// 디바이스의 월드 행렬을 설정한다.

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

}//	void CMyGame::SetMatrix()
//============================================
void CMyGame::SetMaterial()
{
	/*	재질	:	반사되는 빛의 성질을 결정
		속성	:	디퓨즈(확산광)
					엠비언트(주변광),
					Specular(반사광),
					power(반사광의 강도를 조절)
	*/

	D3DMATERIAL9 mtrl = { 0 };
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	
	m_pD3DDevice->SetMaterial(&mtrl);

}//	void CMyGame::SetMaterial()
//============================================
void CMyGame::SetLight()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	memset(&light, 0, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;	//	종류.
	light.Diffuse.r = 1.0f;				//	색상.
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	
	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f), 1.0f, sinf(timeGetTime() / 350.0f));

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;	// 광원 유효 범위.

	m_pD3DDevice->SetLight(0, &light);

	m_pD3DDevice->LightEnable(0, TRUE);

	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00004444);	// 주변 광원 설정.

}//	void CMyGame::SetLight()
//============================================
INT	CMyGame::Init()
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


	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	m_pD3DDevice->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// 정점을 디바이스에 연결
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(SVtxNor));
	// 정점 포멧을 설정
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOM);
	// 렌더링
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 은면 제거 상태 복구.
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
		
		SetMatrix();

		SetMaterial();

		SetLight();

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