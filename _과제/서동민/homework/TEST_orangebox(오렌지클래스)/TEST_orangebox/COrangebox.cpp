#include "stdafx.h"
#include "COrangebox.h"


void COrangebox::Add(int addorangebox)
{
	_total += addorangebox;
}
void COrangebox::Minus(int minusorangebox) {
	_total -= minusorangebox;
}
void COrangebox::Init() {
	_total = 0;
}
void COrangebox::Show() {
	cout << "�� = " << _total << endl;
}
COrangebox::COrangebox()
{
	_total = 0;
}


COrangebox::~COrangebox()
{
	cout << "***�Ҹ���***" << endl;
}
