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
	int					m_nBytePerPixel;	//	픽셀당 바이트.
											//	이 값을 사용하여 색상버퍼의 시작포인터를 형변환하여 사용한다.
											//	4 바이트	:	DWORD
											//	2 바이트	:	WORD
											//	1 바이트	:	BYTE

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