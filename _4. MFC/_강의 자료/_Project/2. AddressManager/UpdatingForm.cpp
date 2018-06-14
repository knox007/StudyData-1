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
	
	// 주소록 생성
	this->addressBook = new AddressBook;
	
	// 리스트뷰 헤더생성
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(0, "번호", LVCFMT_CENTER, 50);		// GetDlgItem은 CWnd * 반환형
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(2, "주소", LVCFMT_CENTER, 200);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 100);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 200);
	
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
	
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(index, number);
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
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
	
	index = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();

	if (index == -1)
	{
		AfxMessageBox(TEXT("편집할 데이터를 선택하세요"));
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
		AfxMessageBox(TEXT("삭제할 데이터를 선택하세요"));
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
	
	// 주소록에서 정리
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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