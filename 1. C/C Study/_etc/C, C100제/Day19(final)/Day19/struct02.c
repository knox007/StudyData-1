#include <stdio.h>
#include <string.h>

/*

	*** ����ü ***
	# ������ ��� ������.

	struct Person a;
	struct Person *p;
	p = &a;
	a�� �ּҸ� �޴� ������ p�� ���Ͽ�,
	a�� ������ �ִ� age��� ����� �����ϱ� ���ؼ� 
	a.age = 20;
	(*p).age = 20;
	�̷������� �ۼ��� �ؾ����� ��Ȯ�ϰ� ������ �����ѵ�, �������� �������� ������
	������ ��� �����ڸ� ��������. 
	' -> ' ȭ��ǥ�̴�.  : "~ �ּ��� ����ü��� ~" ��� �������!
	p -> age = 20;		: p�ּ��� ����ü ��� age�� 20�� ��������;


	#������ �켱����
	�ֿ켱������ : . -> [] ()
	���׿����� : ! ~ + - ++ -- * & sizeof() (�ڷ���)
	���������
	���迬����
	��������
	���׿�����
	���Կ�����
	�޸�������
*/

struct Person{
	char name[10];
	int age;
	double height;
};

void func(struct Person *p){
	printf("�̸�: %s\n", p->name);
	printf("����: %d\n", p->age);
	printf("Ű  : %.1lf\n", p->height);
}

void main(){

	//����� ���� �ڷ���
	//int a = 10;
	//int* pa;
	//pa = &a;
	//*pa = 20;

	struct Person p1;
	struct Person *pP1;

	// ����ü �����͸� ���Ͽ� �� ���Խ�Ű��
	pP1 = &p1;
	strcpy(pP1->name, "ȫ�浿");
	pP1->age = 20;
	pP1->height = 160.5;

	func(pP1);

	/* �Ϲ� ����ü�� �� ���Խ�Ű��
	strcpy(p1.name, "ȫ�浿");
	p1.age = 20;
	p1.height = 160.5;
	*/
}