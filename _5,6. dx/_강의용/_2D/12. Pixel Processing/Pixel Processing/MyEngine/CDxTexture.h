//========================================================
#pragma once
//========================================================
#ifndef _DXTEXTURE_H_
#define _DXTEXTURE_H_
//========================================================
class CDxTexture;
typedef void(CDxTexture::*SetBitsFuncPtr)(DWORD* pdwBits, float fR, float fG, float fB, float fA);
//========================================================
enum eEFFMODE
{
	COLOR,

	MONO,

	INVERSECOLOR,

	GAMMA,

	BITPLANNERSLICING,

};
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

	D3DSURFACE_DESC		m_d3dDesc;
	D3DLOCKED_RECT		m_d3dRc;
	SetBitsFuncPtr		m_pfFunc;

	void SetRGBA_Default(DWORD* pdwBits, float fR, float fG, float fB, float fA);
	void SetRGBA_Mono(DWORD* pdwBits, float fR, float fG, float fB, float fA);
	void SetRGBA_InverseColor(DWORD* pdwBits, float fR, float fG, float fB, float fA);
	void SetRGBA_Gamma(DWORD* pdwBits, float fR, float fG, float fB, float fA);
	void SetRGBA_BitPlannerSlicing(DWORD* pdwBits, float fR, float fG, float fB, float fA);
	
public:
	CDxTexture();
	virtual ~CDxTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD dwColor = 0xff000000, DWORD dwFormat = D3DFMT_UNKNOWN);
	virtual void	Destroy();
	
	void	SetBits(SetBitsFuncPtr pFunc, DWORD* pdwBits, float fR, float fG, float fB, float fA);
	void	SetRGBA(eEFFMODE eMode, float fR = 1.0f, float fG = 1.0f, float fB = 1.0f, float fA = 1.0f);
	void	SetMono();
	void	SetInverseColor();
	void	SetGamma();

public:
	INT		GetImageWidth();
	INT		GetImageHeight();
	void	GetImageRect(RECT* pRc);
	int		GetBytePerPixel();

	LPDIRECT3DTEXTURE9	GetTexture();

};

#endif