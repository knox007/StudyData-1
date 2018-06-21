
// WindowsShutdownDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "WindowsShutdown.h"
#include "WindowsShutdownDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MY_TIMER 100

#define TIME_MODE 0
#define COUNTDOWN_MODE 1

#define SHUTDOWN_MODE 0
#define ESAVING_MODE 1
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

struct time
{
	int hr;
	int min;
	int sec;
};

BOOL doSetSuspendStateHibernate(BOOL force)
{
	HANDLE hToken_;
	TOKEN_PRIVILEGES tokenPriv_;



	// Get a access token for this process. 
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken_))
		return false;



	// Get the LUID for the shutdown privilege.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tokenPriv_.Privileges[0].Luid);



	tokenPriv_.PrivilegeCount = 1;  // one privilege to set    
	tokenPriv_.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;



	// Get the shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken_, FALSE, &tokenPriv_, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);



	if (GetLastError() != ERROR_SUCCESS)
	{
		CloseHandle(hToken_);
		return false;
	}



	BOOL retVal_ = SetSystemPowerState(FALSE, force);
	CloseHandle(hToken_);



	return retVal_;
}

char GetOSVersionType()
{
	// 계산된 윈도우즈 버전을 저장할 변수
	char version = -1;
	// 윈도우즈 버전에 관련된 정보를 얻어올 변수
	OSVERSIONINFOEX osvi;
	// OSVERSIONINFOEX 구조체 값을 얻었는지 OSVERSIONINFO 구조체값을 얻었는지를
	// 구분할 변수 ( 0 이면, OSVERSIONINFO 구조체 정보를 얻었다는 뜻입니다. )
	BOOL version_ex_flag = 0;

	// 운영체제의 버전과 관련된 정보를 얻기 위해 구조체 변수를 초기화합니다.
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	// 현재 운영체제의 버전을 알수 없기 때문에 OSVERSIONINFOEX 속성으로 버전정보를 얻습니다.
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	// GetVersionEx 함수를 사용하여 현재의 운영체제 정보를 얻습니다.
	// OSVERSIONINFOEX 값을 설정하고 호출했기 대문에 윈도우 NT 4.0 SP6 이상 및 그 이후 버전의
	//  윈도우가 아니라면 이 함수는 실패할 것입니다.
	if (!(version_ex_flag = GetVersionEx((OSVERSIONINFO *)&osvi))) {
		// 윈도우즈 버전이 낮아서 OSVERSIONINFOEX 형식으로 값을 얻을수 없는 경우...
		// OSVERSIONINFO 형식으로 재설정하고 값을 얻습니다.
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *)&osvi)) return -1;
	}

	// 얻어온 OSVERSIONINFOEX 구조체 변수의 값을 이용하여 버전을 구별합니다.
	switch (osvi.dwPlatformId) {
		// NT 기술 기반의 운영체제인 경우
	case VER_PLATFORM_WIN32_NT:
		if (osvi.dwMajorVersion <= 4) version = 4;
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0) version = 5;
		else if (version_ex_flag) version = 6;
		break;

		// 윈도우즈 9x 기반의 운영체제인 경우
	case VER_PLATFORM_WIN32_WINDOWS:
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0) version = 1;
		else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10) version = 2;
		else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90) version = 3;
		break;
	}

	return version;
}

char GetNtPrivilege()
{
	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// 현재 프로세스의 권한과 관련된 정보를 변경하기 위해 토큰정보를 엽니다.
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
		TOKEN_QUERY, &h_token)) {
		// 권한과 관련된 정보 접근에 실패함..
		return 0;
	}

	// 현재 프로세스가 SE_SHUTDOWN_NAME 권한을 사용할수 있도록 설정한다.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 지정한 값으로 권한을 조정한다.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		// 권한 조정에 실패한 경우...
		return 0;
	}

	return 1;
}

void PowerOff()
{
	if (GetOSVersionType() <= 3) {
		// 현재 운영체제가 Windows 95, Windows 98, Windows ME 인 경우...
		ExitWindowsEx(EWX_LOGOFF | EWX_POWEROFF | EWX_SHUTDOWN, 0);
		ExitWindowsEx(EWX_FORCE, 0);
	}
	else if (GetNtPrivilege()) {
		// 현재 운영체제가 Windows NT, Windows 2000, Windows XP 인 경우...
		ExitWindowsEx(EWX_FORCE | EWX_POWEROFF, 0);
	}
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWindowsShutdownDlg 대화 상자



CWindowsShutdownDlg::CWindowsShutdownDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWSSHUTDOWN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  timer_mode = 0;
	mode = 0;
	func_mode = 0;
}

void CWindowsShutdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo_hr);
	DDX_Control(pDX, IDC_COMBO2, combo_min);
	//  DDX_Control(pDX, IDC_COMBO3, como_sec);
	DDX_Control(pDX, IDC_COMBO3, combo_sec);
	DDX_Control(pDX, IDC_BUTTON1, btn_start);
	//  DDX_Control(pDX, IDC_RADIO1, radio1);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	combo_hr.SetCurSel(0);
	combo_min.SetCurSel(0);
	combo_sec.SetCurSel(0);
	DDX_Control(pDX, IDC_EDIT2, edit_hr);
	DDX_Control(pDX, IDC_EDIT3, edit_min);
	DDX_Control(pDX, IDC_EDIT4, edit_sec);
}

