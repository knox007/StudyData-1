//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	�Լ��� ����ü ���� ���� & ��ȯ

	-	�Ϲ� ������ ���������� �Լ��� ���ڷ� ���޵ǰų� ��ȯ�� ��
	
		���� ���簡 ����ȴ�.
*/
//----------------
/*
typedef struct
{
	char _name[20];
	char _phoneNumber[20];
	int _age;
}SPerson;
//----------------
SPerson GetPersonInfo()
{
	SPerson tmpPerson;

	printf("�̸� : "); scanf("%s", tmpPerson._name);
	printf("��ȭ��ȣ : "); scanf("%s", tmpPerson._phoneNumber);
	printf("���� : "); scanf("%d", &tmpPerson._age);

	return tmpPerson;
}
//----------------
void ShowPersonIfo(SPerson person)
{
	printf("---- show info ----\n");
	printf("�̸� : %s \n", person._name);
	printf("��ȭ��ȣ : %s \n", person._phoneNumber);
	printf("���� : %d \n", person._age);
		
}
//----------------
int main()
{
	SPerson person = GetPersonInfo();

	ShowPersonIfo(person);

	return 0;
}
//----------------
//*/
//======================================================
/*
	1-2.	�Լ��� ����ü ���� ����( call by reference ) & ��ȯ
*/
//======================================================
/*
//----------------
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;
//----------------
void OriginSymmetry(SPoint *pPtr)
{
	pPtr->_xPos *= -1;
	pPtr->_yPos *= -1;
}
//----------------
void ShowPoint(SPoint pt) {	printf("[%d, %d]\n", pt._xPos, pt._yPos); }
//----------------
int main()
{
	SPoint pos = { 1,-2 };

	ShowPoint(pos);
	OriginSymmetry(&pos);
	ShowPoint(pos);
	OriginSymmetry(&pos);
	ShowPoint(pos);

	return 0;
}
//----------------
//*/
//======================================================
/*
	2.	����ü ���� ������� ������ ����.

		-	�ſ� ���ѵ� ������ ���길 ���.

			-	����, �ּҰ� ��ȯ( & ), ����ü ������ ũ��( sizeof )
*/
//======================================================
/*
//----------------
//	���� ����, sizeof ����.
//----------------
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;

int main()
{
	SPoint pos1 = { 1, 2 };
	SPoint pos2 = pos1;	//	������� ����.

	printf("ũ�� : %d\n", sizeof(pos1));
	printf("[%d, %d]\n", pos1._xPos, pos1._yPos);

	printf("ũ�� : %d\n", sizeof(pos2));
	printf("[%d, %d]\n", pos2._xPos, pos2._yPos);
	
	return 0;
}
//*/


/*
	-	4Ģ ������ �� �ȵǳ�?

	SPoint pos3 = pos1 + pos2;
	printf("ũ�� : %d\n", sizeof(pos3));
	printf("[%d, %d]\n", pos3._xPos, pos3._yPos);

	-	4Ģ ������ ����ȭ�ϴµ� ������ ����.
	
		-	����ü�� ����� �迭�̳� ������ ����, �ٸ� ����ü ���� ������ �� �� �ִ�.
		
		-	�Լ��� �����Ͽ� ��� �� ��.

*/

/*
//----------------
//	�Լ� ����.
//----------------
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;
//----------------
SPoint AddPoint(SPoint pos1, SPoint pos2)
{
	SPoint tmpPos = { pos1._xPos + pos2._xPos, pos1._yPos + pos2._yPos };
	return tmpPos;
}
//----------------
SPoint MinusPoint(SPoint pos1, SPoint pos2)
{
	SPoint tmpPos = { pos1._xPos - pos2._xPos, pos1._yPos - pos2._yPos };
	return tmpPos;
}
//----------------
int main()
{
	SPoint pos1 = { 10, 20 };
	SPoint pos2 = { 5, 15 };
	SPoint tmpPos;

	tmpPos = AddPoint(pos1, pos2);
	printf("[%d, %d]\n", tmpPos._xPos, tmpPos._yPos);

	tmpPos = MinusPoint(pos1, pos2);
	printf("[%d, %d]\n", tmpPos._xPos, tmpPos._yPos);

	return 0;
}
//----------------
//*/
//======================================================
/*
	quiz)

		�ΰ��� ����ü 
		SPoint pos1 = {1,2}
		SPoint pos2 = {5,-1}

		�� ���� ���� �ٲٴ� Swap�Լ��� �����϶�.
*/