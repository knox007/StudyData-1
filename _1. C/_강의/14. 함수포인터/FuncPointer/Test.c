//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	�Լ� ������
	
	-	��ȯ��	(*�Լ� ������ �̸�) ( �Ű����� )
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
2.	�Ű������� �������� ���Ǵ� �Լ� ������
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

	printf("���� �� \n");
	result = WhoIsFirst(age1, age2, OlderFirst);
	printf("%d���� %d�� �� %d���� ��������!!\n",age1,age2,result);


	printf("���� �� \n");
	result = WhoIsFirst(age1, age2, YoungerFirst);
	printf("%d���� %d�� �� %d���� ��������!!\n", age1, age2, result);


	return 0;
}

//*/
//======================================================
/*
	quiz)
		�� ������ �Է��� �޾� ������ ��ȯ�ϴ� ��Ģ ���� �Լ��� ���� �����
			
		�Լ������͸� �̿��Ͽ� 20�� 10�� ���� ��Ģ���� ���α׷��� �����.

*/
//======================================================