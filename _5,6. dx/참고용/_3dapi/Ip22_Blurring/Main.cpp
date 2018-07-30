// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


FLOAT	g_MaskBlurRect3X3[][3] =
{
	{  1/9.f,  1/9.f,  1/9.f},
	{  1/9.f,  1/9.f,  1/9.f},
	{  1/9.f,  1/9.f,  1/9.f},
};


FLOAT	g_MaskBlurCircular5X5[][5] =
{
	{    0.f,  1/21.f,  1/21.f,  1/21.f,    0.f},
	{ 1/21.f,  1/21.f,  1/21.f,  1/21.f,  1/21.f},
	{ 1/21.f,  1/21.f,  1/21.f,  1/21.f,  1/21.f},
	{ 1/21.f,  1/21.f,  1/21.f,  1/21.f,  1/21.f},
	{    0.f,  1/21.f,  1/21.f,  1/21.f,    0.f},
};


// Triangular Mask
//		FLOAT	g_MaskBlurTriangular5X5[][5] =
//		{
//			{  1,  2,  3,  2,  1},
//			{  2,  4,  6,  4,  2},
//			{  3,  6,  9,  6,  3},
//			{  2,  4,  6,  4,  2},
//			{  1,  2,  3,  2,  1},
//		};
//
//		/ 81.f


// Pyramidal Mask
//		FLOAT	g_MaskBlurPyramidal5X5[][5] =
//		{
//			{  0,  0,  1,  0,  0},
//			{  0,  2,  2,  2,  0},
//			{  1,  2,  5,  2,  1},
//			{  0,  2,  2,  2,  0},
//			{  0,  0,  1,  0,  0},
//		};
//
//		/ 25.f




void McColor_TransColorMaskBluring(DWORD* pOut, DWORD* pIn, INT iImgW, INT iImgH, FLOAT* fMask, INT iMskW)
{
	int y=0;
	int x=0;


	for(y=0; y<iImgH; ++y)
	{
		for(int x=0; x<iImgW; ++x)
		{
			INT nBgnX=-1;	INT nEndX= 1;
			INT nBgnY=-1;	INT nEndY= 1;

			if(0==y)
			{
				nBgnY = 0;

				if(0==x)
				{
					nBgnX = 0;
					nEndX = 1;
				}

				else if( (iImgW-1) == x)
				{
					nBgnX = -1;
					nEndX = 0;
				}
			}

			else if( (iImgH-1)==y)
			{
				nEndY = 0;

				if(0==x)
				{
					nBgnX = 0;
					nEndX = 1;
				}

				else if( (iImgW-1) == x)
				{
					nBgnX = -1;
					nEndX = 0;
				}
			}

			FLOAT r = 0.F;
			FLOAT g = 0.F;
			FLOAT b = 0.F;
			float fMsk = 0.f;
			int nIdx = y * iImgW + x;
			
			for(int nMskY=nBgnY; nMskY<=nEndY; ++nMskY)
			{
				for(int nMskX=nBgnX; nMskX<=nEndX; ++nMskX)
				{
					D3DXCOLOR xClr = pIn[ (y+nMskY) * iImgW + ( x+nMskX)];

					fMsk = *(fMask+ iMskW*(nMskY+1) + nMskX+1);

					r += xClr.r * fMsk;
					g += xClr.g * fMsk;
					b += xClr.b * fMsk;
				}
			}

			if(r>1.f)	r = 1.f;
			if(g>1.f)	g = 1.f;
			if(b>1.f)	b = 1.f;


			pOut[nIdx] = D3DXCOLOR(r, g, b, 1.f);
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

	INT iMaskW = sizeof(g_MaskBlurRect3X3[0])/(sizeof(g_MaskBlurRect3X3[0][0]));
	McColor_TransColorMaskBluring(pColorDst
									, pColorSrc, nImgW, nImgH
									, (float*)g_MaskBlurRect3X3
									, iMaskW);

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