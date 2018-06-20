//=====================================================================
// AutoComputerFinishDlg.cpp: 구현 파일
//
//=====================================================================
#include "stdafx.h"
#include "AutoComputerFinish.h"
#include "AutoComputerFinishDlg.h"
#include "afxdialogex.h"
#include <tchar.h>
//=====================================================================
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//=====================================================================
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
	if (!(version_ex_flag = GetVersionEx((OSVERSIONINFO *)&osvi)))
	{
		// 윈도우즈 버전이 낮아서 OSVERSIONINFOEX 형식으로 값을 얻을수 없는 경우...
		// OSVERSIONINFO 형식으로 재설정하고 값을 얻습니다.
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		if (!GetVersionEx((OSVERSIONINFO *)&osvi))
			return -1;

	}//	if (!(version_ex_flag = GetVersionEx((OSVERSIONINFO *)&osvi)))

	// 얻어온 OSVERSIONINFOEX 구조체 변수의 값을 이용하여 버전을 구별합니다.
	switch (osvi.dwPlatformId)
	{
		// NT 기술 기반의 운영체제인 경우
	case VER_PLATFORM_WIN32_NT:
		if (osvi.dwMajorVersion <= 4)
			version = 4;
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			version = 5;
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 && osvi.wProductType == VER_NT_WORKSTATION )
			version = 6;
		else if (version_ex_flag)
			version = 7;
		break;

		// 윈도우즈 9x 기반의 운영체제인 경우
	case VER_PLATFORM_WIN32_WINDOWS:
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
			version = 1;
		else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
			version = 2;
		else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
			version = 3;
		break;

	}//	switch (osvi.dwPlatformId)

	return version;

}//	char GetOSVersionType()
 //=====================================================================
 // 현재 운영체제가 NT 계열인 경우, SE_SHUTDOWN_NAME 레벨의 권한 등급을
 // 가지고 있어야 하기 때문에 아래의 함수를 이용하여 권한을 얻습니다.
char GetNtPrivilege()
{
	HANDLE h_token;
	TOKEN_PRIVILEGES privilege_info;

	// 현재 프로세스의 권한과 관련된 정보를 변경하기 위해 토큰정보를 엽니다.

	// 권한과 관련된 정보 접근에 실패함..
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &h_token))
		return 0;

	// 현재 프로세스가 SE_SHUTDOWN_NAME 권한을 사용할수 있도록 설정한다.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privilege_info.Privileges[0].Luid);
	privilege_info.PrivilegeCount = 1;
	privilege_info.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	// 지정한 값으로 권한을 조정한다.
	AdjustTokenPrivileges(h_token, FALSE, &privilege_info, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	// 권한 조정에 실패한 경우...
	if (GetLastError() != ERROR_SUCCESS)
		return 0;

	return 1;
}//	char GetNtPrivilege()
//=====================================================================
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


// CAutoComputerFinishDlg 대화 상자



CAutoComputerFinishDlg::CAutoComputerFinishDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOCOMPUTERFINISH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoComputerFinishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HOUR, _cboxHour);
	DDX_Control(pDX, IDC_COMBO_MINUTE, _cboxMinute);
	DDX_Control(pDX, IDC_COMBO_MINUTE2, _cboxSecond);
	DDX_Control(pDX, IDC_BUTTON_START, _bttnPlayPause);
	DDX_Control(pDX, IDC_RADIO_COUNTDOWN, _radioCountDown);
	DDX_Control(pDX, IDC_RADIO_COUNTDOWN2, _radioDest);
}

BEGIN_MESSAGE_MAP(CAutoComputerFinishDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CAutoComputerFinishDlg::OnBnClickedButtonSetting)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &CAutoComputerFinishDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CAutoComputerFinishDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CAutoComputerFinishDlg 메시지 처리기

