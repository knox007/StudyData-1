#include <stdio.h>

void main(){

	int* p = NULL;
	int arr[3] = {10, 20, 30};
	printf("arr[0] = %d\n", arr[0]);
	printf("*(arr+0) = %d\n", *(arr+0));
	printf("*(arr+1) = %d\n", *(arr+1));
	//*�迭���� ������(�ּ�) �����. �迭���� ù��° ����� �ּҸ� ��Ÿ����.*
	// �迭���� ��ҵ�(����ȵ����͵�)���� �����Ϸ���, �迭��[�ε�����ȣ]�� ����ϸ�ȴ�.
	// (�߰���) arr[0] => *(arr+0)  : *( + ) => �ٿ��� []�� ����Ѵ�.
	p = &arr[0];
	printf("p = %d\n", p);
	printf("*p = %d\n", *p);
	printf("arr[1] = %d\n", arr[1]);
	printf("*(p+1) = %d\n", *(p+1));
	printf("*(p+1) = %d\n", *(p+2));
	printf("arr + 1 = %d\n", *(arr + 1));

	/*0��
	printf("%d\n", arr[0]);
	printf("%d\n", arr[1]);
	printf("%d\n", arr[2]);
	printf("%d\n", &arr[0]);
	printf("%d\n", &arr[1]);
	printf("%d\n", &arr[2]);
	printf("%d\n", arr);
	p = arr;
	p = &arr[0];
	printf("arr[0] = %d\n", arr[0]);
	printf("&arr[0] = %d\n", &arr[0]);
	printf("p = %d\n", p);
	printf("*p = %d\n", *p);
	*/

}