// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pLcSprite	= NULL;
	m_pInput	= NULL;
	m_pD3DXFont	= NULL;

	m_pTxSrc[0]	= NULL;
	m_pTxSrc[1]	= NULL;
	m_pTxSrc[2]	= NULL;
}


HRESULT CMain::Init()
{
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



	m_pTxSrc[0]	= new CLcTexture;
	if( FAILED(m_pTxSrc[0]->Create(m_pd3dDevice, "Texture/lenna.jpg", 0xFF000000, D3DFMT_R3G3B2)))
		return -1;

	m_pTxSrc[1]	= new CLcTexture;
	if( FAILED(m_pTxSrc[1]->Create(m_pd3dDevice, "Texture/lenna.jpg", 0xFF000000, D3DFMT_X1R5G5B5)))
		return -1;

	m_pTxSrc[2]	= new CLcTexture;
	if( FAILED(m_pTxSrc[2]->Create(m_pd3dDevice, "Texture/lenna.jpg", 0xFF000000, D3DFMT_R8G8B8)))
		return -1;


	return 0;
}


HRESULT CMain::Destroy()
{
	SAFE_DELETE(	m_pLcSprite	);
	SAFE_DELETE(	m_pInput	);
	SAFE_RELEASE(	m_pD3DXFont	);

	for(int i=0; i<3; ++i)
	{
		SAFE_DELETE(	m_pTxSrc[i]	);
	}

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

	LPDIRECT3DTEXTURE9	pTx = NULL;
	D3DSURFACE_DESC		dsc;
	D3DLOCKED_RECT		rc;

	INT		Pitch = 0;
	INT		nByte = 0;

	for(int i=0; i<3; ++i)
	{
		pTx = m_pTxSrc[i]->GetTexture();

		pTx->GetLevelDesc(0, &dsc);				// 텍스처 정보 얻기

		pTx->LockRect(0, &rc, NULL, 0);			// 텍스처 픽셀 정보 얻기

		INT		Pitch = rc.Pitch;

		nByte = Pitch/dsc.Width;				// 1픽셀당 바이트 계산

		if(4==nByte)							// 32Bit
		{
			DWORD*  pARGB = (DWORD*)rc.pBits;
			m_nBit[i] = 32;
		}

		else if(2 == nByte)						// 16 Bit
		{
			WORD*  pARGB = (WORD*)rc.pBits;
			m_nBit[i] = 16;
		}

		else if(1 == nByte)						// 8 Bit
		{
			BYTE*  pARGB = (BYTE*)rc.pBits;
			m_nBit[i] = 8;
		}

		pTx->UnlockRect(0);
	}

	return 0;
}


HRESULT CMain::Render()
{
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	char	sMsg[1024]={0};
	
	for(int i=0; i<3; ++i)
	{
		m_pLcSprite->Draw(
						m_pTxSrc[i]->GetTexture()
						, &m_pTxSrc[i]->GetImageRect()
						, NULL
						, NULL
						, 0
						, &D3DXVECTOR2( 260.f *i, 100)
						, D3DXCOLOR(1,1,1,1));

		RECT	rc;
		rc.left	= 260*i; rc.right	= rc.left +100;
		rc.top	=80;	 rc.bottom	= rc.top + 30;
	
		sprintf(sMsg, "%d 비트", m_nBit[i]);
		m_pD3DXFont->DrawText(NULL, sMsg, -1, &rc, 0, D3DXCOLOR(0,1,1,1));
	}

	RECT	rt	= { 5, 5, m_dScnW-10, 30};
	
	sprintf(sMsg, "FPS: %.f", m_fFps);
	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rt, 0, D3DXCOLOR(1,1,0,1));


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