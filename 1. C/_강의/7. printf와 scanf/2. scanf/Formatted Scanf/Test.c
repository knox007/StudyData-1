//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	 정수 기반의 입력형태
*/




/*
int main(void)
{
	int num1, num2, num3;

	printf("세 개의 정수 입력 : ");

	scanf("%d %o %x", &num1, &num2, &num3);

	printf("\n입력된 정수의 10진수 출력 : \n");

	printf("%d, %d, %d\n\n", num1, num2, num3);

	return 0;
}
//*/
//======================================================





//======================================================
/*
2.	 실수 기반의 입력형태

	-	실수 입력과정에서 e 표기법 가능.

	-	< 입출력 서식 문자 >

				|	float	|	double	|	long double
		------------------------------------------------
		출력	|	%f		|	%f		|	%Lf
		입력	|	%f		|	%lf		|	%Lf
*/




/*
int main(void)
{
	float num1;
	double num2;
	long double num3;

	printf("실수 입력 (e 표기법) : ");
	scanf("%f", &num1);
	printf("입력된 실수는 %f\n\n", num1);

	printf("실수 입력 (e 표기법) : ");
	scanf("%lf", &num2);
	printf("입력된 실수는 %lf\n\n", num2);

	printf("실수 입력 (e 표기법) : ");
	scanf("%Lf", &num3);
	printf("입력된 실수는 %Lf\n\n", num3);

	return 0;
}
//*/
//======================================================