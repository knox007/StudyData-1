#include <stdio.h>
void swap(int* p1, int* p2){
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	printf("*p1 = %d, *p2 = %d\n", *p1, *p2);
}

void main(){
	//����1. num1, num2�� ���� p1, p2�� ���� main�Լ����� �����غ�����.
	int num1 = 10;
	int num2 = 20; 	
	int* p1;	// ������: num1�� �ּҸ� ���� �����ͺ��� ����
	int* p2;	// ������: num2�� �ּҸ� ���� �����ͺ��� ����
	p1 = &num1;
	p2 = &num2;
	/*
	int tmp;	//�ӽ� ������ ����
	printf("num1 = %d, num2 = %d\n", num1, num2);
	p1 = &num1;	// ������ �����ͺ����� �ּҸ� �ִ� ����
	p2 = &num2;
	printf("&num1 = %d, &num2 = %d\n", &num1, &num2);
	printf("p1 = %d, p2 = %d\n", p1, p2);
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	printf("num1 = %d, num2 = %d\n", num1, num2);
	printf("*p1 = %d, *p2 = %d\n", *p1, *p2);
	*/
	//����2. �� ������ swap�Լ����� �����غ���. 
	//swap(&num1, &num2);
	//swap(p1, p2);

	
}