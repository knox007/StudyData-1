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
		m_pTx->GetLevelDesc(0, &m_d3dDesc);			//	텍스쳐 정보 얻기.
		m_pTx->LockRect(0, &m_d3dRc, NULL, 0);		//	텍스쳐 픽셀 정보 얻기.

		int nPitch = m_d3dRc.Pitch;					//	픽셀 간격.

		m_nBytePerPixel = nPitch / m_d3dDesc.Width;	//	1픽셀당 바이트 계산.

		m_pTx->UnlockRect(0);						//	LockRect 이후 처리 필수.
	}

	return m_nBytePerPixel;

}//	int		CDxTexture::GetBytePerPixel()
//========================================================
void CDxTexture::SetColor(float fR, float fG, float fB, float fA)
{
	int nBytePerPixel = GetBytePerPixel();

	if (nBytePerPixel == 4)
	{
		m_pTx->LockRect(0, &m_d3dRc, NULL, 0);

		DWORD* pColorDst = NULL;

		pColorDst = (DWORD*)m_d3dRc.pBits;

		int width = m_d3dDesc.Width;
		int height = m_d3dDesc.Height;

		for (int hei = 0; hei < height; ++hei)
		{
			for (int wid = 0; wid < width; ++wid)
			{
				int idx = hei * width + wid;
				DWORD* pdwColor = pColorDst;

				D3DXCOLOR tmpColor = pdwColor[idx];
				tmpColor.r *= fR;
				tmpColor.g *= fG;
				tmpColor.b *= fB;
				tmpColor.a *= fA;

				pdwColor[idx] = tmpColor;

			}//	for (int hei = 0; hei < height; ++hei)

		}//	for (int wid = 0; wid < width; ++wid)

		m_pTx->UnlockRect(0);

	}//	if (nBytePerPixel == 4)
	else
		MessageBox(NULL, "BPP 4바이트만 지원합니다.", "알림", MB_OK | MB_ICONWARNING);

}//	void	CDxTexture::SetColor(float fR, float fG, float fB)
//========================================================
void CDxTexture::SetMono()
{
	int nBytePerPixel = GetBytePerPixel();

	if (nBytePerPixel == 4)
	{
		m_pTx->LockRect(0, &m_d3dRc, NULL, 0);

		DWORD* pColorDst = NULL;

		pColorDst = (DWORD*)m_d3dRc.pBits;

		int width = m_d3dDesc.Width;
		int height = m_d3dDesc.Height;

		for (int hei = 0; hei < height; ++hei)
		{
			for (int wid = 0; wid < width; ++wid)
			{
				int idx = hei * width + wid;
				D3DXCOLOR pdwColor = pColorDst[idx];

				float fColor =	pdwColor.r * 0.3f +
								pdwColor.g * 0.59f +
								pdwColor.b * 0.11f;

				pColorDst[idx] = D3DXCOLOR(fColor, fColor, fColor, pdwColor.a);

			}//	for (int hei = 0; hei < height; ++hei)

		}//	for (int wid = 0; wid < width; ++wid)

		m_pTx->UnlockRect(0);

	}//	if (nBytePerPixel == 4)
	else
		MessageBox(NULL, "BPP 4바이트만 지원합니다.", "알림", MB_OK | MB_ICONWARNING);

}//	void CDxTexture::SetMono()
//========================================================
void CDxTexture::SetInverseColor()
{
	int nBytePerPixel = GetBytePerPixel();

	if (nBytePerPixel == 4)
	{
		m_pTx->LockRect(0, &m_d3dRc, NULL, 0);

		DWORD* pColorDst = NULL;

		pColorDst = (DWORD*)m_d3dRc.pBits;

		int width = m_d3dDesc.Width;
		int height = m_d3dDesc.Height;

		for (int hei = 0; hei < height; ++hei)
		{
			for (int wid = 0; wid < width; ++wid)
			{
				int idx = hei * width + wid;
				D3DXCOLOR pdwColor = pColorDst[idx];

				pdwColor.r = 1 - pdwColor.r;
				pdwColor.g = 1 - pdwColor.g;
				pdwColor.b = 1 - pdwColor.b;

				pColorDst[idx] = pdwColor;
				
			}//	for (int hei = 0; hei < height; ++hei)

		}//	for (int wid = 0; wid < width; ++wid)

		m_pTx->UnlockRect(0);

	}//	if (nBytePerPixel == 4)
	else
		MessageBox(NULL, "BPP 4바이트만 지원합니다.", "알림", MB_OK | MB_ICONWARNING);

}//	void CDxTexture::SetInverseColor()
//========================================================