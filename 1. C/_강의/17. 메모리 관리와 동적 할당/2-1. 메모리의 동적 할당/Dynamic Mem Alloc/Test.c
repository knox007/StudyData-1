//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	1 - 1.	���������� ���������� �ذ��� ���� �ʴ� ��Ȳ.

		-	��������, ���������� Ư��

			-	10. �Լ��� ���� -> 2. ������ ����� ���ٹ��� ����.
*/

//*
//---------------------------
//	���� 1)
/*
char * ReadUserName()
{
	char name[30];
	printf("�̸� ? ");
	scanf("%s", name);

	return name;
}
int main()
{
	char *pszName1;
	char *pszName2;

	pszName1 = ReadUserName();
	printf("�̸� : %s\n", pszName1);

	pszName2 = ReadUserName();
	printf("�̸� : %s\n", pszName2);
	
	return 0;
}
//*/
//---------------------------
//	���� 2)
/*
char g_szName[30];

char * ReadUserName()
{
	printf("�̸� ? ");
	scanf("%s", g_szName);

	return g_szName;
}

int main()
{
	char *pszName1;
	char *pszName2;

	pszName1 = ReadUserName();
	printf("�̸� : %s\n", pszName1);

	pszName2 = ReadUserName();
	printf("�̸� : %s\n", pszName2);

	
	printf("pszName1 : %s\n", pszName1);
	printf("pszName2 : %s\n", pszName2);
	

	return 0;
}

//*/
//---------------------------
/*
	1 - 2.	�ذ�å

	-	������ �Ҹ��� �ñⰡ ���������� ���������� �ٸ� ������ ����

		-	�Լ� ȣ��� �Ź� �Ҵ�( �������� )

			�Ҵ� �� �Լ�( �ڵ��� )�� ���������� �޸𸮰� �����Ǵ� ����( �������� )

			-	C������ �̸� ���� malloc �� free �� ����.
*/
//---------------------------
/*
	2.	malloc & free

		-	����

			-	#include <stdlib.h>

				void * malloc( size_t size );

					-	�� ������ �޸� ���� �Ҵ�.

					-	������ �Ҵ�� �޸� ������ �ּҰ� ��ȯ.

						���н� NULL ��ȯ.

				void free( void * ptr );

					-	�� ������ �Ҵ�� �޸� ���� ����.

		-	�� ����

			-	malloc �Լ��� �Ҵ�� �޸� ������ ���α׷��Ӱ� free�� ���� �������� ������ 
			
				�Ҵ�� ���·� ��� �����ְ� �ȴ�.

				-	���α׷��Ӱ� �����ϴ� �޸� ����.

		-	��)

				int main()
				{
					void *ptr1 = malloc(4);		//	�������� 4����Ʈ�� �޸� ������ �Ҵ��� �� ù��° ����Ʈ�� �ּҸ� ��ȯ.
					void *ptr2 = malloc(10);

					.............

					free(ptr1);					//	ptr1�� ����Ű�� �޸� ������ �Ҹ�.
					free(ptr2);

					.............
				}

*/
//---------------------------

