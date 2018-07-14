#include <stdio.h>
/*
	*** ���������� ***
	���������� : �������� ������, �����ͺ����� �ּҸ� ��� ������

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

	//����1. swap�Լ��� ���� pp1��pp2�� ������ num1�� num2�� ���� ��ȯ�غ���.  
	//1. num��� p��� pp���� ��������
	p1 = &num1;
	p2 = &num2;
	pp1 = &p1;
	pp2 = &p2;
	//printf("%d\n", **pp1);
	//2. swap �Լ��� �����
	//3. �����͸� ��������. 
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