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
		m_pTx->GetLevelDesc(0, &m_d3dDesc);			//	�ؽ��� ���� ���.
		m_pTx->LockRect(0, &m_d3dRc, NULL, 0);		//	�ؽ��� �ȼ� ���� ���.

		int nPitch = m_d3dRc.Pitch;					//	���� ������ ���� ����Ʈ ��.

		m_nBytePerPixel = nPitch / m_d3dDesc.Width;	//	1�ȼ��� ����Ʈ ���.

		m_pTx->UnlockRect(0);						//	LockRect ���� ó�� �ʼ�.
	}

	return m_nBytePerPixel;

}//	int		CDxTexture::GetBytePerPixel()
//========================================================
void CDxTexture::SetRGBA_ColorShift(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	//	���� �ּ��� �ȼ� �� ������ ����.
	D3DXCOLOR pdwColor = *pdwBits;

	//	�� ���� ��ҿ� ���������� ���Ͽ� ���� ���� ����.
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
	�Ϲ����� ���ó��
		-	������ : (R + G + B)/3
	
	�������� ���ó��
		-	������ : R*0.299 + G*0.587 + B*0.114
		-	����� ���� �ΰ��� ������
			G -> R -> B ������ �Ǿ��ְ� �� �ΰ����� �°�
			������� ���� �����ϱ� ����.

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
	
	//	�� ������ ������ = �ִ밪(1.0) - ���� ����.
	pdwColor.r = 1 - pdwColor.r;
	pdwColor.g = 1 - pdwColor.g;
	pdwColor.b = 1 - pdwColor.b;

	*pdwBits = pdwColor;

}//	void CDxTexture::SetRGBA_InverseColor(DWORD* pdwBits, float fR, float fG, float fB, float fA)
//========================================================
void CDxTexture::SetRGBA_Gamma(DWORD* pdwBits, float fR, float fG, float fB, float fA, int nBit)
{
	D3DXCOLOR pdwColor = *pdwBits;
	//	����  = ���� ���� (1/����)��.
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

		pColorDst = (DWORD*)m_d3dRc.pBits;	//	���� ���� ������.

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
		MessageBox(NULL, "BPP 4����Ʈ�� �����մϴ�.", "�˸�", MB_OK | MB_ICONWARNING);

}//	void	CDxTexture::SetRGBA(float fR, float fG, float fB)
//========================================================