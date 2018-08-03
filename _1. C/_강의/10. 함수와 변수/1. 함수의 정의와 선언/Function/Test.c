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
	
	3개의 정수를 입력받아 가장 작은 수(1)와 가장 큰 수(2)를 반환하는 함수를 만들자.


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
	TestFunc();	//	선언이 되어 있지 않다면 컴파일러는 리턴 타입을 int로 간주한다.

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





//======================================================
/*
5.	다양한 종류의 함수 정의 하기.

	1)	하나의 함수내에 둘 이상의 return 문이 존재하는 경우.

	2)	함수의 리턴값으로 연산.

	3)	함수 내에서 다른 함수 사용.
*/


/*
//	1)	하나의 함수내에 둘 이상의 return 문이 존재하는 경우.
//	int Compare(int num1, int num2);	//	선언이 되어 있지 않다면 컴파일러는 리턴 타입을 int로 간주한다.
int main()
{
	int n1, n2;
	printf("두개의 숫자를 입력하세요 : ");
	scanf("%d %d", &n1, &n2);

	printf("두개의 숫자 중 가장 큰 수는 %d 입니다. \n", Compare(n1, n2));

	return 0;
}

int Compare(int num1, int num2)
{
	if (num1 > num2)
		return num1;
	else
		return num2;
}
//*/



/*
//	2)	함수의 리턴값으로 연산.
//	3)	함수 내에서 다른 함수 사용.
//------------------------------
int GetAbs(int num);
int CompareAbs(int num1, int num2);
//------------------------------
int main()
{
	int num1, num2;
	printf("두개의 정수 입력 : ");
	scanf("%d %d", &num1, &num2);

	printf("%d와 %d중 절대값이 큰 수 : %d\n", num1, num2, CompareAbs(num1, num2));

	return 0;
}
//------------------------------
int GetAbs(int num)
{
	if (num < 0)
		return num * (-1);
	else
		return num;
}
//------------------------------
int CompareAbs(int num1, int num2)
{
	if (GetAbs(num1) > GetAbs(num2))
		return num1;
	else
		return num2;
}
//*/
//======================================================


/*	quiz 2)

섭씨 온도를 입력하면 화씨 온도를 반환하는 함수와 
화씨 온도를 반환하면 섭씨 온도를 반환하는 함수를 만들어 확인해보자.

섭씨(Celsius) = (F - 32) / 1.8
화씨(Fahrenheit) = (1.8 x F) + 32

*/
//======================================================