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
HRESULT CDxFont::Create(LPDIRECT3DDEVICE9 pDev, TCHAR *tszFontName, int fontSize, int fontWeight, BOOL bItalic )
{
	if (FAILED(D3DXCreateFont(pDev
		, fontSize				//	높이
		, 0						//	가로
		, fontWeight			//	폰트타입.
		, 1						//	밉맵레벨,
		, bItalic				//	이탤릭체.
		, DEFAULT_CHARSET		//	캐릭터 셋.
		, OUT_DEFAULT_PRECIS	//	OutputPrecision 
		, DEFAULT_QUALITY		//	퀄리티
		, FF_DONTCARE			//	PitchAndFamily 
		, tszFontName			//	폰트명
		, &m_pDxFont)))			//	폰트 객체
		return E_FAIL;

	return S_OK;

}//	HRESULT CDxFont::Create(LPDIRECT3DDEVICE9 pDev, char *szFontName, int fontSize)
//========================================================
void	CDxFont::Destroy() { SAFE_RELEASE(m_pDxFont); }
//========================================================
void	CDxFont::Draw(LPD3DXSPRITE spr, TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color, int format )
{
	RECT	rc;
	SetRect(&rc, posX, posY, posX + width, posY + height);

	m_pDxFont->DrawText(
		spr,			//	스프라이트
		tszMessage,		//	메시지
		-1,				//	메시지 길이
		&rc,			//	출력 영역
		format,			//	포맷
		color			//	색
	);

}//	void	CDxFont::DrawText(TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color)
//========================================================