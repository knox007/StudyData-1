
// AutoComputerFinishDlg.h: 헤더 파일
//

#pragma once


// CAutoComputerFinishDlg 대화 상자
class CAutoComputerFinishDlg : public CDialogEx
{
// 생성입니다.
public:
	CAutoComputerFinishDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOCOMPUTERFINISH_DIALOG };
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

	void InitCBoxHour();
	void InitCBoxMinute();
	void InitCBoxSecond();

	void SetCbBox(BOOL isActive);
	BOOL IsActive();

	int _totalTimeInSecond;

	BOOL _isActive;
public:
	CComboBox _cboxHour;
	CComboBox _cboxMinute;
	CComboBox _cboxSecond;
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
};
