#include <stdio.h>
/*
	*** 이중포인터 ***
	이중포인터 : 포인터의 포인터, 포인터변수의 주소를 담는 포인터

	int a = 1234;
	int *p;
	int **pp;
	p = &a;
	pp = &p;

	a  == *p == **pp
	&a ==  p ==  *pp
		  &p ==   pp

*/
void swap(int **pp1, int **pp2);

void main(){
	/*
	int num = 20;
	int *p;
	int **pp;

	p = &num;
	pp = &p;
	printf("num = %d\n", num);
	printf("&num = %d\n", &num);
	printf("*p = %d\n", *p);
	printf("p = %d\n", p);
	printf("&p = %d\n", &p);
	printf("pp = %d\n", pp);
	printf("*pp = %d\n", *pp);
	printf("**pp = %d\n", **pp);

	*p = 100;
	**pp = 200;
	printf("num = %d\n", num);
	*/
	int num1 = 10;
	int num2 = 20;
	int *p1;
	int *p2;
	int **pp1;
	int **pp2;

	//문제1. swap함수를 만들어서 pp1과pp2를 가지고 num1과 num2의 값을 교환해보자.  
	//1. num들과 p들고 pp들을 연결하자
	p1 = &num1;
	p2 = &num2;
	pp1 = &p1;
	pp2 = &p2;
	//printf("%d\n", **pp1);
	//2. swap 함수를 만들고
	//3. 데이터를 보내보자. 
	//swap(pp1, pp2);
	swap(&p1, &p2);
	printf("num1 = %d\n", num1);
	printf("num2 = %d\n", num2);
}

void swap(int **pp1, int **pp2){
	int *temp;
	temp = *pp1;
	*pp1 = *pp2;
	*pp2 = temp;
	printf("%d\n", **pp1);
	printf("%d\n", **pp2);
}