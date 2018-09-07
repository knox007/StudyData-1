//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{ 
	TCHAR* m_TexName[] =
	{
		_T("Texture/mario_cloud.png")	,
		_T("Texture/mario_bush2.png")	,
		_T("Texture/mario_bush1.png")	,
		_T("Texture/mario_tile1.png")	,
		_T("Texture/mario_all.png")		,
		_T(""),

	};

	HRESULT hResult = E_FAIL;
	int		curIdx = 0;

	while (m_TexName[curIdx] &&	0 < strlen(m_TexName[curIdx]) )
	{
		hResult = D3DXCreateTextureFromFileEx(
			m_pD3DDevice			// 디바이스 포인터
			, m_TexName[curIdx]		// 텍스처 이름
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_NONE
			, D3DX_FILTER_NONE
			//, 0x00FFFFFF			// 컬러 키
			,0
			, &m_Img[curIdx]		// 텍스처 인포메이션
			, NULL
			, &m_Tex[curIdx]		// 텍스처 포인터
		);


		if (FAILED(hResult))
		{
			MessageBox(m_hWnd, "Texture Create Failed", "Err", 0);
			return -1;

		}// if (FAILED(hResult))

		++curIdx;

	}//	while (m_TexName[curIdx] &&	0 < strlen(m_TexName[curIdx]) )
	
	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{	

	RECT	rcCloud1 = { 0,0, 136, 128 };
	m_pD3DSprite->Draw(m_Tex[0]
		, &rcCloud1
		, NULL
		, &D3DXVECTOR3(200, 50, 0)
		, D3DXCOLOR(1, 1, 1, 1));

	RECT	rcCloud2 = { 144,0, 336, 128 };
	m_pD3DSprite->Draw(m_Tex[0]
		, &rcCloud2
		, NULL
		, &D3DXVECTOR3(500, 50, 0)
		, D3DXCOLOR(1, 1, 1, 1));


	// 나무2를 그린다.
	RECT	rcBush1 = { 0,0, m_Img[1].Width, m_Img[1].Height };
	m_pD3DSprite->Draw(m_Tex[1]
		, &rcBush1
		, NULL
		, &D3DXVECTOR3(100, 286, 0)
		, D3DXCOLOR(1, 1, 1, 1));

	m_pD3DSprite->Draw(m_Tex[1]
		, &rcBush1
		, NULL
		, &D3DXVECTOR3(700, 286, 0)
		, D3DXCOLOR(1, 1, 1, 1));

	// 나무1을 그린다.
	RECT	rcBush2 = { 0,0, m_Img[2].Width, m_Img[2].Height };

	m_pD3DSprite->Draw(m_Tex[2]
		, &rcBush2
		, NULL
		, &D3DXVECTOR3(-50, 400, 0)
		, D3DXCOLOR(1, 1, 1, 1));

	m_pD3DSprite->Draw(m_Tex[2]
		, &rcBush2
		, NULL
		, &D3DXVECTOR3(300, 400, 0)
		, D3DXCOLOR(1, 1, 1, 1));

	m_pD3DSprite->Draw(m_Tex[2]
		, &rcBush2
		, NULL
		, &D3DXVECTOR3(600, 400, 0)
		, D3DXCOLOR(1, 1, 1, 1));


	// 바닥을 그린다.
	RECT	rcTile1 = { 0,0, m_Img[3].Width, m_Img[3].Height };
	RECT	rcTile2 = { 0,66, m_Img[3].Width, m_Img[3].Height };

	for (int i = 0; i<7; ++i)
	{
		m_pD3DSprite->Draw(m_Tex[3]
			, &rcTile1
			, NULL
			, &D3DXVECTOR3(i* m_Img[3].Width* 1.f, 440.f, 0)
			, D3DXCOLOR(1, 1, 1, 1));

		m_pD3DSprite->Draw(m_Tex[3]
			, &rcTile2
			, NULL
			, &D3DXVECTOR3(i* m_Img[3].Width* 1.f, 550, 0)
			, D3DXCOLOR(1, 1, 1, 1));
	}

	// 마리오를 그린다.
	FLOAT		fX1 = m_Img[4].Width / 8.f  * (1 + 0);
	FLOAT		fY1 = m_Img[4].Height / 4.f * (3 + 0);

	FLOAT		fX2 = m_Img[4].Width / 8.f  * (1 + 1);
	FLOAT		fY2 = m_Img[4].Height / 4.f * (3 + 1);


	RECT	rcMario = { LONG(fX1), LONG(fY1), LONG(fX2), LONG(fY2) };
	m_pD3DSprite->Draw(m_Tex[4]
		, &rcMario
		, NULL
		, &D3DXVECTOR3(500, 362, 0)
		, D3DXCOLOR(1, 1, 1, 1));

	return 0;
}
//============================================
INT		CMyGame::FrameMove()	{ return 0; }
//============================================
void	CMyGame::Destroy()
{
	int		curIdx = 0;	
	while (m_Tex[curIdx])
	{
		SAFE_RELEASE(m_Tex[curIdx]);
		++curIdx;
	}

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