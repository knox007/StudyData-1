//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	반환값과 매개변수에 따른 함수의 분류
*/


/*
//-----------------------------
int Add(int num1, int num2)
{
	return num1 + num2;
}
//-----------------------------
void ShowAddResult(int num)
{
	printf("덧셈결과 : %d\n", num);
}
//-----------------------------
int ReadNum()
{
	int num;
	scanf("%d", &num);
	return num;
}
//-----------------------------
void ShowInfo()
{
	printf("두 개의 정수를 입력하면 덧셈결과 출력.\n");
}
//-----------------------------
int main(void)
{
	int result, num1, num2;

	ShowInfo();

	num1 = ReadNum();

	num2 = ReadNum();

	result = Add(num1, num2);

	ShowAddResult(result);

	return 0;
}
//-----------------------------
//*/
//======================================================
/*	quiz 1)	
	
	3개의 정수를 입력받아 가장 작은 수(1)와 가장 큰 수(2)를 출력하는 함수를 만들자.


	int GetMinimum( int a, int b, int c )
	int GetMaximum( int a, int b, int c )
	
	*/













//======================================================
/*
2.	return의 두가지 용도.

		-	값을 반환.
	
		-	함수를 종료.
	
			-	반환형이 void인 함수에서도 return 문을 삽입 가능.

			예)
					void NoReturnFunction( int num )
					{
						......

						if( num < 0 )
							return;

						......
						
					}

*/

/*
void TestFunc()
{
	int a;
	scanf("%d", &a);

	if (a < 10)
		return;

	printf("성공\n");
}

int main()
{
	TestFunc();

	return 0;
}

//*/
//======================================================









//======================================================
/*
3.	함수의 정의와 선언

	-	함수의 정의가 함수의 호출문보다 먼저 등장하는 경우
		
		컴파일러는 이미 컴파일을 통해 해당 함수를 인지한다.

	-	하지만 호출문이 먼저 등장하는 경우 컴파일러는 인지 하질 못한다.

		->	즉, 함수는 호출되기 전에 미리 정의되어야 한다.

	-	컴파일러에게 해당 함수가 이후 어딘가에서 정의한다고 미리 알려줌으로서 에러를 방지한다.

		->	함수의 선언이라고 한다.


4.	함수 선언 방식

		-	반환형	이름( 매개변수 );

			예)	int TestFunc( int a );
				또는
				int TestFunc( int );
*/	

/*
//	void TestFunc();

int main()
{
	TestFunc();

	return 0;
}


void TestFunc()
{
	int a;
	scanf("%d", &a);

	if (a < 10)
		return;

	printf("성공\n");
}
//*/
//======================================================