#include <stdio.h>

void main(){

	int* p = NULL;
	int arr[3] = {10, 20, 30};
	printf("arr[0] = %d\n", arr[0]);
	printf("*(arr+0) = %d\n", *(arr+0));
	printf("*(arr+1) = %d\n", *(arr+1));
	//*배열명은 포인터(주소) 상수다. 배열명은 첫번째 요소의 주소를 나타낸다.*
	// 배열안의 요소들(저장된데이터들)에세 접근하려면, 배열명[인덱스번호]를 사용하면된다.
	// (추가로) arr[0] => *(arr+0)  : *( + ) => 줄여서 []로 사용한다.
	p = &arr[0];
	printf("p = %d\n", p);
	printf("*p = %d\n", *p);
	printf("arr[1] = %d\n", arr[1]);
	printf("*(p+1) = %d\n", *(p+1));
	printf("*(p+1) = %d\n", *(p+2));
	printf("arr + 1 = %d\n", *(arr + 1));

	/*0번
	printf("%d\n", arr[0]);
	printf("%d\n", arr[1]);
	printf("%d\n", arr[2]);
	printf("%d\n", &arr[0]);
	printf("%d\n", &arr[1]);
	printf("%d\n", &arr[2]);
	printf("%d\n", arr);
	p = arr;
	p = &arr[0];
	printf("arr[0] = %d\n", arr[0]);
	printf("&arr[0] = %d\n", &arr[0]);
	printf("p = %d\n", p);
	printf("*p = %d\n", *p);
	*/

}