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
/*
	---------------------------------------
	2.	클래스 템플릿의 선언과 정의의 분리
	---------------------------------------
*/
//=================================================
/*

template <typename T>
class CData
{
	T _data;

public:
	CData(T d);

	void SetData(T d);

	T GetData();

};

template <typename T>
CData<T>::CData(T d)
{
	_data = d;
}

template <typename T>
void CData<T>::SetData(T d)
{
	_data = d;
}

template <typename T>
T CData<T>::GetData()
{
	return _data;
}

//*/

/*
	1)	CData<T>::

		-	" T 타입에 대해 템플릿으로 정의되어 있는 CData 클래스 템플릿 "

	2)	template <typename T>

		-	클래스 선언부에서 이미 선언후 계속 중복 선언.

		-	멤버 함수를 정의할 때마다 반드시 붙여줘야함.


	-	템플릿 클래스의 선언과 정의를 하나의 파일( 주로 *.h )에서 해줘야 함.

		-	템플릿은 컴파일러에 의해 처리됨.

		-	분리된 파일의 연관관계를 찾아주는 것은 링커의 역할.
*/
//=================================================
/*
	Quiz)	다음 스택클래스를 템플릿화 한다.

		스택

		-	자료구조의 일종

		-	LIFO( Last Input, First Out ) / FILO( First Input, Last Out )

		-	push

			-	데이터 저장

			pop

			-	데이터 꺼내기

*/

/*
class CStack
{
	int _topIdx;
	char* _pStack;
	
public:
	CStack(int size = 10);
	~CStack();
	void Push(const char value);
	char Pop();
};

CStack::CStack(int size)
{
	_topIdx = -1;
	_pStack = new char[size];
}

CStack::~CStack()
{
	delete[] _pStack;
	_pStack = NULL;
}

void CStack::Push(const char value)
{
	_pStack[++_topIdx] = value;
}

char CStack::Pop()
{
	return _pStack[_topIdx--];
}

int main()
{
	CStack tmpStack(10);

	tmpStack.Push('a');
	tmpStack.Push('b');
	tmpStack.Push('c');

	for (int i = 0; i < 3; ++i)
		cout << tmpStack.Pop() << endl;

	return 0;
}
//*/

/*
int main()
{
	CStack< char > stackChar(10);
	stackChar.Push('a');
	stackChar.Push('b');
	stackChar.Push('c');


	CStack< int > stackInt(10);
	stackChar.Push(10);
	stackChar.Push(20);
	stackChar.Push(30);


	........

	return 0;
}
*/
//=================================================