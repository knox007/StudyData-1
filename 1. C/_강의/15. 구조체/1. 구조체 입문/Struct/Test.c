//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	����ü ����� ����

		-	����

			-	struct	����üŸ��  ��ü�̸�;

		-	������� ���� ���.

			-	����ü_����_�̸�.�������
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

	printf("ù��° ��ġ ������ �Է��ϼ��� : ");
	scanf("%d %d", &pos1._xPos, &pos1._yPos);

	printf("�ι�° ��ġ ������ �Է��ϼ��� : ");
	scanf("%d %d", &pos2._xPos, &pos2._yPos);

	distance = sqrt( (double)
		((pos1._xPos - pos2._xPos)*(pos1._xPos - pos2._xPos) +
		(pos1._yPos - pos2._yPos)*(pos1._yPos - pos2._yPos)));
	

	printf("�� �� ���� �Ÿ� : %g\n", distance);

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

	strcpy(tmpPerson1._name, "ȫ�浿");
	strcpy(tmpPerson1._phoneNumber, "010-1234-5678");
	tmpPerson1._age = 20;
	printf("%s���� ���̴� %d�� �̸� ��ȭ��ȣ�� %s �Դϴ�.\n", tmpPerson1._name, tmpPerson1._age, tmpPerson1._phoneNumber);
	
	printf("�̸� : ");
	scanf("%s", tmpPerson2._name);

	printf("��ȭ��ȣ : ");
	scanf("%s", tmpPerson2._phoneNumber);

	printf("���� : ");
	scanf("%d", &tmpPerson2._age);

	printf("%s���� ���̴� %d�� �̸� ��ȭ��ȣ�� %s �Դϴ�.\n", tmpPerson2._name, tmpPerson2._age, tmpPerson2._phoneNumber);


	return 0;
}
//*/
//======================================================
/*
2.	����ü �ʱ�ȭ

	-	�迭�� �ʱ�ȭ�� ����.

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

	struct SPerson man = { "ȫ�浿", "010-1234-5678", 20 };

	printf("%d, %d\n\n", pos._xPos, pos._yPos);

	printf("%s, %s, %d\n\n", man._name, man._phoneNumber, man._age);

	return 0;
}
//*/
//======================================================
/*
	4-1.	����ü�� typedef ����

		-	�Ϲ����� ���.
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
	4-2.	����ü�� typedef ����

		-	����ü�� ����.
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
	SPerson man = { "ȫ�浿", "010-1234-5678", 20 };

	printf("[%d, %d]\n", pos._xPos, pos._yPos);
	printf("%s %s %d\n", man._szName, man._szPhoneNum, man._nAge);

	return 0;
}

//*/
//======================================================
/*
	Quiz)
		
		������ �̸�, �ֹ� ��ȣ, �޿� ������ ������ �� �ִ� ����ü�� �����

		������ ����� �غ���.

		��)

			�̸� : ȫ�浿

			�ֹι�ȣ(-�� �Է����� ����) : xxxxxxxxxxxxx

			�޿� ����(���� : ����) : 100

			->	�̸�	 : ȫ�浿
				�ֹι�ȣ : xxxxxx-xxxxxxx
				����	 : 100����
*/
//======================================================