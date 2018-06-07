#pragma once

// CFrameBufferDlg dialog
typedef struct tagRGBA { BYTE r; BYTE g; BYTE b; BYTE a; } RGBA, *PRGBA, *LPRGBA;

class CFrameBufferDlg : public CDialog
{
	DECLARE_DYNAMIC(CFrameBufferDlg)

public:
	CFrameBufferDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFrameBufferDlg();

// Dialog Data
	enum { IDD = IDD_FRAMEBUFFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	LPRGBA		m_lpFrameBuffer;
	int			m_cxFrameBuffer;
	int			m_cyFrameBuffer;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void Resize( int cx, int cy, LPRGBA lpBuffer );
};
