//AddressBook.h

#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#include "Array.h"
#include "Personal.h"
#include <string>

using namespace std;

class AddressBook {
public :
	AddressBook();
	AddressBook(const AddressBook& source);

	~AddressBook();

	int Record(string name, string address, string telephoneNumber, string emailAddress);
	void Find(string name, int* (*indexes), int *count);
	int Correct(int index, string name, string address, string telephoneNumber, string emailAddress);
	int Erase(int index);
	void EraseAll();
	void Arrange();
	Personal& GetAt(int index);
	Personal& operator [](int index);
	AddressBook& operator =(const AddressBook& source);
	
	int& GetCapacity() const;
	int& GetLength() const;

private :
	Array<Personal> personals;
	int capacity;
	int length;
};

inline int& AddressBook::GetCapacity() const {
	return const_cast<int&>(this->capacity);
}

inline int& AddressBook::GetLength() const {
	return const_cast<int&>(this->length);
}

int CompareByString(void *one, void *other);
int CompareByArray(void *one, void *other);

#endif //_ADDRESSBOOK_H