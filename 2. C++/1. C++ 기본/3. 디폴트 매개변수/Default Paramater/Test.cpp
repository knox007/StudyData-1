/*
	����Ʈ �Ű�����

	-	����

		-	��ȯŸ��	�Լ��̸�	(�Ű����� = �ʱⰪ)

	-	�Ű������� �������� ������ �Ű������� �ʱⰪ���� �Ҵ��� ���� ���޵ȴ�.
*/
#include<iostream>

using namespace std;

//*
int Func(int a = 0) { return a + 1; }
int main()
{
	cout << Func(10) << endl;
	cout << Func() << endl;

	return 0;
}
//*/


/*
	����Ʈ �Ű����� ����

	-	�Լ��� ������ �Լ� ���� ������ �����ϸ� 

		����Ʈ �Ű������� ����κп� ��ġ.

	-	�Ű������� 2�� �̻� ������
	
		����Ʈ �Ű������� �������� ��ġ.
	
*/

/*
int BoxVolume(int length, int width = 1, int height = 1);

int main()
{
	cout << "[3,3,3] : " << BoxVolume(3, 3, 3) << endl;
	cout << "[5,5,def] : " << BoxVolume(5,5) << endl;
	cout << "[7,def,def] : " << BoxVolume(7) << endl;


	return 0;
}

int BoxVolume(int length, int width, int height)
//int BoxVolume(int length, int width = 1, int height = 1)
{
	return length * width * height;
}
//*/

/*
	����Ʈ �Ű������� �Լ� �����ε�.
*/

/*
int Func()				{ return 10; }
int Func(int a = 10)	{ return a + 5; }

int main()
{
	cout << Func(10) << endl;
	//cout << Func() << endl;

	return 0;
}
//*/