//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	���� ����� �Լ�. ( ���� ���. )

		-	���Ŀ� ���� ������ �����

			-	 fprintf / fscanf

				-	int fprintf( FILE *stream, const char *format [,argument ]...);
					
					-	���� ���.
				
					int fscanf( FILE *stream, const char *format [, argument ]...);

					-	���� �б�.
					
					����)	int printf( const char *format [, argument]...);

							int scanf( const char *format [, argument]...);

							-	�Ű������� �������� ���.

							-	���� ����� �ٸ� ��.( ���� / �ܼ� )

							-	fscanf�� ��� ������ �дٰ� ���� ���� �����ϰų� 

								������ ����� EOF�� ��ȯ.
							
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
		puts("���� ���� ����!!");
		return -1;
	}

	for (int i = 0; i < 3; ++i)
	{
		puts("�̸� ���� ���� ������ �Է�");
		scanf("%s %c %d", szName, &gender, &age);	//	����Ű�� �Է��� �о������ �ʰ� �Է� ���ۿ� ���ܵд�.
		getchar();									//	�Է� ���ۿ� �����ִ� ����Ű�� �Ҹ��� ���� getcharȣ��.
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
		puts("���� ���� ����!!");
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
	2.	����ü ��ü�� �����

		-	����ü ��ü�� �ϳ��� ���̳ʸ� �����ͷ� �ν��ϰ� ó��.

		-	fwrite�� fread�� ��°�� ó��.

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
		puts("���� ���� ���� (���� ���)");
		return -1;
	}

	puts("�̸�, ����, ���� ������ �Է�");
	scanf("%s %c %d", myFriend1._szName, &myFriend1._gender, &myFriend1._age);
	fwrite( &myFriend1, sizeof(myFriend1), 1, pFile);
	fclose(pFile);

	//------------------------
	//	fread
	pFile = fopen("FriendInfo.bin", "rb");
	if (pFile == NULL)
	{
		puts("���� ���� ���� (�б� ���)");
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
	Quiz)	���� ������ fpritf / fscanf�� �ٲ㼭 ����.
*/
//======================================================