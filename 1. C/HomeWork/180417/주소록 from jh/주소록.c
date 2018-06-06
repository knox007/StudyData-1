#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996) //scanf 보안 경고 제거용

nodenum = 0; // 노드 수

typedef struct node { //노드생성
	char name[200];  //이름 변수
	char phone[200];  //전번 변수
	struct node *prev; //뒤를 연결하는 노드
	struct node *next;  //앞을 연결하는 노드
}node;

typedef node ELEMENT;    //node를 ELEMENT로 바꿈
typedef ELEMENT * LINK; //ELEMENT를 LINK포인터로 바꿈

void setlist(LINK *head, LINK *tail) {
	*head = (LINK)malloc(sizeof(ELEMENT));  //*head 동적할당
	*tail = (LINK)malloc(sizeof(ELEMENT));   // *tail 동적할당
	if (*head == NULL || *tail == NULL) { //초기화가 안될을 경우 종료
		printf("꽉찼습니다.  \n종료합니다");
		exit(1);
	}
	(*head)->next = (*tail);              //*head와 *tail을 연결  
	(*tail)->prev = (*head);
	(*head)->prev = NULL;
	(*tail)->next = NULL;
}
LINK madelist(LINK *head, LINK *tail, char *temp, char *temp2) { //기본적인 노드 세팅
	system("cls");
	LINK p = NULL, t = NULL, ptr = NULL;   //p = 앞노드 t = 뒷노드 = ptr 삽입할 노드

	ptr = (LINK)malloc(sizeof(ELEMENT));    //ptr 동적할당
	strcpy(ptr->name, temp);   //이름을 ptr에 넣어주기
	strcpy(ptr->phone, temp2);   //전번을 ptr에 넣어주기
	if (ptr == NULL) {    //ptr 초기화 실패 할 경우 종료
		printf("꽉 찼습니다. /n종료합니다/n");
		exit(1);
	}


	if (nodenum == 0) { //값의 개수가 0개일경우, *tail을 뒷노드로 설정
		p = *tail;
	}
	else { // 아닐경우 ptr의 뒷노드가 *tail이 될때까지 계속들어간다
		for (p = (*head)->next; p != (*tail); p = (p->next));
	}
	t = p->prev; // 뒷노드는 앞노드의 뒷노드로 설정


	t->next = ptr; // ptr를 연결
	ptr->next = p;
	p->prev = ptr;
	ptr->prev = t;

	nodenum++; // 노드개수 1 증가
	return ptr; //ptr 반환

}
void deletelist(LINK *head, LINK *tail, char *temp) //노드 삭제
{
	system("cls");
	LINK p = NULL, t = NULL, tmp = NULL; //p = 앞노드 t =뒷노드 = tmp는 삭제할 값

	if (nodenum > 0) { //노드수가 1개이상일경우
		for (p = (*head)->next; p != (*tail); p = (p->next)) //p가 끝에 다다를까지 계속 값을 비교
			if (strcmp(temp, p->name) == 0)
				break;

		t = p->prev; //t의 뒷노드를 p로 설정
		if (p != (*tail) && p != (*head)) { //p가 *tail이나 *head가 아닐 경우 
			t->next = p->next; //t랑 p를 이어주고
			(p->next)->prev = t;
			p->next = NULL;  //p의 링크를 끊고
			p->prev = NULL;
			free(p);  //p를 삭제한다
		}
		nodenum--; //노드개수 1개감소
	}
}

void printlist(LINK head, LINK tail) { //모든 목록을 출력

	LINK p = NULL;
	for (p = head->next; p != tail; p = (p->next))//p가 *tail에 다다를때까지 그 안의 값 출력
		printf("%-20s%-20s\n", p->name, p->phone);
}

