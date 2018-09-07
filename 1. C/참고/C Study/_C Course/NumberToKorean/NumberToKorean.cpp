#include "stdafx.h"
#include "NumberToKorean.h"

void NumberToKorean(int number, int digit)
{
	char *res = 0;

	switch ( number	)
	{
	case 1:
		printf("ÀÏ");
		break;
	case 2:
		printf("ÀÌ");
		break;
	case 3:
		printf("»ï");
		break;
	case 4:
		printf("»ç");
		break;
	case 5:
		printf("¿À");
		break;
	case 6:
		printf("À°");
		break;
	case 7:
		printf("Ä¥");
		break;
	case 8:
		printf("ÆÈ");
		break;
	case 9:
		printf("±¸");
		break;

	}//	switch ( number	)

	if (number > 0)
	{
		switch (digit)
		{
		case 10:
			printf("½Ê");
			break;
		case 100:
			printf("¹é");
			break;
		case 1000:
			printf("Ãµ");
			break;
		case 10000:
			printf("¸¸");
			break;
		case 100000:
			printf("½Ê");
			break;
		case 1000000:
			printf("¹é");
			break;
		case 10000000:
			printf("Ãµ");
			break;

		}//	switch (digit)

	}//	if (number > 0)
	
	printf(" ");

}//	char* NumberToKorean(int number, int digit)