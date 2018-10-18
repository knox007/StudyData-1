//=================================================
#include<iostream>
using namespace std;
//=================================================
//	클래스 (기본)
//=================================================
/* 
	1.	구조체와 클래스

		-	구조체 등장 배경

			-	프로그램의 관리와 작업의 편리를 위해 관련있는 데이터를 그룹화.

		-	프로그램

			->	데이터 + 데이터를 조작하는 루틴( 함수 )

			->	구조체 + 함수	->	구조체와 함수를 묶어서 사용.
*/
//=================================================
/*
	Quiz - 1)	이름, 금액을 멤버변수로 하는 구조체를 만든다.

				입금, 출금, 잔액조회를 출력하는 프로그램 작성.


	Quiz - 2)	위의 구조체에 입금, 출금, 잔액 조회 함수를 넣어서 프로그램 작성
*/
//=================================================
/*
	2.	클래스와 객체

		-	용어 정리

			1)	데이터 추상화

				-	어떤 사물을 데이터 적인 측면과 기능적 측면을 통해 정의 하는 것.

					예)	코끼리	-	기능적	측면	-	코로 목욕

													-	코로 물건을 집음


								-	데이터적 측면	-	발 4개

													-	긴 코

													-	몸무게 1톤

			2)	클래스

				-	추상화 된 사물( 데이터 + 기능적 측면 )을 가지고 자료형을 정의.

				-	선언

					-	주로 멤버변수와 함수의 선언들로 구성된 부분.

					정의

					-	주로 멤버함수의 정의로 구성된 부분.

			3)	객체, 인스턴스

				-	클래스를 이용해 정의된 변수.
*/
//=================================================
/*
	3.	클래스 멤버의 접근제어.

		-	public		:	클래스 내부/외부 모두 공개.

			protected	:	클래스 내부/외부 모두 비공개.

							자식 클래스에게는 공개.

			private		:	클래스 내부/외부 모두 비공개.

		
		-	디폴트 접근제어( 접근제어자가 없는 경우 )

			클래스		:	private

			구조체		:	public


		-	public	>	protected	>	private
*/
//=================================================
/*
	4.	멤버함수 외부 정의.

		-	멤버함수를 클래스 외부에 정의하기.

			class CTest
			{
				public :
					void Play();
					......
			}

			void CTest::Play()
			{ .... }

			-	반환형	클래스이름::함수이름(매개변수)
				{ 
					.......
				}
		
		-	클래스 멤버함수의 inline화.

			-	방법

				1)	클래스 내부에 함수 정의.

				2)	클래스 외부에 정의한 함수 앞에 inline 선언.

					예)	inline void CTest::Play()	{ ..... }

					-	최신 컴파일러는 코드 최적화를 수행하기 때문에 inline 키워드가 큰의미 없음.

		-	파일 분할

			-	선언	:	Header 파일

				정의	:	cpp 파일

				
*/
//=================================================
/*
	Quiz - 3)

		4칙 연산을 하는 계산기 클래스를 구현한다.

		예)	CCalculator cal;

			cal.Init();	//	멤버변수 초기화.

			cal.Sum(1,2);
			cal.ShowResult();
			cal.Minus(5,2);
			cal.ShowResult();
			cal.Multi(2,3);
			cal.ShowResult();
			cal.Divide(4,2);
			cal.ShowResult();


*/
//=================================================
















//=================================================
/* Quiz - 2)
struct SAccount
{
	char _name[30];
	int _money;

	void Deposit(int money)	{ _money += money; }
	void WithDraw(int money) { _money -= money; }
	void ShowMetheMoney() { cout << "Money is " << _money << endl; }
};

//class SAccount
//{
//public:
//	char _name[30];
//	int _money;
//
//	void deposit(int money)	{ _money += money; }
//	void withdraw(int money) { _money -= money; }
//	void showmethemoney() { cout << "money is " << _money << endl; }
//};

int main()
{
	SAccount myAccount = { "홍길동", 10000 };

	myAccount.Deposit(1000);
	myAccount.ShowMetheMoney();

	myAccount.WithDraw(500);
	myAccount.ShowMetheMoney();

	return 0;

}//	int main()
//*/
 //=================================================