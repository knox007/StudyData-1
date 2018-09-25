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

	printf("숫자 입력 : ");
	scanf("%d", &num);

	result = IsPositive(num);

	if (result == TRUE)
		printf("%d (은)는 양수!!\n", num);
	else
		printf("%d (은)는 음수!!\n", num);

	return 0;
}
//================================================