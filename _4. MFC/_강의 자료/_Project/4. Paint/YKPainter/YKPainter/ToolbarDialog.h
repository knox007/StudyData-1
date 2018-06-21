#pragma once

#include "ToolbarSetter.h"
#include "DrawObject.h"

// ToolbarDialog ��ȭ �����Դϴ�.

class ToolbarDialog : public CDialogBar
{
	DECLARE_DYNAMIC(ToolbarDialog)

private:
	CStatic m_fgColorBox, m_bgColorBox;

	LineToolbarSetter* m_lineSetter;
	FigureToolbarSetter* m_figureSetter;
	TextToolbarSetter* m_textSetter;

public:
	ToolbarDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ToolbarDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditChange();
	afx_msg void OnRBClicked();
	afx_msg void OnBtnFontClicked();
	afx_msg void OnBtnFontModeClicked();
	afx_msg void OnBtnFontUpdateUI(CCmdUI* pCmdUI);

protected:
	void OnBgClick(void);
	void OnFgClick(void);
public:
	void showTools(TOOLTYPE type);
};
