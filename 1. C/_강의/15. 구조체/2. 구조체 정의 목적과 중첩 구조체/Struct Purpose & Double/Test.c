//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//----------------
/*
	1.	구조체 사용 목적.

		-	연관 데이터를 하나로 통합

			-	데이터 표현 및 관리가 용이
			
				합리적인 코드 작성 가능.
*/
//----------------
/*	예)
typedef struct
{
	char _name[20];			//	학생 이름.
	char _idx[20];			//	고유 번호.
	char _schoolName[20];	//	학교 이름.char _major[20];		//	전공.
	int _year;				//	학년.

}SStudent;
//----------------
//		void ShowStudentInfo(SStudent *pStudent)	학생 정보 출력.
//		void EditStudentInfo(SStudent *pStudent)	학생 정보 편집.
//		void AddStudentInfo(SStudent *pStudent)		학생 정보 추가.

//		SStudent 구조체를 정의 하지 않았다면

//		void ShowStudentInfo(char *pName, char *pIdx, char *pScholName, char *pMajor, int year)
//		void EditStudentInfo(char *pName, char *pIdx, char *pScholName, char *pMajor, int year)
//		void AddStudentInfo(char *pName, char *pIdx, char *pScholName, char *pMajor, int year)
//	1)	매개변수의 호출이 간편해짐.
//	2)	매개변수 수정이 필요한 경우 편집이 간단해짐.

void ShowStudentInfo(SStudent *pStudent)
{
	printf("학생 이름 : %s\n", pStudent->_name);
	printf("고유 번호 : %s\n", pStudent->_idx);
	printf("학교 이름 : %s\n", pStudent->_schoolName);
	printf("전공 : %s\n", pStudent->_major);
	printf("학년 : %d\n", pStudent->_year);
}
//----------------
int main()
{
	//	3)	구조체를 사용하지 않았다면 각 데이터마다 배열을 만들어야함.
	//		예)	char	_name[2][20];
	//			char	_idx[2][20];
	//			char	_schoolName[2][20];
	//			char	_major[2][20];
	//			int		_year[2][20];

	SStudent students[2];
	
	for (int cur = 0; cur < 2; ++cur)
	{
		printf("학생 이름 : "); scanf("%s", students[cur]._name);
		printf("고유 번호 : "); scanf("%s", students[cur]._idx);
		printf("학교 이름 : "); scanf("%s", students[cur]._schoolName);
		printf("전공 : "); scanf("%s", students[cur]._major);
		printf("학년 : "); scanf("%d", &students[cur]._year);
	}

	for (int cur = 0; cur < 2; ++cur)
		ShowStudentInfo(&students[cur]);

	return 0;
}
//*/
//----------------


//======================================================
//----------------
/*
	2.	중첩 구조체.

		-	구조체의 멤버변수로 구조체 가능.

*/
//----------------
/*
typedef struct
{
	int _xPos;
	int _yPos;
	
}SPoint;
//----------------
typedef struct
{
	SPoint _center;
	double _rad;

}SCircle;
//----------------
void ShowCircleInfo(SCircle *pCircle)
{
	printf("[%d, %d]\n", pCircle->_center._xPos, pCircle->_center._yPos);
	printf("rad : %f\n\n", pCircle->_rad);
}
//----------------
int main()
{
	SCircle circle1 = { {1,2}, 3.5 };
	SCircle circle2 = { 2,4, 3.9 };
	//SCircle circle2 = { 2 };	//	초기화 하지않은 일부멤버는 0으로 초기화.
	ShowCircleInfo(&circle1);
	ShowCircleInfo(&circle2);

	return 0;
}
//----------------
//*/
//----------------
//======================================================
/*
	Quiz)

		좌상단좌표[0,0], 우하단좌표 [100.100]인 직사각형 정보를 관리하는

		1)	구조체 SRectangle를 정의하라. 단 다음 구조체를 사용하여 정의한다.

		typedef struct
		{
			int _xPos;
			int _yPos;

		}SPoint;

		2)	SRectangle을 이용하여 직사각형의 넓이를 계산하고

		3)	4개의 꼭지점 정보를 출력하는 프로그램을 만든다.

*/
