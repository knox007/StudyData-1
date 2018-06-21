#pragma once


// m_second 대화 상자

class m_second : public CDialogEx
{
	DECLARE_DYNAMIC(m_second)

public:
	m_second(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~m_second();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_second_hour;
	CComboBox m_second_min;
	CComboBox m_second_sec;
	CEdit m_second_nowtime;
	CEdit m_second_latetime;
	CEdit m_second_endtime;
	CEdit t_hour;
	CEdit t_min;
	CEdit t_sec;
	CString down_hour;
	CString down_min;
	CString down_sec;
};
