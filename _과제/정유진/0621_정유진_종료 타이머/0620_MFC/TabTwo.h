#pragma once


// TabTwo 대화 상자

class TabTwo : public CDialogEx
{
	DECLARE_DYNAMIC(TabTwo)

public:
	TabTwo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabTwo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit_H;
	CEdit edit_M;
	CEdit edit_S;
	CEdit edit_T;
	int H, M, S;
};
