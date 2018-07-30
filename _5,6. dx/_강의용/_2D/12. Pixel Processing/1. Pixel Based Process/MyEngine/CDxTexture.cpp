#include "Global.h"
//========================================================
CDxTexture::CDxTexture()
{
	m_pDev	= NULL;

	m_pTx	= NULL;
	memset(&m_Img, 0, sizeof m_Img);
	m_nBytePerPixel = -1;

}//	CDxTexture::CDxTexture()
//========================================================
CDxTexture::~CDxTexture() {	Destroy(); }
//========================================================
void CDxTexture::Destroy() { SAFE_RELEASE(m_pTx); }
//========================================================
INT CDxTexture::Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD dwColor, DWORD dwFormat)
{
	m_pDev	= pDev;

	m_dwColor = dwColor;

	if(FAILED(D3DXCreateTextureFromFileEx(
		m_pDev
		, sFile
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, (D3DFORMAT)dwFormat
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, m_dwColor
		, &m_Img
		, NULL
		, &m_pTx
		)) )
	{
		m_pTx = NULL;
		MessageBox( GetActiveWindow()
					, "Create Texture Failed"
					, sFile
					, MB_ICONEXCLAMATION
					);
		return -1;
	}

	return 0;

}//	INT CDxTexture::Create(LPDIRECT3DDEVICE9 pDev, char* sFile)
//========================================================
void CDxTexture::GetImageRect(RECT* pRc)
{
	pRc->left = 0;
	pRc->top = 0;
	pRc->right = m_Img.Width;
	pRc->bottom = m_Img.Height;

}//	void CDxTexture::GetImageRect(RECT* pRc)
 //========================================================
INT CDxTexture::GetImageWidth()				{ return m_Img.Width; }
//========================================================
INT CDxTexture::GetImageHeight()			{ return m_Img.Height; }
//========================================================
LPDIRECT3DTEXTURE9 CDxTexture::GetTexture() { return m_pTx;}
//========================================================
int		CDxTexture::GetBytePerPixel()
{
	if (m_nBytePerPixel == -1)
	{
		D3DSURFACE_DESC		d3dDesc;
		D3DLOCKED_RECT		d3dRc;

		m_pTx->GetLevelDesc(0, &d3dDesc);			//	텍스쳐 정보 얻기.
		m_pTx->LockRect(0, &d3dRc, NULL, 0);		//	텍스쳐 픽셀 정보 얻기.

		int nPitch = d3dRc.Pitch;					//	픽셀 간격.

		m_nBytePerPixel = nPitch / d3dDesc.Width;	//	1픽셀당 바이트 계산.

		m_pTx->UnlockRect(0);						//	LockRect 이후 처리 필수.
	}

	return m_nBytePerPixel;

}//	int		CDxTexture::GetBytePerPixel()
//========================================================