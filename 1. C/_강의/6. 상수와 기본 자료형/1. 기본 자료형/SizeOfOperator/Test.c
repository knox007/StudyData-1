//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	sizeof ������.
*/
/*
int main(void)
{
	char cNum = 1;
	int nNum = 1000;
	double dNum = 3.14;

	printf("-----------------------\n");
	printf(" cNum �� ũ�� : %d \n", sizeof(cNum) );
	printf(" nNum �� ũ�� : %d \n", sizeof(nNum) );
	printf(" dNum �� ũ�� : %d \n", sizeof(dNum) );

	printf("-----------------------\n");
	printf(" char �� ũ�� : %d \n", sizeof(char) );
	printf(" int �� ũ�� : %d \n", sizeof(int));
	printf(" long �� ũ�� : %d \n", sizeof(long));
	printf(" long long �� ũ�� : %d \n", sizeof(long long));
	printf(" float �� ũ�� : %d \n", sizeof(float));
	printf(" double �� ũ�� : %d \n", sizeof(double));

	return 0;
}
//*/
//======================================================



//======================================================
/*
2.	���� �ڷ����� ����.

	-	�Ϲ������� cpu�� ó���ϱ⿡ ���� ������ ũ���� ���� �ڷ����� int�� �����Ѵ�.
		
		->	int�� ����ӵ��� �ٸ� �ڷ����� ����ӵ��� �����ϰų� �� ������.

			->	int ������ ���� ũ���� �����ʹ� int�� �����ͷ� �ٲ㼭 ������ ����ȴ�.
			
			->	������ Ƚ���� ����� ��� ����Ǵ� ���� ũ�Ⱑ �۴��� int�� ������ ����ϴ� ���� ����.

		->	char�� short�� �뵵
			
			-> �������� ���� ���Ƽ� ���� �ӵ����� �������� ũ�⸦ ���̴� ���� �� �߿��� �����͵�

				��) mp3�� ���� ���������ͳ� ���������� ó��.

*/
/*
int main(void)
{
	char chNum1 = 1, chNum2 = 2, chResult = 0;
	short shNum1 = 300, shNum2 = 400, shResult = 0;
	printf("-----------------------\n");
	printf("chNum1 �� chNum2�� ũ�� : %d, %d\n", sizeof(chNum1), sizeof(chNum2));
	printf("shNum1 �� shNum2�� ũ�� : %d, %d\n", sizeof(shNum1), sizeof(shNum2));
	printf("-----------------------\n");
	//	int ������ ���� ũ���� �����ʹ� int�� �����ͷ� �ٲ㼭 ������ ����ȴ�.
	printf("char�� �������� ���� ũ�� : %d\n", sizeof(chNum1+chNum2));
	printf("short�� �������� ���� ũ�� : %d\n", sizeof(shNum1+shNum2));
	printf("-----------------------\n");
	chResult = chNum1 + chNum2;
	shResult = shNum1 + shNum2;
	printf("chResult �� shResult�� ũ�� : %d, %d\n", sizeof(chResult), sizeof(shResult));

	return 0;
}
//*/
//======================================================



//======================================================
/*
3.	�Ǽ� �ڷ����� ����.

	-	���� ���������� duble���� ����϶�� ����.

		-	float���� ���е��� ������ long double ���ٴ� �뷮�� �δ��� ���ϱ� ����.
*/
/*
int main()
{
	double dRad;
	double dArea;

	printf("���� ������ : ");
	scanf("%lf", &dRad);

	dArea = dRad * dRad * 3.141592;
	printf("���� ���� : %lf\n", dArea);

	return 0;
}
//*/
//======================================================