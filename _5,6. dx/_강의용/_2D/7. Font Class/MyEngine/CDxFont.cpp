//========================================================
#include "Global.h"
//========================================================
CDxFont::CDxFont()
{
	m_pDxFont = NULL;
}
//========================================================
CDxFont::~CDxFont() { Destroy(); }
//========================================================
HRESULT CDxFont::Create(LPDIRECT3DDEVICE9 pDev, TCHAR *tszFontName, int fontSize)
{
	if (FAILED(D3DXCreateFont(pDev
		, fontSize
		, 0
		, FW_BOLD
		, 1
		, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY
		, FF_DONTCARE
		, tszFontName
		, &m_pDxFont)))
		return E_FAIL;

	return S_OK;

}//	HRESULT CDxFont::Create(LPDIRECT3DDEVICE9 pDev, char *szFontName, int fontSize)
//========================================================
void	CDxFont::Destroy() { SAFE_RELEASE(m_pDxFont); }
//========================================================
void	CDxFont::DrawText(TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color)
{
	RECT	rc;
	::SetRect(&rc, posX, posY, posX + width, posY + height);

	m_pDxFont->DrawText(NULL
		, tszMessage
		, -1
		, &rc
		, 0
		, color
	);
}
//========================================================