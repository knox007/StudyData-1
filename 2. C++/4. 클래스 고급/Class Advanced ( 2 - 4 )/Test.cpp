//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	Ŭ���� (���)
//	
//	[2 - 4]	��� �⺻����
//=================================================
/* 
	1.	�⺻ ����

		-	���	

			-	�ڽ� Ŭ������ �θ� Ŭ������ ��� ����Լ��� ���������

				�����޴� ��.

		-	��� �Ǵ� Ŭ����

			-	Super, Base, �θ�, ���� Ŭ���� ��.

			��ӹ޴� Ŭ����

			-	Sub, Derived, �ڽ�, ���� Ŭ���� ��.

		-	�⺻ ����

			-	���� Ŭ������ ����� ���� �����ϴ� Ŭ������ ����� ����.
*/
//=================================================
/*
class CPerson
{
	int _age;
	char _szName[20];

public:
	int GetAge() { return _age; }
	char* GetName() { return _szName; }
	CPerson(int age = 1, char *pszName = "None")
	//CPerson(int age, char *pszName )
	{
		_age = age;
		strcpy(_szName, pszName);
	}
};

class CStudent : public CPerson
{
	char _szMajor[30];

public :
	CStudent(char* pszMajor) { strcpy(_szMajor, pszMajor); }
	char* GetMajor() { return _szMajor; }

	void ShowData()
	{
		cout << "�̸� : " << GetName() << endl;
		cout << "���� : " << GetAge() << endl;
		cout << "���� : " << GetMajor() << endl;
	}
};

int main()
{
	CStudent Kim("����");
	Kim.ShowData();

	return 0;
}
//*/
/*
	�ҽ� ����

	1)	class CStudent : public CPerson

		-	CStudentŬ������ CPerson Ŭ������ ��� �޴´�( public ��� )

	2)	CStudent Ŭ������ CPerson�� �ִ� ����� ��� ����.
*/

//=================================================
/*
	2.	��ü ��������

		1)	�޸� ������ �Ҵ�( ��ӵǴ� Ŭ������ ���� )

		2)	�ڽ� Ŭ���� ������ ȣ��.

			-	ȣ���� ������ ��ü�κ��� ������� �ʴ´�.

			-	ȣ��� �����ڿ� ���Ͽ� �θ�Ŭ������ ��� �����ڰ�

				ȣ��Ǿ�� �Ѵٴ� ������ ���ٸ� �θ� Ŭ������ �⺻ �����ڰ� ȣ�� �� �����.

				-	�θ� Ŭ������ Ư�� �����ڸ� ȣ���Ϸ��� �θ� Ŭ������ �����ڸ� ��������� ȣ��.

					CChild( int a ) : CParent( a )ó�� ����Ѵ�.( ��� �̴ϼȶ����� )


		3)	�θ� Ŭ���� ������ ȣ�� �� ����.

		4)	�ڽ� Ŭ���� ������ ����.
*/
//=================================================
/*
class CParent
{
public:
	CParent() { cout << "CParent() ȣ��" << endl; }
	CParent(int a) { cout << "CParent(int a) ȣ��" << endl; }
};

class CChild : public CParent
{
public :
	CChild() { cout << "CChild() ȣ��" << endl; }
	CChild(int a) { cout << "CChild(int a) ȣ��" << endl; }
	//CChild(int a) : CParent( a ) { cout << "CChild(int a) ȣ��" << endl; }
};

int main()
{
	CChild child1;
	CChild child2(100);

	return 0;
}
//*/
//=================================================
/*
	Quiz)	���� CStudent ������ �̸��� ���̵� �Է� ������ �ֵ��� �����Ѵ�.
*/
//=================================================
/*
	3.	��ü �Ҹ� ����.

		-	�ڽ� Ŭ������ �Ҹ��ڰ� ȣ��� ��,

			�θ� Ŭ������ �Ҹ��ڰ� ȣ�� ��.

			-	�ڽ� Ŭ������ �θ� Ŭ������ �Ҹ��ڱ��� ȣ��.

				��ü �Ҹ�� �θ� Ŭ������ �����ڿ��� �Ҵ���

				�޸𸮱��� ������ ��ȸ�� ����.
*/
//=================================================
/*
class CParent
{
public:
	CParent() { cout << "CParent() ȣ��" << endl; }
	~CParent() { cout << "~CParent() ȣ��" << endl; }
};

class CChild : public CParent
{
public:
	CChild() { cout << "CChild() ȣ��" << endl; }
	~CChild() { cout << "~CChild() ȣ��" << endl; }
};

int main()
{
	CChild child;

	return 0;
}
//*/
//=================================================
/*
	4.	������ ������ ���

						|	public		|	protected	|	private		|
	---------------------------------------------------------------------
		public ���		|	public		|	protected	|	private		|
	---------------------------------------------------------------------
		protected ���	|	protected	|	protected	|	private		|
	---------------------------------------------------------------------
		private ���	|	���� �Ұ�	|	���� �Ұ�	|	���� �Ұ�	|
	---------------------------------------------------------------------

	->	private ����� ������ ���� �Ұ�.

		������ ����� ���κ��� ���� ������ ������ �ش� ��� ���·� ��ȯ�Ѵ�.

		->	private vs ���� �Ұ� ???
*/
//=================================================
/*
	Quiz)	

		���� ���� ������ �����ϴ� Ŭ����
		
		class CAccount
		{
			int _money;
			char _accNum[20];

			public :

			CAccount(char* pszAccNum, int money )
			{
				strcpy(_accNum, pAszAccnum);
				_money = money;
			}
		}

		CAccount�� ��ӹ޴� CKoreaAccount�� ����� ������ ���� ����ϴ� ���α׷� �ۼ�.

		��, CKoreaAccount�� ��ü�ѵ� ������ ������ �ִ�.

		int main()
		{
			CKoreaAccount korAcc("���¹�ȣ", 100, 1000(��ü�ѵ�) );

			korAcc.ShowData();

			return 0;
		}

		���

			���¹�ȣ : ....
			���� �ܾ� : ....
			��ü �ѵ� : ......
*/
//=================================================