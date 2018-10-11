//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	파일 입출력 함수. ( 자주 사용. )

		-	서식에 따른 데이터 입출력

			-	 fprintf / fscanf

				-	int fprintf( FILE *stream, const char *format [,argument ]...);
					
					-	파일 출력.
				
					int fscanf( FILE *stream, const char *format [, argument ]...);

					-	파일 읽기.
					
					참고)	int printf( const char *format [, argument]...);

							int scanf( const char *format [, argument]...);

							-	매개변수로 가변인자 사용.

							-	적용 대상이 다를 뿐.( 파일 / 콘솔 )

							-	fscanf의 경우 파일을 읽다가 파일 끝에 도달하거나 

								에러가 생기면 EOF를 반환.
							
*/

/*	fprintf
int main()
{
	char szName[10];
	char gender = 'm';
	int age;
	
	FILE* pFile = fopen("friend.txt", "wt");

	if (pFile == NULL)
	{
		puts("파일 열기 실패!!");
		return -1;
	}

	for (int i = 0; i < 3; ++i)
	{
		puts("이름 성별 나이 순으로 입력");
		scanf("%s %c %d", szName, &gender, &age);	//	엔터키의 입력을 읽어들이지 않고 입력 버퍼에 남겨둔다.
		getchar();									//	입력 버퍼에 남아있는 엔터키의 소멸을 위해 getchar호출.
		fprintf(pFile, "%s %c %d", szName, gender, age);
	}
	
	fclose(pFile);
	return 0;

}
//*/



/*	fscanf

int main()
{
	char szName[10];
	char gender = 'm';
	int age;

	FILE* pFile = fopen("friend.txt", "rt");

	if (pFile == NULL)
	{
		puts("파일 열기 실패!!");
		return -1;
	}

	int res = 0;

	while (1)
	{
		res = fscanf(pFile, "%s %c %d", szName, &gender, &age);
		if (res == EOF)
			break;

		printf("%s %c %d\n", szName, gender, age);
	}

	fclose(pFile);

	return 0;

}
//*/
//======================================================
/*
	2.	구조체 객체의 입출력

		-	구조체 객체를 하나의 바이너리 데이터로 인식하고 처리.

		-	fwrite와 fread로 통째로 처리.

*/

//*
typedef struct
{
	char _szName[20];
	char _gender;
	int _age;

} SFriendInfo;

int main()
{
	FILE* pFile;

	SFriendInfo myFriend1;
	SFriendInfo myFriend2;

	//-----------------------
	//	fwrite
	pFile = fopen("FriendInfo.bin", "wb");
	if (pFile == NULL)
	{
		puts("파일 열기 실패 (쓰기 모드)");
		return -1;
	}

	puts("이름, 성별, 나이 순으로 입력");
	scanf("%s %c %d", myFriend1._szName, &myFriend1._gender, &myFriend1._age);
	fwrite( &myFriend1, sizeof(myFriend1), 1, pFile);
	fclose(pFile);

	//------------------------
	//	fread
	pFile = fopen("FriendInfo.bin", "rb");
	if (pFile == NULL)
	{
		puts("파일 열기 실패 (읽기 모드)");
		return -1;
	}
	fread(&myFriend2, sizeof(myFriend2), 1, pFile);
	printf("%s %c %d\n", myFriend2._szName, myFriend2._gender, myFriend2._age);

	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*
	Quiz)	위의 예제를 fpritf / fscanf로 바꿔서 적용.
*/
//======================================================