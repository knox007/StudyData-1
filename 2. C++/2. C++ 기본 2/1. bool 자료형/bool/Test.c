//================================================
#include <stdio.h>
#pragma warning(disable : 4996)
//================================================
const int TRUE = 1;
const int FALSE = 0;
//================================================
int IsPositive(int num)
{
	if (num < 0)
		return FALSE;
	else
		return TRUE;

}//	int IsPositive(int num)
//================================================
int main()
{
	int num;
	int result;
//	bool aaa;

	printf("���� �Է� : ");
	scanf("%d", &num);

	result = IsPositive(num);

	if (result == TRUE)
		printf("%d (��)�� ���!!\n", num);
	else
		printf("%d (��)�� ����!!\n", num);

	return 0;
}
//================================================