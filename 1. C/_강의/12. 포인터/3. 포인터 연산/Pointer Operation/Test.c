//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	�������� ��������
	
	-	T�� �����͸� ������� n�� ũ�� ��ŭ ���� �����ϸ�
		
		n x sizeof(T) ��ŭ �ּҰ��� �����Ѵ�.
		
*/

/*
int main(void)
{
	int *ptr1 = 0x0010;				//	sizeof(int)	?
	double *ptr2 = 0x0010;			//	sizeof(double)	?

	printf("ptr1 = %p     ptr2 = %p\n", ptr1, ptr2);
	printf("ptr1 + 1 = %p   ptr1 + 2 = %p\n", ptr1 + 1, ptr1 + 2);
	printf("ptr2 + 1 = %p   ptr2 + 2 = %p \n", ptr2 + 1, ptr2 + 2);
		
	
	printf("++ptr1, ++ptr2 \n");
	++ptr1, ++ptr2;
	printf("ptr1 = %p     ptr2 = %p\n", ptr1, ptr2);
	
	return 0;
}
//*/


//	�̷��� Ư������ ���� ������ ���� �迭 ���ٵ� �����ϴ�.
/*	
int main(void)
{
	int arr[3] = { 11,22,33 };

	int *ptr = arr;	//	int *ptr = &arr[0]; �� ����.

	printf("%d, %d, %d\n", *ptr, *(ptr + 1), *(ptr + 2));


	printf("%d ", *(ptr++));
	printf("%d ", *(ptr++));
	printf("%d ", *(ptr--));
	printf("%d ", *(ptr--));
	printf("%d \n", *ptr);

	return 0;
}
//*/

/*	Quiz 1)
int main(void)
{
	int arr[3] = { 11,22,33 };

	int *ptr = arr;	//	int *ptr = &arr[0]; �� ����.

	printf("%d, %d, %d\n", *ptr, *(ptr + 1), *(ptr + 2));

	int a = *(ptr++);
	int b = (*ptr)++;
	int c = *(ptr + 1);

	//	��������??
	printf("%d, %d, %d\n", a, b, c);
}
//*/
//======================================================
/*
2.	arr[i] == *(arr+i)

	-	*ptr, *(ptr+1), *(ptr+2) == arr[0], arr[1], arr[2]

	-	�迭 �̸��� ������ ������ ���/������ ���̸� ������ ��ǻ� ����.

	-	printf("%d, %d, %d\n", *ptr, *(ptr + 1), *(ptr + 2));	*ptr == *( ptr + 0 )

		printf("%d, %d, %d\n", ptr[0], ptr[1], ptr[2]);

		printf("%d, %d, %d\n", *arr, *(arr + 1), *(arr + 2));

		printf("%d, %d, %d\n", arr[0], arr[1], arr[2]);

		-	arr[i] == *(arr+i)

*/
//======================================================
/*	Quiz 2)
	
	int arr[] = {1,2,3,4,5};

	�� �迭��  ù��° ��Ҹ� ����Ű�� ������ ���� ptr�� �����ϰ� 

	ptr�� �̿��Ͽ� ��� �迭����� ���� 2�� ������Ų �� ���.

*/


















/*
int main(void)
{
	int arr[] = { 1,2,3,4,5 };

	int *ptr = arr;

	printf("--- before ---\n");
	for (int cur = 0; cur < 5; ++cur)
		printf("%d\n", *(ptr + cur));

	for (int cur = 0; cur < 5; ++cur)
		*(ptr + cur) += 2;

	printf("--- after ---\n");
	for (int cur = 0; cur < 5; ++cur)
		printf("%d\n", *(ptr + cur));

	return 0;
}
//*/