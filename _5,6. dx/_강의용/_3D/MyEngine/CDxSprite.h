//==========================================================
#pragma once
//==========================================================
#ifndef _CDXSPRITE_H_
#define _CDXSPRITE_H_
//==========================================================
class CDxSprite
{
protected:
	LPD3DXSPRITE	m_pDxSprite;

public:
	CDxSprite();
	virtual ~CDxSprite();
	LPD3DXSPRITE GetSprite() { return m_pDxSprite ;	}

	HRESULT Create(LPDIRECT3DDEVICE9 pDev);
	void Destroy();
	
	HRESULT Begin(DWORD dwFlag = D3DXSPRITE_ALPHABLEND) { return m_pDxSprite->Begin(dwFlag); }
	HRESULT End() { return m_pDxSprite->End(); }
	HRESULT Draw(LPDIRECT3DTEXTURE9 pTex
		, const RECT *pSrcRect
		, const D3DXVECTOR2 *pScale
		, const D3DXVECTOR2 *pCenter
		, float fAngle
		, const D3DXVECTOR2 *pPosition
		, D3DCOLOR color);

};
//	class CDxSprite
//==========================================================
#endif
//==========================================================