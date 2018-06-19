#include "Arrangement.h"

void CArrangement::Getmaxnum(){
	
	system("cls");
	char b;
	int idx;
	
	int * tarr = new int[_count];

	for(int i=0;i<_count;i++){
		tarr[i] = (S[i].k + S[i].e + S[i].m) / 3;		
	}
	int num = tarr[0];

	for(int i=1;i<_count;i++){
		if(num < tarr[i]){
			num = tarr[i];
			idx = i;
		}		
	}
	Showavr();
	printf("%d���л��� ������������ �����ֽ��ϴ�  : %d\n", idx + 1,num);
	printf("�ƹ�Ű�� �Է��ϼ��� >> ");
	getchar();
	scanf("%c",&b);
}
/////////////////////////////////////////////
void CArrangement::Getsmallnum(){
	char b;
	int idx;
	int * tarr = new int[_count];
	for(int i=0;i<_count;i++){
		tarr[i] = (S[i].k + S[i].e +S[i].m) / 3;		
	}
	int num = tarr[0];
	//*
	for(int i=1;i<_count;i++){
		if(num > tarr[i]){
			num = tarr[i];
			idx = i;
		}		
	}
	//*/
	system("cls");
	Showavr();
	printf("%d���л��� ���峷������� �����ֽ��ϴ�  : %d\n", idx + 1, num);
	getchar();
	scanf("%c",&b);
}
///////////////////////////////////////////
void CArrangement::Show(){
	printf("������������������������������������\n");
	printf("	����  ��  ����  ��  ����  ��\n");
	for(int i=0;i<_count;i++){
		printf("������������������������������������\n");
		printf("%d�� :	%d��  ��  %d��  ��  %d��  ��\n",i+1,S[i].k,S[i].e,S[i].m);
	}
	printf("������������������������������������");	
}
//////////////////////////////////////////////
void CArrangement::Showavr() {
	int * tarr = new int[_count];
	for (int i = 0; i < _count; i++) {
		tarr[i] = (S[i].k + S[i].e + S[i].m) / 3;
		printf("%d�� : %d\n", i + 1, tarr[i]);
	}
}
//////////////////////////////////////////////
void CArrangement::Showgraph(){
	char b;
	int * tarr = new int[_count];
	for (int i = 0; i<_count; i++) 
		tarr[i] = (S[i].k + S[i].e + S[i].m) / 3;
	system("cls");
	printf("===================\n");
	for(int i=0;i<_count;i++){
		printf("%d��\t: ",i+1);
		for(int j=0;j<tarr[i]/10;j++){
			printf("*");
		}
		printf("\n");
	}
	printf("===================\n");
	printf("�ƹ�Ű�� �Է��ϼ��� >> ");
	getchar();
	scanf("%c",&b);
}
//////////////////////////////////////////////
void CArrangement::Abcshow(){
	char b;
	system("cls");
	int s;
	int * tarr = new int[_count];
	for(int i=0;i<_count;i++)
		tarr[i] = (S[i].k + S[i].e + S[i].m) / 3;	
	//*
	for (int i = 0; i < _count; i++)
		printf("%d�� : %d\n", i + 1, tarr[i]);
	//*/
	for(int i=0;i<_count;i++){
		for(int j=0;j<_count;j++){
			if(tarr[i] > tarr[j]){
				s = tarr[i];
				tarr[i] = tarr[j];
				tarr[j] = s;
			}
		}
	}
	for(int i=0;i<_count;i++){
		printf("%d�� : %d��\n",i+1,tarr[i]);
	}
    printf("�ƹ�Ű�� �Է��ϼ��� >> ");
	getchar();
	scanf("%c",&b);
}
/////////////////////////////////////////////
void CArrangement::Run(){
	int a;
	while(1){
		system("cls");
		
		printf("=====================\n    ���� ���α׷�\n=====================\n\n");
		Show();
		printf("\n1.����ū��պ���\n2.����������պ���\n3.�׷����κ���\n4.��ռ�����Ÿ����\n5.����\n");
		scanf("%d",&a);
		switch(a){
			case 1:
				{
				Getmaxnum();
				break;
				}
			
			case 2:
				{
				Getsmallnum();
				break;
				}
			case 3:
				{
				Showgraph();
				break;
				}
			case 4:
				{
				Abcshow();
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
	_count = (sizeof(S) / sizeof(int)) / 3;
	
	for(int i=0;i<_count;i++){
		S[i].k= (rand() % 70) + 30;
		S[i].e= (rand() % 70) + 30;
		S[i].m= (rand() % 70) + 30;
	}
}


CArrangement::~CArrangement(void)
{
}