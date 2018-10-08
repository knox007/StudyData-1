//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	1.	���� �����

		-	��Ʈ��

			-	������ �������� �̵����.

			-	���� ��Ʈ���� ���� = ���Ϸ� ���� �����͸� �аų� �� �غ� �Ǿ���.
	
	
	2.	���� ��Ʈ�� ���� �Լ�.

		-	���� ��Ʈ�� ���� / �Ҹ� �Լ�.

			1)	fopen

				-	FILE* fopen( const char *filename, const char *mode );

					-	filename	:	��Ʈ���� ������ �����̸�.

					-	mode		:	��Ʈ�� ��� ����.

										���� ���� ���.
			
						-	���� ��� ����

							-	�뵵	:	�б� / ����.

									Read			:	�б�.							r
									Write			:	����.							w
									Append			:	���ٿ� ����.					a
									Read / Write	:	�б�, ���� ��� ����.			r+ / w+
									Append / Read	:	�б�, ���ٿ� ���� ��� ����.	a+

									*	+ ���� �б�/���Ⱑ ���ÿ� �����ѵ�
										�б�->����, ����->�б�� �۾��� ����� ������
										�޸� ���۸� ������ �ϸ� �߸��� ��뿡���� ���輺�� �� ũ��.
											
										-	�Ϲ������� r,w,a����� �ϳ��� �����Ͽ� ��Ʈ���� �����Ѵ�.
												

							-	������	:	�ؽ�Ʈ / ���̳ʸ�.(����Ʈ�� �ؽ�Ʈ ���)

											�ؽ�Ʈ		:	t
											���̳ʸ�	:	b

											��)	���̳ʸ��� �б� ���� ���� ����	:	rb
												�ؽ�Ʈ�� ���� ���� ���� ����		:	wt, w										

									

					-	��ȯ��		:	filename ���ϰ� ��Ʈ���� �����ϰ� �ش� ������

										FILE ����ü ���� �����ͷ� ��ȯ.

				-	���ϰ� ��Ʈ���� ����.

				-	������ ����Ű�� ���� �뵵.

					-	��ȯ�Ǵ� �����͸� �̿��ؼ� ���Ͽ� �����͸� �����ϰų� �д� �뵵.


			2)	fclose

				-	int fclose( FILE* stream );

					-	stream	:	fopen���� ����Ǿ��� ���� ����ü ������.

					-	��ȯ��	:	���� ��Ʈ�� �Ҹ� ������ 0, ���н� EOF ��ȯ.

				-	����Ǿ��� ������ �ݾ���� �ϴ� ����

					-	�ü���� �Ҵ��� �ڿ��� ��ȯ.

						-	���� ������ ������ �ü���� ����.

						-	�ü���� �ý����� �ڿ��� �Ҵ��Ͽ� ��Ʈ���� ������.

							�Ҵ�� �ڿ��� �ݾ��־�� �Ҵ�� �ڿ��� �ü���� ��ȯ�Ͽ�

							���� �޸� ������ Ȯ���Ѵ�.

					-	���۸� �Ǿ��� �������� ���.

						-	�ü���� ���α׷��� ���� ���̿� ����� ���۸� �ּ� ������ ����� �����Ѵ�.

							�����͸� ���Ͽ� �����Ҷ� �ٷ� ����Ǵ� ���� �ƴ϶� �ϴ� ��¹��ۿ� ����Ǿ��ٰ�

							�ü���� ���۸� ��Ŀ� ���� ���߿� ���Ͽ� ����ȴ�.

							fclose�� ���� ������ �ݾ��ָ� ��� ���ۿ� ����Ǿ��ִ� �����Ͱ�
							
							���Ϸ� �̵��ϸ鼭 ��¹��۰� �������.

*/
//======================================================

/*	--- ���� ---

	3.	��� ���� �Լ�.

			-	char *_getcwd( char *buffer, int maxlen );
				
				-	���� �۾� ��θ� ������ �Լ�.
			
					buffer	:	���� �۾� ��� ���ڿ��� ���� ����.
				
					maxlen	:	������ ũ��.
				
					��ȯ��	:	����	-	���� �۾� ����� �ּ�.
				
								����	-	-1.

			-	int chdir( const char *dirname );

				-	���� �۾� ��θ� ����.

					dirname	:	������ ��θ�.

					��ȯ��	:	����	-	0

								����	-	-1

			
			-	int _mkdir( const char *dirname );

				-	�� ��� ����.

				-	dirname	:	������ ��θ�.

					��ȯ��	:	����	-	0

								����	-	-1

										-	�̹� ���� �̸��� ��ΰ� �������� ����.

			-	��� ��� ����

				-	".\\" or "./"

					-	���� ���� ����.

					-	".\\Test" or "./Test"

				-	"..\\" or "../"

					-	���� ���� ����.

					-	"..\\Test" or "../Test"
							
*/

