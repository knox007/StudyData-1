/*
	C������ ������ ���� �Լ��� ���ǰ� ������ ����.

	-	����

		-	�Լ��� �̸��� ���� ������ ������ ���� �߻�.

		-	C �����Ϸ��� ȣ���ϰ��� �ϴ� �Լ��� �̸� �������� ����.
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