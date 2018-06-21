
// 0620_MFCDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "0620_MFC.h"
#include "0620_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 윈도우 버전별
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

// 현재 운영체제가 NT 계열인 경우, SE_SHUTDOWN_NAME 레벨의 권한 등급을
// 가지고 있어야 하기 때문에 아래의 함수를 이용하여 권한을 얻습니다.
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

// 컴퓨터를 끌때 사용할 함수
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


// CMy0620MFCDlg 대화 상자



CMy0620MFCDlg::CMy0620MFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY0620_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pwndShow = NULL;
}

void CMy0620MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_BUTTON3, btn_init);
	DDX_Control(pDX, IDC_BUTTON1, btn_start);
	DDX_Control(pDX, IDC_BUTTON5, btn_mode);
}

BEGIN_MESSAGE_MAP(CMy0620MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMy0620MFCDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy0620MFCDlg::OnBnClickedButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy0620MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy0620MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy0620MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy0620MFCDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMy0620MFCDlg 메시지 처리기

BOOL CMy0620MFCDlg::OnInitDialog()
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


	// ********** 탭 컨트롤 **********
	CString tabOne = TEXT("목표 시간");
	CString tabTwo = TEXT("카운트 다운");

	m_Tab.InsertItem(1, tabOne);
	m_Tab.InsertItem(2, tabTwo);

	CRect rect;
	m_Tab.GetClientRect(&rect);

	m_one.Create(IDD_DIALOG1, &m_Tab);
	m_one.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_one;

	m_two.Create(IDD_DIALOG2, &m_Tab);
	m_two.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);

	for (int i = 0; i < 24; i++) {
		CString Hour;
		Hour.Format(TEXT("%02d"), i);
		m_one.combo_H.AddString(Hour);
	}
	m_one.combo_H.SetCurSel(0);

	for (int i = 0; i < 60; i++) {
		CString Min;
		Min.Format(TEXT("%02d"), i);
		m_one.combo_M.AddString(Min);
	}
	m_one.combo_M.SetCurSel(0);

	for (int i = 0; i < 60; i++) {
		CString Sec;
		Sec.Format(TEXT("%02d"), i);
		m_one.combo_S.AddString(Sec);
	}
	m_one.combo_S.SetCurSel(0);

	NowTime();

	SetTimer(0, 1000, NULL);

	m_two.edit_H.SetWindowText(TEXT("00"));
	m_two.edit_M.SetWindowText(TEXT("00"));
	m_two.edit_S.SetWindowText(TEXT("00"));

	m_two.edit_H.SetLimitText(2);
	m_two.edit_M.SetLimitText(2);
	m_two.edit_S.SetLimitText(2);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMy0620MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy0620MFCDlg::OnPaint()
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
HCURSOR CMy0620MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy0620MFCDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_pwndShow != NULL) {
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int index = m_Tab.GetCurSel();

	switch (index) {
	case 0:
		m_one.ShowWindow(SW_SHOW);
		m_pwndShow = &m_one;
		Tab_num = 0;
		break;
	case 1:
		m_two.ShowWindow(SW_SHOW);
		m_pwndShow = &m_two;
		Tab_num = 1;
		break;
	}

	*pResult = 0;
}

// 종료
void CMy0620MFCDlg::OnBnClickedButton4()
{
	if (MessageBox(TEXT("프로그램을 종료하시겠습니까?"), TEXT("종료"), MB_ICONQUESTION | MB_YESNO) == IDYES) {
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_APP_EXIT, NULL);
		KillTimer(0);
	}
}

void CMy0620MFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	NowTime();

	if (flag) {
		if (Tab_num == 0) {
			CTime cTime = CTime::GetCurrentTime();
			int T_year = cTime.GetYear();
			int T_month = cTime.GetMonth();
			int T_day = cTime.GetDay();
			int T_hour = cTime.GetHour();
			int T_min = cTime.GetMinute();
			int T_sec = cTime.GetSecond();
			CString hour, min, sec;
			int i_hour, i_min, i_sec;

			m_one.combo_H.GetLBText(m_one.combo_H.GetCurSel(), hour);
			m_one.combo_M.GetLBText(m_one.combo_M.GetCurSel(), min);
			m_one.combo_S.GetLBText(m_one.combo_S.GetCurSel(), sec);

			i_hour = _ttoi(hour);
			i_min = _ttoi(min);
			i_sec = _ttoi(sec);

			CTime Time_S(T_year, T_month, T_day, i_hour, i_min, i_sec);
			CTime Time_N(T_year, T_month, T_day, T_hour, T_min, T_sec);
			CTimeSpan Sub;

			if (Time_S > Time_N) {
				Sub = Time_S - Time_N;
			}
			else {
				Sub = (Time_S + 86400) - Time_N;
			}

			if (Sub == 1) {
				if (Mode == 0) {
					PowerOff();
				}
				else {
					KillTimer(0);
					system("rundll32.exe PowrProf.dll,SetSuspendState 0,1,0");
				}
			}

			CString Time_T = Sub.Format(TEXT("%H시 %M분 %S초"));
			m_one.edit_T.SetWindowText(Time_T);
		}
		else {
			m_two.S = m_two.S--;
			if (m_two.S < 0) {
				m_two.M--;
				m_two.S = 59;
			}

			if (m_two.M < 0) {
				m_two.H--;
				m_two.M = 59;
			}

			CString temp1, temp2, temp3;
			temp1.Format(TEXT("%02d"), m_two.H);
			temp2.Format(TEXT("%02d"), m_two.M);
			temp3.Format(TEXT("%02d"), m_two.S);

			if (m_two.H < 0) {
				m_two.edit_T.SetWindowText(TEXT("00시 00분 00초"));
				if (Mode == 0) {
					PowerOff();
				}
				else {
					KillTimer(0);
					system("rundll32.exe PowrProf.dll,SetSuspendState 0,1,0");
				}

			}
			else {
				m_two.edit_T.SetWindowText(temp1 + TEXT("시 ") + temp2 + TEXT("분 ") + temp3 + TEXT("초"));
			}
		}
	}	
	CDialogEx::OnTimer(nIDEvent);
}

