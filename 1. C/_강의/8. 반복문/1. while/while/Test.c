//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	while �� ����

	-	�ݺ� ����
	-	�ݺ� ����
	-	�ݺ������� ���ʶ߸��� ����.

*/


/*
int main(void)
{
	int num = 0;
		
	while (num < 5)
	{
		printf("Hello !! %d ȸ ���\n", num + 1);
	
		++num;	//	�ݺ� ������ ���ʶ߸������� ����.

				//	�ּ� ó���� ��� Ȯ�� �غ���.
	}

	//	2.	�ݺ��� ����� �ϳ��� �����̶�� �߰�ȣ ���� ����.
	//	while (num < 5)
	//		printf("Hello !! %d ȸ ���\n", num + 1), ++num;

	return 0;
}
//*/
//======================================================
/*	quiz)
	���ڸ� �ϳ� �Է� ������ �� ���ڿ� ���� �������� ����Ѵ�.*/



//======================================================
/*
3.	���� ����		
	-	�ʿ信 ���� ���ѷ����� ����⵵ �Ѵ�.
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
���ڸ� �ϳ� �Է� ������ �� �� ��ŭ 3�� ����� ����Ѵ�.

��) 4 �Է� -> 3 6 9 12 ��� */

/*
int main(void)
{
	int inputNum = 0;

	printf("���ڸ� �Է��ϼ��� : ");
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
4.	while ���� ��ø.
	
	-	while �� ���ο��� while���� ����� �� �ִ�.
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
		printf(" %d ��\n", main);
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