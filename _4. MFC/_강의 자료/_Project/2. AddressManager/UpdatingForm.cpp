//UpdatingForm.cpp

#include "UpdatingForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)

ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
//	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)

ON_WM_CLOSE()

END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent)
:CDialog(UpdatingForm::IDD, parent) {
	
	this->addressBook = NULL;
}

BOOL UpdatingForm::OnInitDialog() {
	
	CDialog::OnInitDialog();		// Overriding
	
	// �ּҷ� ����
	this->addressBook = new AddressBook;
	
	// ����Ʈ�� �������
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(0, "��ȣ", LVCFMT_CENTER, 50);		// GetDlgItem�� CWnd * ��ȯ��
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(1, "����", LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(2, "�ּ�", LVCFMT_CENTER, 200);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(3, "��ȭ��ȣ", LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(4, "�̸����ּ�", LVCFMT_CENTER, 200);
	
	return FALSE;
}

void UpdatingForm::OnRecordButtonClicked() {
	
	// ������ ����
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);

	if (name == "")
	{
		AfxMessageBox(TEXT("�̸��� �Է��ϼ���"));
		return;
	}
	
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	
	if (address == "")
	{
		AfxMessageBox(TEXT("�̸��� �Է��ϼ���"));
		return;
	}

	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	if (telephoneNumber == "")
	{
		AfxMessageBox(TEXT("��ȭ��ȣ�� �Է��ϼ���"));
		return;
	}
	
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	if (emailAddress == "")
	{
		AfxMessageBox(TEXT("�̸����� �Է��ϼ���"));
		return;
	}
	
	// �ּҷϿ� ����
	int index = this->addressBook->Record( (LPCSTR)name, (LPCSTR)address, (LPCSTR)telephoneNumber, (LPCSTR)emailAddress);
	
	// ����Ʈ�信 �׸��߰�
	Personal personal = this->addressBook->GetAt(index);
	
	CString number;
	number.Format("%d", index + 1);
	
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(index, number);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}

void UpdatingForm::OnFindButtonClicked() {
	
	FindingForm findingForm;
	
	// ã�������� ���
	findingForm.DoModal();
}

void UpdatingForm::OnCorrectButtonClicked() {
	
	int index;
	
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	
	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	
	index = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();

	if (index == -1)
	{
		AfxMessageBox(TEXT("������ �����͸� �����ϼ���"));
		return;
	}
	
	index = this->addressBook->Correct(index, (LPCSTR)address, (LPCSTR)telephoneNumber, (LPCSTR)emailAddress);
	
	Personal personal = this->addressBook->GetAt(index);
	
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}

void UpdatingForm::OnEraseButtonClicked() {
	
	int index;
	CString number;
	
	index = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();

	if (index == -1)
	{
		AfxMessageBox(TEXT("������ �����͸� �����ϼ���"));
		return;
	}
		

	index = this->addressBook->Erase(index);
	
	if(index == -1) {
		((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();
		
		for(int i = 0; i < this->addressBook->GetLength(); i++) {
			Personal personal = this->addressBook->GetAt(i);
			
			number.Format("%d", i + 1);
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
			
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
			((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		}
	}
}

void UpdatingForm::OnArrangeButtonClicked() {
	
	// �ּҷϿ��� ����
	this->addressBook->Arrange();
	
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();
	
	CString number;
	
	for(int i = 0; i < this->addressBook->GetLength(); i++) {
		Personal personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
		
		((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
	}
}

void UpdatingForm::OnClose() {

	if(addressBook != NULL) {
		delete addressBook;
	}
	OnOK();
}
/*
void UpdatingForm::OnHdnItemdblclickListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMListView->iItem;

	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;

	name = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 4);

	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);


	*pResult = 0;
}
//*/