void findlist(LINK head, LINK tail, char *temp) {//특정 값 찾아서 출력
	system("cls");
	LINK p = NULL;

	for (p = head->next; p != tail; p = (p->next)) { //p가 *tail에 다다를때까지 이름 비교
		if (strcmp(temp, p->name) == 0) {
			printf("있습니다 \n이름 : %s, 전번 : %s\n", p->name, p->phone);
			return;
		}

	}
	printf("없습니다.\n");


}
void modify(LINK head, LINK tail) {
	system("cls");
	char answer[20];
	char prevans[20];

	printf("******************************\n");
	printf("        전화번호부 편집기        \n");
	printf("******************************\n");
	printf("↓전화번호부 목록↓\n");
	printlist(head, tail);
	printf("\n계속하려면 아무 키나 누르시오\n");
	getch();
	printf("수정할 연락처 이름을 입력하시오\n");
	scanf("%s", answer);
	system("cls");
	LINK p = NULL;
	for (p = head->next; p != tail; p = (p->next)) { //p가 *tail에 다다를때까지 이름 비교
		if (strcmp(answer, p->name) == 0) {
			printf("있습니다 \n이름 : %s, 전번 : %s\n", p->name, p->phone);
			printf("수정하시겠습니까? [yes or no]\n 입력 : ");
			scanf("%s", answer);
			if (!strcmp(answer, "yes")) {
				while (1) {
					system("cls");
					printf("연락처 정보 : 이름 : %s, 전번 : %s, \n수정할 곳 입력 [이름 or 전번], 없으면 \"취소\" \n입력 :  ", p->name, p->phone);
					scanf("%s", answer);
					//이름 수정 코드 시작
					if (!strcmp(answer, "이름")) {
						system("cls");
						strcpy(prevans, p->name);
						printf("바꿀 이름 입력(취소하려면 취소 입력)\n입력 : ");
						scanf("%s", answer);
						if (!strcmp(answer, "취소")) {
							break;
						}
						else {
							system("cls");
							strcpy(p->name, answer);
							printf("완료!\n변경 전 : %s\n변경 후 : %s", prevans, p->name);
							Sleep(1000);
							system("cls");
						}
					}// 이름 수정 코드 끝

					 // 전번 수정 코드 시작
					else if (!strcmp(answer, "전번")) {
						system("cls");
						strcpy(prevans, p->phone);
						printf("바꿀 전번 입력(취소하려면 취소 입력)\n입력 : ");
						scanf("%s", answer);
						if (!strcmp(answer, "취소")) {
							break;
						}
						else {
							system("cls");
							strcpy(p->phone, answer);
							printf("완료!\n변경 전 : %s\n변경 후 : %s", prevans, p->phone);
							Sleep(1000);
							system("cls");
						}
					}
					//전번 수정 코드 끝
					else if (!strcmp(answer, "취소")) {
						printf("취소했습니다");
						Sleep(1000);
						system("cls");
						break;
					}
					else {
						printf("잘못입력하셨습니다.. 다시입력..\n");
						Sleep(1000);
						system("cls");
					}
				}
			}
		}
	}
}


char name[20];  //입력할 이름 초기화
char phone[20]; //입력할 전번 초기화
LINK head = NULL;  //*head 초기화
LINK tail = NULL;  //*tail 초기화
int a;  //입력할 변수 초기화


void(*Process)();
void Add()
{
	system("cls");
	printf("이름 입력 : ");
	scanf("%s", name);
	printf("\n");
	printf("전화번호 입력 : ");
	scanf("%s", phone);
	printf("\n");
	madelist(&head, &tail, name, phone);
	printf("완료!");
	Sleep(1000);
	system("cls");
}
void Delete()
{
	system("cls");
	printf("삭제할 이름 입력 : ");
	scanf("%s", name);
	deletelist(&head, &tail, name);
	printf("완료!");
	Sleep(1000);
	system("cls");
}
void ShowAll()
{
	system("cls");
	printf("목록 전체를 볼려면 1, 특정사람을 검색하려면 2를 누르세요\n");
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
		printf("검색할 이름 입력 : ");
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

int main() {  //main함수
	setlist(&head, &tail); //*head, *tail 값 초기화
	

			//프로그램 테스트를 위한 노드들//
	madelist(&head, &tail, "1", "010-0000-0000");
	madelist(&head, &tail, "2", "010-0000-0000");
	madelist(&head, &tail, "3", "010-0000-0000");
	//프로그램 완성 후 지우기//


	while (1) {
		system("cls");
		printf("주소록\n");
		printf("1:추가 \n2:삭제\n3:목록\n4:수정\n5:종료\n");
		scanf("%d", &a); // 옵션 값 입력
		switch (a) {
		case 1: //추가
			Process = Add;
			break;

		case 2: //삭제
			Process = Delete;
			break;

		case 3: //목록 보기
			Process = ShowAll;
			break;

		case 4:
			Process = Edit;
			break;

		case 5: // 종료
			Process = Exit;
			break;
		}

		Process();

	}
}