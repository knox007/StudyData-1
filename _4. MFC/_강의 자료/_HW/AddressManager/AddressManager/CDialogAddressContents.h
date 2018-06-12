#pragma once


// CDialogAddressContents 대화 상자

class CDialogAddressContents : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAddressContents)

public:
	CDialogAddressContents(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDialogAddressContents();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.	

	void InitCityCBBox();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox _cbboxCity;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
