#include <stdio.h>

void main(){

	int num = 10;
	int *pNum;
	pNum = &num;
	printf("num = %d\n", num);
	printf("&num = %d\n", &num);
	printf("pNum = %d\n", pNum);
	printf("*pNum = %d\n", *pNum);
	// ����1. pNum�� ������ num�� ���� 20���� �ٲ㺸��. 
	*pNum = 20;
	printf("num = %d\n", num);
	printf("*pNum = %d\n", *pNum);

}