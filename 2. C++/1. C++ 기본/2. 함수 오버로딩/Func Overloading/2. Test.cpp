/*
	함수 오버로딩

	-	설명

		-	함수의 이름이 같고 매개변수의 타입이나 갯수가 다른 함수들의 정의를 허용.

		-	리턴타입은 고려대상이 아님!!!

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