BOOL CAutoComputerFinishDlg::OnInitDialog()
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

	InitCBoxHour();
	InitCBoxMinute();
	InitCBoxSecond();
	InitRadioBttn();

	_eState = STOP;
	_isActive = FALSE;
	_totalTimeInSecond = 0;

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.

}//	BOOL CAutoComputerFinishDlg::OnInitDialog()
//------------------------------------------------
void CAutoComputerFinishDlg::PowerOff()
{
	if (GetOSVersionType() <= 3)
	{
		// 현재 운영체제가 Windows 95, Windows 98, Windows ME 인 경우...
		//*
		//	MessageBox(TEXT("현재 운영체제가 Windows 95, Windows 98, Windows ME 인 경우"));

		ExitWindowsEx(EWX_LOGOFF | EWX_POWEROFF | EWX_SHUTDOWN, 0);
		ExitWindowsEx(EWX_FORCE, 0);
		//*/

	}//	if (GetOSVersionType() <= 3)
	else if (GetNtPrivilege())
	{
		// 현재 운영체제가 Windows NT, Windows 2000, Windows XP 인 경우...
		//*
		//MessageBox(TEXT("현재 운영체제가 Windows NT, Windows 2000, Windows XP 인 경우..."));

		ExitWindowsEx(EWX_FORCE | EWX_POWEROFF, 0);
		//*/

	}//	else if (GetNtPrivilege())
}
//------------------------------------------------
void CAutoComputerFinishDlg::InitCBoxHour()
{	
	for (int cur = 0; cur < 24; ++cur)
	{
		CString tmp;
		tmp.Format(TEXT("%d"), cur);
		_cboxHour.AddString(tmp);
	}

	_cboxHour.SetCurSel(0);	
	_cboxHour.EnableWindow(FALSE);
	

}//	void CAutoComputerFinishDlg::InitCBoxHour()
//------------------------------------------------
void CAutoComputerFinishDlg::InitCBoxMinute()
{
	for (int cur = 0; cur <= 55;)
	{
		CString tmp;
		tmp.Format(TEXT("%d"), cur);
		_cboxMinute.AddString(tmp);

		cur += 5;
	}

	_cboxMinute.SetCurSel(0);
	_cboxMinute.EnableWindow(FALSE);

}//	void CAutoComputerFinishDlg::InitCBoxMinute()
//------------------------------------------------
void CAutoComputerFinishDlg::InitCBoxSecond()
{
	for (int cur = 0; cur <= 55;)
	{
		CString tmp;
		tmp.Format(TEXT("%d"), cur);
		_cboxSecond.AddString(tmp);

		cur += 5;
	}

	_cboxSecond.SetCurSel(0);
	_cboxSecond.EnableWindow(FALSE);

}//	void CAutoComputerFinishDlg::InitCBoxSecond()
//------------------------------------------------
void CAutoComputerFinishDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAutoComputerFinishDlg::OnPaint()
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
HCURSOR CAutoComputerFinishDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//----------------------------------------------------------
#define TIMERID	1000
void CAutoComputerFinishDlg::OnBnClickedButtonSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SetCbBox(TRUE);

}//	void CAutoComputerFinishDlg::OnBnClickedButtonSetting()
//----------------------------------------------------------
void CAutoComputerFinishDlg::SetCbBox(BOOL isActive)
{
	_isActive = isActive;

	_cboxHour.EnableWindow(isActive);
	_cboxMinute.EnableWindow(isActive);
	_cboxSecond.EnableWindow(isActive);

}//	void CAutoComputerFinishDlg::SetCbBox(BOOL isActive)
//----------------------------------------------------------
void CAutoComputerFinishDlg::InitRadioBttn()
{
	_radioCountDown.SetCheck(BST_CHECKED);
}
//----------------------------------------------------------
BOOL CAutoComputerFinishDlg::IsActive() { return _isActive; }
//----------------------------------------------------------
void CAutoComputerFinishDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == TIMERID)
	{
		_totalTimeInSecond -= 1;

		int valHour = _totalTimeInSecond / 3600;
		int valMinute = _totalTimeInSecond / 60;
		int valSecond = _totalTimeInSecond % 60;

		CString szHour, szMinute, szSecond;
		szHour.Format(TEXT("%d"), valHour);
		szMinute.Format(TEXT("%d"), valMinute);
		szSecond.Format(TEXT("%d"), valSecond);

		_cboxHour.SetWindowTextW(szHour);
		_cboxMinute.SetWindowTextW(szMinute);
		_cboxSecond.SetWindowTextW(szSecond);

		if (_totalTimeInSecond <= 0)
		{
			KillTimer(TIMERID);

			MessageBox(TEXT("윈도우를 종료합니다."));

			_bttnPlayPause.SetWindowTextW(TEXT(">"));

			PowerOff();
			return;
		}

	}//	if (nIDEvent == TIMERID)

	CDialogEx::OnTimer(nIDEvent);
}
//----------------------------------------------------------
void CAutoComputerFinishDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
	if (IsActive() != TRUE)
		return;
	//*/
		

	if (_eState == STOP)
	{
		int idxHour = _cboxHour.GetCurSel();
		int idxMinute = _cboxMinute.GetCurSel();
		int idxSecond = _cboxSecond.GetCurSel();

		CString szHour, szMinute, szSecond;
		_cboxHour.GetLBText(idxHour, szHour);
		_cboxMinute.GetLBText(idxMinute, szMinute);
		_cboxSecond.GetLBText(idxSecond, szSecond);

		int valHour = _ttoi(szHour);
		int valMinute = _ttoi(szMinute);
		int valSecond = _ttoi(szSecond);

		if (valHour == 0 && valMinute == 0 && valSecond == 0)
		{
			MessageBox(TEXT("시간을 입력하세요"));
			return;
		}

		_bttnPlayPause.SetWindowTextW(TEXT("||"));

		_eState = PLAY;		

		_totalTimeInSecond = (valHour * 3600) + (valMinute * 60) + valSecond;

		SetCbBox(FALSE);

		SetTimer(TIMERID, 1000, NULL);
	
	}//	if (_eState == STOP)
	else if (_eState == PLAY)
	{
		_eState = PAUSE;

		KillTimer(TIMERID);

		_bttnPlayPause.SetWindowTextW(TEXT(">"));

	}//	else if (_eState == PLAY)
	else if (_eState == PAUSE)
	{
		CString szHour, szMinute, szSecond;

		_cboxHour.GetWindowTextW(szHour);
		_cboxMinute.GetWindowTextW(szMinute);
		_cboxSecond.GetWindowTextW(szSecond);

		int valHour = _ttoi(szHour);
		int valMinute = _ttoi(szMinute);
		int valSecond = _ttoi(szSecond);

		if (valHour == 0 && valMinute == 0 && valSecond == 0)
		{
			MessageBox(TEXT("시간을 입력하세요"));
			return;
		}

		_bttnPlayPause.SetWindowTextW(TEXT("||"));

		_eState = PLAY;

		_totalTimeInSecond = (valHour * 3600) + (valMinute * 60) + valSecond;

		SetCbBox(FALSE);

		SetTimer(TIMERID, 1000, NULL);

	}//	else if (_eState == PAUSE)

}//	void CAutoComputerFinishDlg::OnBnClickedButtonStart()
//----------------------------------------------------------
void CAutoComputerFinishDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(TIMERID);

	_eState = STOP;

	_cboxHour.SetCurSel(0);
	_cboxMinute.SetCurSel(0);
	_cboxSecond.SetCurSel(0);

	_bttnPlayPause.SetWindowTextW(TEXT(">"));
}
//----------------------------------------------------------