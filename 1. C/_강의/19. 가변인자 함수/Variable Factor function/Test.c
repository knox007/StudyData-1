//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	가변인자 함수.

		-	printf, scanf 처럼 전달인자의 수가 제한되어 있지 않은 함수.

		-	사용.

			-	#include <stdarg.h>	선언.

				va_list		:	가변인자를 가리킬 수 있는 참조자 선언.

				va_start	:	참조 대상과 범위 지정.

				va_arg		:	전달된 정보 추출.

				va_end		:	참조자가 가변인자를 가리키지 않도록 해제.

				...			:	가변인자.



	2.	자료형이 다른 가변 인자 함수 만들기 

		-	https://dojang.io/mod/page/view.php?id=578
*/


//*

#include<stdarg.h>

int Sum(int count, ...);	//	가변인자 함수는 호출될 때 인자의 수가 결정된다.

int main()
{
	printf("1 + 2 = %d\n", Sum(2, 1, 2));
	printf("1 + 2 + 3 = %d\n", Sum(3, 1, 2, 3));
	printf("1 + 2 + 3 + 4 = %d\n", Sum(4, 1, 2, 3, 4));

	return 0;
}

int Sum(int count, ...)
{
	int sum = 0;

	va_list vList;

	va_start(vList, count);

	for (int i = 0; i < count; ++i)
		sum += va_arg(vList, int);

	va_end(vList);

	return sum;
}

//*/
//======================================================
/*
	Quiz)	가변 인자를 이용하여 4칙연산과 평균을 구하는 프로그램 작성.
*/
//======================================================