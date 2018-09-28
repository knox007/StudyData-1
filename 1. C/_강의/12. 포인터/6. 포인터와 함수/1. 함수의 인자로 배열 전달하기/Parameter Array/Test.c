//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	함수의 인자로 배열 전달

	-	배열 자체를 전달할 수 없다.
	
		-	포인터를 이용하여 배열의 주소를 전달한다.

*/

//*
void ShowArray(int *pArray, int len)
//	void ShowArray(int pArray[], int len)	//	이렇게 선언하는 것도 가능.
											//	단, 매개변수를 선언하는 경우만 가능.
{	
	//	매개변수 pArray는 포인터 변수
	//	-	sizeof연산을 할 경우 배열의 크기가 아닌 포인터 변수의 크기가 반환됨.
	//	-	함수 내부에서는 인자로 전달된 배열의 길이를 계산할 수 없음.
	//		-	배열의 크기나 길이도 함께 전달.

	//	int size = sizeof(pArray);
	//	printf("%d\n", size);
	

	int i;
	for (i = 0; i < len; ++i)
		printf("%d ", pArray[i]);

	printf("\n");
}

int main(void)
{
	int arr1[] = { 1,2,3 };
	//int *pArr = arr1;
	//int pArr[] = arr1;	-	( X )
	int arr2[] = { 4,5,6,7,8 };
	int len1 = sizeof(arr1) / sizeof(int);
	int len2 = sizeof(arr2) / sizeof(int);

	ShowArray(arr1, len1);
	ShowArray(arr2, len2);

	return 0;
}
//*/
//======================================================
/*
	quiz)
		 위의 예제에 배열의 각 요소에 동일한 값을 더하는 함수를 만들고 
		 ( void AddArray(int *pArray, int len, int value) )
		 출력결과가 다음과 같이 나오게 한다.

		 처음 값
		 1 2 3
		 -------------
		 변환 값
		 2 3 4
		 4 5 6
		 7 8 9

*/


















/*
void ShowArray(int *pArray, int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%d ", pArray[i]);

	printf("\n");
}

void AddArray(int *pArray, int len, int value)
{
	int i;
	for (i = 0; i < len; ++i)
		pArray[i] += value;
}

int main(void)
{
	int arr1[] = { 1,2,3 };
	int len1 = sizeof(arr1) / sizeof(int);

	printf("처음 값\n");
	ShowArray(arr1, len1);
	printf("-------------------\n");
	printf("변환 값\n");
	AddArray(arr1, len1, 1);
	ShowArray(arr1, len1);

	AddArray(arr1, len1, 2);
	ShowArray(arr1, len1);

	AddArray(arr1, len1, 3);
	ShowArray(arr1, len1);
	
	return 0;
}
//*/