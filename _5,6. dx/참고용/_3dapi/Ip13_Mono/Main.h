// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_


class CMain : public CD3DApp
{
public:
	CLcSprite*		m_pLcSprite;
	CLcInput*		m_pInput;
	LPD3DXFONT		m_pD3DXFont;
	
	CLcTexture*		m_pTxSrc;
	CLcTexture*		m_pTxDst;

public:
	CMain();

	virtual HRESULT Init()		;
	virtual HRESULT Destroy()	;

	virtual HRESULT FrameMove()	;
	virtual HRESULT Render()	;

	virtual HRESULT	Restore()	;
	virtual HRESULT	Invalidate();

	
	virtual LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM);
};


extern CMain*	g_pApp;
#define GMAIN	g_pApp

#endif