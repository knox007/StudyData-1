
// MFC_0620Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_0620.h"
#include "MFC_0620Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

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


// CMFC0620Dlg 대화 상자



CMFC0620Dlg::CMFC0620Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_0620_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pwndShow = NULL;
}

void CMFC0620Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab_controll);
	DDX_Control(pDX, IDC_BUTTON1, m_btc_start);
	DDX_Control(pDX, IDC_COMBO1, m_MODE);
}

BEGIN_MESSAGE_MAP(CMFC0620Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMFC0620Dlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC0620Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC0620Dlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CMFC0620Dlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFC0620Dlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CMFC0620Dlg 메시지 처리기

bool time_flag = false;
int index = 0;
bool first_start = true;
bool start_stop_swap = true;
int mode = 0;

BOOL CMFC0620Dlg::OnInitDialog()
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
	/* 탭바 설정 시작 */
	m_tab_controll.InsertItem(1, _T("목표 시간"));
	m_tab_controll.InsertItem(2, _T("카운트 다운"));
	
	CRect Rect;
	m_tab_controll.GetClientRect(&Rect);

	first.Create(IDD_DIALOG1, &m_tab_controll);
	first.SetWindowPos(NULL, 5, 25, Rect.Width() - 12, Rect.Height() - 33, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &first;

	second.Create(IDD_DIALOG2, &m_tab_controll);
	second.SetWindowPos(NULL, 5, 25, Rect.Width() - 12, Rect.Height() - 33, SWP_NOZORDER);
	/* 탭바 설정 종료 */

	m_MODE.AddString(_T("종료 모드"));
	m_MODE.AddString(_T("절전 모드"));
	m_MODE.SetCurSel(0);

	CString Time;
	for (int i = 0; i < 24; i++) {
		Time.Format(_T("%d"), i);
		first.m_first_combo2.AddString(Time);
		second.m_second_hour.AddString(Time);
	}
	first.m_first_combo2.SetCurSel(0);
	second.m_second_hour.SetCurSel(0);

	for (int i = 0; i < 60; i+=5) {
		Time.Format(_T("%d"), i);
		first.m_first_combo3.AddString(Time);
		second.m_second_min.AddString(Time);
	}
	first.m_first_combo3.SetCurSel(0);
	second.m_second_min.SetCurSel(0);

	for (int i = 0; i < 60; i+=5) {
		Time.Format(_T("%d"), i);
		first.m_first_combo4.AddString(Time);
		second.m_second_sec.AddString(Time);
	}
	first.m_first_combo4.SetCurSel(0);
	second.m_second_sec.SetCurSel(0);
	/* 첫번째 탭바 콤보 박스 설정 종료 */

	now_time();					// 현재 시간 불러오기
	SetTimer(0, 1000, NULL);	// 타이머 시작	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFC0620Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC0620Dlg::OnPaint()
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
HCURSOR CMFC0620Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC0620Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	first.m_first_combo2.EnableWindow(true);
	first.m_first_combo3.EnableWindow(true);
	first.m_first_combo4.EnableWindow(true);
	first.m_first_late.SetWindowText(_T(""));
	second.m_second_hour.EnableWindow(true);
	second.m_second_min.EnableWindow(true);
	second.m_second_sec.EnableWindow(true);
	second.m_second_latetime.SetWindowText(_T(""));
	second.m_second_endtime.SetWindowText(_T(""));
	time_flag = false;
	m_btc_start.SetWindowTextW(_T("시작"));

	if (m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int iSelect = m_tab_controll.GetCurSel();

	switch (iSelect)
	{
	case 0:
		first.ShowWindow(SW_SHOW);
		m_pwndShow = &first;
		index = 0;
		break;
	case 1:
		second.ShowWindow(SW_SHOW);
		m_pwndShow = &second;
		index = 1;
		break;
	}

	*pResult = 0;
}

void CMFC0620Dlg::OnBnClickedButton1()
{
	// 시작 할때요
	first.m_first_combo2.EnableWindow(false);
	first.m_first_combo3.EnableWindow(false);
	first.m_first_combo4.EnableWindow(false);
	second.m_second_hour.EnableWindow(false);
	second.m_second_min.EnableWindow(false);
	second.m_second_sec.EnableWindow(false);

	if (index == 0) {
		time_flag = true;
	} else if (index == 1 && first_start) {
		m_btc_start.SetWindowTextW(_T("일시정지"));
		CString t_hour, t_min, t_sec;
		int i_hour, i_min, i_sec;

		second.m_second_hour.GetWindowText(t_hour);
		second.m_second_min.GetWindowText(t_min);
		second.m_second_sec.GetWindowText(t_sec);

		second.down_hour = t_hour;
		second.down_min = t_min;
		second.down_sec = t_sec;
		time_flag = true;
		first_start = false;
	} else if (index == 1 && !first_start && start_stop_swap) {
		m_btc_start.SetWindowTextW(_T("시작"));
		time_flag = false;
		start_stop_swap = !start_stop_swap;
	} else if (index == 1 && !first_start && !start_stop_swap) {
		m_btc_start.SetWindowTextW(_T("일시정지"));
		time_flag = true;
		start_stop_swap = !start_stop_swap;
	}
}

void CMFC0620Dlg::OnBnClickedButton2()
{
	first.m_first_combo2.EnableWindow(true);
	first.m_first_combo3.EnableWindow(true);
	first.m_first_combo4.EnableWindow(true);		
	first.m_first_late.SetWindowText(_T(""));
	second.m_second_hour.EnableWindow(true);
	second.m_second_min.EnableWindow(true);
	second.m_second_sec.EnableWindow(true);
	second.m_second_latetime.SetWindowText(_T(""));
	second.m_second_endtime.SetWindowText(_T(""));
	m_btc_start.SetWindowTextW(_T("시작"));
	time_flag = false;
	first_start = true;
}

void CMFC0620Dlg::OnTimer(UINT_PTR nIDEvent)
{
	now_time();
	
	if (time_flag && index == 0) {
		CTime cTime = CTime::GetCurrentTime();
		int year = cTime.GetYear();
		int month = cTime.GetMonth();
		int day = cTime.GetDay();
		int hour = cTime.GetHour();
		int minute = cTime.GetMinute();
		int second = cTime.GetSecond();

		CString t_hour, t_min, t_sec;
		int i_hour, i_min, i_sec;

		first.m_first_combo2.GetWindowText(t_hour);
		first.m_first_combo3.GetWindowText(t_min);
		first.m_first_combo4.GetWindowText(t_sec);
		i_hour = _ttoi(t_hour);
		i_min = _ttoi(t_min);
		i_sec = _ttoi(t_sec);

		CTime select_time(year, month, day, i_hour, i_min, i_sec);
		CTime now_time(year, month, day, hour, minute, second);
		CTimeSpan sub_time;
		if (select_time > now_time) {
			sub_time = select_time - now_time;
		} else {
			sub_time = (select_time + 86400) - now_time;
		}

		CString late_time = sub_time.Format(_T("%H시 %M분 %S초"));
		if (sub_time == 1) {
			if (mode == 0) {
				PowerOff();
			} else {
				KillTimer(0);
				system("rundll32.exe PowrProf.dll,SetSuspendState 0,1,0");
			}
		}

		first.m_first_late.SetWindowTextW(late_time);
	} else if (time_flag && index == 1) {
		CString cnt_hour, cnt_min, cnt_sec, late_time;
		int i_cnt_hour, i_cnt_min, i_cnt_sec;

		cnt_hour = second.down_hour;
		cnt_min = second.down_min;
		cnt_sec = second.down_sec;

		i_cnt_hour = _ttoi(cnt_hour);
		i_cnt_min = _ttoi(cnt_min);
		i_cnt_sec = _ttoi(cnt_sec);
		i_cnt_sec--;

		if (i_cnt_sec < 0) {
			i_cnt_sec = 59;
			i_cnt_min--;
		}

		if (i_cnt_min < 0) {
			i_cnt_min = 59;
			i_cnt_hour--;
		}
		// 종료 시간 만들기
		CTime cTime = CTime::GetCurrentTime();
		int hour, min, sec;
		hour = cTime.GetHour();
		min = cTime.GetMinute();
		sec = cTime.GetSecond();

		sec += i_cnt_sec;
		min += i_cnt_min;
		hour += i_cnt_hour;

		if (sec > 60) {
			sec -= 60;
			min++;
		}

		if (min > 60) {
			min -= 60;
			hour++;
		}

		late_time.Format(_T("%02d시 %02d분 %02d초"), hour, min, sec);
		second.m_second_endtime.SetWindowTextW(late_time);

		late_time.Format(_T("%02d"), i_cnt_hour);
		second.down_hour = late_time;
		late_time.Format(_T("%02d"), i_cnt_min);
		second.down_min = late_time;
		late_time.Format(_T("%02d"), i_cnt_sec);
		second.down_sec = late_time;

		late_time.Format(_T("%02d시 %02d분 %02d초"), i_cnt_hour, i_cnt_min, i_cnt_sec);
		second.m_second_latetime.SetWindowTextW(late_time);

		if (i_cnt_hour < 0) {
			if (mode == 0) {
				PowerOff();
			} else {
				KillTimer(0);
				system("rundll32.exe PowrProf.dll,SetSuspendState 0,1,0");
			}
		}
	}
		
	CDialogEx::OnTimer(nIDEvent);
}

void CMFC0620Dlg::now_time() {
	CTime cTime = CTime::GetCurrentTime();
	CString hour, min, sec;
	hour.Format(_T("%02d"), cTime.GetHour());
	min.Format(_T("%02d"), cTime.GetMinute());
	sec.Format(_T("%02d"), cTime.GetSecond());
	first.m_first_time.SetWindowText(hour + "시 " + min + "분 " + sec + "초");
	second.m_second_nowtime.SetWindowText(hour + "시 " + min + "분 " + sec + "초");
}

char CMFC0620Dlg::GetOSVersionType() {
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

// 현재 운영체제가 NT 계열인 경우, SE_SHUTDOWN_NAME 레벨의 권한 등급을
// 가지고 있어야 하기 때문에 아래의 함수를 이용하여 권한을 얻습니다.
char CMFC0620Dlg::GetNtPrivilege() {
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

// 컴퓨터를 끌때 사용할 함수
void CMFC0620Dlg::PowerOff() {
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


void CMFC0620Dlg::OnBnClickedCancel()
{
	KillTimer(0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMFC0620Dlg::OnCbnSelchangeCombo1()
{
	CString temp;

	this->m_MODE.GetLBText(this->m_MODE.GetCurSel(), temp);
	if (temp == "종료 모드") {
		mode = 0;
	} else {
		mode = 1;
	}

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
