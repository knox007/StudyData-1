//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	구조체 선언과 접근

		-	선언

			-	struct	구조체타입  객체이름;

		-	멤버변수 접근 방법.

			-	구조체_변수_이름.멤버변수
*/


/*

struct SPoint
{
	int _xPos;
	int _yPos;
};

struct SPerson
{
	char _name[30];
	char _phoneNumber[20];
	int _age;
};

int main()
{
	struct SPoint pos1, pos2;
	double distance;

	printf("첫번째 위치 정보를 입력하세요 : ");
	scanf("%d %d", &pos1._xPos, &pos1._yPos);

	printf("두번째 위치 정보를 입력하세요 : ");
	scanf("%d %d", &pos2._xPos, &pos2._yPos);

	distance = sqrt( (double)
		((pos1._xPos - pos2._xPos)*(pos1._xPos - pos2._xPos) +
		(pos1._yPos - pos2._yPos)*(pos1._yPos - pos2._yPos)));
	

	printf("두 점 사이 거리 : %g\n", distance);

	return 0;
}

//*/
//======================================================
/*

struct SPoint
{
	int _xPos;
	int _yPos;
};

struct SPerson
{
	char _name[30];
	char _phoneNumber[20];
	int _age;
};

int main()
{
	struct SPerson tmpPerson1,tmpPerson2;

	strcpy(tmpPerson1._name, "홍길동");
	strcpy(tmpPerson1._phoneNumber, "010-1234-5678");
	tmpPerson1._age = 20;
	printf("%s씨의 나이는 %d세 이며 전화번호는 %s 입니다.\n", tmpPerson1._name, tmpPerson1._age, tmpPerson1._phoneNumber);
	
	printf("이름 : ");
	scanf("%s", tmpPerson2._name);

	printf("전화번호 : ");
	scanf("%s", tmpPerson2._phoneNumber);

	printf("나이 : ");
	scanf("%d", &tmpPerson2._age);

	printf("%s씨의 나이는 %d세 이며 전화번호는 %s 입니다.\n", tmpPerson2._name, tmpPerson2._age, tmpPerson2._phoneNumber);


	return 0;
}
//*/
//======================================================
/*
2.	구조체 초기화

	-	배열의 초기화와 유사.

*/

/*
struct SPoint
{
	int _xPos;
	int _yPos;
};

struct SPerson
{
	char _name[30];
	char _phoneNumber[20];
	int _age;
};
int main()
{
	struct SPoint pos = { 10, 20 };

	struct SPerson man = { "홍길동", "010-1234-5678", 20 };

	printf("%d, %d\n\n", pos._xPos, pos._yPos);

	printf("%s, %s, %d\n\n", man._name, man._phoneNumber, man._age);

	return 0;
}
//*/
//======================================================
/*
	4-1.	구조체와 typedef 선언

		-	일반적인 방법.
*/


/*
typedef int INT;
typedef int * PTR_INT;

typedef unsigned int UINT;
typedef unsigned int * PTR_UINT;

typedef unsigned char UCHAR;
typedef unsigned char * PTR_UCHAR;

int main()
{
	INT num1 = 120;
	PTR_INT pNum1 = &num1;

	UINT num2 = 190;
	PTR_UINT pNum2 = &num2;

	UCHAR num3 = 'Z';
	PTR_UCHAR pNum3 = &num3;

	printf("%d %u %c\n", *pNum1, *pNum2, *pNum3);

	return 0;
}

//*/
//======================================================
/*
	4-2.	구조체와 typedef 선언

		-	구조체에 적용.
*/

/*
//	1)
struct SPoint
{
	int _xPos;
	int _yPos;
};

typedef struct SPoint SPos;

//	2)
//typedef struct SPoint
//{
//	int _xPos;
//	int _yPos;
//
//}SPos;

//	3)
typedef struct 
{
	char _szName[20];
	char _szPhoneNum[20];
	int _nAge;

}SPerson;

int main()
{
	SPos pos = { 10,20 };
	SPerson man = { "홍길동", "010-1234-5678", 20 };

	printf("[%d, %d]\n", pos._xPos, pos._yPos);
	printf("%s %s %d\n", man._szName, man._szPhoneNum, man._nAge);

	return 0;
}

//*/
//======================================================
/*
	Quiz)
		
		종업원 이름, 주민 번호, 급여 정보를 관리할 수 있는 구조체를 만들고

		정보를 입출력 해보자.

		예)

			이름 : 홍길동

			주민번호(-는 입력하지 말것) : xxxxxxxxxxxxx

			급여 정보(단위 : 만원) : 100

			->	이름	 : 홍길동
				주민번호 : xxxxxx-xxxxxxx
				월급	 : 100만원
*/
//======================================================