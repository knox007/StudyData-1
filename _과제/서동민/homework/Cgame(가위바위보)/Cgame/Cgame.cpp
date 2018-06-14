#include"stdafx.h"
void Run() {
	string a;
	
	int win = 0;
	int def = 0;
	int draw = 0;
	int gonum = 0;

	int mynum;
	int comnum;

	srand(time(0));

	while (1) {
		system("cls");
		printf("***가위바위보게임시작***    승리 횟수 : %d\n", win);
		printf("                            패배 횟수 : %d\n", def);
		printf("                          무승부 횟수 : %d\n", draw);
		printf("                            게임 횟수 : %d\n", gonum);
		while (1) {
			scanf_s("%d", &mynum);
			if (mynum > 0 && mynum < 4){
				break;
			}
			else if (mynum == 4) {
				printf("종료\n");
				exit(0);
			}
			else {
				printf("다시입력하세요\n");
			}
		}
		comnum = (rand() % 3) + 1;
		printf("나 : ");
		if (mynum == 1) {
			printf("가위  ");
		}
		else if (mynum == 2) {
			printf("바위  ");
		}
		else if (mynum == 3) {
			printf("보  ");
		}
		printf("vs  컴 : ");
		if (comnum == 1) {
			printf("가위\n");
		}
		else if (comnum == 2) {
			printf("바위\n");
		}
		else if (comnum == 3) {
			printf("보\n");
		}
		if (mynum == comnum) {
			printf("무승부!!!\n");
			draw++;
		}
		else if (mynum == 1 && comnum == 2) {
			printf("패배\n");
			def++;
		}
		else if (mynum == 1 && comnum == 3) {
			printf("승리\n");
			win++;
		}
		else if (mynum == 2 && comnum == 1) {
			printf("승리\n");
			win++;
		}
		else if (mynum == 2 && comnum == 3) {
			printf("패배\n");
			def++;
		}
		else if (mynum == 3 && comnum == 1) {
			printf("패배\n");
			def++;
		}
		else if (mynum == 3 && comnum == 2) {
			printf("승리\n");
			win++;
		}
		gonum++;
		printf("승률 : %.2f%\n", (float)win / (float)gonum * 100);
		printf("다시하려면 아무거나 입력하세요 >> ");
		cin >> a;
	}
}
int main() {
	Run();
	return 0;
}