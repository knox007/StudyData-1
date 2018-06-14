//=======================================================
//UpdatingForm.cpp
//=======================================================
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>
#include <afxdlgs.h>
//=======================================================
BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)

ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
//	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
ON_WM_CLOSE()
ON_NOTIFY(NM_DBLCLK, IDC_LISTVIEW_PERSONALS, &UpdatingForm::OnNMDblclkListviewPersonals)
ON_NOTIFY(NM_CLICK, IDC_LISTVIEW_PERSONALS, &UpdatingForm::OnNMClickListviewPersonals)
ON_BN_CLICKED(IDC_BUTTON_SAVE, &UpdatingForm::OnBnClickedButtonSave)
ON_BN_CLICKED(IDC_BUTTON_LOAD, &UpdatingForm::OnBnClickedButtonLoad)
ON_BN_CLICKED(IDC_BUTTON_CLEAR, &UpdatingForm::OnBnClickedButtonClear)
END_MESSAGE_MAP()
//=======================================================
UpdatingForm::UpdatingForm(CWnd *parent):CDialog(UpdatingForm::IDD, parent){ this->addressBook = NULL; }
//-----------------------------------------
enum
{
	NUMBER,
	NAME,
	ADDRESS,
	PHONE,
	EMAIL
};
//-----------------------------------------
BOOL UpdatingForm::OnInitDialog()
{
	
	CDialog::OnInitDialog();		// Overriding
	
	// �ּҷ� ����
	this->addressBook = new AddressBook;
	
	// ����Ʈ�� �������
	_listCtrlAddress = ((CListCtrl *)GetDlgItem(IDC_LISTVIEW_PERSONALS));
	_listCtrlAddress->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	_listCtrlAddress->InsertColumn(NUMBER, TEXT("��ȣ"), LVCFMT_CENTER, 50);		// GetDlgItem�� CWnd * ��ȯ��
	_listCtrlAddress->InsertColumn(NAME, TEXT("����"), LVCFMT_CENTER, 100);
	_listCtrlAddress->InsertColumn(ADDRESS, TEXT("�ּ�"), LVCFMT_CENTER, 200);
	_listCtrlAddress->InsertColumn(PHONE, TEXT("��ȭ��ȣ"), LVCFMT_CENTER, 100);
	_listCtrlAddress->InsertColumn(EMAIL, TEXT("�̸����ּ�"), LVCFMT_CENTER, 200);

	_pEditName = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	_pEditAddress = (CEdit*)GetDlgItem(IDC_EDIT_ADDRESS);
	_pEditPhone = (CEdit*)GetDlgItem(IDC_EDIT_TELEPHONENUMBER);
	_pEditEMail = (CEdit*)GetDlgItem(IDC_EDIT_EMAILADDRESS);

	return FALSE;

}//	BOOL UpdatingForm::OnInitDialog()
//-----------------------------------------
CString UpdatingForm::GetListCtrl(int nIdx, int nSubIdx) { return _listCtrlAddress->GetItemText(nIdx, nSubIdx); }
CString UpdatingForm::GetNameFromLC(int nIdx) { return GetListCtrl(nIdx, NAME);}
CString UpdatingForm::GetAddressFromLC(int nIdx) { return GetListCtrl(nIdx, ADDRESS); }
CString UpdatingForm::GetPhoneFromLC(int nIdx) { return GetListCtrl(nIdx, PHONE); }
CString UpdatingForm::GetEMailFromLC(int nIdx) { return GetListCtrl(nIdx, EMAIL); }
//-----------------------------------------
void UpdatingForm::SetListCtrl(int nIdx, LPCTSTR name, LPCTSTR address, LPCTSTR phone, LPCTSTR email)
{
	_listCtrlAddress->SetItemText(nIdx, NAME, name );
	_listCtrlAddress->SetItemText(nIdx, ADDRESS, address );
	_listCtrlAddress->SetItemText(nIdx, PHONE, phone );
	_listCtrlAddress->SetItemText(nIdx, EMAIL, email );

}//	void UpdatingForm::SetListCtrl(int nIdx, LPCTSTR name, LPCTSTR address, LPCTSTR phone, LPCTSTR email)
//-----------------------------------------
void UpdatingForm::OnRecordButtonClicked()
{	
	// ������ ����
	CString name;
	_pEditName->GetWindowText(name);

	if (name == "")
	{
		AfxMessageBox(TEXT("�̸��� �Է��ϼ���"));
		return;
	}
	
	CString address;
	_pEditAddress->GetWindowText(address);
	
	if (address == "")
	{
		AfxMessageBox(TEXT("�̸��� �Է��ϼ���"));
		return;
	}

	CString telephoneNumber;
	_pEditPhone->GetWindowText(telephoneNumber);
	if (telephoneNumber == "")
	{
		AfxMessageBox(TEXT("��ȭ��ȣ�� �Է��ϼ���"));
		return;
	}
	
	CString emailAddress;
	_pEditEMail->GetWindowText(emailAddress);
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
	number.Format(TEXT("%d"), index + 1);

	_listCtrlAddress->InsertItem(index, number);

	SetListCtrl(index, name, address, telephoneNumber, emailAddress);

	ClearAllEBox();

}//	void UpdatingForm::OnRecordButtonClicked()
//-----------------------------------------
void UpdatingForm::OnFindButtonClicked()
{	
	FindingForm findingForm;
	
	// ã�������� ���
	findingForm.DoModal();

}//	void UpdatingForm::OnFindButtonClicked()
//-----------------------------------------
void UpdatingForm::OnCorrectButtonClicked()
{	
	int index;
	
	CString name;
	_pEditName->GetWindowText(name);
	
	CString address;
	_pEditAddress->GetWindowText(address);
	
	CString telephoneNumber;
	_pEditPhone->GetWindowText(telephoneNumber);
	
	CString emailAddress;
	_pEditEMail->GetWindowText(emailAddress);
	
	index = _listCtrlAddress->GetSelectionMark();

	if (index == -1)
	{
		AfxMessageBox(TEXT("������ �����͸� �����ϼ���"));
		return;
	}
	
	index = this->addressBook->Correct(index, (LPCSTR)name.GetBuffer(), (LPCSTR)address.GetBuffer(), (LPCSTR)telephoneNumber.GetBuffer(), (LPCSTR)emailAddress.GetBuffer());
	
	Personal personal = this->addressBook->GetAt(index);

	SetListCtrl(index, name, address, telephoneNumber, emailAddress);

}//	void UpdatingForm::OnCorrectButtonClicked()
//-----------------------------------------
void UpdatingForm::OnEraseButtonClicked()
{	
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
			
			number.Format(TEXT("%d"), i + 1);
			_listCtrlAddress->InsertItem(i, number);

			SetListCtrl(i,
						(LPCTSTR)personal.GetName().c_str(),
						(LPCTSTR)personal.GetAddress().c_str(),
						(LPCTSTR)personal.GetTelephoneNumber().c_str(),
						(LPCTSTR)personal.GetEmailAddress().c_str());
		}
	}
}//	void UpdatingForm::OnEraseButtonClicked()
//-----------------------------------------
void UpdatingForm::OnArrangeButtonClicked()
{	
	// �ּҷϿ��� ����
	this->addressBook->Arrange();
	
	_listCtrlAddress->DeleteAllItems();
	
	CString number;
	
	for(int i = 0; i < this->addressBook->GetLength(); i++)
	{
		Personal personal = this->addressBook->GetAt(i);
		number.Format(TEXT("%d"), i + 1);
		_listCtrlAddress->InsertItem(i, number);
		SetListCtrl(i,
			(LPCTSTR)personal.GetName().c_str(),
			(LPCTSTR)personal.GetAddress().c_str(),
			(LPCTSTR)personal.GetTelephoneNumber().c_str(),
			(LPCTSTR)personal.GetEmailAddress().c_str());

	}//	for(int i = 0; i < this->addressBook->GetLength(); i++)

}//	void UpdatingForm::OnArrangeButtonClicked()
//-----------------------------------------
void UpdatingForm::OnClose()
{
	if(addressBook != NULL) {
		delete addressBook;
	}
	OnOK();
}
//-----------------------------------------
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

	_pEditName->SetWindowText(name);
	_pEditAddress->SetWindowText(address);
	_pEditPhone->SetWindowText(telephoneNumber);
	_pEditEMail->SetWindowText(emailAddress);

	*pResult = 0;
}
//-----------------------------------------
void UpdatingForm::OnNMClickListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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

	_pEditName->SetWindowText(name);
	_pEditAddress->SetWindowText(address);
	_pEditPhone->SetWindowText(telephoneNumber);
	_pEditEMail->SetWindowText(emailAddress);

	*pResult = 0;

}//	void UpdatingForm::OnNMClickListviewPersonals(NMHDR *pNMHDR, LRESULT *pResult)
//-----------------------------------------
void UpdatingForm::OnBnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	char szFilter[] = TEXT("jackie ����(*.jck)|*.jck| All Files(*.*)|*.*||");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();

		strPathName += ".jck";

		FILE *pF = NULL;

		pF = fopen(strPathName, "w");
		if (pF == NULL)
			return;

		//	���� ����.
		int count = _listCtrlAddress->GetItemCount();	

		fprintf(pF, "%d\r\n", count);

		CString name, address, phone, email;
		for (int cur = 0; cur < count; ++cur)
		{
			name = GetNameFromLC(cur);
			address = GetAddressFromLC(cur);
			phone = GetPhoneFromLC(cur);
			email = GetEMailFromLC(cur);
			
			fprintf(pF, "%s %s %s %s\r\n",name, address, phone, email);

		}//	for (int cur = 0; cur < count; ++cur)

		fclose(pF);

		MessageBox(TEXT("���� �Ϸ�"));

		ClearList();

		ClearAllEBox();

	}//	if (IDOK == dlg.DoModal())

}//	void UpdatingForm::OnBnClickedButtonSave()
//-----------------------------------------
void UpdatingForm::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = "jackie ����(*.jck)|*.jck| All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();

		FILE *pF = fopen(strPathName, "r");

		if (pF == NULL)
			return;

		int count;		
		fscanf(pF, "%d\r\n", &count);

		_listCtrlAddress->DeleteAllItems();
		addressBook->EraseAll();
		
		char szName[256] = "";
		char szAddress[256] = "";
		char szPhone[256] = "";
		char szEMail[256] = "";

		for (int cur = 0; cur < count; ++cur)
		{
			fscanf(pF, "%s %s %s %s\r\n", szName, szAddress, szPhone, szEMail);

			addressBook->Record(szName, szAddress, szPhone, szEMail);

			CString name = CString(szName);
			CString address = CString(szAddress);
			CString phone = CString(szPhone);
			CString email = CString(szEMail);

			CString number;
			number.Format("%d", cur + 1);

			_listCtrlAddress->InsertItem(cur, number);

			SetListCtrl(cur, name, address, phone, email);

		}//	for (int cur = 0; cur < count; ++cur)

		fclose(pF);

		MessageBox(TEXT("�б� �Ϸ�"));

		ClearAllEBox();

	}//	if (IDOK == dlg.DoModal())

}//	void UpdatingForm::OnBnClickedButtonLoad()
//-----------------------------------------
void UpdatingForm::ClearAllEBox()
{
	_pEditName->SetWindowText("");
	_pEditAddress->SetWindowText("");
	_pEditPhone->SetWindowText("");
	_pEditEMail->SetWindowText("");

}//	void UpdatingForm::ClearAllEBox()
//-----------------------------------------
void UpdatingForm::ClearList()
{
	_listCtrlAddress->DeleteAllItems();
	if (addressBook != NULL) {
		delete addressBook;
	}
	this->addressBook = new AddressBook;

}//	void UpdatingForm::ClearList()
//-----------------------------------------
void UpdatingForm::OnBnClickedButtonClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ClearList();
	ClearAllEBox();

}//	void UpdatingForm::OnBnClickedButtonClear()
 //-----------------------------------------