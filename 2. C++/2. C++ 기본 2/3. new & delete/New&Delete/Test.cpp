//=================================================
/*
	1.	new & delete

		-	메모리의 동적 할당과 해제.

			-	C 언어의 malloc / free와 유사.

				-	차이점

					-	malloc	-	void형 포인터 반환.

									추후 개발자가 상황에 맞게 형변환해서 사용.

						new		-	용도에 맞게 포인터를 반환.

									따로 형변환할 필요 없음.

		-	사용

			-	예)
					int 형 데이터 1개의 메모리 공간 할당 및 해제.

						-	int *pVal = new int;

							delete pVal;

					길이가 size 인 int 형 배열을 위한 메모리 공간 할당 및 해제.
						
						-	int *pArr = new int[ size ];

							delete [] pArr;



		-	malloc / free	vs	new / delete

					|		malloc / free		|				new / delete		|
	---------------------------------------------------------------------------------
	속성			|			함수			|				연산자				|
	---------------------------------------------------------------------------------
	초기화			|			X				|		할당과 동시에 초기화 가능	|
					|							|		예)	int *pA = new int(3);	|
	---------------------------------------------------------------------------------
	필요한			|		바이트 단위로		|			컴파일러에 의해			|
	크기설정		|			설정			|				계산됨				|
	---------------------------------------------------------------------------------
	크기 변경		|		realloc을 통해		|			재할당 불가.			|
	가능여부		|			가능			|			STL이 대체 가능.		|
	---------------------------------------------------------------------------------
	할당 실패시		|		NULL 반환			|			NULL 반환.				|
	---------------------------------------------------------------------------------
	생성자,소멸자	|		호출 안함			|			호출					|
	호출여부		|							|									|
	---------------------------------------------------------------------------------

*/
//=================================================
#include<iostream>

using namespace std;

int main()
{
	int size;

	cout << "할당하려는 배열의 크기 : ";
	cin >> size;


	int *pArr = (int*)malloc(sizeof(int)*size);
	//int *pArr = new int [size];

	
	for (int i = 0; i < size; ++i)
		pArr[i] = i + 10;

	for (int i = 0; i < size; ++i)
		cout << "pArr[ " << i << " ] = " << pArr[i] << endl;

	free(pArr);
	//delete[]pArr;

	return 0;
}


//=================================================
//	참고

/*
//	https://egohim.blog.me/70074738205
//	메모리 누수 확인.	-	1.	선언.
#define CRTDBG_MAP_ALLOC 

#include <stdlib.h>
#include <crtdbg.h>


//	#include <new.h>등으로 operator new나 malloc을 
//	Derived해서 정의 한 경우, 사용 할 수 없다.

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

#include<iostream>

using namespace std;

int main()
{
	//	메모리 누수 확인.	-	3.	출력.( 전체 영역 )
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	메모리 누수 확인.	-	4.	메모리 릭 지점 찾기
	//	_CrtSetBreakAlloc(188);

	int size;

	cout << "할당하려는 배열의 크기 : ";
	cin >> size;


	int *pArr = (int*)malloc(sizeof(int)*size);
	//int *pArr = new int [size];


	for (int i = 0; i < size; ++i)
		pArr[i] = i + 10;

	for (int i = 0; i < size; ++i)
		cout << "pArr[ " << i << " ] = " << pArr[i] << endl;

	free(pArr);
	//delete[]pArr;


	//	메모리 누수 확인.	-	2.	출력.( 스코프 영역만 )
	//_CrtDumpMemoryLeaks();

	return 0;
}
//*/
//=================================================
/*
	Quiz)	학생수를 입력받고 그 수만큼 점수를 입력하여 총점과 평균을 계산한다.
	
			예)	학생수 입력 : 5

				1번 학생 : 30
				2번 학생 : 50
				3번 학생 : 60
				4번 학생 : 100
				5번 학생 : 70

				총점 : 310
				평균 : 62
	
*/
//=================================================