//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
1.	����ü	
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

	printf("ù��° ��ġ ������ �Է��ϼ��� : ");
	scanf("%d %d", &pos1.xPos, &pos1.yPos);

	printf("�ι�° ��ġ ������ �Է��ϼ��� : ");
	scanf("%d %d", &pos2.xPos, &pos2.yPos);

	distance = sqrt( (double)
		((pos1.xPos - pos2.xPos)*(pos1.xPos - pos2.xPos) +
		(pos1.yPos - pos2.yPos)*(pos1.yPos - pos2.yPos)));
	

	printf("�� �� ���� �Ÿ� : %g\n", distance);

	return 0;
}

//*/
//======================================================

/*
	quiz)
	�̸��� ��ȭ��ȣ, ���̸� �����ϴ� ����ü�� �����
	scanf�� ������ �Է¹޾� ������ ���� ����ϵ��� �����.

	�̸�		: ȫ�浿
	��ȭ��ȣ	: 010-xxxx-xxxxx
	����		: 20

	ȫ�浿���� ���̴� 20���̸� ��ȭ��ȣ�� 010-xxxx-xxxx �Դϴ�.
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
	
	printf("�̸� : ");
	scanf("%s", tmpPerson.name);

	printf("��ȭ��ȣ : ");
	scanf("%s", tmpPerson.phoneNumber);

	printf("���� : ");
	scanf("%d", &tmpPerson.age);

	printf("%s���� ���̴� %d�� �̸� ��ȭ��ȣ�� %s �Դϴ�.\n", tmpPerson.name, tmpPerson.age, tmpPerson.phoneNumber);


	return 0;
}
//*/