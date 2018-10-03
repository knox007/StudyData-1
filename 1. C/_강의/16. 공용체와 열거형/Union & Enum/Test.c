//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	1.	공용체( Union )

		-	정의

			-	서로 다른 자료형을 가진 데이터들이 동일한 기억 장소를 서로 공유하며 기억되는 형태.

			-	예약어로 union을 사용하는 점을 제외하고 구조체와 유사.

			-	멤버변수 가장 큰 데이터형을 공유함.

				-	데이터 절감을 목적으로 사용.
*/

//*
//---------------------------
typedef struct
{
	int _mem1;
	int _mem2;
	double _mem3;

}SStruct;
//---------------------------
typedef union
{
	int _mem1;
	int _mem2;
	double _mem3;

}UUnion;
//---------------------------
int main()
{
	SStruct sTest;
	UUnion uTest;

	printf("%p %p %p \n", &sTest._mem1, &sTest._mem2, &sTest._mem3);
	printf("size of SStruct = %d\n", sizeof(SStruct));
	printf("%p %p %p \n", &uTest._mem1, &uTest._mem2, &uTest._mem3);
	printf("size of UUnion = %d\n", sizeof(UUnion));

	return 0;
}
//---------------------------
/*
	
	SStruct =>	-----------------
				|	int	_mem1	|
				-----------------
				|	int	_mem2	|
				---------------------------------
				|	double _mem3				|
				---------------------------------


	UUnion	=>	---------------------------------
				|			 double				|
				---------------------------------
				|<-  _mem1  ->|
				|<-  _mem2  ->|
				|<-  _mem3					  ->|

//---------------------------
//*/
//======================================================
/*
	2.	열거형( Enum )

		-	정의
		
			-	2개 이상의 연속적인 정수형 상수를
		
				의미있는 이름을 적용하여 사용하는 것.

		-	특징

			-	0 부터 시작.

			-	이름의 상수 값을 임의로 정의할 수 있음.

			-	다음 이름은 이전 이름의 상수에 1이 증가한 값.

			-	마지막 이름 다음에 나오는 쉼표의 유무는 의미 없음.

			-	이름의 중복을 허용하지 않음.

				



*/


/*
#include<stdlib.h>

typedef enum eLocation
{
	CITY,
	SCHOOL,
	HOSPITAL,
	//HOSPITAL=1,

	EXIT,

} eLOCATION;

int main()
{
	while (1)
	{
		printf("1. 도시\t2. 학교\t3. 병원\n");
		printf("이동할 곳을 입력하세요 (4 : 종료)");
		int location;
		scanf("%d", &location);
		//	eLOCATION eLoc;
		//	scanf("%d", (int*)&eLoc);
		printf("\n");

		switch ( location - 1)
		//	switch (eLoc - 1)
		{
		case CITY:
			printf("도시로 이동\n");
			break;

		case SCHOOL:
			printf("학교로 이동\n");
			break;

		case HOSPITAL:
			printf("병원으로 이동\n");
			break;

		case EXIT:
			printf("종료합니다.\n");
			return 0;

		}

		system("pause");	//	자동종료를 막기위해, 또는 특정 부분에서 더 진행되지 못하게 하는 함.
		system("cls");		//	콘솔창 화면 버퍼 지움.


	}//	while (1)

	return 0;
}
//*/
//======================================================
