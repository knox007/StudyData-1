#ifndef _MAIN_H_
#define _MAIN_H_



class CMain : public CD3DApplication
{
public:
	ID3DXFont*		m_pD3DXFont	;												// D3DX font

	CMcInput*		m_pInput	;
	CMcGrid*		m_pGrid		;

	CMcCamera*		m_pCamT		;

	LPD3DXMESH		m_pMesh		;

public:
	virtual HRESULT Init();
	virtual HRESULT Destroy();
	
	virtual HRESULT Restore();
	virtual HRESULT Invalidate();
	
	virtual HRESULT Render();
	virtual HRESULT FrameMove();
	
	
public:
	LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	CMain();
};


extern CMain*	g_pApp;


#endif