//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	����ü ������ ������

	-	���� �� �ʱ�ȭ.
	
	-	����.
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
	-	��������� ������ ����ϱ�.
*/
//======================================================
/*
//	1)	�ڽŰ� �ٸ� Ÿ���� ������ ����.

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

	printf("���� ������ : %f\n", circle._rad);
	printf("���� �߽� : [%d, %d]\n", circle._pCenter->_xPos, circle._pCenter->_yPos);

	

	return 0;
}
//*/


//*
//	2)	�ڽŰ� ���� Ÿ���� ������ ����.
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
