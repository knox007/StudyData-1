#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#pragma warning (disable : 4996)

typedef struct
{
	char Name[20];
	int AcNum = 0;
	int Money = 0;
}BankData;
BankData info;
BankData gBankData[100];
int gIdxBankData = -1;
int gBankAcNum = 1;

void CreatAc();
void DeleteAc(BankData *AcData);
void Deposit(BankData *AcData);
void Withdraw(BankData *AcData);
void AcInquiry(int AcCk);
void AllAcInquiry();
void Menu();
void CreatFile();
void DataCopy(char *name, int acnum, int money);

int main()
{
	FILE *FileCheck = fopen("bankdata.bin", "rb");

	if (FileCheck != NULL)
	{
		int SizeCheck = 0;

		fseek(FileCheck, 0, SEEK_END);
		SizeCheck = ftell(FileCheck);
		fseek(FileCheck, 0, SEEK_SET);

		int ck;

		while (ck = ftell(FileCheck) != SizeCheck)
		{
			char name[20];
			int acnum, money;

			fscanf(FileCheck, "%s%d%d", name, &acnum, &money);

			DataCopy(name, acnum, money);

		}
		info = { 0, };

		fclose(FileCheck);
	}
	Menu();
}

void Menu()
{
	int choice = 0;
	puts("1. ���� ����");
	puts("2. ���� ����");
	puts("3. ��    ��");
	puts("4. ��    ��");
	puts("5. ��    ȸ");
	puts("6. ��ü ��ȸ");
	puts("7. ��    ��");
	printf("�� �� �� �� : ");
	scanf("%d", &choice);
	system("cls");


	switch (choice)
	{
	case 1:
	{
		CreatAc();
		break;
	}
	case 2:
	{
		AcInquiry(choice);
		break;
	}
	case 3:
	{
		AcInquiry(choice);
		break;
	}
	case 4:
	{
		AcInquiry(choice);
		break;
	}
	case 5:
	{
		AcInquiry(choice);
		break;
	}
	case 6:
	{
		AllAcInquiry();
		break;
	}
	case 7:
	{
		CreatFile();
	}
	}
}

void CreatAc()
{
	printf("�̸� �Է� : ");
	scanf("%s", info.Name);

	printf("���¹�ȣ : ");
	info.AcNum = gBankAcNum;
	gBankAcNum++;
	printf("%d\n", info.AcNum);


	printf("���� �ܾ��� %d�� �Դϴ�.\n", info.Money);

	gBankData[gIdxBankData + 1] = info;
	gIdxBankData++;

	for (int i = 3; i > 0; i--)
	{
		printf("%d ", i);
		Sleep(1000);
	}
	system("cls");

	Menu();
}

void DeleteAc(BankData *AcData)
{
	char ck ;

	puts("�� ���°� �½��ϱ�? Y : N");
	getchar();
	scanf("%c", &ck);

	if (ck == 'Y' or ck == 'y')
	{
		*AcData = { 0, };
		puts("���� �Ϸ�");

		puts("�ʱ� ȭ������ �̵��մϴ�!");

		for (int i = 3; i > 0; i--)
		{
			printf("%d ", i);
			Sleep(1000);
		}
		system("cls");

		Menu();
	}
	else
	{
		puts("�ʱ� ȭ������ �̵��մϴ�!");

		for (int i = 3; i > 0; i--)
		{
			printf("%d ", i);
			Sleep(1000);
		}
		system("cls");

		Menu();
	}
}

void Deposit(BankData *AcData)
{
	int money;

	puts("�Ա��� �ݾ��Է�");
	scanf("%d", &money);

	AcData->Money += money;

	printf("���� �ܰ� : %d\n", AcData->Money);

	puts("�ʱ� ȭ������ �̵��մϴ�!");

	for (int i = 3; i > 0; i--)
	{
		printf("%d ", i);
		Sleep(1000);
	}
	system("cls");

	Menu();
}

