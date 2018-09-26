//=====================================================
/*
	레퍼런스와 함수.

		-	포인터와 같이 Call by Reference 구현 가능.			
*/
//=====================================================
#include<iostream>
using namespace std;
//=====================================================
/*
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int val1 = 10;
	int val2 = 20;

	cout << "--- before ---" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;

	Swap(val1, val2);

	cout << "--- after ---" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;

	return 0;
}
//*/
//=====================================================
/*
	레퍼런스를 이용한 성능 향상.
*/

typedef struct
{
	int _age;
	char _name[20];
	char _phoneNum[20];

} SPerson;


/*
	call by value 방식
	
	-	매개변수 p에 값을 복사한다.

		-	이 과정에서 복사되는 바이트의 수는

			int(4byte) + char[20](20byte) + char[20](20byte) = 44byte.

	call by reference 방식 ( by 레퍼런스 )
	
	-	해당 변수에 이름만 하나더 추가하는 방식이므로 복사는 발생하지 않음.

	-	하지만 함수내부에서 여전히 레퍼런스를 변경할 가능성은 존재.

		-	해결할 방법은??

			-	상수화.
*/

//*
void ShowInfo(SPerson p)
//	void ShowInfo(SPerson &p)
{
	cout << "--- 개인 정보 ---" << endl;
	cout << "이름 : " << p._name << endl;
	cout << "전화번호 : " << p._phoneNum<< endl;
	cout << "나이 : " << p._age<< endl;
}

int main()
{
	SPerson person;

	cout << "이름 : ";
	cin >> person._name;

	cout << "나이 : ";
	cin >> person._age;

	cout << "전화번호 : ";
	cin >> person._phoneNum;

	ShowInfo(person);
	return 0;
}
//*/
//=====================================================









