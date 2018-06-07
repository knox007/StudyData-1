// FrameBufferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PRTracer.h"
#include "FrameBufferDlg.h"


// CFrameBufferDlg dialog

IMPLEMENT_DYNAMIC(CFrameBufferDlg, CDialog)
CFrameBufferDlg::CFrameBufferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFrameBufferDlg::IDD, pParent)
{
	m_lpFrameBuffer = NULL;
	m_cxFrameBuffer = 0;
	m_cyFrameBuffer = 0;
}

CFrameBufferDlg::~CFrameBufferDlg()
{
}

void CFrameBufferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFrameBufferDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFrameBufferDlg message handlers

void CFrameBufferDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	RGBA q;
	int		x, y;
	if( m_lpFrameBuffer )
	{
		for( y = 0 ; y < m_cyFrameBuffer ; y++ )
			for( x = 0 ; x < m_cxFrameBuffer ; x++ )
			{
				q = *(m_lpFrameBuffer + x + y * m_cxFrameBuffer);
				dc.SetPixel( x, y, RGB( q.r, q.g, q.b) );
			}
	}
}

void CFrameBufferDlg::Resize( int cx, int cy, LPRGBA lpBuffer )
{
	m_lpFrameBuffer = lpBuffer;
	m_cxFrameBuffer = cx;
	m_cyFrameBuffer = cy;
	CWnd* pParent = (CWnd*)GetParent();
	RECT	rc;
	pParent->GetWindowRect( &rc );
	POINT	pos = { rc.right + 1, rc.top };
	SetRect( &rc, 0, 0, cx, cy );
	AdjustWindowRect( &rc, GetStyle(), FALSE );
	MoveWindow( pos.x, pos.y, rc.right - rc.left, rc.bottom - rc.top );
}