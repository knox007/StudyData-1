//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	1 - 1.	전역변수와 지역변수로 해결이 되지 않는 상황.

		-	지역변수, 전역변수의 특성

			-	10. 함수와 변수 -> 2. 변수의 생명과 접근범위 참고.
*/

//*
//---------------------------
//	문제 1)
/*
char * ReadUserName()
{
	char name[30];
	printf("이름 ? ");
	scanf("%s", name);

	return name;
}
int main()
{
	char *pszName1;
	char *pszName2;

	pszName1 = ReadUserName();
	printf("이름 : %s\n", pszName1);

	pszName2 = ReadUserName();
	printf("이름 : %s\n", pszName2);
	
	return 0;
}
//*/
//---------------------------
//	문제 2)
/*
char g_szName[30];

char * ReadUserName()
{
	printf("이름 ? ");
	scanf("%s", g_szName);

	return g_szName;
}

int main()
{
	char *pszName1;
	char *pszName2;

	pszName1 = ReadUserName();
	printf("이름 : %s\n", pszName1);

	pszName2 = ReadUserName();
	printf("이름 : %s\n", pszName2);

	
	printf("pszName1 : %s\n", pszName1);
	printf("pszName2 : %s\n", pszName2);
	

	return 0;
}

//*/
//---------------------------
/*
	1 - 2.	해결책

	-	생성과 소멸의 시기가 지역변수나 전역변수와 다른 유형의 변수

		-	함수 호출시 매번 할당( 지역변수 )

			할당 후 함수( 코드블록 )을 빠져나가도 메모리가 유지되는 변수( 전역변수 )

			-	C언어에서는 이를 위해 malloc 와 free 를 제공.
*/
//---------------------------
/*
	2.	malloc & free

		-	원형

			-	#include <stdlib.h>

				void * malloc( size_t size );

					-	힙 영역에 메모리 공간 할당.

					-	성공시 할당된 메모리 공간의 주소값 반환.

						실패시 NULL 반환.

				void free( void * ptr );

					-	힙 영역에 할당된 메모리 공간 해제.

		-	힙 영역

			-	malloc 함수로 할당된 메모리 공간은 프로그래머가 free로 직접 해제하지 않으면 
			
				할당된 상태로 계속 남아있게 된다.

				-	프로그래머가 관리하는 메모리 공간.

		-	예)

				int main()
				{
					void *ptr1 = malloc(4);		//	힙영역에 4바이트의 메모리 공간을 할당한 후 첫번째 바이트의 주소를 반환.
					void *ptr2 = malloc(10);

					.............

					free(ptr1);					//	ptr1이 가리키는 메모리 공간이 소멸.
					free(ptr2);

					.............
				}

*/
//---------------------------

