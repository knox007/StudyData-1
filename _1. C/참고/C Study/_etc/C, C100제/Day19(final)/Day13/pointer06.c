#include <stdio.h>
void swap(int* p1, int* p2){
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	printf("(swap함수) *p1 = %d, *p2 = %d\n", *p1, *p2);
}

void main(){
	//문제3. num1, num2의 값을 메인에서 입력받아, 그 값을 swap 함수에서 변경해보자. 
	int num1 = 0;
	int num2 = 0;
	int *p1;
	int *p2;
	printf("num1입력");
	scanf("%d", &num1);
	printf("num2입력");
	scanf("%d", &num2);
	printf("(메인함수1번출력)num1 = %d, num2 = %d\n", num1, num2);
	//1.
	//swap(&num1, &num2);
	//2.
	p1 = &num1;
	p2 = &num2;
	swap(p1, p2);
	printf("(메인함수2번출력)num1 = %d, num2 = %d\n", num1, num2);

}