//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	while 의 구성

	-	반복 조건
	-	반복 구간
	-	반복조건을 무너뜨리는 연산.

*/


/*
int main(void)
{
	int num = 0;
		
	while (num < 5)
	{
		printf("Hello !! %d 회 출력\n", num + 1);
	
		++num;	//	반복 조건을 무너뜨리기위한 연산.

				//	주석 처리후 결과 확인 해볼것.
	}

	//	2.	반복의 대상이 하나의 문장이라면 중괄호 생략 가능.
	//	while (num < 5)
	//		printf("Hello !! %d 회 출력\n", num + 1), ++num;

	return 0;
}
//*/
//======================================================
/*	quiz)
	숫자를 하나 입력 받으면 그 숫자에 대한 구구단을 출력한다.*/



//======================================================
/*
3.	무한 루프		
	-	필요에 의해 무한루프를 만들기도 한다.
*/


//*
int main(void)
{
	int num = 0;

	printf("input number : ");
	scanf("%d", &num);
	while (num !=0)
	{
		printf("%d x %d = %d\n", 2, num, 2 * num);

		printf("input number : ");
		scanf("%d", &num);
	}

	return 0;
}
//*/
//======================================================
/*	quiz)
숫자를 하나 입력 받으면 그 수 만큼 3의 배수를 출력한다.

예) 4 입력 -> 3 6 9 12 출력 */

/*
int main(void)
{
	int inputNum = 0;

	printf("숫자를 입력하세요 : ");
	scanf("%d", &inputNum);

	int cur = 1;
	while (cur <= inputNum)
	{
		printf("%d x %d = %d\n", 3, cur, 3 * cur);

		++cur;
	}

	return 0;
}
//*/

//======================================================
/*
4.	while 문의 중첩.
	
	-	while 문 내부에서 while문을 사용할 수 있다.
*/



/*
int main(void)
{
	int main = 2;
	int sub = 0;

	while ( main < 10 )
	{
		sub = 1;
		printf("--------------------------\n");
		printf(" %d 단\n", main);
		printf("--------------------------\n");
		while ( sub < 10 )
		{
			int mul = main * sub;

			printf("%d x %d = %d\n", main, sub, mul);

			++sub;

		}//	while (sub < 10)
		
		++main;

	}//	while ( main < 10 )

	return 0;

}//	int main(void)

//*/
//======================================================