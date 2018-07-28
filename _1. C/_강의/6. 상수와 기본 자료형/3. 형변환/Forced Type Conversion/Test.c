//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Forced Type Conversion

	-	연산 결과의 자료형은 피연산자의 자료형과 일치.
		-	num1 / num2 = 0
		-	double divResult = 0;
			->	divResult = 0.000000;
			
	-	소괄호로 변환시키고자하는 타입을 설정해준다.	
		-	이때 소괄호는 형변환 연산자로 사용된다.

*/

//*
int main(void)
{
	int num1 = 3, num2 = 4;
	double divResult = num1 / num2;
	//	다음과 같이 수정.
	//	double divResult = (double)num1 / num2;
	printf("%d / %d = %f\n", num1, num2, divResult);
	
	return 0;
}
//*/
//======================================================