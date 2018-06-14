#include "Arrangement.h"

int CArrangement::Getmaxnum(){
	int num = _arr[0];
	for(int i=0;i<_count;i++){
		if(num < _arr[i+1]){
			num = _arr[i+1];	
		}		
	}
	return num;
}
/////////////////////////////////////////////
int CArrangement::Getsmallnum(){
	int num = _arr[0];
	for(int i=0;i<_count-1;i++){
		if(num > _arr[i+1]){
			num = _arr[i+1];
		}		
	}
	return num;
}
///////////////////////////////////////////
void CArrangement::Show(){
	system("cls");
	for(int i=0;i<_count;i++){
		printf("%d�� : %d\n",i+1,_arr[i]);
	}
}
//////////////////////////////////////////////
void CArrangement::Showgraph(){
	system("cls");
	printf("===================\n");
	for(int i=0;i<_count;i++){
		printf("%d��\t: ",i+1);
		for(int j=0;j<_arr[i]/10;j++){
			printf("*");
		}
		printf("\n");
	}
	printf("===================\n");
}
/////////////////////////////////////////////
void CArrangement::Run(){
	int a;
	string b;
	while(1){
		system("cls");
		printf("===========\n  ���� ���α׷�\n===========\n\n");
		printf("1.����\n2.����ū������\n3.��������������\n4.�׷����κ���\n5.����\n");
		scanf("%d",&a);
		switch(a){
			case 1:
				{
				Show();
				printf("�ƹ�Ű�� �Է��ϼ��� >> ");
				scanf("%s",&b);
				break;
				}
			
			case 2:
				{
				int c;
				c = Getmaxnum();
				system("cls");
				printf("ū�� : %d\n",c);
				scanf("%d",&b);
				break;
				}
			case 3:
				{
				int c;
				c = Getsmallnum();
				system("cls");
				printf("������ : %d\n",c);
				scanf("%d",&b);
				break;
				}
			case 4:
				{
				Showgraph();
				printf("�ƹ�Ű�� �Է��ϼ��� >> ");
				scanf("%s",&b);
				break;
				}
			case 5:
				{
				system("cls");
				printf("����\n");
				exit(0);
			}
		}
	}	
}
////////////////////////////////////////////////
CArrangement::CArrangement()
{
	srand(time(0));
	_count = sizeof(_arr) / sizeof(int);
	for(int i=0;i<_count;i++){
		_arr[i] = (rand() % 91) + 10;
	}
}


CArrangement::~CArrangement(void)
{
}