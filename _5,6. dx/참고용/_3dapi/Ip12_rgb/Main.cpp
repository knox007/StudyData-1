// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


void McColor_ColorRed(DWORD* pOut, DWORD* pIn, INT iImgW, INT iImgH)
{
	for(int y=0; y<iImgH; ++y)
	{
		for(int x=0; x<iImgW; ++x)
		{
			int nIdx = y*iImgW + x;

			D3DXCOLOR xclr = pIn[nIdx];

			xclr.r *= 1.f;
			xclr.g *= 0.f;
			xclr.b *= 0.f;

			pOut[nIdx] = xclr;
		}
	}
}



CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;
	m_pD3DXFont	= NULL;

	m_pTxSrc	= NULL;
	m_pTxMono	= NULL;
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
		, "굴림체"
	};

	D3DXCreateFontIndirect(GDEVICE, &hFont, &m_pD3DXFont);



	m_pTxSrc	= new CLcTexture;
	if( FAILED(m_pTxSrc->Create(m_pd3dDevice, "Texture/lenna.jpg", 0xFF000000)))
		return -1;


	LPDIRECT3DTEXTURE9 pTx = m_pTxSrc->GetTexture();
	D3DSURFACE_DESC dsc;
	D3DLOCKED_RECT	drc;
	DWORD*	pColorSrc= NULL;
	DWORD*	pColorDst= NULL;

	
	// 원본 텍스처 정보 얻기
	pTx->GetLevelDesc(0, &dsc);

	int		nImgW	= dsc.Width;
	int		nImgH	= dsc.Height;


	// 원본 이미지 크기와 동일한 Image Processing 할 텍스처 생성
	hr = D3DXCreateTexture(m_pd3dDevice
					, m_pTxSrc->GetImageWidth()
					, m_pTxSrc->GetImageHeight()
					, 1, 0
					, dsc.Format, D3DPOOL_MANAGED, &m_pTxMono);

	if(FAILED(hr))
		return -1;

	

	// 임시 버퍼 생성
	pColorSrc	= new DWORD[nImgW * nImgH];


	// 원본 텍스처 픽셀 값을 임시 버퍼에 복사
	pTx->LockRect(0, &drc, NULL, 0);
		memcpy(pColorSrc, drc.pBits, nImgW * nImgH * sizeof(DWORD));
	pTx->UnlockRect(0);


	
	// Image Processing...
	m_pTxMono->LockRect(0, &drc, NULL, 0);

		pColorDst = (DWORD*)drc.pBits;
		McColor_ColorRed(pColorDst, pColorSrc, nImgW, nImgH);

	m_pTxMono->UnlockRect(0);


	// 임시 버퍼 해제
	delete [] pColorSrc;


	return 0;
}


HRESULT CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);
	SAFE_RELEASE(	m_pD3DXFont	);

	SAFE_DELETE(	m_pTxSrc	);
	SAFE_RELEASE(	m_pTxMono	);


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
	
	// 원본 컬러 이미지
	m_pLcSprite->Draw(m_pTxSrc->GetTexture()
					, &m_pTxSrc->GetImageRect()
					, NULL
					, NULL
					, 0
					, &D3DXVECTOR2(25, 50), 0Xffffffff);


	//흑백 이미지
	m_pLcSprite->Draw(m_pTxMono
					, &m_pTxSrc->GetImageRect()
					, NULL
					, NULL
					, 0
					, &D3DXVECTOR2(300, 50), 0Xffffffff);


	

	SetRect(&rc, 100, 30, m_dScnW-10, 60);
	sprintf(sMsg, "변환 전                            변환 후");
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