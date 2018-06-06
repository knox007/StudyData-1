#include <stdio.h>
#include <stdlib.h>

int* test(int num);

void m_alloc(int **pp, int num){
	*pp = (int*)malloc(num * sizeof(int));
}
 
void main(){
	// 동적할당 다른함수에서 받아오기.(주소값받아오기)
	int num, i;
	int *p = NULL; // 초기화시키기. #define NULL 0
	int **pp = NULL;
	pp = &p;
	printf("숫자입력: "); 
	scanf("%d", &num);
	//1.다른함수에서 동적할당받기
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

// 동적할당하는 함수 (동적할당만 함수로 분리시킨것)
int* test(int num){
	int *p = NULL;
	p = (int*)malloc(num * sizeof(int));
	return p;
}