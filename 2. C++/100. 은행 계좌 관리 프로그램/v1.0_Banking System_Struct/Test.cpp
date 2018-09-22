//==================================================
#include<iostream>
#pragma warning( disable : 4996)
using namespace std;
//==================================================
//-------------------------------
const int NAMELEN = 20;	//	�̸� ����
typedef struct SAccount
{
	int _id;				//	���¹�ȣ.
	int _balance;			//	�ܾ�
	char _szName[NAMELEN];	//	�̸�.

}SAccount;
//-------------------------------
SAccount g_AccountArray[100];	//	�������� �迭.
int g_index = 0;				//	�輳�� ���¼�.
//-------------------------------
//	�޴�.
//-------------------------------
void ShowMenu()
{
	system("cls");

	cout << "----- Menu -----" << endl;
	cout << "1. ���� ����" << endl;
	cout << "2. �� ��" << endl;
	cout << "3. �� ��" << endl;
	cout << "4. �� ȸ" << endl;
	cout << "5. ��ü ��ȸ" << endl;
	cout << "6. �� ��" << endl;

}//	void ShowMenu()
//-------------------------------
//	���� ����.
//-------------------------------
void MakeAccount()
{
	system("cls");

	int id;
	char name[NAMELEN];
	int balance;
	
	cout << "-- ���� ���� --" << endl;
	cout << "1. ���� ID : ";	cin >> id;
	cout << "2. �� �� : ";		cin >> name;
	cout << "3. �Աݾ� : ";		cin >> balance;

	g_AccountArray[g_index]._id = id;
	g_AccountArray[g_index]._balance = balance;
	strcpy(g_AccountArray[g_index]._szName, name);

	++g_index;

	cout << "�����Ǿ����ϴ�.!!" << endl;
	getchar();
	getchar();

}//	void MakeAccount()
//-------------------------------
//	�� ��.
//-------------------------------
void Deposit()
{
	system("cls");

	int id;
	cout << "-- �Ա��� ���� ID : ";	cin >> id;

	for (int curId = 0; curId < g_index; ++curId)
	{
		if (g_AccountArray[curId]._id == id)
		{
			int money;
			
			cout << "�Ա��� �ݾ� : ";	cin >> money;
			g_AccountArray[curId]._balance += money;
			cout << "-- �Ա� �Ϸ�!!--" << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- ã���� �ϴ� ID�� �����ϴ�. !!--" << endl;
	getchar();
	getchar();

}//	void Deposit()
//-------------------------------
//	�� ��.
//-------------------------------
void Withdraw()
{
	system("cls");

	int id;
	cout << "-- ����� ���� ID : ";	cin >> id;

	for (int curId = 0; curId < g_index; ++curId)
	{
		if (g_AccountArray[curId]._id == id)
		{
			int money;

			cout << "����� �ݾ� : ";	cin >> money;
			g_AccountArray[curId]._balance -= money;
			cout << "-- ��� �Ϸ�!!--" << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- ã���� �ϴ� ID�� �����ϴ�. !!--" << endl;
	getchar();
	getchar();

}//	void Withdraw()
//-------------------------------
//	�˻��� ��ȸ
//-------------------------------
void Inquire()
{
	system("cls");

	int id;
	cout << "-- ��ȸ�� ���� ID : ";	cin >> id;

	for (int curId = 0; curId < g_index; ++curId)
	{
		if (g_AccountArray[curId]._id == id)
		{
			cout << "1. ���� ID : " << g_AccountArray[curId]._id << endl;
			cout << "2. �� �� : " << g_AccountArray[curId]._szName << endl;
			cout << "3. �� �� : " << g_AccountArray[curId]._balance << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- ã���� �ϴ� ID�� �����ϴ�. !!--" << endl;
	getchar();
	getchar();

}//	void Inquire()
//-------------------------------
//	��ü ��ȸ
//-------------------------------
void InquireAll()
{
	system("cls");

	if(g_index == 0)
		cout << "������ ���°� �����ϴ�.!!" << endl;
	else
	{
		for (int curId = 0; curId < g_index; ++curId)
		{
			cout << "---------" << endl;
			cout << "1. ���� ID : " << g_AccountArray[curId]._id << endl;
			cout << "2. �� �� : " << g_AccountArray[curId]._szName << endl;
			cout << "3. �� �� : " << g_AccountArray[curId]._balance << endl;

		}//	for (int curId = 0; curId < g_index; ++curId)
	
	}//	if(g_index == 0)

	getchar();
	getchar();

}//	void InquireAll()
//-------------------------------
enum
{
	MAKEACCOUNT = 1,
	DEPOSIT,
	WITHDRAW,
	INQUIRE,
	INQUIREALL,
	EXIT,

};
#define ENTER 13
//-------------------------------
#include <stdlib.h>
//-------------------------------
int main()
{
	int select;

	while (1)	
	{
		ShowMenu();
		cout << "-- ���� : ";	cin >> select;
				
		switch (select)
		{
		case MAKEACCOUNT:
			MakeAccount();
			break;

		case DEPOSIT:
			Deposit();			
			break;

		case WITHDRAW:
			Withdraw();
			break;

		case INQUIRE:
			Inquire();
			break;

		case INQUIREALL:
			InquireAll();
			break;

		case EXIT:
			return 0;

		default :
			cout << " �ٽ� �����ϼ��� !!" << endl;
			break;

		}//	switch (select)		
		
	}//	while (1)

	return 0;

}//	int main()
//-------------------------------