//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	함수 포인터
	
	-	반환형	(*함수 포인터 이름) ( 매개변수 )
*/


/*
void Add(int a, int b)
{
	printf("%d + %d = %d\n", a, b, a + b);
}

void ShowString(char *psz)
{
	printf("%s\n", psz);
}

int main(void)
{
	char *psz = "Func Pointer";
	int num1 = 10, num2 = 20;

	void (*funcPtr1)(int, int) = Add;
	void(*funcPtr2)(char*) = ShowString;

	funcPtr1(num1, num2);
	funcPtr2(psz);
	
	return 0;
}
//*/
//======================================================



//======================================================
/*
2.	매개변수의 선언으로 사용되는 함수 포인터
*/


/*
int OlderFirst(int age1, int age2)
{
	if (age1 > age2)
		return age1;
	else if (age1 < age2)
		return age2;
	else
		return 0;
}

int YoungerFirst(int age1, int age2)
{
	if (age1 < age2)
		return age1;
	else if (age1 > age2)
		return age2;
	else
		return 0;
}

int WhoIsFirst(int age1, int age2, int(*compare)(int n1, int n2))
{
	return compare(age1, age2);
}

int main()
{
	int age1 = 10;
	int age2 = 20;

	int result = 0;

	printf("대인 순 \n");
	result = WhoIsFirst(age1, age2, OlderFirst);
	printf("%d세와 %d세 중 %d세가 먼저입장!!\n",age1,age2,result);


	printf("소인 순 \n");
	result = WhoIsFirst(age1, age2, YoungerFirst);
	printf("%d세와 %d세 중 %d세가 먼저입장!!\n", age1, age2, result);


	return 0;
}

//*/
//======================================================
/*
	quiz)
		두 정수의 입력을 받아 정수를 반환하는 사칙 연산 함수를 각각 만들고
			
		함수포인터를 이용하여 20과 10에 대한 사칙연산 프로그램을 만든다.

*/
//======================================================