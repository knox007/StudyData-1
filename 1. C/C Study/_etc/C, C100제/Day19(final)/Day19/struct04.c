#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	*** ����ü �迭 ***
	0. ����ü 
	struct Person p1;
	p1.age = 20;

	1. ����ü�� �迭�� ���
	PersonŸ���� ����ü ���� 10���� ��� �ּҷ��� ����� �ʹ�.

	struct Person aP[10];
	aP[3].age = 30;

	�迭�� ÷�ڿ����� []�� ��������� .�� ���� ����Ͽ� ������ Ȱ��.
	�ΰ��� [] , . ������ �켱������ ��� 1���� , ���ʿ켱���̱⶧����
	������� �����ָ� �ȴ�. 

	2. �迭�� ����ü�� ���(���)
	struct Person p;
	p.name[0] = 'A';

	3. ����ü�� �迭�� ����̸� �� ��Ҿȿ� �迭�� �������
	struct Person aP[10];
	aP[1].name[2] = 'B';	//��θ� ������� �����ϸ� �ȴ�.

	4. ����ü �����͹迭
	struct Person *pP;        ==> ����ü �ϳ��� ����Ű�� ������
	struct Person *parP[10];  ==> 10������ �迭�ȿ� ����ü�� ����Ű�� �����Ͱ� 10�� ����ִ�. 
	parP[3]->age = 20;
	(*parP[3]).age = 20;
	(**(parP+3)).age = 20;

*/
struct Person{
	char name[10];
	int age;
	int mobile;
};

void main(){
	/*
	int a;
	int *a;
	struct Person *p2; // ����ü�� ����Ű�� ������

	//�迭
	int ar[3];
	//����ü �迭
	struct Person arP[3];

	struct Person p1;
	struct Person arp[10];
	*/
	/*
	// �̸�ũ�⸸ŭ �޸� �Ҵ��Ҷ�, �����ͻ�� 
	char *name;
	name = (char*)malloc(name_len * sizeof(char));

	//����ü�� ����Ű�� �����͵��� �迭 : ����ü ����Ű�� �����Ͱ� 10�� ����ִ� �迭
	struct Person *pSt;
	pSt = (struct Person*)malloc(sizeof(struct Person));
	*/

	//#�Ҵ�
	// ����ü 10���� �����͸� �̿��ؼ� �Ҵ��Ͽ� ü�������� �����͸� ����/Ȱ������. 
	struct Person *parP[10];
	int i;
	for(i=0;i<10;i++){
		parP[i] = (struct Person*)malloc(sizeof(struct Person));
	}// ����ü�� �ʱ�ȭ ���ֱ� ���� malloc�Լ��� �����Ҵ�.
	// ����ü�� ����Ű���� �ʱ�ȭ �ϴ� ���� ���� ���. 

	parP[3]->age = 20;
	printf("%d\n", parP[3]->age);

	//#����
	for(i=0;i<10;i++){
		free(parP[i]);
	}

}