#include <stdio.h>
#include <Windows.h>

void main(){
	// �ڵ��� �����. 
	int x = 0;
	int y = 0;
	int speed = 0;
	int select;
	int des_x, des_y;
	printf("�������� �����ϼ���>>>");
	scanf("%d %d", &des_x, &des_y); 
	while(1){
		system("cls");
		printf("speed : %d\nX : %d\tY:%d\n", speed, x, y);
		printf("1.�ӵ�\n");
		printf("2.��ȸ��\n");
		printf("3.��ȸ��\n");
		printf("4.����\n");
		printf("5.����\n");
		printf("6.����\n");
		printf("��ȣ�� �Է��ϼ���>>>");
		scanf("%d", &select);
		if(select == 1){
			printf("1������");
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
			printf("���� ����"); break;
		}
	}
}