//FindingForm.h

#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H

#include <afxwin.h>
#include "resource.h"
#include "addressBook.h"

class FindingForm : public CDialog {
public :
	enum { IDD = IDD_FINDINGFORM };
public :
	FindingForm(CWnd *parnet = NULL);
	virtual BOOL OnInitDialog();
public :
	int (*indexes);
	int count;
protected :
	afx_msg void OnFindButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR *lpNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	
	DECLARE_MESSAGE_MAP()
};
#endif //_FINDINGFORM_H