BEGIN_MESSAGE_MAP(CWindowsShutdownDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CWindowsShutdownDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CWindowsShutdownDlg::OnBnClickedRadio2)
//	ON_WM_CREATE()
ON_BN_CLICKED(IDC_BUTTON1, &CWindowsShutdownDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CWindowsShutdownDlg::OnBnClickedButton2)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_RADIO3, &CWindowsShutdownDlg::OnBnClickedRadio3)
ON_BN_CLICKED(IDC_RADIO4, &CWindowsShutdownDlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CWindowsShutdownDlg 메시지 처리기

BOOL CWindowsShutdownDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

	
	

}

void CWindowsShutdownDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWindowsShutdownDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWindowsShutdownDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWindowsShutdownDlg::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mode = TIME_MODE;
}




void CWindowsShutdownDlg::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mode = COUNTDOWN_MODE;
}


struct time input_time;

void CWindowsShutdownDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (timer_active == FALSE) 
	{
		timer_active = TRUE;
		CString str[3];

		if (timer_init == TRUE)
		{
			timer_init = FALSE;
			combo_hr.GetLBText(combo_hr.GetCurSel(), str[0]);
			combo_min.GetLBText(combo_min.GetCurSel(), str[1]);
			combo_sec.GetLBText(combo_sec.GetCurSel(), str[2]);

			input_time.hr = _ttoi(str[0]);
			input_time.min = _ttoi(str[1]);
			input_time.sec = _ttoi(str[2]);

			GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
		}
		
		SetTimer(MY_TIMER, 1000, 0);

		if (mode == COUNTDOWN_MODE)
		{
			btn_start.SetWindowTextW(TEXT("일시정지"));
		}
		else if (mode == TIME_MODE)
		{
			GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		}
		
		
	}
	else if (timer_active == TRUE && mode == COUNTDOWN_MODE)
	{
		KillTimer(MY_TIMER);
		timer_active = FALSE;
		btn_start.SetWindowTextW(TEXT("시작"));
	}
	
}



void CWindowsShutdownDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(MY_TIMER);
	timer_active = FALSE;
	timer_init = TRUE;
	btn_start.SetWindowTextW(TEXT("시작"));
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO3)->EnableWindow(TRUE);

	combo_hr.SetCurSel(0);
	combo_min.SetCurSel(0);
	combo_sec.SetCurSel(0);

	edit_hr.SetWindowTextW(TEXT(""));
	edit_min.SetWindowTextW(TEXT(""));
	edit_sec.SetWindowTextW(TEXT(""));
}


void CWindowsShutdownDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case MY_TIMER:
	{
		CString str[3];
		if (mode == COUNTDOWN_MODE)
		{
			if (input_time.hr == 0 && input_time.min == 0 && input_time.sec == 0)
			{
				if (alert == FALSE)
				{
					alert = TRUE;
					if (func_mode == SHUTDOWN_MODE)
					{
						MessageBox(TEXT("윈도우즈를 종료합니다"), TEXT("알림"), MB_OK);
						PowerOff();
					}
					else if (func_mode == ESAVING_MODE)
					{
						MessageBox(TEXT("윈도우즈가 절전모드로 들어갑니다"), TEXT("알림"), MB_OK);
						doSetSuspendStateHibernate(FALSE);
						PostQuitMessage(WM_QUIT);
					}
				}

			}
			else
			{
				input_time.sec--;
				if (input_time.sec < 0)
				{
					input_time.sec = 59;
					input_time.min--;
				}
				if (input_time.min < 0)
				{
					input_time.min = 59;
					input_time.hr--;
				}


				str[0].Format(TEXT("%d"), input_time.hr);
				str[1].Format(TEXT("%d"), input_time.min);
				str[2].Format(TEXT("%d"), input_time.sec);

				edit_hr.SetWindowTextW(str[0]);
				edit_min.SetWindowTextW(str[1]);
				edit_sec.SetWindowTextW(str[2]);
			}
		}
		else if (mode == TIME_MODE)
		{
			
			
			CTime currTime = CTime::GetCurrentTime();
			int day = currTime.GetDay();
			if (input_time.hr < currTime.GetHour())
				day++;
			CTime destTime(currTime.GetYear(), currTime.GetMonth(), day, input_time.hr, input_time.min, input_time.sec);
			CTimeSpan ts = destTime - currTime;

			if (ts.GetTotalSeconds() <= 0)
			{
				if (alert == FALSE)
				{
					alert = TRUE;
					edit_sec.SetWindowTextW(TEXT(""));
					if (func_mode == SHUTDOWN_MODE)
					{
						MessageBox(TEXT("윈도우즈를 종료합니다"), TEXT("알림"), MB_OK);
						PowerOff();
					}
					else if (func_mode == ESAVING_MODE)
					{
						MessageBox(TEXT("윈도우즈가 절전모드로 들어갑니다"), TEXT("알림"), MB_OK);
						doSetSuspendStateHibernate(FALSE);
						PostQuitMessage(WM_QUIT);
					}
				}
			}
			else
			{
				str[0].Format(TEXT("%d"), ts.GetHours());
				str[1].Format(TEXT("%d"), ts.GetMinutes());
				str[2].Format(TEXT("%d"), ts.GetSeconds());

				edit_hr.SetWindowTextW(str[0]);
				edit_min.SetWindowTextW(str[1]);
				edit_sec.SetWindowTextW(str[2]);
			}
			
			
		}
		

		break;
	}
		
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CWindowsShutdownDlg::OnBnClickedRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	func_mode = SHUTDOWN_MODE;
}




void CWindowsShutdownDlg::OnBnClickedRadio4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	func_mode = ESAVING_MODE;
}
