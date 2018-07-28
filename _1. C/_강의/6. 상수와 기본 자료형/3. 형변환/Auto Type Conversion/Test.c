//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Auto Type Conversion
*/

//*
int main(void)
{
	double num1 = 153;

	int num2 = 3.1415;

	int num3 = 129;

	char ch = num3;

	printf("정수 153을 실수로 표현 : %f\n", num1);
	printf("실수 3.1415을 정수로 표현 : %d\n", num2);
	printf("int 정수 129을 char타입으로 표현 : %d\n", ch);

	return 0;
}
//*/
//======================================================



//======================================================
/*
2.	심볼릭 상수
*/
/*
#define BULLET_SPEED 20
int main(void)
{
	const int BULLET_POW = 100;

	printf("총알의 속도  : %d\n", BULLET_SPEED);
	printf("총알의 공격력  : %d\n", BULLET_POW);

	return 0;
}

//*/
//======================================================