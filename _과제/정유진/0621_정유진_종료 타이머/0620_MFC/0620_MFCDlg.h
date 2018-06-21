
// 0620_MFCDlg.h: 헤더 파일
//

#pragma once
#include "TabOne.h"
#include "TabTwo.h"


// CMy0620MFCDlg 대화 상자
class CMy0620MFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CMy0620MFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY0620_MFC_DIALOG };
	TabOne m_one;
	TabTwo m_two;
	CWnd* m_pwndShow;
//#endif

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
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();

	int Tab_num = 0;
	afx_msg void OnBnClickedButton3();

	void NowTime();
	bool flag = false;
	CButton btn_init;
	afx_msg void OnBnClickedButton2();
	CButton btn_start;
	int Mode = 0;
	afx_msg void OnBnClickedButton5();
	CButton btn_mode;
};
