#include <stdio.h>
void swap(int* p1, int* p2){
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	printf("(swap�Լ�) *p1 = %d, *p2 = %d\n", *p1, *p2);
}

void main(){
	//����3. num1, num2�� ���� ���ο��� �Է¹޾�, �� ���� swap �Լ����� �����غ���. 
	int num1 = 0;
	int num2 = 0;
	int *p1;
	int *p2;
	printf("num1�Է�");
	scanf("%d", &num1);
	printf("num2�Է�");
	scanf("%d", &num2);
	printf("(�����Լ�1�����)num1 = %d, num2 = %d\n", num1, num2);
	//1.
	//swap(&num1, &num2);
	//2.
	p1 = &num1;
	p2 = &num2;
	swap(p1, p2);
	printf("(�����Լ�2�����)num1 = %d, num2 = %d\n", num1, num2);

}