// 시작
void CMy0620MFCDlg::OnBnClickedButton1()
{
	if (Tab_num == 0) {
		CString H, M, S;
		m_one.combo_H.GetLBText(m_one.combo_H.GetCurSel(), H);
		m_one.combo_M.GetLBText(m_one.combo_M.GetCurSel(), M);
		m_one.combo_S.GetLBText(m_one.combo_S.GetCurSel(), S);

		if (H == "00" && M == "00" && S == "00") {
			MessageBox(TEXT("시간을 입력하세요."), TEXT("종료모드"), MB_ICONQUESTION | MB_OK);
			btn_start.EnableWindow(true);
		}
		else {
			flag = true;
			m_one.combo_H.EnableWindow(false);
			m_one.combo_M.EnableWindow(false);
			m_one.combo_S.EnableWindow(false);
			btn_init.EnableWindow(false);
			btn_start.EnableWindow(false);
		}
	}
	else {
		CString E_H, E_M, E_S, strText;
		int temp;

		m_two.edit_H.GetWindowText(E_H);
		m_two.edit_M.GetWindowText(E_M);
		m_two.edit_S.GetWindowText(E_S);

		if (E_H == "00" && E_M == "00" && E_S == "00") {
			MessageBox(TEXT("시간을 입력하세요."), TEXT("종료모드"), MB_ICONQUESTION | MB_OK);
			btn_start.EnableWindow(true);
		}
		else {
			temp = _ttoi(E_H);
			m_two.H = temp;
			temp = _ttoi(E_M);
			m_two.M = temp;
			temp = _ttoi(E_S);
			m_two.S = temp;
			m_two.edit_T.SetWindowText(E_H + TEXT("시 ") + E_M + TEXT("분 ") + E_S + TEXT("초"));
			flag = true;
			m_two.edit_H.EnableWindow(false);
			m_two.edit_M.EnableWindow(false);
			m_two.edit_S.EnableWindow(false);
			btn_init.EnableWindow(false);
			btn_start.EnableWindow(false);
		}
	}
}

// 초기화
void CMy0620MFCDlg::OnBnClickedButton3()
{
	if (Tab_num == 0) {
		m_one.combo_H.SetCurSel(0);
		m_one.combo_M.SetCurSel(0);
		m_one.combo_S.SetCurSel(0);
	}
	else {
		m_two.edit_H.SetWindowText(TEXT("00"));
		m_two.edit_M.SetWindowText(TEXT("00"));
		m_two.edit_S.SetWindowText(TEXT("00"));
	}
}

void CMy0620MFCDlg::NowTime() {
	CTime cTime = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(TEXT("%02d시 %02d분 %02d초"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	m_one.edit_NT.SetWindowText(strTime);
}

// 일시정지
void CMy0620MFCDlg::OnBnClickedButton2()
{
	if (Tab_num == 0) {
		m_one.combo_H.EnableWindow(true);
		m_one.combo_M.EnableWindow(true);
		m_one.combo_S.EnableWindow(true);
		m_one.edit_T.SetWindowText(TEXT(""));
	}
	else {
		m_two.edit_H.EnableWindow(true);
		m_two.edit_M.EnableWindow(true);
		m_two.edit_S.EnableWindow(true);
		m_two.edit_T.SetWindowText(TEXT(""));
	}

	flag = false;
	btn_init.EnableWindow(true);
	btn_start.EnableWindow(true);
	
}

// 종료&절전모드
void CMy0620MFCDlg::OnBnClickedButton5()
{
	if (Mode == 0) {
		btn_mode.SetWindowText(TEXT("절전모드"));
		Mode = 1;
	}
	else {
		btn_mode.SetWindowText(TEXT("종료모드"));
		Mode = 0;
	}
}


