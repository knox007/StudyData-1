//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	�Լ��� ���ڷ� �迭 ����

	-	�迭 ��ü�� ������ �� ����.
	
		-	�����͸� �̿��Ͽ� �迭�� �ּҸ� �����Ѵ�.

*/

//*
void ShowArray(int *pArray, int len)
//	void ShowArray(int pArray[], int len)	//	�̷��� �����ϴ� �͵� ����.
											//	��, �Ű������� �����ϴ� ��츸 ����.
{	
	//	�Ű����� pArray�� ������ ����
	//	-	sizeof������ �� ��� �迭�� ũ�Ⱑ �ƴ� ������ ������ ũ�Ⱑ ��ȯ��.
	//	-	�Լ� ���ο����� ���ڷ� ���޵� �迭�� ���̸� ����� �� ����.
	//		-	�迭�� ũ�⳪ ���̵� �Բ� ����.

	//	int size = sizeof(pArray);
	//	printf("%d\n", size);
	

	int i;
	for (i = 0; i < len; ++i)
		printf("%d ", pArray[i]);

	printf("\n");
}

int main(void)
{
	int arr1[] = { 1,2,3 };
	//int *pArr = arr1;
	//int pArr[] = arr1;	-	( X )
	int arr2[] = { 4,5,6,7,8 };
	int len1 = sizeof(arr1) / sizeof(int);
	int len2 = sizeof(arr2) / sizeof(int);

	ShowArray(arr1, len1);
	ShowArray(arr2, len2);

	return 0;
}
//*/
//======================================================
/*
	quiz)
		 ���� ������ �迭�� �� ��ҿ� ������ ���� ���ϴ� �Լ��� ����� 
		 ( void AddArray(int *pArray, int len, int value) )
		 ��°���� ������ ���� ������ �Ѵ�.

		 ó�� ��
		 1 2 3
		 -------------
		 ��ȯ ��
		 2 3 4
		 4 5 6
		 7 8 9

*/


















/*
void ShowArray(int *pArray, int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%d ", pArray[i]);

	printf("\n");
}

void AddArray(int *pArray, int len, int value)
{
	int i;
	for (i = 0; i < len; ++i)
		pArray[i] += value;
}

int main(void)
{
	int arr1[] = { 1,2,3 };
	int len1 = sizeof(arr1) / sizeof(int);

	printf("ó�� ��\n");
	ShowArray(arr1, len1);
	printf("-------------------\n");
	printf("��ȯ ��\n");
	AddArray(arr1, len1, 1);
	ShowArray(arr1, len1);

	AddArray(arr1, len1, 2);
	ShowArray(arr1, len1);

	AddArray(arr1, len1, 3);
	ShowArray(arr1, len1);
	
	return 0;
}
//*/