#include <stdio.h>
// ***�Լ��� 4���� Ÿ��***
// ����x, �Ķ����x
// void = ������ ����. 
// () = �Ķ���� X ==> ȣ���Ҷ� ���ڵ�X
void showInfo(){								//����ι�
	printf("���̸��� ȫ�浿 �Դϴ�.\n");		//�ٵ�κ�
}// �Լ�����

// ����o, �Ķ����X
// int = ������ �����ϴ� �Լ���~
// return 10; = �Լ��� �����ϸ�, ���� 10�� ȣ���Ѱ����� �����ش�.
int getInteger(){
	printf("����Ÿ�� �ִ� �Լ�\n");
	return 10;
}
// ����X, �Ķ����o
void showAge(int b){
	printf("����� ���̴� %d�� �Դϴ�.\n", b);
}
// ����o, �Ķ����o
int sum(int a, int b){
	int tot;
	tot = a + b;
	return tot;
}

void main(){
	int num;
	int age = 0;
	int num1 = 10;
	int num2 = 20;

	//�Լ� ȣ��
	showInfo();
	// num : getInteger()�Լ��� �����ϰ� return���� �������� ���� �����ϴ� ����
	// getInteger(); : �Լ� ȣ��. 
	num = getInteger();
	printf("%d\n", num);
	printf("����� ���̸� �Է��ϼ���>>>");
	scanf("%d", &age);
	showAge(age);
	num = sum(num1, num2);
	printf("%d\n", num);
}


