//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	Call By Value	

		-	�Լ� ȣ��� �Ű������� �ܼ��� ���� �����ϴ� ������ ȣ�� ���.

		-	�� ���� ���.

	2.	Call By Reference

		-	�Լ� ȣ��� �Ű������� �޸� ���ٿ� ���Ǵ� �ּҰ��� �����ϴ� ȣ�� ���.

		-	�ּ� ���� ���.

*/

/*	
//------------------
//	���� ������ ��������?

//	�׸��� �ٸ��� �۵���Ű���� �Ϸ���?

//------------------
//	n1�� n2�� �ٲٴ� �Լ�.
void Swap(int n1, int n2)
{
	int tmp = n1;
	n1 = n2;
	n2 = tmp;

	printf("n1 = %d,   n2 = %d\n", n1, n2);
}

int main(void)
{
	int n1 = 10;
	int n2 = 20;
	printf("n1 = %d,   n2 = %d\n", n1, n2);

	Swap(n1, n2);

	printf("n1 = %d,   n2 = %d\n", n1, n2);

	return 0;	
}
//*/
//======================================================












/*
void SwapPtr(int *pn1, int *pn2)
{
	int tmp = *pn1;
	*pn1 = *pn2;
	*pn2 = tmp;
}
*/


//======================================================
/*
	scanf�� ���� ����.

	��)
		int num;
		scanf("%d", &num);

		-	scanf�� ���� num�� �ּҷ� �����Ͽ� ���� ä���ִ´�.

		char szTmp[30];
		scanf("%s", szTmp);			
		
		-	scanf("%s", &szTmp);	( X )

		-	szTmp ��ü�� �ּҰ��̱� ����.

			-	�迭�� �̸��� �迭 ù ����� �ּҿ� ����.

*/

//======================================================
/*
	quiz)
		�������� ���� �ٲٴ� �Լ��� ������.

		Swap( &num1, &num2, &num3 );
				
		 num1	->	num2
		 num2	->	num3
		 num3	->	num1
*/










/*
void Swap(int *ptr1, int *ptr2, int *ptr3)
{
	int tmp = *ptr3;

	*ptr3 = *ptr2;
	*ptr2 = *ptr1;
	*ptr1 = tmp;
}

int main()
{
	int n1 = 10, n2 = 20, n3 = 30;

	printf("%d,  %d,  %d\n", n1, n2, n3);
	Swap(&n1, &n2, &n3);
	printf("%d,  %d,  %d\n", n1, n2, n3);

	return 0;
}

//*/