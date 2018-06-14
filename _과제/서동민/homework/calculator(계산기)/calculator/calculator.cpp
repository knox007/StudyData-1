#include "stdafx.h"
#include "calculator.h"


int Calculator::Add(int a, int b) {
	return a + b;
}
int Calculator::Minus(int a, int b) {
	return a - b;
}
int Calculator::Multi(int a, int b) {
	return a * b;
}
int Calculator::Divide(int a, int b) {
	return a / b;
}

	
void Calculator::Run() {
	int num;
	int a, b, c;
	while (1) {
		printf("=============\n 계산기프로그램\n=============\n\n");
		printf("1.덧셈\n");
		printf("2.뺄셈\n");
		printf("3.곱셈\n");
		printf("4.나눗셈\n");
		printf("5.종료\n");
		scanf_s("%d", &c);
		if (c != 5) {
			printf("첫번째수를 입력하세요 >> ");
			scanf_s("%d", &a);
			printf("두번째수를 입력하세요 >> ");
			scanf_s("%d", &b);
		}
		switch (c)
		{
			case 1: {
				num = Add(a, b);
				printf("%d + %d = %d\n\n", a, b, num);
				break;
			}
			case 2: {
				num = Minus(a, b);
				printf("%d - %d = %d\n\n", a, b, num);
				break;
			}
			case 3: {
				num = Multi(a, b);
				printf("%d * %d = %d\n\n", a, b, num);
				break;
			}
			case 4: {
				num = Divide(a, b);
				printf("%d / %d = %d\n\n", a, b, num);
				break;
			}
			case 5: {
				printf("종료\n\n");
				exit(0);
				break;
			}
		}
	}
}


Calculator::Calculator()
}
}


Calculator::~Calculator()
{
}
