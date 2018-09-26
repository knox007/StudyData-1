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

/*

typedef struct
{
	int _age;
	char _name[20];
	char _phoneNum[20];

} SPerson;


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
/*
	���۷����� �����ϴ� �Լ�	
*/

/*
//	�߸��� ����

int& Func()
{	
	int val = 10;
	
	//	"���������� �ڵ��ϰ� ������ �Բ��Ѵ�!!!"
	//	-	val�� Func�Լ��� ����� �Բ� �޸𸮿��� �������.

	return val;
}

int main()
{
	int &ref = Func();
	//	ref��� �̸��� �پ� �ִ� �޸� ������ ��������ȴ�.
			
	cout << ref << endl;
	//	���������� ����� �Ǿ����ϴ��� �ŷ��� �� ���� ���� �ǹ���.

	return 0;
}
//*/
//=====================================================
//	������ ����

/*
int& Func(int &val)	//	2.	val1�� val�̶�� �̸��� �߰���.
{
	val++;
	return val;	//	3.	val�̶�� �̸��� �����.
				//		-	�޸� ������ ������� ���� �ƴ�.
}

int main()
{
	//	1.	val1 �̶�� �޸� ���� �Ҵ�.
	int val1 = 10;
	int &ref = Func(val1);	//	4. ref��� �̸��� �߰���.

	cout << "val1 = " << val1 << endl;
	cout << "ref = " << ref << endl;

	return 0;
}
//*/
//=====================================================









