#include <stdio.h>
#include <Windows.h>

void main(){
	// 자동차 만들기. 
	int x = 0;
	int y = 0;
	int speed = 0;
	int select;
	int des_x, des_y;
	printf("목적지를 설정하세요>>>");
	scanf("%d %d", &des_x, &des_y); 
	while(1){
		system("cls");
		printf("speed : %d\nX : %d\tY:%d\n", speed, x, y);
		printf("1.속도\n");
		printf("2.좌회전\n");
		printf("3.우회전\n");
		printf("4.전진\n");
		printf("5.정지\n");
		printf("6.종료\n");
		printf("번호를 입력하세요>>>");
		scanf("%d", &select);
		if(select == 1){
			printf("1번선택");
			Sleep(1000); 
		}
		if(select == 2){

		}
		if(select == 3){

		}
		if(select == 4){

		}
		if(select == 5){

		}
		if(select == 6){
			printf("게임 종료"); break;
		}
	}
}