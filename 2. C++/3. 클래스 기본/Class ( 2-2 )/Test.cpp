//=================================================
#include<iostream>
using namespace std;
//=================================================
//	클래스 (기본2-2)
//=================================================
/* 
	1.	클래스 디자인의 기본 원칙

		-	공통점 묶기, 조금만 알기.

			-	조금만 알기

				-	"정보 은닉"

					-	객체 외부에서 멤버변수에 직접 접근하지 못하도록 함.

					-	일반적으로 멤버변수는 private로 선언.

					-	Get / Set 과 같은 함수로 멤버변수에 접근한다.

			-	공통점 묶기

				-	"캡슐화"

					-	관련 데이터와 함수를 하나의 클래스로 묶음.

					-	멤버변수를 조작하는 함수는 외부함수가 아닌
					
						해당 클래스의 멤버함수로 구성.

					-	Y2K 문제.

						-	당시 운영체제의 연도수를 두자리로 인식.

						-	에러 발생이나 기능 수정시 포커싱을 최소화 할 수 있음.


	
	
	2.	생성자 / 소멸자

		-	생성자

			-	객체 생성과 동시에 멤버변수를 초기화 할 수 있는 인터페이스.

			-	예)	class CTest
					{
						public:

							CTest();
							......
					}

				참고)

					C#, Java 식 초기화.
					
					class CTest
					{
						int a = 10;
						int b = 20;
					}

					->	C/C++ 에서는 허용안됨.


			-	외형적 특징

				-	함수와 유사.

				-	클래스 이름과 동일.

				-	리턴타입, 리턴 값 없음.

			
			
			-	객체가 메모리에 할당되는 과정.

				예)	class CTest				
					{
						int _a,-b;

						public:

							CTest()
							{
								_a = 10;
								_b = 20;
							}
					}

					int main()
					{
						CTest _test;
						.....
					}


					1)	_test 가 메모리에 할당.

					2)	_a,_b는 쓰레기값으로 채워짐.

					3)	생성자 호출.

					4)	_a,_ b 초기화.

	
			-	매개변수가 있는 생성자

				예)	class CTest
					{
						int _a,_b;

						public:
							CTest(int a, int b )
							{
								_a = a;
								_b = b;
							}
					}

					int main()
					{
						CTest _test(1,2);

						CTest _test2 = CTest(1,2);

						.....
					}

			-	public / private 생성자.

				예)	class CTest									
					{
						CTest();

						......
					}

					int main()
					{
						CTest _test;

						....
					}

					-	객체가 생성될까?

					-	고의로 private으로 선언하는 경우.

						예) 디자인패턴( 싱글턴 )

			
			
			-	생성자의 특징

				-	생성자를 정의하지 않으면 컴파일러에 의해 기본 생성자(매개변수가 없는 생성자)가 자동 삽입되며
				
					아무일도 하지 않음.	( 디폴트 생성자. )

					예)
						class CTest
						{
								int _x, _y;

							public:

								void DoSomething() {...}
								.....
						}


						class CTest
						{
								int _x, _y;

							public:

								CTest() {}

								void DoSomething() {...}
								.....
						}
				
					-	생성자가 하나라도 정의되어 있다면 디폴트 생성자는 생성되지 않음.

						예)	class CTest
							{
								int _a, _b;

								public:

									CTest( int a, int b )
									{
										_a = a;
										_b = b;
									}

									......
							}

							int main()
							{
								CTest _test1(1,2);

								CTest _test2;	->	!!!!! 에러발생.
													
													이유는????
							}

				-	오버로딩 가능.

				-	디폴트 매개변수 설정 가능.

			

		-	소멸자

			-	객체가 메모리에서 소멸되는 타이밍에 호출.

			-	동적할당된 멤버변수의 소멸처리나 static 변수등의 처리에 활용.

			-	특징

				-	일종의 함수.

				-	~클래스이름()

				-	리턴값, 매개변수 없음.

				-	오버로딩 안됨.

			-	동적으로 메모리를 할당하는 멤버변수가 있다면

				반드시 소멸자를 정의하여 처리해줘야 함.


			-	소멸자를 정의해주지 않으면 디폴트 소멸자가 자동으로 삽입되며

				아무런 일도 하지않는다.

				예)
				class CTest
				{
						int _x, _y;

					public:

						void DoSomething() {...}
						.....
				}


				class CTest
				{
						int _x, _y;

					public:

						CTest() {}

						~CTest() {}

						void DoSomething() {...}
						.....
				}
*/
//=================================================
/*
	Quiz - 1)	직사각형을 나타내는 CRectangle,
				원을 나타내는 CCircle 클래스를
				다음과 같이 사용할 수 있도록 구현한다.

			CRectangle _rec(가로,세로);
			_rec.GetArea();		//	면적
			_rec.GetGirth();	//	둘레

			CCircle	_circle(반지름);
			_circle.GetArea();	//	면적
			_circle.GetGirth();	//	둘레


	Quiz - 2)	시,분,초를 관리하는 CTime클래스를
				다음과 같이 사용할 수 있도록 구현한다.
		
			CTime _time(시);
			CTime _time(시,분);
			CTime _time(시,분,초);

			_time.ShowTime();		->	xx시 xx분 xx초
			_time.ShowTimeInSec();	->	xx초.

*/
//=================================================
/*
	3 - 1.	this 포인터

		-	자기 참조 포인터.

			-	자기 자신을 가리키는 포인터.

*/
//=================================================

/*
class CTest
{
public:
	CTest * GetThis() { return this; }
};

int main()
{
	CTest* pTest = new CTest();

	cout << pTest << endl;
	cout << pTest->GetThis() << endl;
	
	return 0;
}
//*/


/*
	3 - 2.	this포인터의 활용.

		-	매개변수로 멤버변수 값을 할당할때 

			매개변수의 이름과 멤버변수의 이름이 같을때 구분.
*/

/*
class CTest
{
public:
	int aa, bb;
		
	CTest(int aa, int bb)
	{
		aa = aa;
		bb = bb;
	}
		
	//CTest(int aa, int bb)
	//{
	//	this->aa = aa;
	//	this->bb = bb;
	//}	

	void ShowData()
	{
		cout << aa << "  " << bb << endl;
	}
};

int main()
{
	CTest* pTest = new CTest(3,3);

	//	결과는???
	pTest->ShowData();

	return 0;
}

//*/
//=================================================
