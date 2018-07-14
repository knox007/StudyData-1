#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996) //scanf ���� ��� ���ſ�

nodenum = 0; // ��� ��

typedef struct node { //������
	char name[200];  //�̸� ����
	char phone[200];  //���� ����
	struct node *prev; //�ڸ� �����ϴ� ���
	struct node *next;  //���� �����ϴ� ���
}node;

typedef node ELEMENT;    //node�� ELEMENT�� �ٲ�
typedef ELEMENT * LINK; //ELEMENT�� LINK�����ͷ� �ٲ�

void setlist(LINK *head, LINK *tail) {
	*head = (LINK)malloc(sizeof(ELEMENT));  //*head �����Ҵ�
	*tail = (LINK)malloc(sizeof(ELEMENT));   // *tail �����Ҵ�
	if (*head == NULL || *tail == NULL) { //�ʱ�ȭ�� �ȵ��� ��� ����
		printf("��á���ϴ�.  \n�����մϴ�");
		exit(1);
	}
	(*head)->next = (*tail);              //*head�� *tail�� ����  
	(*tail)->prev = (*head);
	(*head)->prev = NULL;
	(*tail)->next = NULL;
}
LINK madelist(LINK *head, LINK *tail, char *temp, char *temp2) { //�⺻���� ��� ����
	system("cls");
	LINK p = NULL, t = NULL, ptr = NULL;   //p = �ճ�� t = �޳�� = ptr ������ ���

	ptr = (LINK)malloc(sizeof(ELEMENT));    //ptr �����Ҵ�
	strcpy(ptr->name, temp);   //�̸��� ptr�� �־��ֱ�
	strcpy(ptr->phone, temp2);   //������ ptr�� �־��ֱ�
	if (ptr == NULL) {    //ptr �ʱ�ȭ ���� �� ��� ����
		printf("�� á���ϴ�. /n�����մϴ�/n");
		exit(1);
	}


	if (nodenum == 0) { //���� ������ 0���ϰ��, *tail�� �޳��� ����
		p = *tail;
	}
	else { // �ƴҰ�� ptr�� �޳�尡 *tail�� �ɶ����� ��ӵ���
		for (p = (*head)->next; p != (*tail); p = (p->next));
	}
	t = p->prev; // �޳��� �ճ���� �޳��� ����


	t->next = ptr; // ptr�� ����
	ptr->next = p;
	p->prev = ptr;
	ptr->prev = t;

	nodenum++; // ��尳�� 1 ����
	return ptr; //ptr ��ȯ

}
void deletelist(LINK *head, LINK *tail, char *temp) //��� ����
{
	system("cls");
	LINK p = NULL, t = NULL, tmp = NULL; //p = �ճ�� t =�޳�� = tmp�� ������ ��

	if (nodenum > 0) { //������ 1���̻��ϰ��
		for (p = (*head)->next; p != (*tail); p = (p->next)) //p�� ���� �ٴٸ����� ��� ���� ��
			if (strcmp(temp, p->name) == 0)
				break;

		t = p->prev; //t�� �޳�带 p�� ����
		if (p != (*tail) && p != (*head)) { //p�� *tail�̳� *head�� �ƴ� ��� 
			t->next = p->next; //t�� p�� �̾��ְ�
			(p->next)->prev = t;
			p->next = NULL;  //p�� ��ũ�� ����
			p->prev = NULL;
			free(p);  //p�� �����Ѵ�
		}
		nodenum--; //��尳�� 1������
	}
}

void printlist(LINK head, LINK tail) { //��� ����� ���

	LINK p = NULL;
	for (p = head->next; p != tail; p = (p->next))//p�� *tail�� �ٴٸ������� �� ���� �� ���
		printf("%-20s%-20s\n", p->name, p->phone);
}

