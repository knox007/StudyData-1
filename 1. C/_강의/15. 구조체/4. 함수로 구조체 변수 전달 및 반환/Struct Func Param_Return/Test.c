//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	함수로 구조체 변수 전달 & 반환

	-	일반 변수와 마찬가지로 함수의 인자로 전달되거나 반환될 때
	
		값의 복사가 진행된다.
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

	printf("이름 : "); scanf("%s", tmpPerson._name);
	printf("전화번호 : "); scanf("%s", tmpPerson._phoneNumber);
	printf("나이 : "); scanf("%d", &tmpPerson._age);

	return tmpPerson;
}
//----------------
void ShowPersonIfo(SPerson person)
{
	printf("---- show info ----\n");
	printf("이름 : %s \n", person._name);
	printf("전화번호 : %s \n", person._phoneNumber);
	printf("나이 : %d \n", person._age);
		
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
	1-2.	함수로 구조체 변수 전달( call by reference ) & 반환
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
	2.	구조체 변수 대상으로 가능한 연산.

		-	매우 제한된 형태의 연산만 허용.

			-	대입, 주소값 반환( & ), 구조체 변수의 크기( sizeof )
*/
//======================================================
/*
//----------------
//	대입 연산, sizeof 연산.
//----------------
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;

int main()
{
	SPoint pos1 = { 1, 2 };
	SPoint pos2 = pos1;	//	멤버간의 복사.

	printf("크기 : %d\n", sizeof(pos1));
	printf("[%d, %d]\n", pos1._xPos, pos1._yPos);

	printf("크기 : %d\n", sizeof(pos2));
	printf("[%d, %d]\n", pos2._xPos, pos2._yPos);
	
	return 0;
}
//*/


/*
	-	4칙 연산은 왜 안되나?

	SPoint pos3 = pos1 + pos2;
	printf("크기 : %d\n", sizeof(pos3));
	printf("[%d, %d]\n", pos3._xPos, pos3._yPos);

	-	4칙 연산을 정형화하는데 무리가 있음.
	
		-	구조체의 멤버로 배열이나 포인터 변수, 다른 구조체 등의 변수가 올 수 있다.
		
		-	함수를 정의하여 사용 할 것.

*/

/*
//----------------
//	함수 적용.
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

		두개의 구조체 
		SPoint pos1 = {1,2}
		SPoint pos2 = {5,-1}

		의 값을 서로 바꾸는 Swap함수를 구현하라.
*/