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

struct SPoint
{
	int _xPos;
	int _yPos;
};

int main()
{
	struct SPoint pos1 = { 1,2 };
	struct SPoint pos2 = { 100, 200 };
	
	struct SPoint *pPos3 = &pos1;
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
//*
//	1)	�ٸ� Ÿ���� ������ ����.

struct SPoint
{
	int _xPos;
	int _yPos;
};

struct SCircle
{
	double _rad;
	struct SPoint * _pCenter;
};

int main()
{
	

	return 0;
}
//*/