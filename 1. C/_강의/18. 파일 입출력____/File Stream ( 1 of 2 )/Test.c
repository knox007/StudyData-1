//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	1.	파일 입출력

		-	스트림

			-	일종의 데이터의 이동통로.

			-	파일 스트림의 형성 = 파일로 부터 데이터를 읽거나 쓸 준비가 되었음.
	
	
	2.	파일 스트림 관련 함수.

		-	파일 스트림 개방 / 소멸 함수.

			1)	fopen

				-	FILE* fopen( const char *filename, const char *mode );

					-	filename	:	스트림을 형성할 파일이름.

					-	mode		:	스트림 방식 설정.

										파일 개방 모드.
			
						-	개방 모드 기준

							-	용도	:	읽기 / 쓰기.

									Read			:	읽기.							r
									Write			:	쓰기.							w
									Append			:	덧붙여 쓰기.					a
									Read / Write	:	읽기, 쓰기 모두 가능.			r+ / w+
									Append / Read	:	읽기, 덧붙여 쓰기 모두 가능.	a+

									*	+ 모드는 읽기/쓰기가 동시에 가능한데
										읽기->쓰기, 쓰기->읽기로 작업이 변경될 때마다
										메모리 버퍼를 비워줘야 하며 잘못된 사용에대한 위험성도 더 크다.
											
										-	일반적으로 r,w,a모드중 하나를 선택하여 스트림을 형성한다.
												

							-	데이터	:	텍스트 / 바이너리.(디폴트는 텍스트 모드)

											텍스트		:	t
											바이너리	:	b

											예)	바이너리형 읽기 모드로 파일 개방	:	rb
												텍스트형 쓰기 모드로 파일 개방		:	wt, w										

									

					-	반환값		:	filename 파일과 스트림을 형성하고 해당 정보를

										FILE 구조체 형식 포인터로 반환.

				-	파일과 스트림을 형성.

				-	파일을 가리키기 위한 용도.

					-	반환되는 포인터를 이용해서 파일에 데이터를 저장하거나 읽는 용도.


			2)	fclose

				-	int fclose( FILE* stream );

					-	stream	:	fopen으로 개방되었던 파일 구조체 포인터.

					-	반환값	:	파일 스트림 소멸 성공시 0, 실패시 EOF 반환.

				-	개방되었던 파일을 닫아줘야 하는 이유

					-	운영체제가 할당한 자원의 반환.

						-	파일 개방의 권한은 운영체제에 있음.

						-	운영체제는 시스템의 자원을 할당하여 스트림을 개방함.

							할당된 자원을 닫아주어야 할당된 자원을 운영체제에 반환하여

							가용 메모리 공간을 확보한다.

					-	버퍼링 되었던 데이터의 출력.

						-	운영체제는 프로그램과 파일 사이에 입출력 버퍼를 둬서 성능의 향상을 도모한다.

							데이터를 파일에 저장할때 바로 저장되는 것이 아니라 일단 출력버퍼에 저장되었다가

							운영체제의 버퍼링 방식에 따라 나중에 파일에 저장된다.

							fclose를 통해 파일을 닫아주면 출력 버퍼에 저장되어있던 데이터가
							
							파일로 이동하면서 출력버퍼가 비워진다.

*/
//======================================================

/*	--- 참고 ---

	3.	경로 관련 함수.

			-	char *_getcwd( char *buffer, int maxlen );
				
				-	현재 작업 경로를 얻어오는 함수.
			
					buffer	:	현재 작업 경로 문자열을 담을 버퍼.
				
					maxlen	:	버퍼의 크기.
				
					반환값	:	성공	-	현재 작업 경로의 주소.
				
								실패	-	-1.

			-	int chdir( const char *dirname );

				-	현재 작업 경로를 변경.

					dirname	:	변경할 경로명.

					반환값	:	성공	-	0

								실패	-	-1

			
			-	int _mkdir( const char *dirname );

				-	새 경로 생성.

				-	dirname	:	생성할 경로명.

					반환값	:	성공	-	0

								실패	-	-1

										-	이미 같은 이름의 경로가 있을때도 실패.

			-	상대 경로 설정

				-	".\\" or "./"

					-	현재 폴더 기준.

					-	".\\Test" or "./Test"

				-	"..\\" or "../"

					-	상위 폴더 기준.

					-	"..\\Test" or "../Test"
							
*/

