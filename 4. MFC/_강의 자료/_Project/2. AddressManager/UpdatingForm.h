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
	CEdit *_pEditName;
	CEdit *_pEditAddress;
	CEdit *_pEditPhone;
	CEdit *_pEditEMail;
protected :
	void SetListCtrl(int nIdx, LPCTSTR name, LPCTSTR address, LPCTSTR phone, LPCTSTR email);
	void ClearAllEBox();
	void ClearList();
	CString GetListCtrl(int nIdx, int nSubIdx);
	CString GetNameFromLC( int nIdx);
	CString GetAddressFromLC(int nIdx);
	CString GetPhoneFromLC(int nIdx);
	CString GetEMailFromLC(int nIdx);
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();	
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclkListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonClear();
};
#endif //_UPDATINGFORM_H