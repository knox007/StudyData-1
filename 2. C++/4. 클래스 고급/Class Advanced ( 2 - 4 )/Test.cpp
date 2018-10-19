//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[2 - 4]	상속 기본개념
//=================================================
/* 
	1.	기본 개념

		-	상속	

			-	자식 클래스가 부모 클래스의 모든 멤버함수와 멤버변수를

				물려받는 것.

		-	상속 되는 클래스

			-	Super, Base, 부모, 상위 클래스 등.

			상속받는 클래스

			-	Sub, Derived, 자식, 하위 클래스 등.

		-	기본 원리

			-	기존 클래스의 멤버를 새로 정의하는 클래스의 멤버로 포함.
*/
//=================================================
/*
class CPerson
{
	int _age;
	char _szName[20];

public:
	int GetAge() { return _age; }
	char* GetName() { return _szName; }
	CPerson(int age = 1, char *pszName = "None")
	//CPerson(int age, char *pszName )
	{
		_age = age;
		strcpy(_szName, pszName);
	}
};

class CStudent : public CPerson
{
	char _szMajor[30];

public :
	CStudent(char* pszMajor) { strcpy(_szMajor, pszMajor); }
	char* GetMajor() { return _szMajor; }

	void ShowData()
	{
		cout << "이름 : " << GetName() << endl;
		cout << "나이 : " << GetAge() << endl;
		cout << "전공 : " << GetMajor() << endl;
	}
};

int main()
{
	CStudent Kim("국어");
	Kim.ShowData();

	return 0;
}
//*/
/*
	소스 설명

	1)	class CStudent : public CPerson

		-	CStudent클래스가 CPerson 클래스를 상속 받는다( public 상속 )

	2)	CStudent 클래스는 CPerson에 있는 멤버를 모두 포함.
*/

//=================================================
/*
	2.	객체 생성과정

		1)	메모리 공간의 할당( 상속되는 클래스를 감안 )

		2)	자식 클래스 생성자 호출.

			-	호출은 되지만 몸체부분이 실행되진 않는다.

			-	호출된 생성자에 대하여 부모클래스의 어떠한 생성자가

				호출되어야 한다는 선언이 없다면 부모 클래스의 기본 생성자가 호출 및 실행됨.

				-	부모 클래스의 특정 생성자를 호출하려면 부모 클래스의 생성자를 명시적으로 호출.

					CChild( int a ) : CParent( a )처럼 사용한다.( 멤버 이니셜라이저 )


		3)	부모 클래스 생성자 호출 및 실행.

		4)	자식 클래스 생성자 실행.
*/
//=================================================
/*
class CParent
{
public:
	CParent() { cout << "CParent() 호출" << endl; }
	CParent(int a) { cout << "CParent(int a) 호출" << endl; }
};

class CChild : public CParent
{
public :
	CChild() { cout << "CChild() 호출" << endl; }
	CChild(int a) { cout << "CChild(int a) 호출" << endl; }
	//CChild(int a) : CParent( a ) { cout << "CChild(int a) 호출" << endl; }
};

int main()
{
	CChild child1;
	CChild child2(100);

	return 0;
}
//*/
//=================================================
/*
	Quiz)	위의 CStudent 예제가 이름과 나이도 입력 받을수 있도록 수정한다.
*/
//=================================================
/*
	3.	객체 소멸 과정.

		-	자식 클래스의 소멸자가 호출된 뒤,

			부모 클래스의 소멸자가 호출 됨.

			-	자식 클래스는 부모 클래스의 소멸자까지 호출.

				객체 소멸시 부모 클래스의 생성자에서 할당한

				메모리까지 해제할 기회를 제공.
*/
//=================================================
/*
class CParent
{
public:
	CParent() { cout << "CParent() 호출" << endl; }
	~CParent() { cout << "~CParent() 호출" << endl; }
};

class CChild : public CParent
{
public:
	CChild() { cout << "CChild() 호출" << endl; }
	~CChild() { cout << "~CChild() 호출" << endl; }
};

int main()
{
	CChild child;

	return 0;
}
//*/
//=================================================
/*
	4.	세가지 형태의 상속

						|	public		|	protected	|	private		|
	---------------------------------------------------------------------
		public 멤버		|	public		|	protected	|	private		|
	---------------------------------------------------------------------
		protected 멤버	|	protected	|	protected	|	private		|
	---------------------------------------------------------------------
		private 멤버	|	접근 불가	|	접근 불가	|	접근 불가	|
	---------------------------------------------------------------------

	->	private 멤버는 무조건 접근 불가.

		나머지 상속은 본인보다 접근 권한이 넓으면 해당 상속 형태로 변환한다.

		->	private vs 접근 불가 ???
*/
//=================================================
/*
	Quiz)	

		은행 계좌 정보를 관리하는 클래스
		
		class CAccount
		{
			int _money;
			char _accNum[20];

			public :

			CAccount(char* pszAccNum, int money )
			{
				strcpy(_accNum, pAszAccnum);
				_money = money;
			}
		}

		CAccount를 상속받는 CKoreaAccount를 만들어 다음과 같이 사용하는 프로그램 작성.

		단, CKoreaAccount는 이체한도 정보를 가지고 있다.

		int main()
		{
			CKoreaAccount korAcc("계좌번호", 100, 1000(이체한도) );

			korAcc.ShowData();

			return 0;
		}

		결과

			계좌번호 : ....
			계좌 잔액 : ....
			이체 한도 : ......
*/
//=================================================