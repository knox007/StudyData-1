// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_

class CMain : public CD3DApp
{
public:
	LPD3DXFONT		m_pD3DXFont;

	CLcTexture*		m_pTxBck;			// ��� �ؽ�ó
	RECT			m_ImgRcB;			// RECT �ִ� �̹���

	CLcTexture*		m_pTxAni;			// �ִ� �ؽ�ó

	DWORD			m_dTimeBgn;			// ���� Ÿ��
	DWORD			m_dTimeEnd;			// �� Ÿ��

	RECT			m_ImgRc1;			// RECT �ִ� �̹���
	RECT			m_ImgRc2;			// RECT �ִ� �̹���


public:
	CMain();

	virtual INT		Init();
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual INT		Render();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};


extern CMain*	g_pApp;

#endif
