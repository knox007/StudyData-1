//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
//======================================================
/*
	1 - 1.	malloc 의 반환형은 void*

		-	void형 포인터.

			-	형(Type)이 존재하지 않는 포인터.

			-	예)
					void * ptr;

			-	장점
			
				-	어떠한 변수의 주소값이든 담을수 있다.

					함수의 주소값도 담을수 있다.

			-	단점
			
				-	아무런 포인터 연산을 할수 없다.

				-	값의 변경이나 참조도 불가.
					
					-	가리키는 대상이 어떠한 타입의 변수인지에 대한 정보가 없다.

			-	주소값을 일단 저장한뒤 나중에 포인터 형을 결정할 경우 주로 사용됨.
*/

/*

void SimpleFunc() { printf("Simple Func!!\n"); }

int main()
{
	int num = 20;

	void* ptr;

	ptr = &num;
	printf("ptr = %p\n", ptr);

	//	*ptr = 30;
	//	++ptr;

	ptr = SimpleFunc;
	printf("ptr = %p\n", ptr);

	return 0;
}
//*/
//---------------------------
/*	1 - 2.	malloc 의 반환형은 void*

	-	void* 타입인 이유.

		-	원하는 만큼 메모리 공간을 할당하고 주소를 반환하면

			프로그래머가 직접 포인터형의 변환을 통해서 

			어떻게 사용할지 결정.
			
*/

/*
int main()
{
	int * ptr1 = (int*)malloc(sizeof(int));
	int * ptr2 = (int*)malloc(sizeof(int)*7);

	*ptr1 = 20;

	for (int i = 0; i < 7; ++i)
		ptr2[i] = i + 1;

	printf("*ptr1 = %d\n", *ptr1);

	printf("*ptr2 \n");
	for (int i = 0; i < 7; ++i)
		printf("%d ", ptr2[i]);
	printf("\n");

	free(ptr1);
	free(ptr2);

	return 0;
}
//*/
//---------------------------
/*
	2.	그 밖에...

		-	calloc

			-	원형

				void* calloc( size_t elementCount, size_t elementSize );

				-	elementCount	:	할당할 블록의 갯수

				-	elementSize		:	블록 하나당 바이트 크기.

			-	malloc( 40 ) == calloc( 10, 4 )

			-	malloc 와 차이점.

				-	메모리 공간의 모든 비트를 0으로 초기화.

					-	malloc의 경우 쓰레기값으로 채워짐.

		-	realloc

			-	원형

				void* realloc( void *ptr, size_t size );

				-	ptr		:	확장하고자 하는 힙 메모리의 주소.

				-	size	:	확장하고자 하는 메모리의 전체 크기.

			-	예)

				int *pArr = (int*)malloc(sizeof( int ) * 3 );

				.......

				pArr = (int * )realloc(pArr, sizeof( int ) * 5 );

			-	malloc 와 realloc의 반환값.

				-	같은 경우.

					-	malloc로 할당한 메모리 공간뒤 확장할 영역이 넉넉한 경우.

				-	다른 경우.

					-	넉넉하지 않은 경우, 새로 요구하는 크기의 메모리 공간을 별도 할당한뒤

						이전 데이터의 값을 복사.

*/
//---------------------------
/*
	Quiz)
		
		문제 1),2)의 상황을 malloc와 free를 이용해서 해결하자.
*/
//---------------------------