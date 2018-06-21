
// WindowsShutdownDlg.h: 헤더 파일
//

#pragma once


// CWindowsShutdownDlg 대화 상자
class CWindowsShutdownDlg : public CDialogEx
{
// 생성입니다.
public:
	CWindowsShutdownDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWSSHUTDOWN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
//	int timer_mode;
	afx_msg void OnBnClickedRadio2();
	int mode = 0;
	CComboBox combo_hr;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CComboBox combo_min;
//	CComboBox como_sec;
	afx_msg void OnBnClickedButton1();
	CComboBox combo_sec;
	afx_msg void OnBnClickedButton2();
	CButton btn_start;
	bool timer_active = FALSE;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	CButton radio1;
	CEdit edit_hr;
	CEdit edit_min;
	CEdit edit_sec;
	bool timer_init = TRUE;
	bool alert = FALSE;
	int func_mode = 0;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
