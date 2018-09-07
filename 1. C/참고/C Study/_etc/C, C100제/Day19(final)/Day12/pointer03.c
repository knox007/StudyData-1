#include <stdio.h>

void main(){

	int num = 10;
	int *pNum;
	pNum = &num;
	printf("num = %d\n", num);
	printf("&num = %d\n", &num);
	printf("pNum = %d\n", pNum);
	printf("*pNum = %d\n", *pNum);
	// 문제1. pNum을 가지고 num의 값을 20으로 바꿔보자. 
	*pNum = 20;
	printf("num = %d\n", num);
	printf("*pNum = %d\n", *pNum);

}