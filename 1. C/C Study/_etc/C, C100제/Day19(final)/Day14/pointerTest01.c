#include <stdio.h>

void swap(int *p1, int *p2){
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
int max(int a, int b, int c){
	int max;
	int i;
	max = a;
	if(max < b){
		max = b;
	}
	if(max < c){
		max = c;
	}
	return max;
}

void main(){
	// �����͹���
	// ����4. int a = 10;�� ������ ������ ���Ͽ� ���� 1000���� �ٲ㺸����
	/*
	int a = 10;
	int b = 20;
	int *p1;
	int *p2;
	int tmp;
	p1 = &a;
	p2 = &b;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	swap(&a, &b);
	swap(p1, p2);
	
	// ����5. a = 10, b = 50 �μ��� ���� �����͸� �̿��Ͽ� �ٲ㺸���� 
	// ����6. ����5���� �μ��� ���� swap�Լ��� �̿��Ͽ� ���� �ٲ㺸����
	// ����7. a = 10, b = 50, c = 25 ������ ���ڸ� ������ ���� ū���� �����ִ� �Լ��� ��������.(�Լ�����)
	int a = 10;
	int b = 20;
	int c = 30;
	int result;
	result = max(a, b,c);
	*/
	// ����8. int arr[3] = {10, 20, 30}; �̶�� �迭�� �ְ�, 
	//			�����ͺ����� ���Ͽ� arr�� ù��°,�ι�°,����° ��Ҹ� ���� ����غ�����. 
	int arr[3] = {10, 20, 30};
	int *p;
	p = &arr[0]; // p = arr; // *(arr+0) == arr[0]  *( + ) == [] // 
	printf("%d\n", *p);
	p++;
	printf("%d\n", *p);
	p++;
	printf("%d\n", *p);
}