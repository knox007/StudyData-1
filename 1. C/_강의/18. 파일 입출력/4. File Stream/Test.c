//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	파일 위치 지시자

		-	FILE 구조체는 파일 입출력 함수가 호출될때마다 파일의 위치를 가리키는 포인터가 참조 및 갱신이 됨.

			예)	fgets로 20바이트를 읽는다면 파일의 현재 참조하고 있는 위치부터 20바이트를 읽은 뒤

				파일의 위치를 가리키는 포인터는 현재 위치로부터 21번째 바이트로 이동한다.

		-	파일이 처음 개방되면 무조건 파일의 맨 앞부분을 가리킨다.

			-	파일의 특정 부분에서부터 데이터를 읽거나 쓰고자 한다면 "파일 위치 지시자"를 이동시켜야 함.
*/
//======================================================
/*
	2.	파일 위치 지시자 이동 : fseek

		-	int fseek( FILE *pFile, long offset, int whereFrom );

			-	파일 위치 지시자를 whereFrom으로부터 offset만큼 이동.

			-	offset

				-	양수	:	파일 끝으로 이동.

				-	음수	:	파일 시작위치로 이동.

			-	whereFrom
				
				-	SEEK_SET	:	파일 맨 앞.

									파일의 첫번째 바이트.

					SEEK_CUR	:	현재 위치.

					SEEK_END	:	파일 맨 끝.

									= EOF
									
										-	마지막 파일 다음 위치
										
										-	파일의 끝을 알리기위해 삽입됨.

										

			
*/
//======================================================
/*
int main()
{
	//	파일 생성.
	FILE *pFile = fopen("FilePosition.txt", "wt");

	if (pFile == NULL)
	{
		puts("파일 열기 실패");
		return -1;
	}

	fputs("123456789", pFile);
	fclose(pFile);


	//	파일 열기.
	pFile = fopen("FilePosition.txt", "rt");

	//	SEEK_END
	fseek(pFile, -2, SEEK_END);
	putchar(fgetc(pFile));

	//	SEEK_SET
	fseek(pFile, 2, SEEK_SET);
	putchar(fgetc(pFile));

	//	SEEK_CUR
	fseek(pFile, 2, SEEK_CUR);
	putchar(fgetc(pFile));

	puts("");

	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*
	3.	파일 위치 지시자의 현재 위치 : ftell

		-	long ftell( FILE* pFile );

			-	파일 위치 지시자의 현재 위치 정보 반환.

			-	시작 바이트의 위치는 0 반환.

				배열의 인덱스 관리와 유사.
*/


/*
int main()
{
	//	파일 생성.
	FILE *pFile = fopen("FTellTest.txt", "wt");
	if (pFile == NULL)
	{
		puts("파일 열기 실패");
		return -1;
	}

	fputs("1234-", pFile);
	fclose(pFile);

	//	파일 열기.
	pFile = fopen("FTellTest.txt", "rt");
	long filePos = 0;
	for (int i = 0; i < 4; ++i)
	{
		putchar(fgetc(pFile));	//	현재 위치 출력.
		filePos = ftell(pFile);	//	위치 정보 얻기.

		fseek(pFile, -1, SEEK_END);	//	마지막 한칸 뒤 정보 찾기.
		putchar(fgetc(pFile));
		fseek(pFile, filePos, SEEK_SET);//	아까 얻은 위치정보를 참고하여 이동.
	}

	puts("");

	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*
	Quiz)	ftell 함수를 이용하여 파일의 크기를 구하는 프로그램 작성.
	
*/
//======================================================