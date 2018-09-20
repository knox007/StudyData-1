//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	배열의 접근

	-	arr[idx]	:	배열 arr의 (idx + 1 )번째 요소
*/


/*

int main(void)
{
	int arr[5];
	int sum = 0;

	arr[0] = 10, arr[1] = 20, arr[2] = 30, arr[3] = 40, arr[4] = 50;
//	arr[0] = 10, arr[1] = 20, arr[2] = 30, arr[3] = 40, arr[4] = 50, arr[5] = 60;

	for (int cur = 0; cur < 5; ++cur)
//	for (int cur = 0; cur < 6; ++cur)
		sum += arr[cur];

	printf("모든 배열 요소의 합 : %d\n", sum);

	return 0;
}
//-----------------------------
/*
	추가설명.

	-	배열의 모든 요소는 반복문을 통하여 순차적으로 접근하는 것이 가능.

	-	배열의 길이를 초과하여 접근 하는 경우 
		
		컴파일러는 배열접근에 대한 유효성 검사를 진행하지 않아서 컴파일 에러가 발생하지 않음.

		-	이때 할당하지 않은 메모리 공간을 침범하게 되는데 반응은 상황에 따라 다름.
		
			경우에 따라 문제가 발견되지 않을 수도 있음.
*/

//*/
//======================================================





//======================================================
/*
2.	배열의 초기화.

	-	int arr1[3] = {1, 2, 3};
		
		-	{}로 묶인 부분을 초기화 리스트라고 함.

	-	int arr2[] = {1, 2, 3};

		-	초기화 리스트가 선언되면 배열의 길이 정보 생략 가능.

		-	컴파일러가 초기화 리스트의 수를 참조하여 길이 정보를 채워주기 때문.

			-	int arr2[] = {1, 2, 3};		==		int arr2[3] = {1, 2, 3};

	-	int arr3[5] = {1, 2};

		-	첫 번째 요소부터 순차적으로 값을 채워나가되 값이 존재하지 않는 요소들은 0으로 채워짐.

			-	int arr3[5] = {1, 2};		==		int arr3[5] = {1, 2, 0, 0, 0};
*/


/*

int main(void)
{
	int arr1[5] = { 1,2,3,4,5 };
	int arr2[] = { 1,2,3,4,5,6,7 };
	int arr3[5] = { 1,2 };

	printf("배열 arr1의 크기 : %d\n", sizeof(arr1));
	printf("배열 arr2의 크기 : %d\n", sizeof(arr2));
	printf("배열 arr3의 크기 : %d\n", sizeof(arr3));

	int arr1Len, arr2Len, arr3Len;
	arr1Len = sizeof(arr1) / sizeof(int);
	arr2Len = sizeof(arr2) / sizeof(int);
	arr3Len = sizeof(arr3) / sizeof(int);

	int cur = 0;
	for (cur = 0; cur < arr1Len; ++cur)
		printf("%d ", arr1[cur]);
	printf("\n");

	for (cur = 0; cur < arr2Len; ++cur)
		printf("%d ", arr2[cur]);
	printf("\n");

	for (cur = 0; cur < arr3Len; ++cur)
		printf("%d ", arr3[cur]);
	printf("\n");

	return 0;
}

//*/
//======================================================
/*	quiz)

	길이가 5인 int 형 배열을 선언하고 총 5개의 정수를 입력받는다.
	입력후에 다음의 내용이 출력하도록 한다.

	최대 값, 최소 값과 총 합.

	hint)	배열을 이용하여 scanf로 값을 입력 받을 때는 이런 식으로 한다.
	
			scanf("%d", &arr[0]);	->	1번째 요소에 정수값을 입력받음.



	예)	정수를 5개 입력하세요 : 1 2 3 4 5

		최대값 : 5
		최소값 : 1
		총 합 : 15		


*/
//======================================================























/*
int main(void)
{
	int arr[5] = { 0, };
	printf("정수를 5개 입력하세요 : ");

	//-------------------------
	//	총합.
	int tot = 0;
	for (int cur = 0; cur < 5; ++cur)
	{
		scanf("%d", &arr[cur]);

		tot += arr[cur];
	}
	//-------------------------	
	int min = arr[0];		
	//	최소값.
	for (int cur = 1; cur < 5; ++cur)
	{
		if (min > arr[cur])
			min = arr[cur];
	}
	//-------------------------
	int max = arr[0];
	//	최대값.
	for (int cur = 1; cur < 5; ++cur)
	{
		if (max < arr[cur])
			max = arr[cur];
	}
	//-------------------------
	//	결과.
	printf("최대값 : %d\n", max);
	printf("최소값 : %d\n", min);
	printf("총합 : %d\n", tot);
	//-------------------------

	return 0;
}
//*/