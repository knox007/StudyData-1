//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	파일 입출력 함수. ( 자주 사용. )

		-	바이너리 데이터의 입출력

			-	size_t fread( void *buffer, size_t size, size_t count, FILE *stream );

				-	buffer	:	읽어드린 데이터가 저장될 버퍼.

				-	size	:	항목 크기.

				-	count	:	항목 갯수.

				-	stream	:	읽어드릴 파일 포인터.

				-	반환값	:	성공					-	매개변수 count 값.

														-	성공했지만 count를 다 읽지못한채

															파일의 끝에 도달하는 경우
															
															count 보다 작은 값 반환.

								실패, 파일 끝 도달 시	-	count 보다 작은 값.


		-	size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream );

				-	buffer	:	저장할 데이터의 포인터.

				-	반환값	:	성공	-	매개변수 count 값.

								실패	-	count 보다 작은 값.

*/
//======================================================
/*	파일 저장.
int main()
{
	int buf[7] = { 1,2,3,4,5,6,7 };

	FILE* pfSrc = fopen("src.bin", "wb");

	if (pfSrc == NULL)
	{
		puts("파일 열기 실패");
		return -1;
	}

	fwrite(buf, sizeof(int), 7, pfSrc);

	fclose(pfSrc);

	return 0;
}
//*/
//======================================================
/*	파일 로딩.
int main()
{
	int buf[7] = { 0, };

	FILE* pfSrc = fopen("src.bin", "rb");

	if (pfSrc == NULL)
	{
		puts("파일 열기 실패");
		return -1;
	}

	fread(buf, sizeof(int), 7, pfSrc);

	for (int cur = 0; cur < 7; ++cur)
		printf("%d ", buf[cur]);

	printf("\n");

	fclose(pfSrc);

	return 0;
}
//*/
//======================================================
/*
Quiz)	fread / fwrite 를 이용해 파일 복사 프로그램 작성.
*/
//======================================================



















































/*	파일 복사.
int main()
{
	FILE* pfSrc = fopen("src.bin", "rb");
	FILE* pfDst = fopen("dst.bin", "wb");

	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("파일 열기 실패!!");
		return -1;
	}

	int readCount = 0;
	int readBuf[7] = { 0 };
	

//	readCount = fread(readBuf, sizeof(int), 7, pfSrc);
//	fwrite(readBuf, sizeof(int), 7, pfDst);

	while (1)
	{
		readCount = fread(readBuf, sizeof(int), 7, pfSrc);

		if (readCount < 7)
		{
			if (feof(pfSrc) != 0)
			{
				fwrite(readBuf, sizeof(int), readCount, pfDst);
				puts("파일 복사 완료");
				break;
			}
			else
				puts("파일 복사 실패!!!ㅠㅠ");

			break;
		}

		fwrite(readBuf, sizeof(int), 7, pfDst);
	}

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/
//======================================================