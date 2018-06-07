// PRTracerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include <stdlib.h>

#define MAINBODY
#include "PRTracer.h"
#include "PRTracerDlg.h"
#include "ZParser.h"
#include "ZParsedData.h"
#include "ZFLog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPRTracerDlg ��ȭ ����



CPRTracerDlg::CPRTracerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPRTracerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cxFrameBuffer = 0;
	m_cyFrameBuffer = 0;
	m_lpFrameBuffer = NULL;
	g_pLog = new ZFLog( ZF_LOG_TARGET_CONSOLE | ZF_LOG_TARGET_WINDOW );
	m_pRayTracer = NULL;
}

void CPRTracerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_FILENAME, m_textFilename);
	DDX_Control(pDX, IDC_PROGRESS_RENDER, m_progressRender);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_editWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_editHeight);
	DDX_Control(pDX, IDC_CHECK_AUTOREFRESH, m_btnAutoRefresh);
	DDX_Control(pDX, IDC_BTN_RENDER, m_btnRender);
}

BEGIN_MESSAGE_MAP(CPRTracerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPENXML, OnBnClickedBtnOpenxml)
	ON_BN_CLICKED(IDC_BTN_RENDER, OnBnClickedBtnRender)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_CHECK_AUTOREFRESH, OnBnClickedCheckAutorefresh)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CPRTracerDlg::AllocFrameBuffer()
{
	CString	str;
	m_editWidth.GetWindowText( str );
	m_cxFrameBuffer = atoi( (LPCTSTR)str );
	m_editHeight.GetWindowText( str );
	m_cyFrameBuffer = atoi( (LPCTSTR)str );
	if( m_lpFrameBuffer ) delete m_lpFrameBuffer;
	m_lpFrameBuffer = new RGBA[m_cxFrameBuffer * m_cyFrameBuffer];
	memset( m_lpFrameBuffer, 127, (m_cxFrameBuffer * m_cyFrameBuffer)*sizeof(RGBA) );
}

// CPRTracerDlg �޽��� ó����

BOOL CPRTracerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_editWidth.SetWindowText( "640" );
	m_editHeight.SetWindowText( "480" );

	m_pDlgFrameBuffer = new CFrameBufferDlg();
	m_pDlgFrameBuffer->Create( IDD_FRAMEBUFFER, this );
	m_pDlgFrameBuffer->ShowWindow( SW_HIDE );

	AllocFrameBuffer();
	m_pDlgFrameBuffer->Resize( m_cxFrameBuffer, m_cyFrameBuffer, m_lpFrameBuffer );

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CPRTracerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPRTracerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CPRTracerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPRTracerDlg::OnBnClickedBtnOpenxml()
{
	// TODO: Add your control notification handler code here
	CFileDialog		dlg( TRUE, "", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "XML Files (*.xml)|*.xml||", this, 0 );

	if( dlg.DoModal() != IDCANCEL )
	{
		m_pRayTracer = new ZRayTracer( m_cxFrameBuffer, m_cyFrameBuffer, (char*)dlg.GetPathName().GetBuffer(128) );
		m_btnRender.EnableWindow( 1 );
	}
}

void CPRTracerDlg::OnBnClickedBtnRender()
{
	// TODO: Add your control notification handler code here
	AllocFrameBuffer();
	m_pDlgFrameBuffer->ShowWindow( SW_SHOW );
	m_pDlgFrameBuffer->Resize( m_cxFrameBuffer, m_cyFrameBuffer, m_lpFrameBuffer );

	if( m_pRayTracer )
	{
		Color3f	c;
		m_progressRender.SetRange( 0, m_cyFrameBuffer );
		for( int y = 0 ; y < m_cyFrameBuffer ; y++ )
		{
			for( int x = 0 ; x < m_cxFrameBuffer ; x++ )
			{
				c = m_pRayTracer->TraceRay( m_cxFrameBuffer, m_cyFrameBuffer, x, y );
				m_lpFrameBuffer[ y * m_cxFrameBuffer + x ].r = (int)(c.r * 255.0f);
				m_lpFrameBuffer[ y * m_cxFrameBuffer + x ].g = (int)(c.g * 255.0f);
				m_lpFrameBuffer[ y * m_cxFrameBuffer + x ].b = (int)(c.b * 255.0f);
			}
			m_progressRender.SetPos( y );
		}
	}
}

void CPRTracerDlg::OnBnClickedBtnRefresh()
{
	// TODO: Add your control notification handler code here
	m_pDlgFrameBuffer->Invalidate( FALSE );
}

void CPRTracerDlg::OnBnClickedCheckAutorefresh()
{
	// TODO: Add your control notification handler code here
	if( m_btnAutoRefresh.GetCheck() )
		SetTimer( 10, 100, NULL );
	else
		KillTimer( 10 );
}

void CPRTracerDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_pDlgFrameBuffer->Invalidate( FALSE );

	CDialog::OnTimer(nIDEvent);
}

void CPRTracerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	m_pDlgFrameBuffer->DestroyWindow();

	S_DEL( m_lpFrameBuffer );
	S_DEL( m_pRayTracer );
	S_DEL( m_pDlgFrameBuffer );
	S_DEL( g_pLog );
	OnCancel();
}