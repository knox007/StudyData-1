#include"header.h"

void main(){
	int rnum;
	int dfct;
	int num;
	int i;
	int ch = 0;
	char yn;
	srand(time(0));
	while(1){
		i=0;
		system("cls");
		printf("==================\n   스무고개게임\n==================\n");
		Sleep(1000);
		printf("난이도를 입력하세요 >> ");
		scanf("%d",&dfct);
		rnum = (rand() % 100) + 1;
		printf("랜덤수를 1~100으로 정했습니다\n");
		/* rnum 보기
		printf("rnum == %d\n",rnum);
		//*/
		Sleep(3000);
		system("cls");
		printf("기회는 %d번!!\n",dfct);
		printf("시작!!\n");
		while(i<dfct){
			scanf("%d",&num);
			if(num > 0 && num <101){
				if(num > rnum){
					printf("%d보다 작습니다",num);
					printf(" 기회 : %d\n",dfct - i-1);
					i++;
				}
				else if(num < rnum){
					printf("%d보다 큽니다",num);
					printf(" 기회 : %d\n",dfct - i-1);
					i++;
				}
				else if(num == rnum){
					ch = 1;
					break;
				}
			}
			else{
				printf("1~100까지의 수를 입력하세요\n");
				Sleep(1000);
			}
		}	
		if(ch == 1){
			printf("%d번째 성공!!!\n",i+1);
		}
			else{
			printf("실패ㅠㅠ\n");
			printf("컴퓨터가 선택한수는 %d였습니다\n",rnum);
		}
		Sleep(4000);
		printf("again??(y,n) >> ");
		Sleep(500);
		while(1){
			getchar();
			scanf("%c",&yn);
			if(yn == 'y'){
				break;
			}
			else if(yn == 'n'){
				system("cls");
				printf("종료\n");
				exit(0);
				
			}
			else {
				printf("(y,n)으로 답해주세요");
				Sleep(2000);
			}
		}
	}
}