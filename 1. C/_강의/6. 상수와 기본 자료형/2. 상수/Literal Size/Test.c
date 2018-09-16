//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Literal Size

	int 형으로 표현이 가능한 정수형 상수는 int 형으로 메모리 공간에 저장하기로 규정.

	double 형으로 표현이 가능한 실수형 상수는 double 형으로 메모리 공간에 저장하기로 규정.

	문자형 상수의 경우 컴파일러에 의해 정수로 변환되므로 int형으로 표현된다.

*/
/*
int main(void)
{
	printf("literal int size : %d\n", sizeof(10));
	printf("literal double size : %d\n", sizeof(3.14));
	printf("literal char size : %d\n", sizeof('A'));

	return 0;
}
//*/
//======================================================



//======================================================
/*
2.	심볼릭 상수
*/
//*
#define BULLET_SPEED 20

const int BULLET_COUNT = 10;
int g_nCurBulletCount = 0;

void Shoot()
{
	if (g_nCurBulletCount > BULLET_COUNT)
//	if (g_nCurBulletCount > 10)
		return;

	++g_nCurBulletCount;
}

int main(void)
{
	const int BULLET_POW = 100;	

	printf("총알의 속도  : %d\n", BULLET_SPEED);
	printf("총알의 공격력  : %d\n", BULLET_POW);
	
	return 0;
}

//*/
//======================================================