//FindingForm.cpp

#include "FindingForm.h"
#include "UpdatingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm, CDialog)

ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
ON_NOTIFY(NM_DBLCLK, IDC_LISTVIEW_PERSONALS, OnListViewItemDoubleClicked)
ON_WM_CLOSE()

END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent)
:CDialog(FindingForm::IDD, parent) {
	
	this->indexes = NULL;
	this->count = 0;
}

BOOL FindingForm::OnInitDialog() {
	
	CDialog::OnInitDialog();
	
	// 리스트뷰 헤더생성
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(0, "번호", LVCFMT_CENTER, 50);		// GetDlgItem은 CWnd * 반환형
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(2, "주소", LVCFMT_CENTER, 200);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 200);
	
	return FALSE;
}

void FindingForm::OnFindButtonClicked() {
	
	CString name;
	
	// 성명을 읽음
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	
	if (name == "")
	{
		AfxMessageBox(TEXT("이름을 입력하세요"));
		return;
	}

	// 주소록 윈도우 찾음
	UpdatingForm *updatingForm = (UpdatingForm *)CWnd::FindWindow("#32770", "주소록");
	
	if(this->indexes != NULL) {
		delete[] this->indexes;
	}
	
	updatingForm->addressBook->Find( (LPCSTR)name, &(this->indexes), &(this->count));

	if (count == 0 )
	{
		AfxMessageBox(TEXT("찾고자하는 데이터가 없습니다."));
		return;
	}
	
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();
	
	CString number;
	if(this->count > 0) {
		for(int i = 0; i < this->count; i++) {
			Personal personal = updatingForm->addressBook->GetAt(this->indexes[i]);	
			number.Format("%d", i + 1);
			
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		}
	}
}

void FindingForm::OnListViewItemDoubleClicked(NMHDR *lpNotifyStruct, LRESULT *result) {

	int index = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();

	UpdatingForm *updatingForm = (UpdatingForm *)CWnd::FindWindow("#32770", "주소록");

	CString name = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 1);
	CString address = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 2);
	CString telephoneNumber = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 3);
	CString emailAddress = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 4);
	
	(updatingForm->GetDlgItem(IDC_EDIT_NAME))->SetWindowText(name);
	(updatingForm->GetDlgItem(IDC_EDIT_ADDRESS))->SetWindowText(address);
	(updatingForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER))->SetWindowText(telephoneNumber);
	(updatingForm->GetDlgItem(IDC_EDIT_EMAILADDRESS))->SetWindowText(emailAddress);
	((CListCtrl *)updatingForm->GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetSelectionMark(this->indexes[index]);

	if(this->indexes != NULL) {
		delete[] this->indexes;
	}
	OnOK();
}

void FindingForm::OnClose() {

	if(this->indexes != NULL) {
		delete[] this->indexes;
	}
	OnOK();
}


