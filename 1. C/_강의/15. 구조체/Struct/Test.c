//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	구조체	
*/


/*
struct point
{
	int xPos;
	int yPos;
};

int main()
{
	struct point pos1, pos2;
	double distance;

	printf("첫번째 위치 정보를 입력하세요 : ");
	scanf("%d %d", &pos1.xPos, &pos1.yPos);

	printf("두번째 위치 정보를 입력하세요 : ");
	scanf("%d %d", &pos2.xPos, &pos2.yPos);

	distance = sqrt( (double)
		((pos1.xPos - pos2.xPos)*(pos1.xPos - pos2.xPos) +
		(pos1.yPos - pos2.yPos)*(pos1.yPos - pos2.yPos)));
	

	printf("두 점 사이 거리 : %g\n", distance);

	return 0;
}

//*/
//======================================================

/*
	quiz)
	이름과 전화번호, 나이를 관리하는 구조체를 만들고
	scanf로 정보를 입력받아 다음과 같이 출력하도록 만든다.

	이름		: 홍길동
	전화번호	: 010-xxxx-xxxxx
	나이		: 20

	홍길동씨의 나이는 20세이며 전화번호는 010-xxxx-xxxx 입니다.
*/

































/*
struct person
{
	char name[30];
	char phoneNumber[20];
	int age;
};


int main()
{
	struct person tmpPerson;
	
	printf("이름 : ");
	scanf("%s", tmpPerson.name);

	printf("전화번호 : ");
	scanf("%s", tmpPerson.phoneNumber);

	printf("나이 : ");
	scanf("%d", &tmpPerson.age);

	printf("%s씨의 나이는 %d세 이며 전화번호는 %s 입니다.\n", tmpPerson.name, tmpPerson.age, tmpPerson.phoneNumber);


	return 0;
}
//*/