//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Forced Type Conversion

	-	���� ����� �ڷ����� �ǿ������� �ڷ����� ��ġ.
		-	num1 / num2 = 0
		-	double divResult = 0;
			->	divResult = 0.000000;
			
	-	�Ұ�ȣ�� ��ȯ��Ű�����ϴ� Ÿ���� �������ش�.	
		-	�̶� �Ұ�ȣ�� ����ȯ �����ڷ� ���ȴ�.

*/

//*
int main(void)
{
	int num1 = 3, num2 = 4;
	double divResult = num1 / num2;
	//	������ ���� ����.
	//	double divResult = (double)num1 / num2;
	printf("%d / %d = %f\n", num1, num2, divResult);
	
	return 0;
}
//*/
//======================================================