//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	strlen

		-	���ڿ� ���� ��ȯ.
*/

#include <string.h>
/*
int main()
{
	char szTmp[50];

	printf("���ڿ��� �Է��ϼ��� : ");
	scanf("%s", szTmp);

	int length = strlen(szTmp);

	printf("%s�� ���̴� %d �Դϴ�.\n", szTmp, length);

	return 0;
}
//*/
//======================================================
/*
2.	strcpy / strncpy

	-	���ڿ� ����.
*/

/*
int main()
{
	char szOrigin[20] = "1234567890";
	char szTmp1[20];
	char szTmp2[5];

	// strcpy
	strcpy(szTmp1, szOrigin);
	printf("%s\n", szTmp1);

	// strncpy 1
	strncpy(szTmp2, szOrigin, sizeof(szTmp2));
	printf("%s\n", szTmp2);

	// strncpy 2
	strncpy(szTmp2, szOrigin, sizeof(szTmp2)-1);
	szTmp2[sizeof(szTmp2) - 1] = 0;
	printf("%s\n", szTmp2);

	return 0;
}
//*/
//======================================================
/*
3.	strcat / strncat

-	���ڿ� �߰�.

*/

/*
int main()
{
	char szTmp1[20] = "First~";
	char szTmp2[20] = "Second!!";

	char szTmp3[20] = "Strncpy : ";
	char szTmp4[20] = "1234567890";

	//	strcat
	strcat(szTmp1, szTmp2);
	printf("%s\n", szTmp1);

	//	strncat
	strncat(szTmp3, szTmp4, 5);
	printf("%s\n", szTmp3);

	return 0;
}
//*/
//======================================================
/*
4.	strcmp / strncmp

-	���ڿ� ��.

*/

/*
int main()
{
	char szTmp1[30];
	char szTmp2[30];

	printf("ù��° ���ڿ� �Է� : ");
	scanf("%s", szTmp1);

	printf("�ι�° ���ڿ� �Է� : ");
	scanf("%s", szTmp2);

	if (!strcmp(szTmp1, szTmp2))
		printf("������ ���ڿ�!!\n");
	else
	{
		printf("�ٸ� ���ڿ�!!\n");

		if( !strncmp((szTmp1 + 1), szTmp2, 3))
			printf("������ �� 3���ڴ� ����!!\n");
	}

	return 0;
}
//*/
//======================================================
/*
5.	atoi / atol / atof

-	���ڿ��� ���������� ��ȯ.

*/

/*
#include <stdlib.h>

int main()
{
	char szInt[20];
	char szDouble[20];

	printf("���� �Է� : ");
	scanf("%s", szInt);
	printf("%d\n", atoi(szInt));
	
	printf("�Ǽ� �Է� : ");
	scanf("%s", szDouble);
	printf("%f\n", atof(szDouble));

	return 0;
}
//*/
//======================================================
/*
	Quiz)

		������ ������ ���ڿ��� �Է¹޾� �� �ȿ� �����ϴ� ������ ������ ����ϴ� ���α׷� �ۼ�.

		��)	ad8a9aadf0a12

			-> 8 + 9 + 0 + 1 + 2 = 20

		��Ʈ) �ƽ�Ű�ڵ�ǥ ����.
*/






































/*
int CharToNumber(char cWord) { return cWord - '0'; }

int main()
{
	char szWords[30] = "a9b4c31";

	int len = strlen(szWords);

	int sum = 0;
	for (int cur = 0; cur < len; ++cur)
	{
		if ('0' <= szWords[cur] && szWords[cur] <= '9')
			sum += CharToNumber(szWords[cur]);
	}

	printf("%s�� ���ڵ��� �� : ", szWords);
	printf("%d\n", sum);

	return 0;
}
//*/
