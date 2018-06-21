
// MFC_0620Dlg.h: 헤더 파일
//

#pragma once

#include "m_first.h"
#include "m_second.h"

// CMFC0620Dlg 대화 상자
class CMFC0620Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC0620Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_0620_DIALOG };
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
	CTabCtrl m_tab_controll;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CWnd* m_pwndShow;
	m_first first;
	m_second second;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void now_time();
	char GetOSVersionType();
	char GetNtPrivilege();
	void PowerOff();
	afx_msg void OnBnClickedCancel();
	CButton m_btc_start;
	CComboBox m_MODE;
	afx_msg void OnCbnSelchangeCombo1();
};
