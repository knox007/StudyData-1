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


/*
//	2)	�ڽŰ� ���� Ÿ���� ������ ����.
typedef struct SPoint
{
	int _xPos;
	int _yPos;

	struct SPoint *_pPoint;

} SPoint;

int main()
{
	SPoint pos1 = { 1,1 };
	SPoint pos2 = { 2,2 };
	SPoint pos3 = { 3,3 };

	pos1._pPoint = &pos2;
	pos2._pPoint = &pos3;
	pos3._pPoint = &pos1;

	printf("���� ���� ����\n");
	printf("[%d, %d]��(��) [%d, %d]�� ����\n",
		pos1._xPos, pos1._yPos, pos1._pPoint->_xPos,pos1._pPoint->_yPos);

	printf("[%d, %d]��(��) [%d, %d]�� ����\n",
		pos2._xPos, pos2._yPos, pos2._pPoint->_xPos, pos2._pPoint->_yPos);

	printf("[%d, %d]��(��) [%d, %d]�� ����\n",
		pos3._xPos, pos3._yPos, pos3._pPoint->_xPos, pos3._pPoint->_yPos);

	return 0;
}

//*/
//======================================================
/*
	-	����ü������ �ּҿ� ù��° ����� �ּ�.

		-	����ü ������ �ּ� �� == ù��° ����� �ּ� ��.
*/

/*
typedef struct
{
	int _xPos;
	int _yPos;

}SPos;

typedef struct
{
	char _name[20];
	char _phoneNum[20];
	int _age;

}SPerson;

int main()
{
	SPos pos = { 10, 10 };
	SPerson person = { "ȫ�浿","010-1234-5678", 20 };

	printf("%p %p\n", &pos, &pos._xPos);
	printf("%p %p\n", &person, person._name);

	return 0;
}

//*/
//======================================================