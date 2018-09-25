//=================================================
/*
	bool 형 변수

	-	c++에서 추가된 기본 자료형.

	-	true와 false 의 값만 관리.

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

	cout << "숫자 입력 : ";
	cin >> nNum;

	bResult = IsPositive(nNum);

	if (bResult == true)
		cout << nNum << " (은)는 양수!!" << endl;
	else
		cout << nNum << " (은)는 음수!!" << endl;

	/*
		true와 false는 각각 int 형 정수로 

		1, 0으로 묵시적 형변환이 이뤄짐.
	*/
	int boolValue = true;
	cout << "true == " << boolValue << endl;
	boolValue = false;
	cout << "false == " << boolValue << endl;

	return 0;

}//	int main()
//=================================================