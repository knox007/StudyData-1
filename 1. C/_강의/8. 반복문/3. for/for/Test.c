//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	while vs for (1)

	-	for���� ��� �ݺ��� �����ϱ� ���� �ʿ��� ��� ��Ҹ� �ѱ��� ��� ����.
	
	-	�ʱ��	:	�ݺ��� �����ϱ� �ռ� �� �ѹ� �����. 
		
		���ǽ�	:	�Ź� �ݺ��� �����ϱ� �ռ� ����Ǹ�, 

					���ǽ��� ����� ���� �ݺ� ������ ������.

		������	:	�ݺ� ���� ���� �� ����.
*/


/*	while
int main(void)
{
	int num = 0;
	
	while (num < 3)
	{
		printf("Hello !! %d ȸ ���\n", num + 1);
	
		++num;	//	�ݺ� ������ ���ʶ߸������� ����.

				//	�ּ� ó���� ��� Ȯ�� �غ���.
	}
	

	return 0;
}
//*/


/*	for
int main(void)
{		
	for(int num = 0; num < 3; ++num)
		printf("Hello !! %d ȸ ���\n", num + 1);

	return 0;
}
//*/

/*
2.	while vs for (2)
	
	-	�ݺ��� Ƚ���� ��������� ������ ��� for�� ����.

	-	�׿��� ���, Ư�� ������� �Է°��� ���� �ݺ� ������ �������� ��� while ����.

*/
//======================================================





//======================================================
/*
3.	�ʱ�� 
	-	�ʱ���� for�� ���γ� �ܺο����� ���� �� �ʱ�ȭ�� �����ϴ�.	
*/


/*
int main(void)
{
	int total = 0;

	int inputNum;

	printf("1 ���� �Է��� ���ڱ����� �� : ");
	scanf("%d", &inputNum);

	//for (int cur = 1; cur <= inputNum; ++cur)
	int cur;
	for (cur = 1; cur <= inputNum; ++cur)
		total += cur;

	printf("1 ~ %d ������ �� : %d\n", inputNum, total);
	
	return 0;
}
//*/
//======================================================
/*	quiz)
	�� ���� �Է��Ͽ� �������� ū�� ������ ���� ���Ѵ�.
*/





/*
int main(void)
{
	int total = 0;

	int inputNumSmall;
	int inputNumBig;

	printf("�������� �Է��ϼ��� : ");
	scanf("%d", &inputNumSmall);
	printf("ū ���� �Է��ϼ��� : ");
	scanf("%d", &inputNumBig);

	int cur;
	for (cur = inputNumSmall; cur <= inputNumBig; ++cur)
		total += cur;

	printf("%d ~ %d ������ �� : %d\n", inputNumSmall, inputNumBig, total);

	return 0;
}
//*/



//======================================================
/*
4.	���ǽĿ� ���� �ݺ� ó��

	-	for(;;)
		-	���ǽ��� ������� ������ ������ �ν��Ͽ� ���� ������ �ȴ�.
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

		printf("���� �Է� (������ ����ó��) : ");

		scanf("%d", &input);

		++count;

	}//	for( ; input >= 0; )

	printf("���� : %d,   ��� : %d\n", total, total / (count - 1));

	return 0;
}
//*/
//======================================================




//======================================================
/*
5.	for ���� ��ø

	-	while��ó�� ��ø�� ������.
*/
//======================================================
/*	quiz)
	for���� ��ø�� ����Ͽ� �������� �������.
*/