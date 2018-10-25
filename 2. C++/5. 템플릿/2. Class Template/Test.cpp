//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	Ŭ���� ���ø�
	---------------
*/
//=================================================
/*
class CData
{
	int _data;
public:
	CData(int d) { _data = d; }

	void SetData(int d) { _data = d;  }

	int GetData() { return _data; }
};

int main()
{
	CData d1(0);
	d1.SetData(10);

	CData d2(100);

	cout << d1.GetData() << endl;
	cout << d2.GetData() << endl;
	
	return 0;
}
//*/
//=================================================
/*	�� �ҽ��� ���ø�ȭ.
template <typename T>
class CData
{
	T _data;

public:
	CData(T d) { _data = d; }

	void SetData(T d) { _data = d; }

	T GetData() { return _data; }

};


int main()
{
	CData<int> d1(0);
	d1.SetData(10);

	CData<char> d2('a');

	cout << d1.GetData() << endl;
	cout << d2.GetData() << endl;

	return 0;
}
//*/
//=================================================
/*
	�Լ� ���ø����� �޸� Ŭ���� ���ø��� ������� ��ü ������
	
	�ڷ����� ��������� ��������� ��.

	-	����

		-	��ü ������

			1)	�޸� ���� �Ҵ�.

			2)	������ ȣ��.

			3)	���� ���ڸ� �����ؼ� T�� �ڷ��� ����.

				1)	�޸� ������ �Ҵ��� ���� �Ͼ�Ƿ� 

					T�� �ڷ����� �� ���� ��������� �˷���� ��.

				2)	�����ڸ� ���� ���޵Ǵ� ������ �ڷ�����

					�����Ǿ�� �� ���ø��� �ڷ����� �ٸ� ���� ����.
*/
//=================================================
