//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//----------------
/*
	1.	����ü ��� ����.

		-	���� �����͸� �ϳ��� ����

			-	������ ǥ�� �� ������ ����
			
				�ո����� �ڵ� �ۼ� ����.
*/
//----------------
/*	��)
typedef struct
{
	char _name[20];			//	�л� �̸�.
	char _idx[20];			//	���� ��ȣ.
	char _schoolName[20];	//	�б� �̸�.char _major[20];		//	����.
	int _year;				//	�г�.

}SStudent;
//----------------
//		void ShowStudentInfo(SStudent *pStudent)	�л� ���� ���.
//		void EditStudentInfo(SStudent *pStudent)	�л� ���� ����.
//		void AddStudentInfo(SStudent *pStudent)		�л� ���� �߰�.

//		SStudent ����ü�� ���� ���� �ʾҴٸ�

//		void ShowStudentInfo(char *pName, char *pIdx, char *pScholName, char *pMajor, int year)
//		void EditStudentInfo(char *pName, char *pIdx, char *pScholName, char *pMajor, int year)
//		void AddStudentInfo(char *pName, char *pIdx, char *pScholName, char *pMajor, int year)
//	1)	�Ű������� ȣ���� ��������.
//	2)	�Ű����� ������ �ʿ��� ��� ������ ��������.

void ShowStudentInfo(SStudent *pStudent)
{
	printf("�л� �̸� : %s\n", pStudent->_name);
	printf("���� ��ȣ : %s\n", pStudent->_idx);
	printf("�б� �̸� : %s\n", pStudent->_schoolName);
	printf("���� : %s\n", pStudent->_major);
	printf("�г� : %d\n", pStudent->_year);
}
//----------------
int main()
{
	//	3)	����ü�� ������� �ʾҴٸ� �� �����͸��� �迭�� ��������.
	//		��)	char	_name[2][20];
	//			char	_idx[2][20];
	//			char	_schoolName[2][20];
	//			char	_major[2][20];
	//			int		_year[2][20];

	SStudent students[2];
	
	for (int cur = 0; cur < 2; ++cur)
	{
		printf("�л� �̸� : "); scanf("%s", students[cur]._name);
		printf("���� ��ȣ : "); scanf("%s", students[cur]._idx);
		printf("�б� �̸� : "); scanf("%s", students[cur]._schoolName);
		printf("���� : "); scanf("%s", students[cur]._major);
		printf("�г� : "); scanf("%d", &students[cur]._year);
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
	2.	��ø ����ü.

		-	����ü�� ��������� ����ü ����.

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
	//SCircle circle2 = { 2 };	//	�ʱ�ȭ �������� �Ϻθ���� 0���� �ʱ�ȭ.
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

		�»����ǥ[0,0], ���ϴ���ǥ [100.100]�� ���簢�� ������ �����ϴ�

		1)	����ü SRectangle�� �����϶�. �� ���� ����ü�� ����Ͽ� �����Ѵ�.

		typedef struct
		{
			int _xPos;
			int _yPos;

		}SPoint;

		2)	SRectangle�� �̿��Ͽ� ���簢���� ���̸� ����ϰ�

		3)	4���� ������ ������ ����ϴ� ���α׷��� �����.

*/
