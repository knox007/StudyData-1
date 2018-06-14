//UpdatingForm.h

#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H

#include <afxwin.h>
#include <afxcmn.h>
#include "resource.h"

class AddressBook;		// ptr 사용위해 전방선언
class UpdatingForm : public CDialog {
public :
	enum { IDD = IDD_UPDATINGFORM };
public :
	UpdatingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
public :
	AddressBook *addressBook;
	CListCtrl *_listCtrlAddress;
protected :
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();	
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclkListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult);
};
#endif //_UPDATINGFORM_H