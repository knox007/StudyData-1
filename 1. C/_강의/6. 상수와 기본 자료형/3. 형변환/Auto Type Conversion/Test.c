//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Auto Type Conversion
*/

//*
int main(void)
{
	double num1 = 153;

	int num2 = 3.1415;

	int num3 = 129;

	char ch = num3;

	printf("���� 153�� �Ǽ��� ǥ�� : %lf\n", num1);
	printf("�Ǽ� 3.1415�� ������ ǥ�� : %d\n", num2);
	printf("int ���� 129�� charŸ������ ǥ�� : %d\n", ch);

	return 0;
}
//*/
//======================================================