/*
#include <direct.h>	//getcwd
#define _MAX_PATH 260

int main()
{
	char strBuffer[_MAX_PATH] = { 0, };
	char *pstrBuffer = NULL;


	printf("---현재 작업 경로 변경 전 ---\n");
	//	현재 작업 경로 얻기.
	pstrBuffer = _getcwd(strBuffer, _MAX_PATH);

	printf("작업 경로 : %s\n", pstrBuffer);

	//	작업 경로 생성.
	int res = mkdir(".\\Test");

	//	작업 경로 변경.
	//res = chdir("./Test");
	res = chdir("..\\");

	printf("---현재 작업 경로 변경 후 ---\n");

	pstrBuffer = _getcwd(strBuffer, _MAX_PATH);

	printf("작업 경로 : %s\n", pstrBuffer);

	return 0;
}
//*/
//======================================================
/*
	3.	파일 입출력 함수. ( 자주 사용되지는 않음. )

		-	문자 입/출력
			
			-	int fgetc( FILE *stream );

				-	파일의 끝에 도달하거나 읽기 실패인 경우 EOF를 반환.

			-	int fputc( int c, FILE *stream );



		-	문자열 입/출력
			
			-	char *fgets( char *str, int numChars, FILE *stream );

				-	파일의 끝에 도달하여 더 이상 읽을 데이터가 없거나

					오류 발생시 NULL 반환.

			-	int fputs( const char *str, FILE *stream );

		
		-	feof

			-	int feof( FILE* pFile );

				-	저장된 파일을 읽을때 파일의 끝에 도달했는지 확인하는 함수.

				-	파일의 끝에 도달한 경우 0이 아닌 값 반환.


*/


/*	파일 저장.
int main()
{
	//	쓰기 모드로 개방.
	FILE *pFile = fopen("Test.txt", "wt");

	if (pFile == NULL)
	{
		printf("Test.txt 열기 실패\n");
		return -1;
	}

	//	문자 출력.
	fputc('A', pFile);
	fputc('B', pFile);

	//	문자열 출력
	fputs("Hello World\n", pFile);
	fputs("!!!!\n", pFile);

	//	파일 닫기
	fclose(pFile);

	return 0;
}
//*/

/*	파일 열기.
int main()
{
	//	읽기 모드로 개방.
	FILE *pFile = fopen("Test.txt", "rt");

	if (pFile == NULL)
	{
		printf("Test.txt 열기 실패\n");
		return -1;
	}

	char str[30];
	int ch;

	//	문자 가져오기.
	ch = fgetc(pFile);
	printf("%c\n", ch);
	ch = fgetc(pFile);
	printf("%c\n", ch);

	//	문자열 가져오기.
	fgets(str, sizeof(str), pFile);
	printf("%s", str);
	fgets(str, sizeof(str), pFile);
	printf("%s", str);

	//	파일 닫기.
	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*	파일 복사
int main()
{
	FILE* pfSrc = fopen("Test.txt", "rt");
	FILE* pfDst = fopen("TestCopy.txt", "wt");

	int ch;

	puts("파일 복사 시작!!");
	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("파일 오픈 실패!!");

		return -1;
	}

	while ((ch = fgetc(pfSrc)) != EOF)
		fputc(ch, pfDst);

	if (feof(pfSrc) != 0)
		puts("파일 복사 완료!!");
	else
		puts("파일 복사 실패!!");

	puts("프로그램 종료!!");

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/
//======================================================
/*
	Quiz)

		위 예제와 동일한 작업을 fgets와 fputs를 이용하여 작성한다.
*/
//======================================================










































/*	파일 복사
int main()
{
	FILE* pfSrc = fopen("Test.txt", "rt");
	FILE* pfDst = fopen("TestCopy.txt", "wt");

	char str[30];

	puts("파일 복사 시작!!");
	if (pfSrc == NULL || pfDst == NULL)
	{
	puts("파일 오픈 실패!!");

	return -1;
	}

	while ((fgets( str, sizeof(str), pfSrc)) != NULL)
		fputs(str, pfDst);

	if (feof(pfSrc) != 0)
		puts("파일 복사 완료!!");
	else
		puts("파일 복사 실패!!");

	puts("프로그램 종료!!");

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/