//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	do ~ while�� �� �ڿ������� ���
	
	-	while�� ����3 �� ��.
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
	
	} while (num != 0);	//	;���� ������!!
	
	return 0;
}
//*/
//======================================================
/*	quiz)
	0 ~ 100 ���� ¦���� ���� ���϶�
	����� 2550.
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

	} while (num <= 100);	//	;���� ������!!

	printf("%d\n", sum);

	return 0;
}