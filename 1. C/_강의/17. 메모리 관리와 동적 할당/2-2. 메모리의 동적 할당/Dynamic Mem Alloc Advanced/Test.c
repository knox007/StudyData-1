//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
//======================================================
/*
	1 - 1.	malloc �� ��ȯ���� void*

		-	void�� ������.

			-	��(Type)�� �������� �ʴ� ������.

			-	��)
					void * ptr;

			-	����
			
				-	��� ������ �ּҰ��̵� ������ �ִ�.

					�Լ��� �ּҰ��� ������ �ִ�.

			-	����
			
				-	�ƹ��� ������ ������ �Ҽ� ����.

				-	���� �����̳� ������ �Ұ�.
					
					-	����Ű�� ����� ��� Ÿ���� ���������� ���� ������ ����.

			-	�ּҰ��� �ϴ� �����ѵ� ���߿� ������ ���� ������ ��� �ַ� ����.
*/

/*

void SimpleFunc() { printf("Simple Func!!\n"); }

int main()
{
	int num = 20;

	void* ptr;

	ptr = &num;
	printf("ptr = %p\n", ptr);

	//	*ptr = 30;
	//	++ptr;

	ptr = SimpleFunc;
	printf("ptr = %p\n", ptr);

	return 0;
}
//*/
//---------------------------
/*	1 - 2.	malloc �� ��ȯ���� void*

	-	void* Ÿ���� ����.

		-	���ϴ� ��ŭ �޸� ������ �Ҵ��ϰ� �ּҸ� ��ȯ�ϸ�

			���α׷��Ӱ� ���� ���������� ��ȯ�� ���ؼ� 

			��� ������� ����.
			
*/

/*
int main()
{
	int * ptr1 = (int*)malloc(sizeof(int));
	int * ptr2 = (int*)malloc(sizeof(int)*7);

	*ptr1 = 20;

	for (int i = 0; i < 7; ++i)
		ptr2[i] = i + 1;

	printf("*ptr1 = %d\n", *ptr1);

	printf("*ptr2 \n");
	for (int i = 0; i < 7; ++i)
		printf("%d ", ptr2[i]);
	printf("\n");

	free(ptr1);
	free(ptr2);

	return 0;
}
//*/
//---------------------------
/*
	2.	�� �ۿ�...

		-	calloc

			-	����

				void* calloc( size_t elementCount, size_t elementSize );

				-	elementCount	:	�Ҵ��� ����� ����

				-	elementSize		:	��� �ϳ��� ����Ʈ ũ��.

			-	malloc( 40 ) == calloc( 10, 4 )

			-	malloc �� ������.

				-	�޸� ������ ��� ��Ʈ�� 0���� �ʱ�ȭ.

					-	malloc�� ��� �����Ⱚ���� ä����.

		-	realloc

			-	����

				void* realloc( void *ptr, size_t size );

				-	ptr		:	Ȯ���ϰ��� �ϴ� �� �޸��� �ּ�.

				-	size	:	Ȯ���ϰ��� �ϴ� �޸��� ��ü ũ��.

			-	��)

				int *pArr = (int*)malloc(sizeof( int ) * 3 );

				.......

				pArr = (int * )realloc(pArr, sizeof( int ) * 5 );

			-	malloc �� realloc�� ��ȯ��.

				-	���� ���.

					-	malloc�� �Ҵ��� �޸� ������ Ȯ���� ������ �˳��� ���.

				-	�ٸ� ���.

					-	�˳����� ���� ���, ���� �䱸�ϴ� ũ���� �޸� ������ ���� �Ҵ��ѵ�

						���� �������� ���� ����.

*/
//---------------------------
/*
	Quiz)
		
		���� 1),2)�� ��Ȳ�� malloc�� free�� �̿��ؼ� �ذ�����.
*/
//---------------------------