void Withdraw(BankData *AcData)
{
	int money;

	puts("����� �ݾ��Է�");
	scanf("%d", &money);

	if (AcData->Money - money < 0)
	{
		printf("���� �ܰ��� ��� �ݾ��� �����ϴ�.\n");
	}
	else
	{
		AcData->Money -= money;
	}

	printf("���� �ܰ� : %d\n", AcData->Money);

	puts("�ʱ� ȭ������ �̵��մϴ�!");
	
	for (int i = 3; i > 0; i--)
	{
		printf("%d ", i);
		Sleep(1000);
	}
	system("cls");

	Menu();
}

void AcInquiry(int AcCk)
{
	int AcNum, ck = 1;
	puts("���¹�ȣ �Է�");
	scanf("%d", &AcNum);
	for (int i = 0; i < 100; i++)
	{
		if (gBankData[i].AcNum == AcNum && gBankData[i].AcNum != 0)
		{
			printf("��   �� : %s\n", gBankData[i].Name);
			printf("���¹�ȣ : %d\n", gBankData[i].AcNum);
			printf("��   �� : %d\n", gBankData[i].Money);

			ck = 0;

			switch (AcCk)
			{
			case 2:
			{
				DeleteAc(&gBankData[i]);
				break;
			}
			case 3:
			{
				Deposit(&gBankData[i]);
				break;
			}
			case 4:
			{
				Withdraw(&gBankData[i]);
				break;
			}
			case 5:
			{
				puts("�ʱ� ȭ������ �̵��մϴ�!");

				for (int i = 3; i > 0; i--)    
				{
					printf("%d ", i);
					Sleep(1000);
				}
				system("cls");
				Menu();
				
			}
			}
			
		}
	}
	if(ck)
	{
		puts("��ϵ� ���°� �����ϴ�.");
		puts("�ʱ� ȭ������ �̵��մϴ�!");

		for (int i = 3; i > 0; i--)
		{
			printf("%d ", i);
			Sleep(1000);
		}
		system("cls");
		Menu();
	}
}

void  AllAcInquiry()
{
	if (gIdxBankData < 0)
	{
		puts("��ϵ� ������ �����ϴ�.");
		puts("�ʱ� ȭ������ �̵��մϴ�!");
		
		for (int i = 3; i > 0; i--)
		{
			printf("%d ", i);
			Sleep(1000);
		}
		system("cls");

		Menu();
	}
	else
	{
		for (int i = 0; i < gBankAcNum - 1; i++)
		{
			if (gBankData[i].AcNum != 0)
			{
				printf("��   �� : %s\n", gBankData[i].Name);
				printf("���¹�ȣ : %d\n", gBankData[i].AcNum);
				printf("��   �� : %d\n", gBankData[i].Money);
				printf("\n--------------------\n");
			}
		}
	}

	puts("�ʱ� ȭ������ �̵��մϴ�!");

	Sleep(5000);

	system("cls");

	Menu();
}

void CreatFile()
{
	FILE *ptFile = fopen("bankdata.txt", "wt");
	FILE *pbFile = fopen("bankdata.bin", "wb");
	for (int i = 0; i < gIdxBankData + 1; i++)
	{	
		if (gBankData[i].AcNum != 0)
		{
			fprintf(ptFile, "�̸� : %s ", gBankData[i].Name);
			fprintf(ptFile, "���¹�ȣ : %d ", gBankData[i].AcNum);
			fprintf(ptFile, "�ܰ� : %d\n", gBankData[i].Money);

			fprintf(pbFile, "%s ", gBankData[i].Name);
			fprintf(pbFile, "%d ", gBankData[i].AcNum);
			fprintf(pbFile, "%d", gBankData[i].Money);
		}
	}

	fclose(pbFile);
	fclose(ptFile);
}

void DataCopy(char *name, int acnum, int money)
{
	strcpy(info.Name, name);
	info.AcNum = acnum;
	info.Money = money;

	gBankData[gIdxBankData + 1] = info;
	gIdxBankData++;

	gBankAcNum = info.AcNum + 1;
}