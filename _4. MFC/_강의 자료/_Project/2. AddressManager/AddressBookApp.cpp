//AddressBookApp.cpp

#include "AddressBookApp.h"
#include "UpdatingForm.h"

AddressBookApp addressBookApp;

BOOL AddressBookApp::InitInstance() {

	UpdatingForm updatingForm;
	this->m_pMainWnd = &updatingForm;
	updatingForm.DoModal();

	return TRUE;
}