//===========================================================================
#pragma once
//===========================================================================
#ifndef _CDXSPRITE_H_
#endif _CDXSPRITE_H_
//===========================================================================
class CDxSprite
{
protected:
	LPD3DXSPRITE m_pDxSprite;

public:
	CDxSprite();
	virtual ~CDxSprite();

	HRESULT		Create();

	HRESULT		Draw(LPDIRECT3DTEXTURE9 pTex,
		RECT* pSrcRect,
		D3DXVECTOR2* pscale,
		D3DXVECTOR2* pCenter,
		float fAngle,
		D3DXVECTOR2* pPosition,
		D3DCOLOR color);			


};
//	class CDxSprite
//===========================================================================
#endif
//===========================================================================