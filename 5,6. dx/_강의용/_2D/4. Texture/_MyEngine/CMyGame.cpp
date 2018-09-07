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
		m_pD3DDevice				//	디바이스 포인터
		, "texture/myfamily.jpg"	//	텍스쳐 경로
		,284
		,426
		//, D3DX_DEFAULT			//	가로
									//	0 이나 D3DX_DEFAULT 일경우 강제로 해당값보다 큰 2의 지수값으로 만든다.
		//, D3DX_DEFAULT			//	세로
		, 1							//	밉맵 레벨*( 문서 참고 )
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE			//	필터링
		, D3DX_FILTER_NONE			//	밉 필터링
		, 0							//	컬러키
		, &m_d3DImageInfo			//	텍스쳐 정보
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
	m_pD3DTxtr	:	텍스쳐.

	rt1			:	출력할 소스 영역.
					NULL이면 전체 영역.
	vcCenter	:	스프라이트의 피벗(기준점) 설정.
					NULL이면 (0,0,0), 좌상단이 기준점
	pPosition	:	스프라이트의 위치.
					vcCenter을 기준으로 이동.
					NULL이면 vcCenter을 (0,0,0)으로 이동시킴. 

	*/

	m_pD3DSprite->Draw(m_pD3DTxtr, &rt1, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));
	//	m_pD3DSprite->Draw(m_pD3DTxtr, NULL, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));		//	출력영역 NULL
	//	m_pD3DSprite->Draw(m_pD3DTxtr, NULL, NULL, &vcPos, D3DXCOLOR(1, 1, 1, 1));			//					피벗 NULL
	//	m_pD3DSprite->Draw(m_pD3DTxtr, NULL, NULL, NULL, D3DXCOLOR(1, 1, 1, 1));			//								위치 NULL
	//	m_pD3DSprite->Draw(m_pD3DTxtr, &rt1, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 0.5f));	//											색상 변경( 알파값 0.5 적용 )

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