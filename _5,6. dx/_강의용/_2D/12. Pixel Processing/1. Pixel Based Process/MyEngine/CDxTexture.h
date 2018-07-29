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
	int					m_nBytePerPixel;

public:
	CDxTexture();
	virtual ~CDxTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD dwColor, DWORD dwFormat = D3DFMT_UNKNOWN);
	virtual void	Destroy();

public:
	INT		GetImageWidth();
	INT		GetImageHeight();
	void	GetImageRect(RECT* pRc);
	int		GetBytePerPixel();

	LPDIRECT3DTEXTURE9	GetTexture();
};

#endif