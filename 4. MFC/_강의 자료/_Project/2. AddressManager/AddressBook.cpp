//AddressBook.cpp

#include "AddressBook.h"

using namespace std;

AddressBook::AddressBook(const AddressBook& source)
:personals(source.personals) {
	
	this->capacity = source.capacity;
	this->length = source.length;
}

AddressBook::~AddressBook() {
}

AddressBook::AddressBook()
:personals(10) {
	
	this->capacity = 10;
	this->length = 0;
}

Personal& AddressBook::operator [](int index) {
	
	return this->personals[index];
}

int AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress){
	int index;
	
	Personal personal(name, address, telephoneNumber, emailAddress);
	
	if(this->length < this->capacity) {
		index = this->personals.Store(this->length, personal);
	}
	else {
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;
	return index;
}
void AddressBook::EraseAll()
{
	int length = personals.GetLength();
	if( length > 0 )
		personals.DeleteAll();
}
int AddressBook::Erase(int index) {
	
	index = this->personals.Delete(index);
	this->capacity--;
	this->length--;
	
	return index;
}

void AddressBook::Find(string name, int* (*indexes), int *count) {
	
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareByString);
}

int AddressBook::Correct(int index,string name, string address, string telephonNumber, string emailAddress) {
	
	Personal personal(name, address, telephonNumber, emailAddress);
	index = this->personals.Modify(index, personal);
	
	return index;
}

Personal& AddressBook :: GetAt(int index){
	return this->personals.GetAt(index);
}

int CompareByString(void *one, void *other) {
	
	return ((Personal *)one)->GetName().compare(*((string *)other));
}

int CompareByArray(void *one, void *other) {
	
	return ((Personal *)one)->GetName().compare(((Personal *)other)->GetName());
}

void AddressBook::Arrange() {
	this->personals.SelectionSort(CompareByArray);
}
