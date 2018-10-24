//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[4 - 5]	오버라이딩.
//=================================================
/* 
	1.	함수 오버라이딩.

		-	부모 클래스에서 선언된 멤버함수를

			자식 클래스에서 재정의.

		-	자식 클래스에서 재정의된 함수는 

			부모 클래스의 동일한 함수를 가린다.

			-	하지만 시야를 달리하면 볼수 있다.

				->	시야 = 포인터 접근.

*/
//=================================================
/*
class CPerson
{
	public :
		void Sleep() { cout << "CPerson Zzz.." << endl; }
};

class CStudent : public CPerson
{
	public:
		void Sleep() { cout << "CStudent Zzz.." << endl; }
		void Study() { cout << "Study!!" << endl; }
};


int main()
{
	CPerson* pPerson = new CPerson;
	CStudent* pStudent = new CStudent;
	
	pPerson->Sleep();
	pStudent->Sleep();	//	부모와 동일한 함수를 가린다.

	CPerson* pPerson2 = pStudent;
	pPerson2->Sleep();

	delete pPerson;
	delete pStudent;
	pStudent = NULL;
	
	//delete pPerson2;	//	e!!!!!

	return 0;
}
//*/
//=================================================
/*
	2 - 1.	virtual	선언.
		
		-	선언

			-	virtual  반환형  함수이름 ( 매개변수목록 );

		-	정의
		
			-	멤버함수를 가상으로 선언하는 것으로써,

				virtual 키워드를 이용하여 동적으로 바인딩.

				-	바인딩

					-	각종 값들이 확정되어 더이상 변경할 수 없는 구속 상태가 되는 것.

				-	동적 바인딩

					-	실행시간( 런타임 )에 바인딩을 실행.

					-	일반적으로 포인터로 주소를 할당하여 작업 하는 경우.

				-	정적 바인딩

					-	컴파일 시간에 바인딩 실행.

		-	 특징

			-	부모 클래스의 포인터로 가리키건 자식의 포인터로 가리키건

				오버라이딩된 자식 클래스의 함수를 호출.

			-	이미 선언된 함수( 오버라이딩 된 함수 )를 존재하지 않는 함수처럼 취급.

			-	가상 함수의 속성은 상속 됨.

				-	virtual키워드를 사용하던 사용하지 않던 virtual 로 선언된다.

				-	소스 이해도를 높히기위해 virtual 키워드를 붙혀주자.
*/
//=================================================
/*
class CParent
{
public:
	virtual void SayHello() { cout << "난 부모" << endl; }
};

class CChild : public CParent
{
public:
	virtual void SayHello() { cout << "난 자식" << endl; }
};

int main()
{
	CChild* pChild = new CChild;
	pChild->SayHello();

	CParent* pParent = pChild;
	pParent->SayHello();

	delete pChild;

	return 0;
}
//*/
//=================================================
/*
	2 - 2.	virtual	선언.

		-	오버라이딩 된 함수 호출.

			-	virtual 선언된 함수는 죽지않는다.

				다만 가려질 뿐이다.

*/
//=================================================
/*
class AAA
{
public:
	virtual void Func() { cout << "AAA" << endl; }
};

class BBB : public AAA
{
public:
	virtual void Func()
	{
		AAA::Func();				//	1)
		cout << "BBB" << endl;
	}
};

int main()
{
	AAA* pA = new BBB;

	cout << "-- First Test --" << endl;
	pA->Func();

	cout << "-- Second Test --" << endl;
	pA->AAA::Func();				//	2)
	
	delete pA;

	return 0;
}
//*/

