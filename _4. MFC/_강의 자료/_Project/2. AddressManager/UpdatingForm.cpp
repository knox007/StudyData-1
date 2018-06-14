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
	
	// 주소록 생성
	this->addressBook = new AddressBook;
	
	// 리스트뷰 헤더생성
	_listCtrlAddress = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS));
	_listCtrlAddress->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	_listCtrlAddress->InsertColumn(NUMBER, "번호", LVCFMT_CENTER, 50);		// GetDlgItem은 CWnd * 반환형
	_listCtrlAddress->InsertColumn(NAME, "성명", LVCFMT_CENTER, 100);
	_listCtrlAddress->InsertColumn(ADDRESS, "주소", LVCFMT_CENTER, 200);
	_listCtrlAddress->InsertColumn(PHONE, "전화번호", LVCFMT_CENTER, 100);
	_listCtrlAddress->InsertColumn(EMAIL, "이메일주소", LVCFMT_CENTER, 200);
	
	return FALSE;
}

void UpdatingForm::OnRecordButtonClicked() {
	
	// 개인을 읽음
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);

	if (name == "")
	{
		AfxMessageBox(TEXT("이름을 입력하세요"));
		return;
	}
	
	CString address;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	
	if (address == "")
	{
		AfxMessageBox(TEXT("이름을 입력하세요"));
		return;
	}

	CString telephoneNumber;
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	if (telephoneNumber == "")
	{
		AfxMessageBox(TEXT("전화번호를 입력하세요"));
		return;
	}
	
	CString emailAddress;
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	if (emailAddress == "")
	{
		AfxMessageBox(TEXT("이메일을 입력하세요"));
		return;
	}
	
	// 주소록에 기재
	int index = this->addressBook->Record( (LPCSTR)name, (LPCSTR)address, (LPCSTR)telephoneNumber, (LPCSTR)emailAddress);
	
	// 리스트뷰에 항목추가
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
	
	// 찾기윈도우 출력
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
		AfxMessageBox(TEXT("편집할 데이터를 선택하세요"));
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
		AfxMessageBox(TEXT("삭제할 데이터를 선택하세요"));
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
	
	// 주소록에서 정리
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

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int index = pNMItemActivate->iItem;

	if (index == -1)
	{
		AfxMessageBox(TEXT("데이터를 선택하세요"));
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