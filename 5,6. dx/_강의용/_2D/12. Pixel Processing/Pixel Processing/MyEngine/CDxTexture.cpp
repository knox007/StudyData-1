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

		int nPitch = m_d3dRc.Pitch;					//	가로 한줄의 실제 바이트 수.

		m_nBytePerPixel = nPitch / m_d3dDesc.Width;	//	1픽셀당 바이트 계산.

		m_pTx->UnlockRect(0);						//	LockRect 이후 처리 필수.
	}

	return m_nBytePerPixel;

}//	int		CDxTexture::GetBytePerPixel()
//========================================================
void CDxTexture::SetRGBA_ColorShift(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	//	현재 주소의 픽셀 색 정보를 얻어옴.
	D3DXCOLOR pdwColor = *pdwBits;

	//	각 색상 요소에 일정비율을 곱하여 색상 비율 조정.
	pdwColor.r *= fR;
	pdwColor.g *= fG;
	pdwColor.b *= fB;
	pdwColor.a *= fA;

	*pdwBits = pdwColor;

}//	void CDxTexture::SetRGBA_ColorShift(DWORD* pdwBits, float fR, float fG, float fB, float fA )
//========================================================
void CDxTexture::SetRGBA_Mono(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	/*
	일반적인 흑백처리
		-	최종색 : (R + G + B)/3
	
	현실적인 흑백처리
		-	최종색 : R*0.299 + G*0.587 + B*0.114
		-	사람의 눈에 민감한 정도가
			G -> R -> B 순으로 되어있고 그 민감도에 맞게
			평균적인 값을 적용하기 때문.

	*/
	D3DXCOLOR pdwColor = *pdwBits;

	float fColor = pdwColor.r * fR +
		pdwColor.g * fG +
		pdwColor.b * fB;

	*pdwBits = D3DXCOLOR(fColor, fColor, fColor, pdwColor.a);

}//	void CDxTexture::SetRGBA_Mono(DWORD* pdwBits, float fR, float fG, float fB, float fA)
//========================================================
void CDxTexture::SetRGBA_InverseColor(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	D3DXCOLOR pdwColor = *pdwBits;
	
	//	각 색상의 반전값 = 최대값(1.0) - 현재 색상값.
	pdwColor.r = 1 - pdwColor.r;
	pdwColor.g = 1 - pdwColor.g;
	pdwColor.b = 1 - pdwColor.b;

	*pdwBits = pdwColor;

}//	void CDxTexture::SetRGBA_InverseColor(DWORD* pdwBits, float fR, float fG, float fB, float fA)
//========================================================
void CDxTexture::SetRGBA_Gamma(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	D3DXCOLOR pdwColor = *pdwBits;
	//	색상  = 현재 색의 (1/감마)승.
	pdwColor.r = powf(pdwColor.r, 1.f / fR);
	pdwColor.g = powf(pdwColor.g, 1.f / fG);
	pdwColor.b = powf(pdwColor.b, 1.f / fB);

	*pdwBits = pdwColor;

}//	void CDxTexture::SetRGBA_Gamma(DWORD* pdwBits, float fR, float fG, float fB, float fA)
//========================================================
void CDxTexture::SetRGBA_BitPlannerSlicing(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	D3DXCOLOR pdwColor = *pdwBits;
	//	
	DWORD dwR = DWORD(pdwColor.r * 255);
	DWORD dwG = DWORD(pdwColor.g * 255);
	DWORD dwB = DWORD(pdwColor.b * 255);
		
	dwR >>= (8 - nBit);
	dwG >>= (8 - nBit);
	dwB >>= (8 - nBit);
	
	dwR <<= (8 - nBit);
	dwG <<= (8 - nBit);
	dwB <<= (8 - nBit);	

	*pdwBits = D3DXCOLOR(dwR / 255.f, dwG / 255.f, dwB / 255.f, 1.f);
	

}//	void SetRGBA_BitPlannerSlicing(DWORD* pdwBits, float fR, float fG, float fB, float fA)
//========================================================
void CDxTexture::SetBits(SetBitsFuncPtr pFunc, DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	m_pfFunc = pFunc;
	(this->*m_pfFunc)(pdwBits, fR, fG, fB, fA, nBit);
}
//========================================================
void CDxTexture::SetRGBA(eEFFMODE eMode, float fR, float fG, float fB, float fA, int nBit)
{
	int nBytePerPixel = GetBytePerPixel();

	if (nBytePerPixel == 4)
	{
		m_pTx->LockRect(0, &m_d3dRc, NULL, 0);

		DWORD* pColorDst = NULL;

		pColorDst = (DWORD*)m_d3dRc.pBits;	//	색상 버퍼 포인터.

		int width = m_d3dDesc.Width;
		int height = m_d3dDesc.Height;

		for (int hei = 0; hei < height; ++hei)
		{
			for (int wid = 0; wid < width; ++wid)
			{
				int idx = hei * width + wid;
				DWORD* pdwColor = pColorDst;

				switch (eMode)
				{
				case COLORSHIFT:
					SetBits(&CDxTexture::SetRGBA_ColorShift, (pdwColor + idx), fR, fG, fB, fA, nBit);
					break;

				case MONO:
					SetBits(&CDxTexture::SetRGBA_Mono, (pdwColor + idx), fR, fG, fB, fA, nBit);
					break;

				case INVERSECOLOR:
					SetBits(&CDxTexture::SetRGBA_InverseColor, (pdwColor + idx), fR, fG, fB, fA, nBit);
					break;

				case GAMMA:
					SetBits(&CDxTexture::SetRGBA_Gamma, (pdwColor + idx), fR, fG, fB, fA, nBit);
					break;
					
				case BITPLANNERSLICING:
					SetBits(&CDxTexture::SetRGBA_BitPlannerSlicing, (pdwColor + idx), fR, fG, fB, fA, nBit);
					break;
					
				}//	switch (eMode)
				
			}//	for (int hei = 0; hei < height; ++hei)

		}//	for (int wid = 0; wid < width; ++wid)

		m_pTx->UnlockRect(0);

	}//	if (nBytePerPixel == 4)
	else
		MessageBox(NULL, "BPP 4바이트만 지원합니다.", "알림", MB_OK | MB_ICONWARNING);

}//	void	CDxTexture::SetRGBA(float fR, float fG, float fB)
//========================================================