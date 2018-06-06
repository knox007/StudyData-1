#include <stdio.h>
#include <stdlib.h>

void main(){
	/*
	// 문제1. 숫자를 입력받고, 해당 숫자만큼 방을만들어서 10부터 10단위씩 증가하는 값을 대입해보자. (5, 10~ 50까지 대입)
	int *p; // 동적할당하여 주소받을 포인터변수
	int num, i;
	printf("숫자입력: ");
	// 숫자받기. 
	scanf("%d", &num);
	// 받은 숫자만큼 동적할당하기.
	p = (int*)malloc(num * sizeof(int));
	// 포문을 돌려서 방하나씩 접근하고 접근할때마다 값을 대입시키자. (자동화시키기)
	for(i=1;i<=num;i++){
		p[i-1] = i*10;
	}
	for(i=0; i<num; i++){
		printf("%d\n", p[i]);
	}
	*/
	// 문제2. 숫자를 입력받고, 함수를 하나 만들어서 그쪽에서 해당 숫자만큼 방을 만들고 값 대입. 단, 값대입은 main에서..
	int num, i;
	int *p;
	printf("숫자입력: "); 
	scanf("%d", &num);
	p = test(num);

	for(i=1;i<=num;i++){
		p[i-1] = i*10;
	}

}

// 동적할당하는 함수 (동적할당만 함수로 분리시킨것)
// 돌려줄 값이 주소이니 함수의 리턴타입도 주소(포인터)로 바꾸자. 
int* test(int num){
	int *p;
	p = (int*)malloc(num * sizeof(int));
	return p;	// 동적할당하고 받은 주소를 메인함수에 돌려주자. 
}