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

	printf("���� 153�� �Ǽ��� ǥ�� : %f\n", num1);
	printf("�Ǽ� 3.1415�� ������ ǥ�� : %d\n", num2);
	printf("int ���� 129�� charŸ������ ǥ�� : %d\n", ch);

	return 0;
}
//*/
//======================================================



//======================================================
/*
2.	�ɺ��� ���
*/
/*
#define BULLET_SPEED 20
int main(void)
{
	const int BULLET_POW = 100;

	printf("�Ѿ��� �ӵ�  : %d\n", BULLET_SPEED);
	printf("�Ѿ��� ���ݷ�  : %d\n", BULLET_POW);

	return 0;
}

//*/
//======================================================