//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	조건부 컴파일

		-	매크로를 사용하여 특정 조건에 따라 소스코드의 일부를
		
			컴파일에 적용하거나 예외 시키는 것.


		-	유형
		
			-	#if ... #endif

			-	#ifdef ... #endif

			-	#ifndef ... #endif
*/
//======================================================
/*
	2 - 1. #if ... #endif

			-	매크로의 조건이 참인가?	
*/

/*
#define ADD 1
#define MINUS 0

int main()
{
	int num1, num2;
	printf("두 개의 정수 입력 : ");
	scanf("%d %d", &num1, &num2);

#if ADD==1	// 또는 #if ADD
	printf("%d + %d = %d\n", num1, num2, num1 + num2);
#endif

#if MINUM
	printf("%d - %d = %d\n", num1, num2, num1 - num2);
#endif

	return 0;
}

//*/
//======================================================
/*
2 - 2. #ifdef ( ifndef ) ... #endif

		-	매크로가 선언되었는가( 선언되지 않았는가 )?

			-	매크로의 값은 중요하지 않음.
*/


/*
#define ADD 1
//	#define ADD

#define MINUS 0
//	#define MINUS

int main()
{
	int num1, num2;
	printf("두 개의 정수 입력 : ");
	scanf("%d %d", &num1, &num2);

#ifdef ADD
	printf("%d + %d = %d\n", num1, num2, num1 + num2);
#endif

#ifdef MINUS
	printf("%d - %d = %d\n", num1, num2, num1 - num2);
#endif

	return 0;
}
//*/
//======================================================
/*
	2 - 3.	#else, #elif

			-	else의 역할과 같음.

			-	#elif는 #if에만 가능.
				
				-	#elif -> #else if

				-	마지막 조건은 #else로 마무리.
*/

/*
#define COUNT 5

int main()
{
#if COUNT == 1
	puts("COUNT = 1");
#elif COUNT == 2
	puts("COUNT = 2");
#elif COUNT == 3
	puts("COUNT = 3");
#else
	puts("COUNT = ???");
#endif

	return 0;
}

//*/
//======================================================
/*
	3 - 1.	기타

		-	매크로를 이용한 문자열화

			-	문자열 안에서 매크로의 매개변수 치환은 발생하지 않음.

				예)	#define STRINGDATA(A, B)	"A는 B이다"

				-	# 연산자 : 매크로내의 매개변수를 문자열로 치환한다.

					-	#define STRINGDATA(A)	#A


			-	문자열은 나란히 선언하면 하나의 문자열로 간주한다.

				예)	char *pStr = "abc""def";

					->	char *pStr = "abcdef";

					->	#define STRINGDATA(A, B)	#A "은(는) " #B "이다"
*/
//======================================================
/*
//	-- Before --
#define STRINGDATA(A, B)	"A은(는) B이다"

int main()
{
	printf("%s\n", STRINGDATA(홍길동, 바보));

	return 0;
}
//*/

/*
//	-- After --
#define STRINGDATA(A, B)	#A "은(는) " #B "이다"

int main()
{
	printf("%s\n", STRINGDATA(홍길동, 바보));

	return 0;
}

//*/
//======================================================
/*
3 - 1.	기타

		-	단순 결합

			-	##	:	매크로함수의 매개변수를 다른 대상( 매개변수, 숫자, 문자, 문자열 등 )과 

						이어줄 때 사용.

				예)	#define LINK(A,B)	A##B
*/

/*
#define LINK(A,B)	A##B

int main()
{
	int link = LINK(10, 04);
	printf("%d\n", link);

	return 0;
}
//*/
//======================================================
/*
	Quiz)	두 값을 입력받아 더 큰수를 구하는 프로그램 작성.

			팁1)	MAX(A,B)라는 매크로를 정의

			팁2)	삼항 연산자를 사용.
*/
//======================================================