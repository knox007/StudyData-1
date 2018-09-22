//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	구조체 배열의 선언

	-	일반적인 배열의 선언방식과 동일.

*/

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

/*
int main()
{
	struct SPoint arrPos[3];

	int idx;

	for (idx = 0; idx < 3; ++idx)
	{
		printf("점의 좌표 입력 : ");
		scanf("%d %d", &arrPos[idx]._xPos, &arrPos[idx]._yPos);
	}
	
	for (idx = 0; idx < 3; ++idx)
		printf("[%d, %d] ", arrPos[idx]._xPos, arrPos[idx]._yPos);

	printf("\n");

	return 0;
}

//*/
//======================================================
/*

2.	구조체 배열 초기화

*/

//*
int main()
{
	struct SPerson avengers[3] = 
	{
		{"IronMan", "010-1234-5678", 50},
		{ "Hulk", "010-1234-5678", 40 },
		{ "SpiderMan", "010-1234-5678", 30 }
	};

	int idx = 0;
	for (idx = 0; idx < 3; ++idx)
		printf("%s %s %d\n", avengers[idx]._name, avengers[idx]._phoneNumber, avengers[idx]._age);

	return 0;
}
//*/
//======================================================