// NumberToKorean.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "NumberToKorean.h"
#include <stdio.h>

int main()
{
	int numbers;
	printf("숫자를 입력하세요 : ");
    scanf("%d", &numbers);

	int tmp = numbers;
	
	int digit = 1;

	while (tmp > 0)
	{
		digit *= 10;

		tmp /= 10;
	}

	digit /= 10;

	while (digit > 0)
	{
		NumberToKorean(numbers / digit % 10, digit);

		digit /= 10;
	}
	
	printf("\r\n");


    return 0;
}

