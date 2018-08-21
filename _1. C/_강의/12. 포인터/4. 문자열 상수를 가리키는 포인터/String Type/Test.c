//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	두가지 형태의 문자열 표현
		
		-	배열을 이용한 변수형태의 문자열

		-	포인터를 이용한 상수형태의 문자열.

	2.	상수형태의 문자열 처리 방식.

		예)	
			char *pStr = "Const String";

			1)	"Const String"이라는 문자열이 메모리 공간에 할당.
			
			2)	할당된 메모리의 주소값이 반환된다.

			3)	주소값이 0x1234라고 가정하면
				
				char *pStr = "Const String";

				->	char *pStr = 0x1234; 로 변환되어 포인터 변수에 저장된다.

	3.	printf의 경우..

		printf("Const String");

		->	printf( 0x1234 );

			-	printf 함수는 문자열을 통째로 전달받는 것이 아니라

				문자열의 주소값을 전달 받는다.
			
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

		입력을 위한 char형 배열 szTmp를 만들고

		char형 포인터 pszTmp로 szTmp를 가리켜서

		다음과 같은 동작을 하는 프로그램을 작성.

		글자 입력	:	abcd
		바꾸고 싶은 글자 : a
		바꿀 글자	: h
		입력한 글자	:	abcd
		결과		:	hbcd


*/























//*
int main(void)
{
	char str[50];

	printf("글자를 입력하세요 : ");
	scanf("%s", str);		
	getchar();

	char chFind;
	char chChange;
	printf("바꾸고 싶은 글자는 ? ");
	scanf("%c", &chFind);
	getchar();

	printf("바꿀 글자는 ? ");
	scanf("%c", &chChange);

	printf("입력한 글자 : ");
	printf("%s\n", str);

	char *pStr = str;
	int cur = 0;
	while (pStr[cur] != '\0')
	{
		if (pStr[cur] == chFind)
			pStr[cur] = chChange;

		++cur;
	}

	printf("결과 : ");
	printf("%s\n", str);
	
	return 0;
}
//*/