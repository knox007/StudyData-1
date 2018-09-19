/*
	C언어에서는 다음과 같은 함수의 정의가 허용되지 않음.

	-	원인

		-	함수의 이름이 같기 때문에 컴파일 오류 발생.

		-	C 컴파일러는 호출하고자 하는 함수의 이름 정보만을 참고.
*/
#include <stdio.h>

int Func() { return 10; }

int Func(int a, int b) { return a + b; }

int main()
{
	printf("%d\n", Func());

	printf("%d\n", Func(1,3));

	return 0;
}