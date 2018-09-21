//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	널문자

	-	아스키 코드 값 : 0
	
	-	문자형태 출력 : nothing
*/


/*
int main(void)
{
	char str[] = "Good morning!";	//	널문자가 자동으로 추가됨.

	printf("문자열 출력 : %s\n", str);
	printf("\n");
	printf("배열 str의 크기 : %d\n", sizeof(str));
	printf("\n");
	printf("널 문자의 문자형 출력 : %c\n", str[13]);
	printf("\n");
	printf("널 문자의 정수형(아스키 코드) 출력 : %d\n", str[13]);
	printf("\n");
	str[12] = '?';
	printf("문자열 출력 : %s\n", str);
	printf("\n");

	//	널문자, 공백 문자, 개행문자의 차이
	char null = '\0';
	char space = ' ';
	char newline = '\n';
	printf("%d, %d, %d\n", null, space, newline);
	printf("\n");

	char str2[] = "A";
	printf("문자열 출력 : %s\n", str2);
	printf("\n");
	printf("배열 str2의 크기 : %d\n", sizeof(str2));
	
	return 0;
}

//*/
//======================================================




//======================================================
/*
2.	scanf를 이용한 문자열 입력.

	-	서식 문자 "%s" 사용.( printf와 동일 )
	
	-	예)	char str[50];
			scanf("%s", str );	
			"%s"	:	문자열 입력을 위한 서식 문자.
			str		:	입력된 문자열을 저장할 배열.
			
	-	문자열 입력시 &는 사용하지 않는다.
		
		추후 "포인터" 수업에서 설명.

	-	scanf를 통하여 입력받은 문자열의 끝에도 널문자가 삽입됨.

	-	문자열과 문자 배열의 차이

		-	널문자의 존재 유무.

		-	예)	char arr1[] = {'H', 'i', '~'};			//	문장끝에 널문자가 없으므로 문자 배열.

				char arr2[] = {'H', 'i', '~', '\0'};	//	문장끝에 널문자가 있으므로 문자열.

	-	참고사항 

		-	scanf는 공백으로 데이터를 구분 짓는다.
*/


/*
int main(void)
{
	char str[50];
	int idx = 0;

	printf("문자열 입력 : ");
	scanf("%s", str);		//	& ?
	printf("입력받은 문자열 : %s\n", str);

	printf("문자 단위 출력 : ");
	while (str[idx] != '\0')
	{
		printf("%c", str[idx]);
		++idx;
	}
	printf("\n");
	
	
	//	문자열과 문자배열의 출력.
		char arr1[] = { 'H', 'i', '~' };
		char arr2[] = { 'H', 'i', '~', '\0' };
		printf("%s,    %s\n", arr1, arr2);	

	return 0;
}

//*/
//======================================================
/*
quiz)	입력받은 영단어의 길이를 출력하는 프로그램.

		예)	영단어를 입력하세요 : love

			love의 글자수 : 4 단어.
*/













/*
int main(void)
{
	char str[50];
	int idx = 0;
	int length = 0;

	printf("문자열 입력 : ");
	scanf("%s", str);
	
	while (str[idx] != '\0')
		++idx;

	length = idx;
	printf("%s의 길이는 %d 입니다.\n", str, length);

	return 0;
}
//*/




//======================================================
/*
3.	널문자의 필요성

	-	메모리상에서 문자열(모든 데이터)은 이진 데이터로 저장됨.

		시작과 끝이 표시되어 있지 않다면 문자열을 구분하는 것은 불가능.

	-	시작	:	문자열의 0번째 인덱스
	
		마지막	:	널문자가 삽입된 인덱스
*/

/*
int main()
{
	char str[50] = "I like C programming";
	printf("문자열 : %s\n", str);

	str[8] = '\0';	//	또는 str[8] = 0;
	printf("문자열 : %s\n", str);

	str[6] = '\0';
	printf("문자열 : %s\n", str);

	str[1] = '\0';
	printf("문자열 : %s\n", str);

	return 0;
}

//*/
//======================================================
/*
	quiz)	영단어를 입력받고 각각의 아스키 코드 값을 출력한뒤

			그 중 아스키 코드값이 가장 큰 문자를 출력한다.

			예) 영단어를 입력하세요 : love

				l : 108
				o : 111
				v : 118
				e : 101

				아스키 코드값이 가장 큰 문자 : v
*/








/*
int main()
{
	char szInput[50];
	printf("영단어를 입력하세요 : ");
	scanf("%s", szInput);

	int idx = 0;
	char max = szInput[0];
	while (szInput[idx] != 0)
	{
		printf("%c :  %d\n", szInput[idx], szInput[idx]);

		if (max < szInput[idx])
			max = szInput[idx];

		++idx;
	}
	
	printf("아스키 코드값이 가장 큰 문자는 %c\n", max);

	return 0;
}
//*/
//======================================================