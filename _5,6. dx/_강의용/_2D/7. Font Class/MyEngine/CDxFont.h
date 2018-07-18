//========================================================
#pragma once
//========================================================
#ifndef _DXFONT_H_
#define _DXFONT_H_
//========================================================
class CDxFont
{
protected:
	LPD3DXFONT m_pDxFont;

public:
	CDxFont();
	virtual ~CDxFont();

	virtual HRESULT Create(LPDIRECT3DDEVICE9 pDev, TCHAR *tszFontName, int fontSize);
	virtual void	Destroy();
	virtual void	DrawText(TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color);

};
//========================================================
#endif
//========================================================