/*
	디폴트 매개변수

	-	형식

		-	반환타입	함수이름	(매개변수 = 초기값)

	-	매개변수를 전달하지 않으면 매개변수에 초기값으로 할당한 값이 전달된다.
*/
#include<iostream>

using namespace std;

//*
int Func(int a = 0) { return a + 1; }
int main()
{
	cout << Func(10) << endl;
	cout << Func() << endl;

	return 0;
}
//*/


/*
	디폴트 매개변수 설정

	-	함수의 선언이 함수 정의 이전에 존재하면 

		디폴트 매개변수는 선언부분에 위치.

	-	매개변수가 2개 이상 있을때
	
		디폴트 매개변수는 마지막에 위치.
	
*/

/*
int BoxVolume(int length, int width = 1, int height = 1);

int main()
{
	cout << "[3,3,3] : " << BoxVolume(3, 3, 3) << endl;
	cout << "[5,5,def] : " << BoxVolume(5,5) << endl;
	cout << "[7,def,def] : " << BoxVolume(7) << endl;


	return 0;
}

int BoxVolume(int length, int width, int height)
//int BoxVolume(int length, int width = 1, int height = 1)
{
	return length * width * height;
}
//*/

/*
	디폴트 매개변수와 함수 오버로딩.
*/

/*
int Func()				{ return 10; }
int Func(int a = 10)	{ return a + 5; }

int main()
{
	cout << Func(10) << endl;
	//cout << Func() << endl;

	return 0;
}
//*/