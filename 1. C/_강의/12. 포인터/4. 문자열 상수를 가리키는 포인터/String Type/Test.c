//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	�ΰ��� ������ ���ڿ� ǥ��
		
		-	�迭�� �̿��� ���������� ���ڿ�

		-	�����͸� �̿��� ��������� ���ڿ�.

	2.	��������� ���ڿ� ó�� ���.

		��)	
			char *pStr = "Const String";

			1)	"Const String"�̶�� ���ڿ��� �޸� ������ �Ҵ�.
			
			2)	�Ҵ�� �޸��� �ּҰ��� ��ȯ�ȴ�.

			3)	�ּҰ��� 0x1234��� �����ϸ�
				
				char *pStr = "Const String";

				->	char *pStr = 0x1234; �� ��ȯ�Ǿ� ������ ������ ����ȴ�.

	3.	printf�� ���..

		printf("Const String");

		->	printf( 0x1234 );

			-	printf �Լ��� ���ڿ��� ��°�� ���޹޴� ���� �ƴ϶�

				���ڿ��� �ּҰ��� ���� �޴´�.
			
*/

/*
int main(void)
{
	char str1[] = "String_1";
	char *pStr2 = "String_2";
	printf("%s,  %s\n", str1, pStr2);

	pStr2 = "String_3";
	printf("%s,  %s\n", str1, pStr2);

	str1[0] = 'A';
	pStr2[0] = 'A';
	printf("%s,  %s\n", str1, pStr2);

	return 0;
}
//*/
//======================================================
/*
	quiz)

		�Է��� ���� char�� �迭 szTmp�� �����

		char�� ������ pszTmp�� szTmp�� �����Ѽ�

		������ ���� ������ �ϴ� ���α׷��� �ۼ�.

		���� �Է�	:	abcd
		�ٲٰ� ���� ���� : a
		�ٲ� ����	: h
		�Է��� ����	:	abcd
		���		:	hbcd


*/























//*
int main(void)
{
	char str[50];

	printf("���ڸ� �Է��ϼ��� : ");
	scanf("%s", str);		
	getchar();

	char chFind;
	char chChange;
	printf("�ٲٰ� ���� ���ڴ� ? ");
	scanf("%c", &chFind);
	getchar();

	printf("�ٲ� ���ڴ� ? ");
	scanf("%c", &chChange);

	printf("�Է��� ���� : ");
	printf("%s\n", str);

	char *pStr = str;
	int cur = 0;
	while (pStr[cur] != '\0')
	{
		if (pStr[cur] == chFind)
			pStr[cur] = chChange;

		++cur;
	}

	printf("��� : ");
	printf("%s\n", str);
	
	return 0;
}
//*/