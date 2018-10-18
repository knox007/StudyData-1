//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	Ŭ���� (���)
//	
//	[1]	���� ������
//=================================================
/* 
	1.	������ �ʱ�ȭ.

		-	int a = 10;

			int a(10);

			->	c++���� ��� ����.

		-	��ü�� �ʱ�ȭ�� ���� ������� �����ұ�???
*/
//=================================================
/*
class CTest
{
	int _x;

public:
	CTest(int a) { _x = a; }
	void ShowData() { cout << _x << endl; }
};
int main()
{
	int a = 10;
	//int a(10);
	cout << a << endl;

	CTest _test1(10);
	_test1.ShowData();

	CTest _test2 = 20;//	->	CTest _test2(10)���� ������ ����ȯ.
	_test2.ShowData();

	return 0;
}
//*/
//=================================================
/*
	2.	���� �������� ����

		-	���� ������

			-	�ڽŰ� ���� ����( �ڷ��� )�� ��ü�� ���ڷ� ������ �ִ� ������.

			-	������( const ������& �Ű������̸� )

				-	const
					
					-	������ �ȿ��� �Ű�����( ��ü )�� ���뺯���� ���ġ ����.

				-	& (���۷���)

					-	���۷����� ���� ������ ���ѷ����� ������ ��.

					-	������ �����Ϸ��� ����ó������.
*/
//=================================================
/*
class CTest
{
public:
	CTest() { cout << "-- CTest() --" << endl; }

	CTest(int a) { cout << "-- CTest(int a) --" << endl; }

	CTest(const CTest& test) { cout << "-- CTest(const CTest& test) --" << endl; }
};

int main()
{
	CTest test1;
	CTest test2(10);
	CTest test3(test2);

	return 0;
}
//*/
//=================================================
/*
	3 - 1.	����Ʈ ���� ������

		-	Ŭ�������� ���α׷����� ���ǰ� ������ �ڵ����� ���� �Ǵ� ��.
			
			-	����Ʈ ������
				
				-	�ϴ��� ����.

			-	����Ʈ �Ҹ���

				-	�ϴ��� ����.

			-	����Ʈ ���� ������.

				-	�ϴ��� ����!!!!

					-	����������� ����.
*/
//=================================================
/*
class CTest
{
	int _x, _y;

public:
	CTest(int x, int y)	{ _x = x,	_y = y; }
	
	//CTest( const CTest& test)
	//{
	//	_x = test._x;
	//	_y = test._y;
	//}

	void ShowData()		{ cout << _x << " " << _y << endl; }
};


int main()
{
	CTest test1(10, 20);
	CTest test2(test1);

	test1.ShowData();
	test2.ShowData();

	return 0;
}
//*/
//=================================================
/*
	3 - 2.	����Ʈ ���� �������� ������.

		-	���� ����(Shallow Copy)
		
			-	��ü�� ���� ������� ���� ���ο� ��ü�� �����ϴµ� 
			
				���� ��ü�� ����Ÿ���� ����� ������ �ִٸ� �������� ����.

		-	���� ���� (Deep Copy)

			-	��ü ����
			
			-	��ü�� ���� ��� ���(���� �������� ���)�� ����.
			
				��ü�� ���� Ÿ���� ����� ������ ��� �������� ���簡 �ƴ� ������ ��ü ��ü�� ����Ǵ� ��.

		��ó: http://wonjayk.tistory.com/256

*/
//=================================================
/*
class CPersonInfo
{
	char* _pszName;
	char* _pszPhone;
	int _age;

public:
	CPersonInfo(char* pszName, char* pszPhone, int age)
	{
		_pszName = new char[strlen(pszName) + 1];
		_pszPhone = new char[strlen(pszPhone) + 1];

		strcpy(_pszName, pszName);
		strcpy(_pszPhone, pszPhone);
		_age = age;
	}

	~CPersonInfo()
	{
		delete[] _pszName;
		delete[] _pszPhone;
	}

	void ShowData()
	{
		cout << _pszName << endl;
		cout << _pszPhone << endl;
		cout << _age << endl;
	}
};

int main()
{
	CPersonInfo Kim("Kim", "010xxxxxxxx", 20);
	CPersonInfo Kim2 = Kim;

	Kim.ShowData();
	Kim2.ShowData();

	return 0;

//	�����߻�!!!!!
//		������ ? ? ? ?
}

//*/
//=================================================
/*
	Quiz)	���� ������ ��������ڿ� �������縦 �̿��ؼ� �ذ��Ѵ�.
*/
//=================================================
/*
	4.	���� �������� ȣ�� ����.

		1)	������ ������ ��ü�� ���ο� ��ü�� �ʱ�ȭ.

			��)	CTest test1;

				CTest test2 = test1;	->	test2(test1); ������ ��ȯ.

		2)	�Լ� ȣ��� ��ü�� �������� �����ϴ� ���.
			
			��)	
				void Func( CTest test )	{ .... }

				int main()
				{
					CTest _test;

					Func( _test );

					....
				}

				1)	�Ű����� test�� ���� �޸� ���� �Ҵ�.

				2)	test�� _test ����.


		3)	�Լ������� ��ü�� �������� ����.

			��)	
				int GetValue()
				{
					int val = 10;

					return val;
				}

				int main()
				{
					cout<< GetValue()<<endl;
					....
				}

				1)	�Լ��� ȣ���� �������� ���� ����Ǿ� ����.

				2)	ȣ���� �������� ���� Ÿ������ ������ �޸� �Ҵ��� �߻�.


				CTest Func()
				{
					CTest test(10);

					return test;
				}

				int main()
				{
					Func();

					....
				}
*/
//=================================================