//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	���� ��ġ ������

		-	FILE ����ü�� ���� ����� �Լ��� ȣ��ɶ����� ������ ��ġ�� ����Ű�� �����Ͱ� ���� �� ������ ��.

			��)	fgets�� 20����Ʈ�� �д´ٸ� ������ ���� �����ϰ� �ִ� ��ġ���� 20����Ʈ�� ���� ��

				������ ��ġ�� ����Ű�� �����ʹ� ���� ��ġ�κ��� 21��° ����Ʈ�� �̵��Ѵ�.

		-	������ ó�� ����Ǹ� ������ ������ �� �պκ��� ����Ų��.

			-	������ Ư�� �κп������� �����͸� �аų� ������ �Ѵٸ� "���� ��ġ ������"�� �̵����Ѿ� ��.
*/
//======================================================
/*
	2.	���� ��ġ ������ �̵� : fseek

		-	int fseek( FILE *pFile, long offset, int whereFrom );

			-	���� ��ġ �����ڸ� whereFrom���κ��� offset��ŭ �̵�.

			-	offset

				-	���	:	���� ������ �̵�.

				-	����	:	���� ������ġ�� �̵�.

			-	whereFrom
				
				-	SEEK_SET	:	���� �� ��.

									������ ù��° ����Ʈ.

					SEEK_CUR	:	���� ��ġ.

					SEEK_END	:	���� �� ��.

									= EOF
									
										-	������ ���� ���� ��ġ
										
										-	������ ���� �˸������� ���Ե�.

										

			
*/
//======================================================
/*
int main()
{
	//	���� ����.
	FILE *pFile = fopen("FilePosition.txt", "wt");

	if (pFile == NULL)
	{
		puts("���� ���� ����");
		return -1;
	}

	fputs("123456789", pFile);
	fclose(pFile);


	//	���� ����.
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
	3.	���� ��ġ �������� ���� ��ġ : ftell

		-	long ftell( FILE* pFile );

			-	���� ��ġ �������� ���� ��ġ ���� ��ȯ.

			-	���� ����Ʈ�� ��ġ�� 0 ��ȯ.

				�迭�� �ε��� ������ ����.
*/


/*
int main()
{
	//	���� ����.
	FILE *pFile = fopen("FTellTest.txt", "wt");
	if (pFile == NULL)
	{
		puts("���� ���� ����");
		return -1;
	}

	fputs("1234-", pFile);
	fclose(pFile);

	//	���� ����.
	pFile = fopen("FTellTest.txt", "rt");
	long filePos = 0;
	for (int i = 0; i < 4; ++i)
	{
		putchar(fgetc(pFile));	//	���� ��ġ ���.
		filePos = ftell(pFile);	//	��ġ ���� ���.

		fseek(pFile, -1, SEEK_END);	//	������ ��ĭ �� ���� ã��.
		putchar(fgetc(pFile));
		fseek(pFile, filePos, SEEK_SET);//	�Ʊ� ���� ��ġ������ �����Ͽ� �̵�.
	}

	puts("");

	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*
	Quiz)	ftell �Լ��� �̿��Ͽ� ������ ũ�⸦ ���ϴ� ���α׷� �ۼ�.
	
*/
//======================================================