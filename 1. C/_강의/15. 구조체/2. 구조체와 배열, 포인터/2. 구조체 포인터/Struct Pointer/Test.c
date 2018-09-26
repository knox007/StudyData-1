//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	구조체 변수와 포인터

	-	선언 및 초기화.
	
	-	접근.
*/

/*

typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;

int main()
{
	SPoint pos1 = { 1,2 };
	SPoint pos2 = { 100, 200 };
	
	SPoint *pPos3 = &pos1;
	(*pPos3)._xPos += 4;
	(*pPos3)._yPos += 5;
	printf("[%d, %d]\n", pPos3->_xPos, pPos3->_yPos);

	pPos3 = &pos2;
	pPos3->_xPos += 1;
	pPos3->_yPos += 2;
	printf("[%d, %d]\n", (*pPos3)._xPos, (*pPos3)._yPos);

	return 0;
}

//*/
//======================================================
/*
	-	멤버변수로 포인터 사용하기.
*/
//======================================================
/*
//	1)	자신과 다른 타입의 포인터 변수.

typedef struct 
{
	int _xPos;
	int _yPos;

}SPoint;

typedef struct 
{
	double _rad;
	SPoint * _pCenter;

}SCircle;

int main()
{
	SPoint center = { 1,1 };
	double rad = 5;

	SCircle circle = { rad, &center };

	printf("원의 반지름 : %f\n", circle._rad);
	printf("원의 중심 : [%d, %d]\n", circle._pCenter->_xPos, circle._pCenter->_yPos);

	

	return 0;
}
//*/


//*
//	2)	자신과 같은 타입의 포인터 변수.
typedef struct
{
	int _xPos;
	int _yPos;
	SPoint *pPoint;

}SPoint;

int main()
{


	return 0;
}

//*/
