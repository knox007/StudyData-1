#pragma once


// TabOne 대화 상자

class TabOne : public CDialogEx
{
	DECLARE_DYNAMIC(TabOne)

public:
	TabOne(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabOne();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo_H;
	CComboBox combo_M;
	CComboBox combo_S;
	CEdit edit_T;
	CEdit edit_NT;
};
