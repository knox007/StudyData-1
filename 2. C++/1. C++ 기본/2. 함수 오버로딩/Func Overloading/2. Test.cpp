/*
	�Լ� �����ε�

	-	����

		-	�Լ��� �̸��� ���� �Ű������� Ÿ���̳� ������ �ٸ� �Լ����� ���Ǹ� ���.

		-	����Ÿ���� �������� �ƴ�!!!

*/

#include <iostream>

using namespace std;

int Func()	{ return 10; }
//void Func() { return; }

int Func(int a, int b)			{ return a + b; }
//float Func(float a, float b)	{ return a + b; }
//float Func(int a, int b)		{ return a + b; }
//float Func(float a)			{ return a * 2; }


int main()
{
	cout << Func(10,20) << endl;
	cout << Func() << endl;
	return 0;
}

