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

	/*	버텍스 버퍼 생성.		
		-	3개의 버텍스 데이터를 관리할 메모리 할당.
		-	FVF를 지정하여 데이터의 형식을 설정.
	*/
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(
		3 * sizeof(CUSTOMVERTEX),	//	생성할 정점버퍼의 크기.
		0,							//	리소스 사용방법 설정.	
		D3DFVF_CUSTOMVERTEX,		//	정점 포맷( FVF )형식.
		D3DPOOL_DEFAULT,			//	정점 버퍼가 저장될 메모리 위치( 비디오 카드, 시스템 메모리 )와 관리방식 설정.
									//	D3DPOOL_DEFAULT		:	가장 적합한 메모리풀로 설정.
									//	D3DPOOL_MANAGED		:	비디오 카드
									//	D3DPOOL_SYSTEMMEM	:	시스템 메모리
		/*
		비디오 메모리에 생성되는 경우.
		-	GPU에 의해 정점 셰이더, T&L등 강력한 하드웨어 가속을 사용할 수 있음.
		-	비디오 카드 자체의 메모리 용량을 벗어날 순 없음.

		시스템 메모리에 생성되는 경우.
		-	하드웨어 가속 사용 불가.
		-	메모리 용량이 비디오 메모리에 비해 상대적으로 풍부함.
		*/


		&m_pVB,						//	반환될 정점버퍼.
		NULL)))						//	예약값, 현재는 NULL
		return E_FAIL;

	VOID* pVertices;

	//	버텍스 버퍼의 메모리에 대한 독점(외부 접근 차단)과 버텍스버퍼의 포인터 획득
	if (FAILED(m_pVB->Lock
	(
		0,					//	독점하려는 정점 정보의 옵셋값.
		sizeof(vertices),	//						사이즈	->	정점 버퍼 전체를 잠그려면 옵셋값과 사이즈를 모두 0으로 지정.
		(void**)&pVertices,	//	버텍스 버퍼의 포인터를 반환 받을 포인터
		0					//	독점시 적용하려는 플래그.
	)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();


	return S_OK;
}
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

	//	정점 버퍼를 디바이스의 데이터 스트림(연속적인 데이터 흐름)에 연결.
	m_pD3DDevice->SetStreamSource(
		0,			//	정점 버퍼를 연결할 스트림 소스 지정, 다중스트림을 안쓸거면 0으로 한다.
		m_pVB,		//	스트림을 연결할 정점 버퍼의 포인터
		0,			//	렌더링 파이프 라인으로 보내질 정점 버퍼의 옵셋, 일반적으로 0으로 함.
		sizeof(CUSTOMVERTEX)	//	정점 버퍼 한덩어리의 크기.
	);
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLELIST,		//	그리기 타입 설정
		0,						//	시작 버텍스의 인덱스
		1						//	렌더링하는 기본 도형의 수.
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