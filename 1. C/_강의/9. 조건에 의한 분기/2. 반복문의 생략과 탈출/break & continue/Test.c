//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	break
*/


/*
int main(void)
{
	int sum = 0, num = 0;

	while (1)
	{
		sum += num;

		if (sum >= 11)
			break;

		++num;

	}//	while (1)

	printf("sum : %d\n", sum);
	printf("num : %d\n", num);

	return 0;
}
//*/
//======================================================
/*	quiz 1)	
	
	입력 : 2

	2 x 1 = 2
	2 x 2 = 4

	또는 

	입력 : 6

	6 x 1 = 6
	6 x 2 = 12
	6 x 3 = 18
	.....
	6 x 6 = 18

	*/





//======================================================
/*
2.	continue
*/

/*
int main(void)
{
	int num;

	printf("범위 입력 : ");
	scanf("%d", &num);
	printf("홀수 출력 : \n");
	for (int cur = 0; cur <= num; ++cur)
	{
		if (cur % 2 == 0)
			continue;

		printf("%d\n", cur);
	}
	return 0;

}
//*/
//======================================================
/*	quiz 2)	
	
	n이라는 정수를 입력 받아서
	1~100 중 n의 배수를 합한 값을 출력.

*/
//======================================================