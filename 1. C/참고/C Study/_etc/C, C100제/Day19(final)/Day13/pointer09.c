#include <stdio.h>

	// 포인터 연산자. 
	// 포인터에 연산을 할경우 그 포인터의 데이터 타입 크기단위로 더해진다. 

void main(){

	int arr[] = {1,2,3,4,5};
	// int형의 데이터를 받을 포인터타입 p변수 선언 : int형포인터타입 변수
	int* p;

	// p에 배열arr의 주소를 넣는다.
	p = arr; // p = &arr[0];
	printf("첫번째요소 = %d\n", *p);	// 배열의 첫번째 주소에 있는 값이 출력
	printf("p주소1: %d\n", p);
	// p에 1을 더함. 포인터에 1을 더하면 p가 int형 포인터라서 4byte만큼 더해진다.
	p++;	
	printf("두번째요소 = %d\n", *p);
	printf("p주소2: %d\n", p);
	p--;
	printf("첫번째요소 = %d\n", *p);
	printf("p주소3: %d\n", p);
}