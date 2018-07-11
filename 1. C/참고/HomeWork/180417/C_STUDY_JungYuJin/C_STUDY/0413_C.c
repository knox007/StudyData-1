#include <stdio.h>
#include <string.h>
#include <windows.h> 
#include <stdlib.h>

struct Person_Info {
	char name[10];
	char address[20];
	char hp[20];
};

struct Person_Info_Package {
	struct Person_Info *info;
	int cnt;
};

void view_map();

int wall[15][15] = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 2, 3, 4, 0, 5, 6, 7, 8, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

void main() {

	struct Person_Info_Package info_p = {0};
	int menu, num;
	info_p.cnt = 0;

	view_map();
	Sleep(2000);

	for ( ; ; ) {
		int i;

		system("cls");
		
		printf("〓〓〓〓〓〓〓〓〓〓〓 \n");
		printf("      주소록 메뉴      \n");
		printf("〓〓〓〓〓〓〓〓〓〓〓 \n\n");

		printf(" 1. 주소록 리스트 \n\n");
		printf(" 2. 주소록 추가 \n\n");
		printf(" 3. 주소록 삭제 \n\n");
		printf(" 4. 주소록 수정 \n\n");
		printf(" 5. 종료 \n\n");
		printf("---------------------- \n\n");
		
		printf(" 메뉴를 입력하세요 ▶ ");
		scanf("%d", &menu);

		if (menu == 1) {
			system("cls");

			printf("〓〓〓〓〓〓〓〓〓〓〓 \n");
			printf("     주소록 리스트     \n");
			printf("〓〓〓〓〓〓〓〓〓〓〓 \n\n");

			for (i=0; i<info_p.cnt; i++) {
				printf("[%d] 이름 : %s | 주소 : %s | 연락처 : %s \n\n", i+1, info_p.info[i].name, info_p.info[i].address, info_p.info[i].hp);
			}

			printf("뒤로가기 하시려면 숫자를 입력하세요 ▶ ");
			scanf("%d", &num);

		} else if (menu == 2) {
			struct Person_Info_Package info_p2;
			char Name[10], Address[20], Hp[20];

			system("cls");

			printf("〓〓〓〓〓〓〓〓〓〓〓 \n");
			printf("      주소록 추가      \n");
			printf("〓〓〓〓〓〓〓〓〓〓〓 \n\n");

			info_p2.info = info_p.info;

			info_p.info = (struct Person_Info *)malloc(sizeof(struct Person_Info) * info_p.cnt+1);

			for (i=0; i<info_p.cnt; i++) {
				info_p.info[i] = info_p2.info[i];
			}

			printf(" 추가 할 이름·주소· \n 연락처를 입력하세요 ▶ ");
			scanf("%s %s %s", &Name, &Address, &Hp);

			//info_p.cnt++;

			/*strcpy(info_p.info[info_p.cnt].name, Name);

			strcpy(info_p.info[info_p.cnt].address, Address);
			strcpy(info_p.info[info_p.cnt].hp, Hp);*/

			info_p.cnt++;
		} else if (menu == 3) {
			int num;
			struct Person_Info_Package info_p3;

			system("cls");

			printf("〓〓〓〓〓〓〓〓〓〓〓 \n");
			printf("      주소록 삭제      \n");
			printf("〓〓〓〓〓〓〓〓〓〓〓 \n\n");

			for (i=0; i<info_p.cnt; i++) {
				printf("[%d] 이름 : %s | 주소 : %s | 연락처 : %s \n\n", i+1, info_p.info[i].name, info_p.info[i].address, info_p.info[i].hp);
			}

			printf(" 삭제 할 번호를 입력하세요 ▶ ");
			scanf("%d", &num);

			info_p3.info = info_p.info;

			info_p.info = (struct Person_Info *)malloc(sizeof(struct Person_Info) * info_p.cnt-1);

			for (i=0; i<info_p.cnt-1; i++) {
				if (i >= num-1) {
					info_p.info[i] = info_p3.info[i+1];
				} else {
					info_p.info[i] = info_p3.info[i];
				}
			}
			info_p.cnt--;
		} else if (menu == 4) {
			int num;
			char Name[10], Address[20], Hp[20];

			system("cls");

			printf("〓〓〓〓〓〓〓〓〓〓〓 \n");
			printf("      주소록 수정      \n");
			printf("〓〓〓〓〓〓〓〓〓〓〓 \n\n");

			for (i=0; i<info_p.cnt; i++) {
				printf("[%d] 이름 : %s | 주소 : %s | 연락처 : %s \n\n", i+1, info_p.info[i].name, info_p.info[i].address, info_p.info[i].hp);
			}

			printf(" 수정 할 번호를 입력하세요 ▶ ");
			scanf("%d", &num);

			printf("\n\n");

			printf(" 수정 할 이름·주소· \n 연락처를 입력하세요 ▶ ");
			scanf("%s %s %s", &Name, &Address, &Hp);

			strcpy(info_p.info[num-1].name, Name);
			strcpy(info_p.info[num-1].address, Address);
			strcpy(info_p.info[num-1].hp, Hp);

		} else if (menu == 5) {
			system("cls");

			printf("주소록 프로그램을 종료합니다. \n\n");
			break;
		} else {
			system("cls");

			printf("ERROR!!! \n\n");
			printf("뒤로가기 하시려면 숫자를 입력하세요 ▶ ");
			scanf("%d", &num);
		}
	}
}

void view_map() {
	int i, j;
	for (i=0; i<10; i++) {
		for (j=0; j<10; j++) {
			if (wall[i][j] == 0) {
				printf("  ");
			} else if (wall[i][j] == 1) {
				printf("〓");
			} else if (wall[i][j] == 2) {
				printf("주");
			} else if (wall[i][j] == 3) {
				printf("소");
			} else if (wall[i][j] == 4) {
				printf("록");
			} else if (wall[i][j] == 5) {
				printf("프");
			} else if (wall[i][j] == 6) {
				printf("로");
			} else if (wall[i][j] == 7) {
				printf("그");
			} else if (wall[i][j] == 8) {
				printf("램");
			} 
		}
		printf("\n");
	}
}



