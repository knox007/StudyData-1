//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	���Ǻ� ������

		-	��ũ�θ� ����Ͽ� Ư�� ���ǿ� ���� �ҽ��ڵ��� �Ϻθ�
		
			�����Ͽ� �����ϰų� ���� ��Ű�� ��.


		-	����
		
			-	#if ... #endif

			-	#ifdef ... #endif

			-	#ifndef ... #endif
*/
//======================================================
/*
	2 - 1. #if ... #endif

			-	��ũ���� ������ ���ΰ�?	
*/

/*
#define ADD 1
#define MINUS 0

int main()
{
	int num1, num2;
	printf("�� ���� ���� �Է� : ");
	scanf("%d %d", &num1, &num2);

#if ADD==1	// �Ǵ� #if ADD
	printf("%d + %d = %d\n", num1, num2, num1 + num2);
#endif

#if MINUM
	printf("%d - %d = %d\n", num1, num2, num1 - num2);
#endif

	return 0;
}

//*/
//======================================================
/*
2 - 2. #ifdef ( ifndef ) ... #endif

		-	��ũ�ΰ� ����Ǿ��°�( ������� �ʾҴ°� )?

			-	��ũ���� ���� �߿����� ����.
*/


/*
#define ADD 1
//	#define ADD

#define MINUS 0
//	#define MINUS

int main()
{
	int num1, num2;
	printf("�� ���� ���� �Է� : ");
	scanf("%d %d", &num1, &num2);

#ifdef ADD
	printf("%d + %d = %d\n", num1, num2, num1 + num2);
#endif

#ifdef MINUS
	printf("%d - %d = %d\n", num1, num2, num1 - num2);
#endif

	return 0;
}
//*/
//======================================================
/*
	2 - 3.	#else, #elif

			-	else�� ���Ұ� ����.

			-	#elif�� #if���� ����.
				
				-	#elif -> #else if

				-	������ ������ #else�� ������.
*/

/*
#define COUNT 5

int main()
{
#if COUNT == 1
	puts("COUNT = 1");
#elif COUNT == 2
	puts("COUNT = 2");
#elif COUNT == 3
	puts("COUNT = 3");
#else
	puts("COUNT = ???");
#endif

	return 0;
}

//*/
//======================================================
/*
	3 - 1.	��Ÿ

		-	��ũ�θ� �̿��� ���ڿ�ȭ

			-	���ڿ� �ȿ��� ��ũ���� �Ű����� ġȯ�� �߻����� ����.

				��)	#define STRINGDATA(A, B)	"A�� B�̴�"

				-	# ������ : ��ũ�γ��� �Ű������� ���ڿ��� ġȯ�Ѵ�.

					-	#define STRINGDATA(A)	#A


			-	���ڿ��� ������ �����ϸ� �ϳ��� ���ڿ��� �����Ѵ�.

				��)	char *pStr = "abc""def";

					->	char *pStr = "abcdef";

					->	#define STRINGDATA(A, B)	#A "��(��) " #B "�̴�"
*/
//======================================================
/*
//	-- Before --
#define STRINGDATA(A, B)	"A��(��) B�̴�"

int main()
{
	printf("%s\n", STRINGDATA(ȫ�浿, �ٺ�));

	return 0;
}
//*/

/*
//	-- After --
#define STRINGDATA(A, B)	#A "��(��) " #B "�̴�"

int main()
{
	printf("%s\n", STRINGDATA(ȫ�浿, �ٺ�));

	return 0;
}

//*/
//======================================================
/*
3 - 1.	��Ÿ

		-	�ܼ� ����

			-	##	:	��ũ���Լ��� �Ű������� �ٸ� ���( �Ű�����, ����, ����, ���ڿ� �� )�� 

						�̾��� �� ���.

				��)	#define LINK(A,B)	A##B
*/

/*
#define LINK(A,B)	A##B

int main()
{
	int link = LINK(10, 04);
	printf("%d\n", link);

	return 0;
}
//*/
//======================================================
/*
	Quiz)	�� ���� �Է¹޾� �� ū���� ���ϴ� ���α׷� �ۼ�.

			��1)	MAX(A,B)��� ��ũ�θ� ����

			��2)	���� �����ڸ� ���.
*/
//======================================================