//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	do ~ while가 더 자연스러운 경우
	
	-	while문 예제3 과 비교.
*/


//*
int main(void)
{
	int num = 0;

	do
	{
		printf("input number : (0 : finish)");
		scanf("%d", &num);

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