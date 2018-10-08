//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	���� ����� �Լ�. ( ���� ���. )

		-	���̳ʸ� �������� �����

			-	size_t fread( void *buffer, size_t size, size_t count, FILE *stream );

				-	buffer	:	�о�帰 �����Ͱ� ����� ����.

				-	size	:	�׸� ũ��.

				-	count	:	�׸� ����.

				-	stream	:	�о�帱 ���� ������.

				-	��ȯ��	:	����					-	�Ű����� count ��.

														-	���������� count�� �� ��������ä

															������ ���� �����ϴ� ���
															
															count ���� ���� �� ��ȯ.

								����, ���� �� ���� ��	-	count ���� ���� ��.


		-	size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream );

				-	buffer	:	������ �������� ������.

				-	��ȯ��	:	����	-	�Ű����� count ��.

								����	-	count ���� ���� ��.

*/
//======================================================
/*	���� ����.
int main()
{
	int buf[7] = { 1,2,3,4,5,6,7 };

	FILE* pfSrc = fopen("src.bin", "wb");

	if (pfSrc == NULL)
	{
		puts("���� ���� ����");
		return -1;
	}

	fwrite(buf, sizeof(int), 7, pfSrc);

	fclose(pfSrc);

	return 0;
}
//*/
//======================================================
/*	���� �ε�.
int main()
{
	int buf[7] = { 0, };

	FILE* pfSrc = fopen("src.bin", "rb");

	if (pfSrc == NULL)
	{
		puts("���� ���� ����");
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
Quiz)	fread / fwrite �� �̿��� ���� ���� ���α׷� �ۼ�.
*/
//======================================================



















































/*	���� ����.
int main()
{
	FILE* pfSrc = fopen("src.bin", "rb");
	FILE* pfDst = fopen("dst.bin", "wb");

	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("���� ���� ����!!");
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
				puts("���� ���� �Ϸ�");
				break;
			}
			else
				puts("���� ���� ����!!!�Ф�");

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