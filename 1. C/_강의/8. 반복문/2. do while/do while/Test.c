//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	do ~ while가 더 자연스러운 경우
	
	-	while문 예제3 과 비교.
*/


/*
int main(void)
{
	int num = 0;

	do
	{
		printf("input number : (0 : finish)");
		scanf("%d", &num);

		if( num != 0 )
			printf("%d x %d = %d\n", 2, num, 2 * num);
	
	} while (num != 0);	//	;으로 마무리!!
	
	return 0;
}
//*/
//======================================================
/*	quiz)
	0 ~ 100 이하 짝수의 합을 구하라
	결과는 2550.
*/














int main(void)
{
	int num = 0;

	int sum = 0;
	do
	{
		if (num % 2 == 0)
			sum += num;
		++num;

	} while (num <= 100);	//	;으로 마무리!!

	printf("%d\n", sum);

	return 0;
}