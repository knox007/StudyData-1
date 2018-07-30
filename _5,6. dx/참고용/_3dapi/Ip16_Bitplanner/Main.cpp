// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


void McColor_TransColorBitPlanner(DWORD* pOut, DWORD* pIn, INT iImgW, INT iImgH, INT nBit)
{
	for(int y=0; y<iImgH; ++y)
	{
		for(int x=0; x<iImgW; ++x)
		{
			int nIdx = y*iImgW + x;

			D3DXCOLOR xclr = pIn[nIdx];

			DWORD r = DWORD(xclr.r * 255);
			DWORD g = DWORD(xclr.g * 255);
			DWORD b = DWORD(xclr.b * 255);

			r >>= (8-nBit);
			g >>= (8-nBit);
			b >>= (8-nBit);

			r <<= (8-nBit);
			g <<= (8-nBit);
			b <<= (8-nBit);

			pOut[nIdx] = D3DXCOLOR(r/255.f, g/255.f, b/255.f, 1.f);
		}
	}
}



CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;
	m_pD3DXFont	= NULL;

	m_pTxSrc	= NULL;
	m_pTxDst	= NULL;
}


HRESULT CMain::Init()
{
	HRESULT hr=0;

	m_pLcSprite = new CLcSprite;
	if(FAILED(m_pLcSprite->Create(m_pd3dSprite)))
		return -1;

	m_pInput = new CLcInput;
	if( FAILED(m_pInput->Create(m_hWnd)))
		return -1;

	D3DXFONT_DESC hFont =
	{
		14, 0
		, FW_BOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, "����ü"
	};

	D3DXCreateFontIndirect(GDEVICE, &hFont, &m_pD3DXFont);



	m_pTxSrc	= new CLcTexture;
	if( FAILED(m_pTxSrc->Create(m_pd3dDevice, "Texture/lenna.jpg", 0xFF000000)))
		return -1;

	int		nImgW	= m_pTxSrc->GetSurfaceWidth();
	int		nImgH	= m_pTxSrc->GetSurfaceHeight();

	DWORD*	pColorSrc= NULL;
	DWORD*	pColorDst= NULL;


	// ���� �ؽ�ó ũ��� ������ Image Processing �� �ؽ�ó ����
	m_pTxDst	= new CLcTexture;
	if( FAILED(m_pTxDst->Create(m_pd3dDevice
											, nImgW
											, nImgH
											, 1
											, m_pTxSrc->GetSurfaceFormat()
											, 0
											)))
		return -1;
		

	
	// Image Processing...
	pColorSrc = (DWORD*)m_pTxSrc->LockRect();
	pColorDst = (DWORD*)m_pTxDst->LockRect();

	McColor_TransColorBitPlanner(pColorDst, pColorSrc, nImgW, nImgH, 2);

	m_pTxDst->UnlockRect();
	m_pTxSrc->UnlockRect();


	return 0;
}


HRESULT CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);
	SAFE_RELEASE(	m_pD3DXFont	);

	SAFE_DELETE(	m_pTxSrc	);
	SAFE_DELETE(	m_pTxDst	);


	return 0;
}


HRESULT CMain::Restore()
{
	m_pD3DXFont->OnResetDevice();

	return 0;
}


HRESULT CMain::Invalidate()
{
	m_pD3DXFont->OnLostDevice();
	return 0;
}


HRESULT CMain::FrameMove()
{
	SAFE_FRMMOV(	m_pInput	);

	return 0;
}


HRESULT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	char	sMsg[1024]={0};
	RECT	rc;
	
	// ���� �÷� �̹���
	m_pLcSprite->Draw(m_pTxSrc->GetTexture()
					, &m_pTxSrc->GetImageRect()
					, NULL
					, NULL
					, 0
					, &D3DXVECTOR2(25, 50), 0Xffffffff);


	//��� �̹���
	m_pLcSprite->Draw(m_pTxDst->GetTexture()
					, &m_pTxDst->GetImageRect()
					, NULL
					, NULL
					, 0
					, &D3DXVECTOR2(300, 50), 0Xffffffff);


	

	SetRect(&rc, 100, 30, m_dScnW-10, 60);
	sprintf(sMsg, "��ȯ ��                            ��ȯ ��");
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rc, 0, D3DXCOLOR(0,1,1,1));



	SetRect(&rc, 5, 5, m_dScnW-10, 30);
	sprintf(sMsg, "FPS: %.f", m_fFps);
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rc, 0, D3DXCOLOR(1,1,0,1));


	m_pd3dDevice->EndScene();

	return 0;
}


LRESULT CMain::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(m_pInput)
		m_pInput->MsgProc(hWnd, msg, wParam, lParam);
	
	switch( msg )
	{
		case WM_PAINT:
		{
			break;
		}
	}

	return CD3DApp::MsgProc( hWnd, msg, wParam, lParam );
}