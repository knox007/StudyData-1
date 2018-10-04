//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	strlen

		-	문자열 길이 반환.
*/

#include <string.h>
/*
int main()
{
	char szTmp[50];

	printf("문자열을 입력하세요 : ");
	scanf("%s", szTmp);

	int length = strlen(szTmp);

	printf("%s의 길이는 %d 입니다.\n", szTmp, length);

	return 0;
}
//*/
//======================================================
/*
2.	strcpy / strncpy

	-	문자열 복사.
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

	// strcpy 1
	strncpy(szTmp2, szOrigin, sizeof(szTmp2));
	printf("%s\n", szTmp2);

	// strcpy 2
	strncpy(szTmp2, szOrigin, sizeof(szTmp2)-1);
	szTmp2[sizeof(szTmp2) - 1] = 0;
	printf("%s\n", szTmp2);

	return 0;
}
//*/
//======================================================
/*
3.	strcat / strncat

-	문자열 추가.

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

-	문자열 비교.

*/

/*
int main()
{
	char szTmp1[30];
	char szTmp2[30];

	printf("첫번째 문자열 입력 : ");
	scanf("%s", szTmp1);

	printf("두번째 문자열 입력 : ");
	scanf("%s", szTmp2);

	if (!strcmp(szTmp1, szTmp2))
		printf("동일한 문자열!!\n");
	else
	{
		printf("다른 문자열!!\n");

		if( !strncmp(szTmp1, szTmp2, 3))
			printf("하지만 앞 3글자는 동일!!\n");
	}

	return 0;
}
//*/
//======================================================
/*
5.	atoi / atol / atof

-	문자열을 숫자형으로 변환.

*/

/*
#include <stdlib.h>

int main()
{
	char szInt[20];
	char szDouble[20];

	printf("정수 입력 : ");
	scanf("%s", szInt);
	printf("%d\n", atoi(szInt));
	
	printf("실수 입력 : ");
	scanf("%s", szDouble);
	printf("%f\n", atof(szDouble));

	return 0;
}
//*/
//======================================================
/*
	Quiz)

		적당한 길이의 문자열을 입력받아 그 안에 존재하는 숫자의 총합을 계산하는 프로그램 작성.

		예)	ad8a9aadf0a12

			-> 8 + 9 + 0 + 1 + 2 = 20
*/