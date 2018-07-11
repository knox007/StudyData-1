#include <stdio.h>
#include <stdlib.h> //malloc()

void main(){

	// 배열문제
	// 1.방 5개 만들고 90, 80, 70, 60, 50 저장하고, 낮은 수부터 다시 정렬시켜서 저장해보자. 
	// 포인터 문제
	// 1. 숫자 두개를 입력받고, swap함수에서 값을 바꿔보자
	// 2. 1번 문제의 배열의 인덱스0번의 요소를 포인터를 이용하여 1000을 바꿔보자. 
	// 동적할당
	// 1. 포인터를 이용하여 방 5개를 만들고 1, 2, 3, 4, 5를 저장해보자.  
	int* p;
	p = (int*)malloc(5 * sizeof(int));
	p[0] = 1;
	p[1] = 2;
	p[2] = 3;
	p[3] = 4;
	p[4] = 5;
	/*
	char* ch;
	ch = (char*)malloc(10*sizeof(char));

	double* dp;
	dp = (double*)malloc(3*sizeof(double));
	*/





}