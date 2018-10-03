//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	1.	����ü( Union )

		-	����

			-	���� �ٸ� �ڷ����� ���� �����͵��� ������ ��� ��Ҹ� ���� �����ϸ� ���Ǵ� ����.

			-	������ union�� ����ϴ� ���� �����ϰ� ����ü�� ����.

			-	������� ���� ū ���������� ������.

				-	������ ������ �������� ���.
*/

//*
//---------------------------
typedef struct
{
	int _mem1;
	int _mem2;
	double _mem3;

}SStruct;
//---------------------------
typedef union
{
	int _mem1;
	int _mem2;
	double _mem3;

}UUnion;
//---------------------------
int main()
{
	SStruct sTest;
	UUnion uTest;

	printf("%p %p %p \n", &sTest._mem1, &sTest._mem2, &sTest._mem3);
	printf("size of SStruct = %d\n", sizeof(SStruct));
	printf("%p %p %p \n", &uTest._mem1, &uTest._mem2, &uTest._mem3);
	printf("size of UUnion = %d\n", sizeof(UUnion));

	return 0;
}
//---------------------------
/*
	
	SStruct =>	-----------------
				|	int	_mem1	|
				-----------------
				|	int	_mem2	|
				---------------------------------
				|	double _mem3				|
				---------------------------------


	UUnion	=>	---------------------------------
				|			 double				|
				---------------------------------
				|<-  _mem1  ->|
				|<-  _mem2  ->|
				|<-  _mem3					  ->|

//---------------------------
//*/
//======================================================
/*
	2.	������( Enum )

		-	����
		
			-	2�� �̻��� �������� ������ �����
		
				�ǹ��ִ� �̸��� �����Ͽ� ����ϴ� ��.

		-	Ư¡

			-	0 ���� ����.

			-	�̸��� ��� ���� ���Ƿ� ������ �� ����.

			-	���� �̸��� ���� �̸��� ����� 1�� ������ ��.

			-	������ �̸� ������ ������ ��ǥ�� ������ �ǹ� ����.

			-	�̸��� �ߺ��� ������� ����.

				



*/


/*
#include<stdlib.h>

typedef enum eLocation
{
	CITY,
	SCHOOL,
	HOSPITAL,
	//HOSPITAL=1,

	EXIT,

} eLOCATION;

int main()
{
	while (1)
	{
		printf("1. ����\t2. �б�\t3. ����\n");
		printf("�̵��� ���� �Է��ϼ��� (4 : ����)");
		int location;
		scanf("%d", &location);
		//	eLOCATION eLoc;
		//	scanf("%d", (int*)&eLoc);
		printf("\n");

		switch ( location - 1)
		//	switch (eLoc - 1)
		{
		case CITY:
			printf("���÷� �̵�\n");
			break;

		case SCHOOL:
			printf("�б��� �̵�\n");
			break;

		case HOSPITAL:
			printf("�������� �̵�\n");
			break;

		case EXIT:
			printf("�����մϴ�.\n");
			return 0;

		}

		system("pause");	//	�ڵ����Ḧ ��������, �Ǵ� Ư�� �κп��� �� ������� ���ϰ� �ϴ� ��.
		system("cls");		//	�ܼ�â ȭ�� ���� ����.


	}//	while (1)

	return 0;
}
//*/
//======================================================
