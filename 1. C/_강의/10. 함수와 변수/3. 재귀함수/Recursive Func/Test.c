//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	��� �Լ�

	-	�Լ� ������ �ڱ� �ڽ��� �ٽ� ȣ���ϴ� �Լ�.


2.	����

	-	void RecursiveFunc()
		{
			printf( "Recursive!!\n" );

			RecursiveFunc();
		}

	-	����

		-	�Լ��� �����ϴ� ��ɹ��� cpu�� ���簡 �Ǿ� ����.

		-	�Լ� �߰��� �ٽ� �ڱ� �ڽ��� ������ ���纻�� cpu�� �Ѱܼ� ����.

3.	���� ����

	-	����Լ��� �����Ҷ� Ż�������� ����� ��.
		
*/


/*
void Recursive(int num)
{
	if (num <= 0)
		return;

	printf("Recursive Call!! %d\n", num);

	Recursive(num - 1);
}

int main(void)
{
	Recursive(3);

	return 0;
}
//*/
//======================================================
/*
quiz)	�Է��� �� ���� ���� ������ ���� ���ϴ� ��� �Լ�

*/















/*
int Recursive(int num)
{
	if (num == 0)
		return num;
	else
		return num + Recursive(num - 1);
}

int main(void)
{
	//int num = Recursive(100);
	int num = Recursive(3);

	printf("%d\n", num);

	return 0;
}
//*/