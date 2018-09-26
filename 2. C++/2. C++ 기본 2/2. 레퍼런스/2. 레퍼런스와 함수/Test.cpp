//=====================================================
/*
	���۷����� �Լ�.

		-	�����Ϳ� ���� Call by Reference ���� ����.			
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
	���۷����� �̿��� ���� ���.
*/

typedef struct
{
	int _age;
	char _name[20];
	char _phoneNum[20];

} SPerson;


/*
	call by value ���
	
	-	�Ű����� p�� ���� �����Ѵ�.

		-	�� �������� ����Ǵ� ����Ʈ�� ����

			int(4byte) + char[20](20byte) + char[20](20byte) = 44byte.

	call by reference ��� ( by ���۷��� )
	
	-	�ش� ������ �̸��� �ϳ��� �߰��ϴ� ����̹Ƿ� ����� �߻����� ����.

	-	������ �Լ����ο��� ������ ���۷����� ������ ���ɼ��� ����.

		-	�ذ��� �����??

			-	���ȭ.
*/

//*
void ShowInfo(SPerson p)
//	void ShowInfo(SPerson &p)
{
	cout << "--- ���� ���� ---" << endl;
	cout << "�̸� : " << p._name << endl;
	cout << "��ȭ��ȣ : " << p._phoneNum<< endl;
	cout << "���� : " << p._age<< endl;
}

int main()
{
	SPerson person;

	cout << "�̸� : ";
	cin >> person._name;

	cout << "���� : ";
	cin >> person._age;

	cout << "��ȭ��ȣ : ";
	cin >> person._phoneNum;

	ShowInfo(person);
	return 0;
}
//*/
//=====================================================









