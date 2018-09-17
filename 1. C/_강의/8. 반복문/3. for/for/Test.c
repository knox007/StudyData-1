//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	while vs for (1)

	-	for문의 경우 반복을 구성하기 위해 필요한 모든 요소를 한군데 묶어서 관리.
	
	-	초기식	:	반복을 시작하기 앞서 딱 한번 실행됨. 
		
		조건식	:	매번 반복을 시작하기 앞서 실행되며, 

					조건식의 결과에 따라 반복 유무가 결정됨.

		증감식	:	반복 영역 실행 후 진행.
*/


/*	while
int main(void)
{
	int num = 0;
	
	while (num < 3)
	{
		printf("Hello !! %d 회 출력\n", num + 1);
	
		++num;	//	반복 조건을 무너뜨리기위한 연산.

				//	주석 처리후 결과 확인 해볼것.
	}
	

	return 0;
}
//*/


/*	for
int main(void)
{		
	for(int num = 0; num < 3; ++num)
		printf("Hello !! %d 회 출력\n", num + 1);

	return 0;
}
//*/

/*
2.	while vs for (2)
	
	-	반복의 횟수가 명시적으로 정해진 경우 for문 권장.

	-	그외의 경우, 특히 사용자의 입력값에 따라 반복 유무가 정해지는 경우 while 권장.

*/
//======================================================





//======================================================
/*
3.	초기식 
	-	초기식은 for문 내부나 외부에서도 선언 및 초기화가 가능하다.	
*/


/*
int main(void)
{
	int total = 0;

	int inputNum;

	printf("1 부터 입력한 숫자까지의 합 : ");
	scanf("%d", &inputNum);

	//for (int cur = 1; cur <= inputNum; ++cur)
	int cur;
	for (cur = 1; cur <= inputNum; ++cur)
		total += cur;

	printf("1 ~ %d 까지의 합 : %d\n", inputNum, total);
	
	return 0;
}
//*/
//======================================================
/*	quiz)
	두 수를 입력하여 작은수와 큰수 사이의 합을 구한다.
*/





/*
int main(void)
{
	int total = 0;

	int inputNumSmall;
	int inputNumBig;

	printf("작은수를 입력하세요 : ");
	scanf("%d", &inputNumSmall);
	printf("큰 수를 입력하세요 : ");
	scanf("%d", &inputNumBig);

	int cur;
	for (cur = inputNumSmall; cur <= inputNumBig; ++cur)
		total += cur;

	printf("%d ~ %d 까지의 합 : %d\n", inputNumSmall, inputNumBig, total);

	return 0;
}
//*/



//======================================================
/*
4.	조건식에 의한 반복 처리

	-	for(;;)
		-	조건식이 비워지면 무조건 참으로 인식하여 무한 루프가 된다.
*/



/*
int main(void)
{
	int total = 0;

	int input = 0;

	int count = 0;

	for (; input >= 0; )
	//for (;;)
	{
		total += input;

		printf("정수 입력 (음수는 종료처리) : ");

		scanf("%d", &input);

		++count;

	}//	for( ; input >= 0; )

	printf("총합 : %d,   평균 : %d\n", total, total / (count - 1));

	return 0;
}
//*/
//======================================================




//======================================================
/*
5.	for 문의 중첩

	-	while문처럼 중첩이 가능함.
*/
//======================================================
/*	quiz)
	for문의 중첩을 사용하여 구구단을 출력하자.
*/