//=====================================================
/*
	레퍼런스

		-	이름이 존재하는 메모리 공간(변수)에 하나의 이름을 더 부여하는 행위.

			-	변수에 별명을 붙여주는 행위.

		-	키워드 & 사용.

			-	두가지 용법

				예)
					int nVal = 10;

					int *pVal = &nVal;	//	주소값 얻기.

					int &rVal = nVal;	//	레퍼런스 선언.

			
*/
//=====================================================
#include<iostream>
using namespace std;
//=====================================================
int Func1()
{
	int nVal = 20;
	int &ref = nVal;

	return nVal;
}
int Func2()
{
	int nVal = 20;
	int &ref = nVal;

	return ref;	//	ref는 int형 레퍼런스인데도 반환이 가능하다.
}
int main()
{
	int nVal = 10;

	int &ref = nVal;

	nVal++;
	cout << "nVal : " << nVal <<endl;
	cout << "ref : " << ref << endl;

	ref++;
	cout << "nVal : " << nVal << endl;
	cout << "ref : " << ref << endl;

	cout << "Func1() : " << Func1() << endl;
	cout << "Func2() : " << Func2() << endl;

	return 0;
}
/*
	확인

		-	레퍼런스를 가지고 하는 연산은 해당 참조변수를 가지고 하는 연산과 같은 효과를 지님.

			-	레퍼런스와 변수는 생성과정의 차이만 있을뿐 생성되고나면 거의 같은 것이다.

			-	상황에 따라 아주 미묘한 차이가 있다.

				-	"클래스의 상속과 다형성"에서 다시 언급.
*/
//=====================================================
/*
	주의 사항
		
		-	선언과 동시에 초기화가 되어야함.

		-	상수로 초기화 불가능.
*/
//=====================================================