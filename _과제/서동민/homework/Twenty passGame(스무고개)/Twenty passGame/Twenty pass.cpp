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
		printf("==================\n   ����������\n==================\n");
		Sleep(1000);
		printf("���̵��� �Է��ϼ��� >> ");
		scanf("%d",&dfct);
		rnum = (rand() % 100) + 1;
		printf("�������� 1~100���� ���߽��ϴ�\n");
		/* rnum ����
		printf("rnum == %d\n",rnum);
		//*/
		Sleep(3000);
		system("cls");
		printf("��ȸ�� %d��!!\n",dfct);
		printf("����!!\n");
		while(i<dfct){
			scanf("%d",&num);
			if(num > 0 && num <101){
				if(num > rnum){
					printf("%d���� �۽��ϴ�",num);
					printf(" ��ȸ : %d\n",dfct - i-1);
					i++;
				}
				else if(num < rnum){
					printf("%d���� Ů�ϴ�",num);
					printf(" ��ȸ : %d\n",dfct - i-1);
					i++;
				}
				else if(num == rnum){
					ch = 1;
					break;
				}
			}
			else{
				printf("1~100������ ���� �Է��ϼ���\n");
				Sleep(1000);
			}
		}	
		if(ch == 1){
			printf("%d��° ����!!!\n",i+1);
		}
			else{
			printf("���ФФ�\n");
			printf("��ǻ�Ͱ� �����Ѽ��� %d�����ϴ�\n",rnum);
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
				printf("����\n");
				exit(0);
				
			}
			else {
				printf("(y,n)���� �����ּ���");
				Sleep(2000);
			}
		}
	}
}