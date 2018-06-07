// PRTracerDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
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


// CPRTracerDlg 대화 상자



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

// CPRTracerDlg 메시지 처리기

BOOL CPRTracerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_editWidth.SetWindowText( "640" );
	m_editHeight.SetWindowText( "480" );

	m_pDlgFrameBuffer = new CFrameBufferDlg();
	m_pDlgFrameBuffer->Create( IDD_FRAMEBUFFER, this );
	m_pDlgFrameBuffer->ShowWindow( SW_HIDE );

	AllocFrameBuffer();
	m_pDlgFrameBuffer->Resize( m_cxFrameBuffer, m_cyFrameBuffer, m_lpFrameBuffer );

	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CPRTracerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
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