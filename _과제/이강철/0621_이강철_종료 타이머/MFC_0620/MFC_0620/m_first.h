#pragma once


// m_first 대화 상자

class m_first : public CDialogEx
{
	DECLARE_DYNAMIC(m_first)

public:
	m_first(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~m_first();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CComboBox m_first_combo1;
	CComboBox m_first_combo2;
	CComboBox m_first_combo3;
	CComboBox m_first_combo4;
	afx_msg void OnCbnSelchangeCombo1();	
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();	
	afx_msg void OnCbnSelchangeCombo4();
	CEdit m_first_time;
	afx_msg void OnEnChangeEdit1();
	CEdit m_first_late;
	afx_msg void OnEnChangeEdit2();
};
