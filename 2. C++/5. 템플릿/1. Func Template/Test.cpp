//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	템플릿
	---------------

		-	Template	:	형판, 견본, 본보기

		-	삼각 모형자 비유

			-	삼각형을 그릴 수 있는 틀이 준비되어 있음.

			-	어떤 색의 필기구를 사용하느냐에 따라

				삼각형의 색이 결정 됨.


		-	삼각 모형자 개념을 프로그래밍에 비유.

			-	틀은 준비되어 있지만 색이 정해져 있지 않음.

			-	기능은 정해져 있지만 자료형은 정해져 있지 않음.

			-	삼각형 틀 : 기능, 역할

				색연필 : 데이터

				색 : 데이터 타입.

	------------------------------
	2.	템플릿의 선언 및 사용
	------------------------------

		-	선언

			1)	____ Add(___ a, ___ b) { return a + b; }


			2)	데이터 타입을 "T"로 치환.

				-	T Add(T a, T b) { return a + b; }


			3)	컴파일러는 T 라는 자료형을 인식 못하므로

				template 키워드를 사용하여 템플릿 타입임을 명시해준다.


				template< typename T > 또는 template< class T >

				T Add(T a, T b) { return a + b; }

		-	사용
		
			template< typename T >

			T Add(T a, T b) { return a + b; }

			int main()
			{
				cout << Add(1, 3) << endl;

				cout << Add(1.1f, 3.2f) << endl;

				return 0;

			}

			->	템플릿으로 정의된 함수의 자료형이 결정되는 시점은

				인자가 전달되는 시점이다.

*/
//=================================================
/*
//	함수 템플릿.
template <typename T>
T Add(T a, T b) { return a + b; }

int main()
{
	//	템플릿 함수.
	cout << Add(10, 20) << endl;		//	템플릿으로 정의된 함수의 자료형이 결정되는 시점!!
	cout << Add(1.1f, 2.2f) << endl;
	
	return 0;
}
//*/
//=================================================
/*
	-----------------------------------
	3.	둘 이상의 타입에 대한 템플릿화.
	-----------------------------------

		-	위 템플릿 함수 Add를 다음과 같이 호출해보자.

			cout << Add(1, 2.2f) << endl;

			에러의 원인은???

		-	선언

			template < typename T1, typename T2 >
*/
//=================================================
/*
template < typename T1, typename T2 >
void ShowData(T1 a, T2 b)
{
	cout << a << endl;
	cout << b << endl;
}

int main()
{
	ShowData(1, 2);
	ShowData(1, 2.5f);

	return 0;
}
//*/
//=================================================
/*
	-------------------------
	4.	함수 템플릿의 특수화.
	-------------------------

		-	최신 컴파일러에선 자동으로 처리해주는 듯.
*/
//=================================================
/*
template <typename T>
int GetSize(T a) { return sizeof(a); }

//	template<>
int GetSize(char *a) { return sizeof(a); }

int main()
{
	int a = 10;
	double b = 2.2;
	char* pStr = "Hello";

	cout << GetSize(a) << endl;
	cout << GetSize(b) << endl;
	cout << GetSize(pStr) << endl;

	return 0;
}
//*/
//=================================================
/*
	Quiz)	사칙 연산 프로그램을 함수 템플릿으로 만든다.
*/
//=================================================