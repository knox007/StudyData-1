//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	포인터의 증감연산
	
	-	T형 포인터를 대상으로 n의 크기 만큼 값을 증감하면
		
		n x sizeof(T) 만큼 주소값이 증감한다.
		
*/

/*
int main(void)
{
	int *ptr1 = 0x0010;				//	sizeof(int)	?
	double *ptr2 = 0x0010;			//	sizeof(double)	?

	printf("ptr1 = %p     ptr2 = %p\n", ptr1, ptr2);
	printf("ptr1 + 1 = %p   ptr1 + 2 = %p\n", ptr1 + 1, ptr1 + 2);
	printf("ptr2 + 1 = %p   ptr2 + 2 = %p \n", ptr2 + 1, ptr2 + 2);
		
	
	printf("++ptr1, ++ptr2 \n");
	++ptr1, ++ptr2;
	printf("ptr1 = %p     ptr2 = %p\n", ptr1, ptr2);
	
	return 0;
}
//*/


//	이러한 특성으로 인해 다음과 같은 배열 접근도 가능하다.
/*	
int main(void)
{
	int arr[3] = { 11,22,33 };

	int *ptr = arr;	//	int *ptr = &arr[0]; 과 동일.

	printf("%d, %d, %d\n", *ptr, *(ptr + 1), *(ptr + 2));


	printf("%d ", *(ptr++));
	printf("%d ", *(ptr++));
	printf("%d ", *(ptr--));
	printf("%d ", *(ptr--));
	printf("%d \n", *ptr);

	return 0;
}
//*/

/*	Quiz 1)
int main(void)
{
	int arr[3] = { 11,22,33 };

	int *ptr = arr;	//	int *ptr = &arr[0]; 과 동일.

	printf("%d, %d, %d\n", *ptr, *(ptr + 1), *(ptr + 2));

	int a = *(ptr++);
	int b = (*ptr)++;
	int c = *(ptr + 1);

	//	실행결과는??
	printf("%d, %d, %d\n", a, b, c);
}
//*/
//======================================================
/*
2.	arr[i] == *(arr+i)

	-	*ptr, *(ptr+1), *(ptr+2) == arr[0], arr[1], arr[2]

	-	배열 이름과 포인터 변수는 상수/변수의 차이만 있을뿐 사실상 동일.

	-	printf("%d, %d, %d\n", *ptr, *(ptr + 1), *(ptr + 2));	*ptr == *( ptr + 0 )

		printf("%d, %d, %d\n", ptr[0], ptr[1], ptr[2]);

		printf("%d, %d, %d\n", *arr, *(arr + 1), *(arr + 2));

		printf("%d, %d, %d\n", arr[0], arr[1], arr[2]);

		-	arr[i] == *(arr+i)

*/
//======================================================
/*	Quiz 2)
	
	int arr[] = {1,2,3,4,5};

	이 배열의  첫번째 요소를 가리키는 포인터 변수 ptr을 선언하고 

	ptr을 이용하여 모든 배열요소의 값을 2씩 증가시킨 후 출력.

*/


















/*
int main(void)
{
	int arr[] = { 1,2,3,4,5 };

	int *ptr = arr;

	printf("--- before ---\n");
	for (int cur = 0; cur < 5; ++cur)
		printf("%d\n", *(ptr + cur));

	for (int cur = 0; cur < 5; ++cur)
		*(ptr + cur) += 2;

	printf("--- after ---\n");
	for (int cur = 0; cur < 5; ++cur)
		printf("%d\n", *(ptr + cur));

	return 0;
}
//*/