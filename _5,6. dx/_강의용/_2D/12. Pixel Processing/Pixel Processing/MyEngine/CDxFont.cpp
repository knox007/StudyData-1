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
		, fontSize				//	����
		, 0						//	����
		, fontWeight			//	��ƮŸ��.
		, 1						//	�Ӹʷ���,
		, bItalic				//	���Ÿ�ü.
		, DEFAULT_CHARSET		//	ĳ���� ��.
		, OUT_DEFAULT_PRECIS	//	OutputPrecision 
		, DEFAULT_QUALITY		//	����Ƽ
		, FF_DONTCARE			//	PitchAndFamily 
		, tszFontName			//	��Ʈ��
		, &m_pDxFont)))			//	��Ʈ ��ü
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
		spr,			//	��������Ʈ
		tszMessage,		//	�޽���
		-1,				//	�޽��� ����
		&rc,			//	��� ����
		format,			//	����
		color			//	��
	);

}//	void	CDxFont::DrawText(TCHAR *tszMessage, int posX, int posY, int width, int height, D3DXCOLOR color)
//========================================================