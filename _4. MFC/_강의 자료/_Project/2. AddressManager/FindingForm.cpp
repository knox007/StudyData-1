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
	
	// ����Ʈ�� �������
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(0, TEXT("��ȣ"), LVCFMT_CENTER, 50);		// GetDlgItem�� CWnd * ��ȯ��
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(1, TEXT("����"), LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(2, TEXT("�ּ�"), LVCFMT_CENTER, 200);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(3, TEXT("��ȭ��ȣ"), LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(4, TEXT("�̸����ּ�"), LVCFMT_CENTER, 200);
	
	return FALSE;
}

void FindingForm::OnFindButtonClicked() {
	
	CString name;
	
	// ������ ����
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	
	if (name == "")
	{
		AfxMessageBox(TEXT("�̸��� �Է��ϼ���"));
		return;
	}

	// �ּҷ� ������ ã��
	UpdatingForm *updatingForm = (UpdatingForm *)CWnd::FindWindow(TEXT("#32770"), TEXT("�ּҷ�"));
	
	if(this->indexes != NULL) {
		delete[] this->indexes;
	}
	
	updatingForm->addressBook->Find( (LPCSTR)name.GetBuffer(), &(this->indexes), &(this->count));

	if (count == 0 )
	{
		AfxMessageBox(TEXT("ã�����ϴ� �����Ͱ� �����ϴ�."));
		return;
	}
	
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();
	
	CString number;
	if(this->count > 0) {
		for(int i = 0; i < this->count; i++) {
			Personal personal = updatingForm->addressBook->GetAt(this->indexes[i]);	
			number.Format(TEXT("%d"), i + 1);
			
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, (LPCTSTR)personal.GetName().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, (LPCTSTR)personal.GetAddress().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, (LPCTSTR)personal.GetTelephoneNumber().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, (LPCTSTR)personal.GetEmailAddress().c_str());
		}
	}
}

void FindingForm::OnListViewItemDoubleClicked(NMHDR *lpNotifyStruct, LRESULT *result) {

	int index = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();

	UpdatingForm *updatingForm = (UpdatingForm *)CWnd::FindWindow(TEXT("#32770"), TEXT("�ּҷ�"));

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


