#include <stdio.h>
#include <stdlib.h>

int* test(int num);

void m_alloc(int **pp, int num){
	*pp = (int*)malloc(num * sizeof(int));
}
 
void main(){
	// �����Ҵ� �ٸ��Լ����� �޾ƿ���.(�ּҰ��޾ƿ���)
	int num, i;
	int *p = NULL; // �ʱ�ȭ��Ű��. #define NULL 0
	int **pp = NULL;
	pp = &p;
	printf("�����Է�: "); 
	scanf("%d", &num);
	//1.�ٸ��Լ����� �����Ҵ�ޱ�
	//p = test(num);
	//2. 
	m_alloc(&p, num);
	//3. 
	*pp = (int*)malloc(num * sizeof(int));
	for(i=1;i<=num;i++){
		p[i-1] = i*10;
	}
	for(i=0;i<num;i++){
		printf("%d\n", p[i]);
	}
}

// �����Ҵ��ϴ� �Լ� (�����Ҵ縸 �Լ��� �и���Ų��)
int* test(int num){
	int *p = NULL;
	p = (int*)malloc(num * sizeof(int));
	return p;
}