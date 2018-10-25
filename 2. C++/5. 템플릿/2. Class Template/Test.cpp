//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	Ŭ���� ���ø�
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
/*	�� �ҽ��� ���ø�ȭ.
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
	�Լ� ���ø����� �޸� Ŭ���� ���ø��� ������� ��ü ������
	
	�ڷ����� ��������� ��������� ��.

	-	����

		-	��ü ������

			1)	�޸� ���� �Ҵ�.

			2)	������ ȣ��.

			3)	���� ���ڸ� �����ؼ� T�� �ڷ��� ����.

				1)	�޸� ������ �Ҵ��� ���� �Ͼ�Ƿ� 

					T�� �ڷ����� �� ���� ��������� �˷���� ��.

				2)	�����ڸ� ���� ���޵Ǵ� ������ �ڷ�����

					�����Ǿ�� �� ���ø��� �ڷ����� �ٸ� ���� ����.
*/
//=================================================
/*
	---------------------------------------
	2.	Ŭ���� ���ø��� ����� ������ �и�
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

		-	" T Ÿ�Կ� ���� ���ø����� ���ǵǾ� �ִ� CData Ŭ���� ���ø� "

	2)	template <typename T>

		-	Ŭ���� ����ο��� �̹� ������ ��� �ߺ� ����.

		-	��� �Լ��� ������ ������ �ݵ�� �ٿ������.


	-	���ø� Ŭ������ ����� ���Ǹ� �ϳ��� ����( �ַ� *.h )���� ����� ��.

		-	���ø��� �����Ϸ��� ���� ó����.

		-	�и��� ������ �������踦 ã���ִ� ���� ��Ŀ�� ����.
*/
//=================================================
/*
	Quiz)	���� ����Ŭ������ ���ø�ȭ �Ѵ�.

		����

		-	�ڷᱸ���� ����

		-	LIFO( Last Input, First Out ) / FILO( First Input, Last Out )

		-	push

			-	������ ����

			pop

			-	������ ������

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