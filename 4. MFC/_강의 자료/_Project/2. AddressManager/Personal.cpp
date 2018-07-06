#include "Personal.h"

Personal::Personal()
:name(""), address(""), telephoneNumber(""), emailAddress("") {
}

Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
:name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress) { //데이터 멤버(매개변수) 순서
}

Personal::Personal(const Personal& source)
:name(source.name), address(source.address), telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress) {
}

Personal& Personal::operator =(const Personal& source) {

	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}

Personal::~Personal() {
}

bool Personal::IsEqual(const Personal& other) {

	bool ret = false;
	
	if(this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 && this->telephoneNumber.compare(other.address) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}

bool Personal::IsNotEqual(const Personal& other) {

	bool ret = false;
	
	if(this->name.compare(other.name) != 0 || this->address.compare(other.address) == 0 && this->telephoneNumber.compare(other.address) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}

bool Personal::operator ==(const Personal& source) {

	bool ret = false;

	if(this->name.compare(source.name) == 0 && this->address.compare(source.address) == 0 && this->telephoneNumber.compare(source.address) == 0 && this->emailAddress.compare(source.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}


bool Personal::operator !=(const Personal& source) {

	bool ret = false;
	
	if(this->name.compare(source.name) != 0 || this->address.compare(source.address) == 0 && this->telephoneNumber.compare(source.address) != 0 || this->emailAddress.compare(source.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
//Personal.cpp