//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	일반적인 if 문의 활용
*/


/*
int main(void)
{
	int num;

	printf("정수를 입력하세요 : ");
	scanf("%d", &num);

	if (num < 0)
		printf("입력값은 0 보다 작습니다.\n");	//	if 문 밑에 중괄호가 없다면 한 문장만 if문에 적용된다.

	if (num > 0)
		printf("입력값은 0 보다 큽니다.\n");

	if (num == 0)
		printf("입력값은 0 입니다.\n");

	return 0;
}
//*/
//======================================================
/*	quiz 1)	
	1. 덧셈   2. 뺄셈   3. 곱셈  4. 나눗셈
	연산방식을 선택하세요 : 3	
	두개의 실수를 입력하세요. 2.13 5.12
	결과 : 10.956800

	*/







//======================================================
/*
2.	일반적인 if 문의 문제점

	-	num의 조건이 0보다 작다하더라도 이하 조건들을 모두 실행한다.
		-	하나의 조건이 만족했을때 이하 조건 체크는 무의미 하므로 건너띄도록해야한다.

	-	if ~ else 문으로 이하 조건은 건너띈다.
		-	else문은 if키워드와 더불어 사용된다.		
*/



/*
int main(void)
{
	int num;

	printf("정수를 입력하세요 : ");
	scanf("%d", &num);

	if (num < 0)
		printf("입력값은 0 보다 작습니다.\n");	//	if 문 밑에 중괄호가 없다면 한 문장만 if문에 적용된다.
	else if (num > 0)
		printf("입력값은 0 보다 큽니다.\n");
	else
		printf("입력값은 0 입니다.\n");

	return 0;
}
//*/
//======================================================
/*	quiz 2)
	quiz 1)에 else를 적용해보자.

*/






//======================================================
/*
3.	다중 if ~ else의 진실.

	-	다중 if ~ else는 else블록을 대상으로 if ~ else를 중첩시킨 것과 같다.

	예)	
			if( 조건 A )
				Do Something

			else if( 조건 B)
				Do Something

			else if( 조건 C)
				Do Something


			->

			if( 조건 A )
			Do Something

			else
			{
				if( 조건 B)
					Do Something

				else if( 조건 C)
					Do Something
			
			}	
*/

//======================================================
/*
4.	삼항 연산자.

	-	형식	
		
		(조건)	?	(참 인 경우 반환되는 값)	:	(거짓 인 경우 반환되는 값.)


		예)	int num = (num1 > 10)	?	20	:	30;

	-	대입 연산자 보다 조건 연산자의 우선순위가 높으므로 조건 연산자가 먼저 진행된다.

		조건의 결과( num1 > 10 )

*/
//======================================================
/*	quiz 3)
	정수를 입력받아 절대값으로 변환하는 프로그램 만들기.

*/