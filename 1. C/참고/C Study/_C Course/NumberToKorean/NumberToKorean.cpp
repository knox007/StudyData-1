#include "stdafx.h"
#include "NumberToKorean.h"

void NumberToKorean(int number, int digit)
{
	char *res = 0;

	switch ( number	)
	{
	case 1:
		printf("��");
		break;
	case 2:
		printf("��");
		break;
	case 3:
		printf("��");
		break;
	case 4:
		printf("��");
		break;
	case 5:
		printf("��");
		break;
	case 6:
		printf("��");
		break;
	case 7:
		printf("ĥ");
		break;
	case 8:
		printf("��");
		break;
	case 9:
		printf("��");
		break;

	}//	switch ( number	)

	if (number > 0)
	{
		switch (digit)
		{
		case 10:
			printf("��");
			break;
		case 100:
			printf("��");
			break;
		case 1000:
			printf("õ");
			break;
		case 10000:
			printf("��");
			break;
		case 100000:
			printf("��");
			break;
		case 1000000:
			printf("��");
			break;
		case 10000000:
			printf("õ");
			break;

		}//	switch (digit)

	}//	if (number > 0)
	
	printf(" ");

}//	char* NumberToKorean(int number, int digit)