/*
#include <direct.h>	//getcwd
#define _MAX_PATH 260

int main()
{
	char strBuffer[_MAX_PATH] = { 0, };
	char *pstrBuffer = NULL;


	printf("---���� �۾� ��� ���� �� ---\n");
	//	���� �۾� ��� ���.
	pstrBuffer = _getcwd(strBuffer, _MAX_PATH);

	printf("�۾� ��� : %s\n", pstrBuffer);

	//	�۾� ��� ����.
	int res = mkdir(".\\Test");

	//	�۾� ��� ����.
	//res = chdir("./Test");
	res = chdir("..\\");

	printf("---���� �۾� ��� ���� �� ---\n");

	pstrBuffer = _getcwd(strBuffer, _MAX_PATH);

	printf("�۾� ��� : %s\n", pstrBuffer);

	return 0;
}
//*/
//======================================================
/*
	3.	���� ����� �Լ�. ( ���� �������� ����. )

		-	���� ��/���
			
			-	int fgetc( FILE *stream );

				-	������ ���� �����ϰų� �б� ������ ��� EOF�� ��ȯ.

			-	int fputc( int c, FILE *stream );



		-	���ڿ� ��/���
			
			-	char *fgets( char *str, int numChars, FILE *stream );

				-	������ ���� �����Ͽ� �� �̻� ���� �����Ͱ� ���ų�

					���� �߻��� NULL ��ȯ.

			-	int fputs( const char *str, FILE *stream );

		
		-	feof

			-	int feof( FILE* pFile );

				-	����� ������ ������ ������ ���� �����ߴ��� Ȯ���ϴ� �Լ�.

				-	������ ���� ������ ��� 0�� �ƴ� �� ��ȯ.


*/


/*	���� ����.
int main()
{
	//	���� ���� ����.
	FILE *pFile = fopen("Test.txt", "wt");

	if (pFile == NULL)
	{
		printf("Test.txt ���� ����\n");
		return -1;
	}

	//	���� ���.
	fputc('A', pFile);
	fputc('B', pFile);

	//	���ڿ� ���
	fputs("Hello World\n", pFile);
	fputs("!!!!\n", pFile);

	//	���� �ݱ�
	fclose(pFile);

	return 0;
}
//*/

/*	���� ����.
int main()
{
	//	�б� ���� ����.
	FILE *pFile = fopen("Test.txt", "rt");

	if (pFile == NULL)
	{
		printf("Test.txt ���� ����\n");
		return -1;
	}

	char str[30];
	int ch;

	//	���� ��������.
	ch = fgetc(pFile);
	printf("%c\n", ch);
	ch = fgetc(pFile);
	printf("%c\n", ch);

	//	���ڿ� ��������.
	fgets(str, sizeof(str), pFile);
	printf("%s", str);
	fgets(str, sizeof(str), pFile);
	printf("%s", str);

	//	���� �ݱ�.
	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*	���� ����
int main()
{
	FILE* pfSrc = fopen("Test.txt", "rt");
	FILE* pfDst = fopen("TestCopy.txt", "wt");

	int ch;

	puts("���� ���� ����!!");
	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("���� ���� ����!!");

		return -1;
	}

	while ((ch = fgetc(pfSrc)) != EOF)
		fputc(ch, pfDst);

	if (feof(pfSrc) != 0)
		puts("���� ���� �Ϸ�!!");
	else
		puts("���� ���� ����!!");

	puts("���α׷� ����!!");

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/
//======================================================
/*
	Quiz)

		�� ������ ������ �۾��� fgets�� fputs�� �̿��Ͽ� �ۼ��Ѵ�.
*/
//======================================================










































/*	���� ����
int main()
{
	FILE* pfSrc = fopen("Test.txt", "rt");
	FILE* pfDst = fopen("TestCopy.txt", "wt");

	char str[30];

	puts("���� ���� ����!!");
	if (pfSrc == NULL || pfDst == NULL)
	{
	puts("���� ���� ����!!");

	return -1;
	}

	while ((fgets( str, sizeof(str), pfSrc)) != NULL)
		fputs(str, pfDst);

	if (feof(pfSrc) != 0)
		puts("���� ���� �Ϸ�!!");
	else
		puts("���� ���� ����!!");

	puts("���α׷� ����!!");

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/