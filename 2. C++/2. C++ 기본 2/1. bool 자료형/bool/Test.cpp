//=================================================
/*
	bool �� ����

	-	c++���� �߰��� �⺻ �ڷ���.

	-	true�� false �� ���� ����.

	-	
*/
//=================================================
#include<iostream>
using namespace std;
//=================================================
bool IsPositive(int nNum)
{
	if (nNum < 0)
		return false;
	else
		return true;

}//	bool IsPositive(int nNum)
//=================================================
int main()
{
	int nNum;
	bool bResult;

	cout << "���� �Է� : ";
	cin >> nNum;

	bResult = IsPositive(nNum);

	if (bResult == true)
		cout << nNum << " (��)�� ���!!" << endl;
	else
		cout << nNum << " (��)�� ����!!" << endl;

	/*
		true�� false�� ���� int �� ������ 

		1, 0���� ������ ����ȯ�� �̷���.
	*/
	int boolValue = true;
	cout << "true == " << boolValue << endl;
	boolValue = false;
	cout << "false == " << boolValue << endl;

	return 0;

}//	int main()
//=================================================