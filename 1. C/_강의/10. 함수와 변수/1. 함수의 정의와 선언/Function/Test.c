//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	��ȯ���� �Ű������� ���� �Լ��� �з�
*/

/*
//-----------------------------
int Add(int num1, int num2)
{
	return num1 + num2;
}
//-----------------------------
void ShowAddResult(int num)
{
	printf("������� : %d\n", num);
}
//-----------------------------
int ReadNum()
{
	int num;
	scanf("%d", &num);
	return num;
}
//-----------------------------
void ShowInfo()
{
	printf("�� ���� ������ �Է��ϸ� ������� ���.\n");
}
//-----------------------------
int main(void)
{
	int result, num1, num2;

	ShowInfo();

	num1 = ReadNum();

	num2 = ReadNum();

	result = Add(num1, num2);

	ShowAddResult(result);

	return 0;
}
//-----------------------------
//*/
//======================================================
/*	quiz 1)
	
	3���� ������ �Է¹޾� ���� ���� ��(1)�� ���� ū ��(2)�� ��ȯ�ϴ� �Լ��� ������.


	int GetMinimum( int a, int b, int c )
	int GetMaximum( int a, int b, int c )
	
*/





/*
//---------------------
int GetMinimum(int a, int b, int c)
{
	if (a < b)
	{
		if (a < c)
			return a;
	}
	else if (b < c)
		return b;
	else 
		return c;
}
//---------------------
int GetMaximum(int a, int b, int c)
{
	if (a > b)
	{
		if (a > c)
			return a;
	}
	else if (b > c)
		return b;
	else
		return c;
}
//---------------------
int main(void)
{
	printf("3���� ���ڸ� �Է��ϼ��� \n");

	int a, b, c;

	scanf("%d %d %d", &a, &b, &c);

	int min, max;

	min = GetMinimum(a, b, c);
	max = GetMaximum(a, b, c);

	printf("���� ���� �� : %d\n", min);
	printf("���� ū �� : %d\n", max);

	return 0;
}
//---------------------
//*/

//======================================================
/*
2.	return�� �ΰ��� �뵵.

		-	���� ��ȯ.
	
		-	�Լ��� ����.
	
			-	��ȯ���� void�� �Լ������� return ���� ���� ����.

			��)
					void NoReturnFunction( int num )
					{
						......

						if( num < 0 )
							return;

						......
						
					}

*/

/*
void TestFunc()
{
	int a;
	scanf("%d", &a);

	if (a < 10)
		return;

	printf("����\n");
}

int main()
{
	TestFunc();

	return 0;
}

//*/
//======================================================









//======================================================
/*
3.	�Լ��� ���ǿ� ����

	-	�Լ��� ���ǰ� �Լ��� ȣ�⹮���� ���� �����ϴ� ���
		
		�����Ϸ��� �̹� �������� ���� �ش� �Լ��� �����Ѵ�.

	-	������ ȣ�⹮�� ���� �����ϴ� ��� �����Ϸ��� ���� ���� ���Ѵ�.

		->	��, �Լ��� ȣ��Ǳ� ���� �̸� ���ǵǾ�� �Ѵ�.

	-	�����Ϸ����� �ش� �Լ��� ���� ��򰡿��� �����Ѵٰ� �̸� �˷������μ� ������ �����Ѵ�.

		->	�Լ��� �����̶�� �Ѵ�.


4.	�Լ� ���� ���

		-	��ȯ��	�̸�( �Ű����� );
		

			��)	int TestFunc( int a );
				�Ǵ�
				int TestFunc( int );
*/	

/*
void TestFunc();

int main()
{
	TestFunc();	//	������ �Ǿ� ���� �ʴٸ� �����Ϸ��� ���� Ÿ���� int�� �����Ѵ�.

	return 0;
}


void TestFunc()
{
	int a;
	scanf("%d", &a);

	if (a < 10)
		return;

	printf("����\n");
}
//*/
//======================================================





//======================================================
/*
5.	�پ��� ������ �Լ� ���� �ϱ�.

	1)	�ϳ��� �Լ����� �� �̻��� return ���� �����ϴ� ���.

	2)	�Լ��� ���ϰ����� ����.

	3)	�Լ� ������ �ٸ� �Լ� ���.
*/


/*
//	1)	�ϳ��� �Լ����� �� �̻��� return ���� �����ϴ� ���.
//	int Compare(int num1, int num2);	
//	-	�Լ��� ������ �Ǿ� ���� �ʴٸ� �����Ϸ��� ���� Ÿ���� int�� �����Ѵ�.
int main()
{
	int n1, n2;
	printf("�ΰ��� ���ڸ� �Է��ϼ��� : ");
	scanf("%d %d", &n1, &n2);

	printf("�ΰ��� ���� �� ���� ū ���� %d �Դϴ�. \n", Compare(n1, n2));

	return 0;
}

int Compare(int num1, int num2)
{
	if (num1 > num2)
		return num1;
	else
		return num2;
}
//*/



/*
//	2)	�Լ��� ���ϰ����� ����.
//	3)	�Լ� ������ �ٸ� �Լ� ���.
//------------------------------
int GetAbs(int num);
int CompareAbs(int num1, int num2);
//------------------------------
int main()
{
	int num1, num2;
	printf("�ΰ��� ���� �Է� : ");
	scanf("%d %d", &num1, &num2);

	printf("%d�� %d�� ���밪�� ū �� : %d\n", num1, num2, CompareAbs(num1, num2));

	return 0;
}
//------------------------------
int GetAbs(int num)
{
	if (num < 0)
		return num * (-1);
	else
		return num;
}
//------------------------------
int CompareAbs(int num1, int num2)
{
	if (GetAbs(num1) > GetAbs(num2))
		return num1;
	else
		return num2;
}
//*/
//======================================================


/*	quiz 2)

���� �µ��� �Է��ϸ� ȭ�� �µ��� ��ȯ�ϴ� �Լ��� 
ȭ�� �µ��� ��ȯ�ϸ� ���� �µ��� ��ȯ�ϴ� �Լ��� ����� Ȯ���غ���.

����(Celsius) = (F - 32) / 1.8
ȭ��(Fahrenheit) = (1.8 x C) + 32

��)
	�����µ��� �Է��ϼ��� : 
	ȭ����  �Դϴ�.

	ȭ���µ��� �Է��ϼ���
	������  �Դϴ�.

*/
//======================================================

/*
float GetCels(float Fah)	{ return (Fah - 32) / 1.8f; }
float GetFahr(float Cels)	{ return (1.8f * Cels) + 32; }

int main()
{
	float Cel, Fah;
	printf("�����µ��� �Է��ϼ��� : ");
	scanf("%f", &Cel);
	Fah = GetFahr(Cel);
	printf("ȭ���� %f �Դϴ�.\n",Fah);


	printf("ȭ���µ��� �Է��ϼ��� : ");
	scanf("%f", &Fah);
	Cel = GetCels(Fah);
	printf("������ %f �Դϴ�.\n", Cel);


	return 0;
}
//*/