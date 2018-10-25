//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	클래스 템플릿
	---------------
*/
//=================================================
/*
class CData
{
	int _data;
public:
	CData(int d) { _data = d; }

	void SetData(int d) { _data = d;  }

	int GetData() { return _data; }
};

int main()
{
	CData d1(0);
	d1.SetData(10);

	CData d2(100);

	cout << d1.GetData() << endl;
	cout << d2.GetData() << endl;
	
	return 0;
}
//*/
//=================================================
/*	위 소스를 템플릿화.
template <typename T>
class CData
{
	T _data;

public:
	CData(T d) { _data = d; }

	void SetData(T d) { _data = d; }

	T GetData() { return _data; }

};


int main()
{
	CData<int> d1(0);
	d1.SetData(10);

	CData<char> d2('a');

	cout << d1.GetData() << endl;
	cout << d2.GetData() << endl;

	return 0;
}
//*/
//=================================================
/*
	함수 템플릿과는 달리 클래스 템플릿을 기반으로 객체 생성시
	
	자료형을 명시적으로 선언해줘야 함.

	-	이유

		-	객체 생성시

			1)	메모리 공간 할당.

			2)	생성자 호출.

			3)	전달 인자를 참조해서 T의 자료형 결정.

				1)	메모리 공간의 할당이 먼저 일어나므로 

					T의 자료형을 그 전에 명시적으로 알려줘야 함.

				2)	생성자를 통해 전달되는 인자의 자료형과

					결정되어야 할 템플릿의 자료형이 다를 수도 있음.
*/
//=================================================
