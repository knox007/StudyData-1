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

	virtual HRESULT Create(LPDIRECT3DDEVICE9 pDev, TCHAR *tszFontName, int fontSize, int fontWeight, BOOL bItalic = FALSE);
	virtual void	Destroy();
	virtual void	Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color, int format = 0);

};
//========================================================
#endif
//========================================================