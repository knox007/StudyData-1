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
	// 포인터문제
	// 문제4. int a = 10;을 포인터 변수를 통하여 값을 1000으로 바꿔보세요
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
	
	// 문제5. a = 10, b = 50 두수의 값을 포인터를 이용하여 바꿔보세요 
	// 문제6. 문제5번의 두수의 값을 swap함수를 이용하여 값을 바꿔보세요
	// 문제7. a = 10, b = 50, c = 25 세개의 숫자를 보내서 가장 큰값을 돌려주는 함수를 만들어보세요.(함수문제)
	int a = 10;
	int b = 20;
	int c = 30;
	int result;
	result = max(a, b,c);
	*/
	// 문제8. int arr[3] = {10, 20, 30}; 이라는 배열이 있고, 
	//			포인터변수를 통하여 arr의 첫번째,두번째,세번째 요소를 각각 출력해보세요. 
	int arr[3] = {10, 20, 30};
	int *p;
	p = &arr[0]; // p = arr; // *(arr+0) == arr[0]  *( + ) == [] // 
	printf("%d\n", *p);
	p++;
	printf("%d\n", *p);
	p++;
	printf("%d\n", *p);
}