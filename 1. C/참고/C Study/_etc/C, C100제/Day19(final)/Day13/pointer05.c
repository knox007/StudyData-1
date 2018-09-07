#include <stdio.h>
void swap(int* p1, int* p2){
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	printf("*p1 = %d, *p2 = %d\n", *p1, *p2);
}

void main(){
	//문제1. num1, num2의 값을 p1, p2를 통해 main함수에서 변경해보세요.
	int num1 = 10;
	int num2 = 20; 	
	int* p1;	// 포인터: num1의 주소를 받을 포인터변수 선언
	int* p2;	// 포인터: num2의 주소를 받을 포인터변수 선언
	p1 = &num1;
	p2 = &num2;
	/*
	int tmp;	//임시 저장할 변수
	printf("num1 = %d, num2 = %d\n", num1, num2);
	p1 = &num1;	// 실제로 포인터변수에 주소를 넣는 과정
	p2 = &num2;
	printf("&num1 = %d, &num2 = %d\n", &num1, &num2);
	printf("p1 = %d, p2 = %d\n", p1, p2);
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	printf("num1 = %d, num2 = %d\n", num1, num2);
	printf("*p1 = %d, *p2 = %d\n", *p1, *p2);
	*/
	//문제2. 위 문제를 swap함수에서 변경해보기. 
	//swap(&num1, &num2);
	//swap(p1, p2);

	
}