void findlist(LINK head, LINK tail, char *temp) {//Ư�� �� ã�Ƽ� ���
	system("cls");
	LINK p = NULL;

	for (p = head->next; p != tail; p = (p->next)) { //p�� *tail�� �ٴٸ������� �̸� ��
		if (strcmp(temp, p->name) == 0) {
			printf("�ֽ��ϴ� \n�̸� : %s, ���� : %s\n", p->name, p->phone);
			return;
		}

	}
	printf("�����ϴ�.\n");


}
void modify(LINK head, LINK tail) {
	system("cls");
	char answer[20];
	char prevans[20];

	printf("******************************\n");
	printf("        ��ȭ��ȣ�� ������        \n");
	printf("******************************\n");
	printf("����ȭ��ȣ�� ��ϡ�\n");
	printlist(head, tail);
	printf("\n����Ϸ��� �ƹ� Ű�� �����ÿ�\n");
	getch();
	printf("������ ����ó �̸��� �Է��Ͻÿ�\n");
	scanf("%s", answer);
	system("cls");
	LINK p = NULL;
	for (p = head->next; p != tail; p = (p->next)) { //p�� *tail�� �ٴٸ������� �̸� ��
		if (strcmp(answer, p->name) == 0) {
			printf("�ֽ��ϴ� \n�̸� : %s, ���� : %s\n", p->name, p->phone);
			printf("�����Ͻðڽ��ϱ�? [yes or no]\n �Է� : ");
			scanf("%s", answer);
			if (!strcmp(answer, "yes")) {
				while (1) {
					system("cls");
					printf("����ó ���� : �̸� : %s, ���� : %s, \n������ �� �Է� [�̸� or ����], ������ \"���\" \n�Է� :  ", p->name, p->phone);
					scanf("%s", answer);
					//�̸� ���� �ڵ� ����
					if (!strcmp(answer, "�̸�")) {
						system("cls");
						strcpy(prevans, p->name);
						printf("�ٲ� �̸� �Է�(����Ϸ��� ��� �Է�)\n�Է� : ");
						scanf("%s", answer);
						if (!strcmp(answer, "���")) {
							break;
						}
						else {
							system("cls");
							strcpy(p->name, answer);
							printf("�Ϸ�!\n���� �� : %s\n���� �� : %s", prevans, p->name);
							Sleep(1000);
							system("cls");
						}
					}// �̸� ���� �ڵ� ��

					 // ���� ���� �ڵ� ����
					else if (!strcmp(answer, "����")) {
						system("cls");
						strcpy(prevans, p->phone);
						printf("�ٲ� ���� �Է�(����Ϸ��� ��� �Է�)\n�Է� : ");
						scanf("%s", answer);
						if (!strcmp(answer, "���")) {
							break;
						}
						else {
							system("cls");
							strcpy(p->phone, answer);
							printf("�Ϸ�!\n���� �� : %s\n���� �� : %s", prevans, p->phone);
							Sleep(1000);
							system("cls");
						}
					}
					//���� ���� �ڵ� ��
					else if (!strcmp(answer, "���")) {
						printf("����߽��ϴ�");
						Sleep(1000);
						system("cls");
						break;
					}
					else {
						printf("�߸��Է��ϼ̽��ϴ�.. �ٽ��Է�..\n");
						Sleep(1000);
						system("cls");
					}
				}
			}
		}
	}
}


char name[20];  //�Է��� �̸� �ʱ�ȭ
char phone[20]; //�Է��� ���� �ʱ�ȭ
LINK head = NULL;  //*head �ʱ�ȭ
LINK tail = NULL;  //*tail �ʱ�ȭ
int a;  //�Է��� ���� �ʱ�ȭ


void(*Process)();
void Add()
{
	system("cls");
	printf("�̸� �Է� : ");
	scanf("%s", name);
	printf("\n");
	printf("��ȭ��ȣ �Է� : ");
	scanf("%s", phone);
	printf("\n");
	madelist(&head, &tail, name, phone);
	printf("�Ϸ�!");
	Sleep(1000);
	system("cls");
}
void Delete()
{
	system("cls");
	printf("������ �̸� �Է� : ");
	scanf("%s", name);
	deletelist(&head, &tail, name);
	printf("�Ϸ�!");
	Sleep(1000);
	system("cls");
}
void ShowAll()
{
	system("cls");
	printf("��� ��ü�� ������ 1, Ư������� �˻��Ϸ��� 2�� ��������\n");
	scanf("%d", &a);
	if (a == 1) {
		system("cls");
		printlist(head, tail);
		getch();
		system("cls");
	}
	else if (a == 2) {
		system("cls");
		strcpy(name, "");
		printf("�˻��� �̸� �Է� : ");
		scanf("%s", &name);
		findlist(head, tail, name);
		getch();
		system("cls");
	}
}
void Edit()
{
	modify(head, tail);
}
void Exit()
{
	exit(1);
}

int main() {  //main�Լ�
	setlist(&head, &tail); //*head, *tail �� �ʱ�ȭ
	

			//���α׷� �׽�Ʈ�� ���� ����//
	madelist(&head, &tail, "1", "010-0000-0000");
	madelist(&head, &tail, "2", "010-0000-0000");
	madelist(&head, &tail, "3", "010-0000-0000");
	//���α׷� �ϼ� �� �����//


	while (1) {
		system("cls");
		printf("�ּҷ�\n");
		printf("1:�߰� \n2:����\n3:���\n4:����\n5:����\n");
		scanf("%d", &a); // �ɼ� �� �Է�
		switch (a) {
		case 1: //�߰�
			Process = Add;
			break;

		case 2: //����
			Process = Delete;
			break;

		case 3: //��� ����
			Process = ShowAll;
			break;

		case 4:
			Process = Edit;
			break;

		case 5: // ����
			Process = Exit;
			break;
		}

		Process();

	}
}