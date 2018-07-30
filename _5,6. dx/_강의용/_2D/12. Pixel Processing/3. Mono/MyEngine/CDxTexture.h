//========================================================
#pragma once
//========================================================
#ifndef _DXTEXTURE_H_
#define _DXTEXTURE_H_
//========================================================
class CDxTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;
	
	D3DXIMAGE_INFO		m_Img;
	LPDIRECT3DTEXTURE9	m_pTx;
	DWORD				m_dwColor;
	int					m_nBytePerPixel;	//	�ȼ��� ����Ʈ.
											//	�� ���� ����Ͽ� ��������� ���������͸� ����ȯ�Ͽ� ����Ѵ�.
											//	4 ����Ʈ	:	DWORD
											//	2 ����Ʈ	:	WORD
											//	1 ����Ʈ	:	BYTE

	D3DSURFACE_DESC		m_d3dDesc;
	D3DLOCKED_RECT		m_d3dRc;

public:
	CDxTexture();
	virtual ~CDxTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD dwColor = 0xff000000, DWORD dwFormat = D3DFMT_UNKNOWN);
	virtual void	Destroy();
	virtual void	SetColor(float fR, float fG, float fB, float fA = 1.0f);
	virtual void	SetMono();

public:
	INT		GetImageWidth();
	INT		GetImageHeight();
	void	GetImageRect(RECT* pRc);
	int		GetBytePerPixel();

	LPDIRECT3DTEXTURE9	GetTexture();

};

#endif