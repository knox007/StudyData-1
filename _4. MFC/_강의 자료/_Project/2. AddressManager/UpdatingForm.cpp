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

ON_NOTIFY(NM_DBLCLK, IDC_LISTVIEW_PERSONALS, &UpdatingForm::OnNMDblclkListviewPersonals)

END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent)
:CDialog(UpdatingForm::IDD, parent) {
	
	this->addressBook = NULL;

}
enum
{
	NUMBER,
	NAME,
	ADDRESS,
	PHONE,
	EMAIL
};
BOOL UpdatingForm::OnInitDialog() {
	
	CDialog::OnInitDialog();		// Overriding
	
	// �ּҷ� ����
	this->addressBook = new AddressBook;
	
	// ����Ʈ�� �������
	_listCtrlAddress = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS));
	_listCtrlAddress->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	_listCtrlAddress->InsertColumn(NUMBER, "��ȣ", LVCFMT_CENTER, 50);		// GetDlgItem�� CWnd * ��ȯ��
	_listCtrlAddress->InsertColumn(NAME, "����", LVCFMT_CENTER, 100);
	_listCtrlAddress->InsertColumn(ADDRESS, "�ּ�", LVCFMT_CENTER, 200);
	_listCtrlAddress->InsertColumn(PHONE, "��ȭ��ȣ", LVCFMT_CENTER, 100);
	_listCtrlAddress->InsertColumn(EMAIL, "�̸����ּ�", LVCFMT_CENTER, 200);
	
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

	_listCtrlAddress->InsertItem(index, number);	
	_listCtrlAddress->SetItemText(index, NAME, personal.GetName().c_str());
	_listCtrlAddress->SetItemText(index, ADDRESS, personal.GetAddress().c_str());
	_listCtrlAddress->SetItemText(index, PHONE, personal.GetTelephoneNumber().c_str());
	_listCtrlAddress->SetItemText(index, EMAIL, personal.GetEmailAddress().c_str());
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
	
	index = _listCtrlAddress->GetSelectionMark();

	if (index == -1)
	{
		AfxMessageBox(TEXT("������ �����͸� �����ϼ���"));
		return;
	}
	
	index = this->addressBook->Correct(index, (LPCSTR)name, (LPCSTR)address, (LPCSTR)telephoneNumber, (LPCSTR)emailAddress);
	
	Personal personal = this->addressBook->GetAt(index);

	_listCtrlAddress->SetItemText(index, NAME, personal.GetName().c_str());
	_listCtrlAddress->SetItemText(index, ADDRESS, personal.GetAddress().c_str());
	_listCtrlAddress->SetItemText(index, PHONE, personal.GetTelephoneNumber().c_str());
	_listCtrlAddress->SetItemText(index, EMAIL, personal.GetEmailAddress().c_str());
}

void UpdatingForm::OnEraseButtonClicked() {
	
	int index;
	CString number;
	
	index = _listCtrlAddress->GetSelectionMark();

	if (index == -1)
	{
		AfxMessageBox(TEXT("������ �����͸� �����ϼ���"));
		return;
	}
		

	index = this->addressBook->Erase(index);
	
	if(index == -1) {
		_listCtrlAddress->DeleteAllItems();
		
		for(int i = 0; i < this->addressBook->GetLength(); i++) {
			Personal personal = this->addressBook->GetAt(i);
			
			number.Format("%d", i + 1);
			_listCtrlAddress->InsertItem(i, number);

			_listCtrlAddress->SetItemText(i, NAME, personal.GetName().c_str());
			_listCtrlAddress->SetItemText(i, ADDRESS, personal.GetAddress().c_str());
			_listCtrlAddress->SetItemText(i, PHONE, personal.GetTelephoneNumber().c_str());
			_listCtrlAddress->SetItemText(i, EMAIL, personal.GetEmailAddress().c_str());
		}
	}
}

void UpdatingForm::OnArrangeButtonClicked() {
	
	// �ּҷϿ��� ����
	this->addressBook->Arrange();
	
	_listCtrlAddress->DeleteAllItems();
	
	CString number;
	
	for(int i = 0; i < this->addressBook->GetLength(); i++) {
		Personal personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		_listCtrlAddress->InsertItem(i, number);
		
		_listCtrlAddress->SetItemText(i, NAME, personal.GetName().c_str());
		_listCtrlAddress->SetItemText(i, ADDRESS, personal.GetAddress().c_str());
		_listCtrlAddress->SetItemText(i, PHONE, personal.GetTelephoneNumber().c_str());
		_listCtrlAddress->SetItemText(i, EMAIL, personal.GetEmailAddress().c_str());
	}
}

void UpdatingForm::OnClose() {

	if(addressBook != NULL) {
		delete addressBook;
	}
	OnOK();
}

void UpdatingForm::OnNMDblclkListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int index = pNMItemActivate->iItem;

	if (index == -1)
	{
		AfxMessageBox(TEXT("�����͸� �����ϼ���"));
		return;
	}

	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;

	name = _listCtrlAddress->GetItemText(index, NAME);
	address = _listCtrlAddress->GetItemText(index, ADDRESS);
	telephoneNumber = _listCtrlAddress->GetItemText(index, PHONE);
	emailAddress = _listCtrlAddress->GetItemText(index, EMAIL);

	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	*pResult = 0;
}