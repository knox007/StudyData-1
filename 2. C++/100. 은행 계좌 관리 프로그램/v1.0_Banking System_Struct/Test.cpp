//==================================================
#include<iostream>
#pragma warning( disable : 4996)
using namespace std;
//==================================================
//-------------------------------
const int NAMELEN = 20;	//	이름 길이
typedef struct SAccount
{
	int _id;				//	계좌번호.
	int _balance;			//	잔액
	char _szName[NAMELEN];	//	이름.

}SAccount;
//-------------------------------
SAccount g_AccountArray[100];	//	계좌정보 배열.
int g_index = 0;				//	계설된 계좌수.
//-------------------------------
//	메뉴.
//-------------------------------
void ShowMenu()
{
	system("cls");

	cout << "----- Menu -----" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 조 회" << endl;
	cout << "5. 전체 조회" << endl;
	cout << "6. 종 료" << endl;

}//	void ShowMenu()
//-------------------------------
//	계좌 개설.
//-------------------------------
void MakeAccount()
{
	system("cls");

	int id;
	char name[NAMELEN];
	int balance;
	
	cout << "-- 계좌 개설 --" << endl;
	cout << "1. 계좌 ID : ";	cin >> id;
	cout << "2. 이 름 : ";		cin >> name;
	cout << "3. 입금액 : ";		cin >> balance;

	g_AccountArray[g_index]._id = id;
	g_AccountArray[g_index]._balance = balance;
	strcpy(g_AccountArray[g_index]._szName, name);

	++g_index;

	cout << "개설되었습니다.!!" << endl;
	getchar();
	getchar();

}//	void MakeAccount()
//-------------------------------
//	입 금.
//-------------------------------
void Deposit()
{
	system("cls");

	int id;
	cout << "-- 입금할 계좌 ID : ";	cin >> id;

	for (int curId = 0; curId < g_index; ++curId)
	{
		if (g_AccountArray[curId]._id == id)
		{
			int money;
			
			cout << "입금할 금액 : ";	cin >> money;
			g_AccountArray[curId]._balance += money;
			cout << "-- 입금 완료!!--" << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- 찾고자 하는 ID가 없습니다. !!--" << endl;
	getchar();
	getchar();

}//	void Deposit()
//-------------------------------
//	출 금.
//-------------------------------
void Withdraw()
{
	system("cls");

	int id;
	cout << "-- 출금할 계좌 ID : ";	cin >> id;

	for (int curId = 0; curId < g_index; ++curId)
	{
		if (g_AccountArray[curId]._id == id)
		{
			int money;

			cout << "출금할 금액 : ";	cin >> money;
			g_AccountArray[curId]._balance -= money;
			cout << "-- 출금 완료!!--" << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- 찾고자 하는 ID가 없습니다. !!--" << endl;
	getchar();
	getchar();

}//	void Withdraw()
//-------------------------------
//	검색후 조회
//-------------------------------
void Inquire()
{
	system("cls");

	int id;
	cout << "-- 조회할 계좌 ID : ";	cin >> id;

	for (int curId = 0; curId < g_index; ++curId)
	{
		if (g_AccountArray[curId]._id == id)
		{
			cout << "1. 계좌 ID : " << g_AccountArray[curId]._id << endl;
			cout << "2. 이 름 : " << g_AccountArray[curId]._szName << endl;
			cout << "3. 잔 액 : " << g_AccountArray[curId]._balance << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- 찾고자 하는 ID가 없습니다. !!--" << endl;
	getchar();
	getchar();

}//	void Inquire()
//-------------------------------
//	전체 조회
//-------------------------------
void InquireAll()
{
	system("cls");

	if(g_index == 0)
		cout << "개설된 계좌가 없습니다.!!" << endl;
	else
	{
		for (int curId = 0; curId < g_index; ++curId)
		{
			cout << "---------" << endl;
			cout << "1. 계좌 ID : " << g_AccountArray[curId]._id << endl;
			cout << "2. 이 름 : " << g_AccountArray[curId]._szName << endl;
			cout << "3. 잔 액 : " << g_AccountArray[curId]._balance << endl;

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
		cout << "-- 선택 : ";	cin >> select;
				
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
			cout << " 다시 선택하세요 !!" << endl;
			break;

		}//	switch (select)		
		
	}//	while (1)

	return 0;

}//	int main()
//-------------------------------