/*
	방법 1)

		-	상황에 따라 유용.

		-	자식 클래스들의 특정기능을 실행하기전에

			공통으로 처리해야할 부분이 있을때 유용.

	방법 2)

		-	거의 사용하지 않음.

		-	클래스 디자인 자체를 수정해야할 여지가 있는지 

			고민할 필요 있음.
*/
//=================================================
/*
	3.	순수 가상함수와 추상 클래스.

		1)	순수 가상 함수
			
			-	선언

				-	virtual void SayHello() = 0;
				
			-	진짜로 존재하지 않는 ( 함수의 몸체가 존재하지 않는 )가상의 함수.

			-	선언만 하고 정의 하지 않음.

		
		2)	추상 클래스

			-	순수 가상 함수가 하나 이상 있는 클래스.

			-	객체화 하지 못함.

				변수나 인스턴스를 만들지 못함.

				-	함수의 정의가 생략되었으므로( 순수 가상함수를 사용함으로 )

					완전한 클래스가 아님.
			
			-	객체화할 필요가 없는 클래스이므로

				인터페이스의 기능만 할 뿐.
				
*/
//=================================================
/*
class CAnimal
{
protected:
	char _szName[30];

public:
	CAnimal(char* pszName) { strcpy(_szName, pszName); }
	const char* GetName() { return _szName; }
	virtual void MakeVoice() = 0;		// 순수 가상함수.
};

int main()
{
	CAnimal animal("Cat");

	animal.MakeVoice();

	return 0;
}
//*/
//=================================================
/*
	Quiz - 1)	위의 CAnimal을 상속받는 동물 클래스를 구현한뒤
	
				각 동물들의 이름과 울음소리( MakeVoice() )를 출력하는 프로그램을 만든다.

*/
//=================================================
/*
	4.	virtual 소멸자
*/
//=================================================
/*
class CParent
{
public :
	~CParent() { cout << "~CParent" << endl; }
};

class CChild : public CParent
{
public :
	~CChild() { cout << "~CChild" << endl; }
};

int main()
{
	CParent* pParent = new CChild();
	CChild* pChild = new CChild();

	delete pParent;
	delete pChild;

	return 0;
}
//*/

/*
	분석
	
		-	pParent는 CChild 타입의 객체를 가리키고 있지만

			CParent 타입의 포인터로 가리키고 있으므로

			CChild 객체를 CPaent객체로 인식.

	해결

		-	~CParent()를 virtual로 선언.

		-	과정.

			1)	CParent 소멸자 호출 시도.

			2)	소멸자가 virtual 이므로 CChild 소멸자를 호출.

				-	비록 이름은 다르지만( ~CParent(), ~CChild() )

					둘다 소멸자인 관계로 virtual 함수를 오버라이딩 했을때의

					현상이 그대로 적용.

			3)	CChild의 소멸자는 CParent를 상속받으므로 다시 CParent의 소멸자 호출.

*/
//=================================================
/*
	Quiz - 2)
		
		근로자의 이름과 급여를 관리하는 프로그램을 만든다.

		1)	추상클래스로 근로자 클래스를 만든뒤,

			정규직, 일용직, 파트타임의 자식 클래스를 만든다.

		2)	근로자 매니저 프로그램을 만든다.

			근로자 매니저에 근로자를 등록하고 조회하는 기능을 넣는다.

			매니저는 근로자를 최대 10명만 등록하도록 한다.

		
			정규직 - 월급.

			일용직 - 근무 일수 * 일당.

			파트 타임 - 총 근무 시간 * 시간 수당.


		실행)

			--- 근로자 등록 ---

			이름 : 김구라

			1) 정규직	2) 일용직	3) 파트타임
			고용타입 : 1

			월급 : 100

			
			--- 근로자 등록 ---

			이름 : 유재석

			1) 정규직	2) 일용직	3) 파트타임
			고용타입 : 3

			총 근무 시간 : 10
			시간수당 : 3


			-- 조회 --

			1) 김구라	정규직		100만원
			2) 유재석	파트타임	30만원



*/




























































/*	Quiz - 1)
class CAnimal
{
	protected:
		char _szName[30];

	public:
		CAnimal(char* pszName) { strcpy(_szName, pszName); }
		const char* GetName() { return _szName; }
		virtual void MakeVoice() = 0;		// 순수 가상함수.
};


class CCat : public CAnimal
{
	public:
		CCat(char *pszName) : CAnimal(pszName) {}
		virtual void MakeVoice() { cout << "Meow" << endl; }
};


class CDog : public CAnimal
{
public:
	CDog(char *pszName) : CAnimal(pszName) {}
	virtual void MakeVoice() { cout << "BowWow" << endl; }
};



int main()
{
	CCat cat("Nero");
	CDog dog("Baduk");

	CAnimal* pAnimal[2] = { &cat, &dog };

	for (int i = 0; i < 2; i++)
	{
		cout <<"이름 : "<<pAnimal[i]->GetName() << endl;
		cout << "소리 : ";
		pAnimal[i]->MakeVoice();
		cout << endl;
	}

	return 0;
}
//*/