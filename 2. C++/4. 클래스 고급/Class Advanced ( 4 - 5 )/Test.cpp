//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	Ŭ���� (���)
//	
//	[4 - 5]	�������̵�.
//=================================================
/* 
	1.	�Լ� �������̵�.

		-	�θ� Ŭ�������� ����� ����Լ���

			�ڽ� Ŭ�������� ������.

		-	�ڽ� Ŭ�������� �����ǵ� �Լ��� 

			�θ� Ŭ������ ������ �Լ��� ������.

			-	������ �þ߸� �޸��ϸ� ���� �ִ�.

				->	�þ� = ������ ����.

*/
//=================================================
/*
class CPerson
{
	public :
		void Sleep() { cout << "CPerson Zzz.." << endl; }
};

class CStudent : public CPerson
{
	public:
		void Sleep() { cout << "CStudent Zzz.." << endl; }
		void Study() { cout << "Study!!" << endl; }
};


int main()
{
	CPerson* pPerson = new CPerson;
	CStudent* pStudent = new CStudent;
	
	pPerson->Sleep();
	pStudent->Sleep();	//	�θ�� ������ �Լ��� ������.

	CPerson* pPerson2 = pStudent;
	pPerson2->Sleep();

	delete pPerson;
	delete pStudent;
	pStudent = NULL;
	
	//delete pPerson2;	//	e!!!!!

	return 0;
}
//*/
//=================================================
/*
	2 - 1.	virtual	����.
		
		-	����

			-	virtual  ��ȯ��  �Լ��̸� ( �Ű�������� );

		-	����
		
			-	����Լ��� �������� �����ϴ� �����ν�,

				virtual Ű���带 �̿��Ͽ� �������� ���ε�.

				-	���ε�

					-	���� ������ Ȯ���Ǿ� ���̻� ������ �� ���� ���� ���°� �Ǵ� ��.

				-	���� ���ε�

					-	����ð�( ��Ÿ�� )�� ���ε��� ����.

					-	�Ϲ������� �����ͷ� �ּҸ� �Ҵ��Ͽ� �۾� �ϴ� ���.

				-	���� ���ε�

					-	������ �ð��� ���ε� ����.

		-	 Ư¡

			-	�θ� Ŭ������ �����ͷ� ����Ű�� �ڽ��� �����ͷ� ����Ű��

				�������̵��� �ڽ� Ŭ������ �Լ��� ȣ��.

			-	�̹� ����� �Լ�( �������̵� �� �Լ� )�� �������� �ʴ� �Լ�ó�� ���.

			-	���� �Լ��� �Ӽ��� ��� ��.

				-	virtualŰ���带 ����ϴ� ������� �ʴ� virtual �� ����ȴ�.

				-	�ҽ� ���ص��� ���������� virtual Ű���带 ��������.
*/
//=================================================
/*
class CParent
{
public:
	virtual void SayHello() { cout << "�� �θ�" << endl; }
};

class CChild : public CParent
{
public:
	virtual void SayHello() { cout << "�� �ڽ�" << endl; }
};

int main()
{
	CChild* pChild = new CChild;
	pChild->SayHello();

	CParent* pParent = pChild;
	pParent->SayHello();

	delete pChild;

	return 0;
}
//*/
//=================================================
/*
	2 - 2.	virtual	����.

		-	�������̵� �� �Լ� ȣ��.

			-	virtual ����� �Լ��� �����ʴ´�.

				�ٸ� ������ ���̴�.

*/
//=================================================
/*
class AAA
{
public:
	virtual void Func() { cout << "AAA" << endl; }
};

class BBB : public AAA
{
public:
	virtual void Func()
	{
		AAA::Func();				//	1)
		cout << "BBB" << endl;
	}
};

int main()
{
	AAA* pA = new BBB;

	cout << "-- First Test --" << endl;
	pA->Func();

	cout << "-- Second Test --" << endl;
	pA->AAA::Func();				//	2)
	
	delete pA;

	return 0;
}
//*/

/*
	��� 1)

		-	��Ȳ�� ���� ����.

		-	�ڽ� Ŭ�������� Ư������� �����ϱ�����

			�������� ó���ؾ��� �κ��� ������ ����.

	��� 2)

		-	���� ������� ����.

		-	Ŭ���� ������ ��ü�� �����ؾ��� ������ �ִ��� 

			����� �ʿ� ����.
*/
//=================================================
/*
	3.	���� �����Լ��� �߻� Ŭ����.

		1)	���� ���� �Լ�
			
			-	����

				-	virtual void SayHello() = 0;
				
			-	��¥�� �������� �ʴ� ( �Լ��� ��ü�� �������� �ʴ� )������ �Լ�.

			-	���� �ϰ� ���� ���� ����.

		
		2)	�߻� Ŭ����

			-	���� ���� �Լ��� �ϳ� �̻� �ִ� Ŭ����.

			-	��üȭ ���� ����.

				������ �ν��Ͻ��� ������ ����.

				-	�Լ��� ���ǰ� �����Ǿ����Ƿ�( ���� �����Լ��� ��������� )

					������ Ŭ������ �ƴ�.
			
			-	��üȭ�� �ʿ䰡 ���� Ŭ�����̹Ƿ�

				�������̽��� ��ɸ� �� ��.
				
*/
//=================================================
/*
class CAnimal
{
protected:
	char _szName[30];

public:
	CAnimal(char* pszName) { strcpy(_szName, pszName); }
	const char* GetName() { return _szName; }
	virtual void MakeVoice() = 0;		// ���� �����Լ�.
};

int main()
{
	CAnimal animal("Cat");

	animal.MakeVoice();

	return 0;
}
//*/
//=================================================
/*
	Quiz - 1)	���� CAnimal�� ��ӹ޴� ���� Ŭ������ �����ѵ�
	
				�� �������� �̸��� �����Ҹ�( MakeVoice() )�� ����ϴ� ���α׷��� �����.

*/
//=================================================
/*
	4.	virtual �Ҹ���
*/
//=================================================
/*
class CParent
{
public :
	~CParent() { cout << "~CParent" << endl; }
};

class CChild : public CParent
{
public :
	~CChild() { cout << "~CChild" << endl; }
};

int main()
{
	CParent* pParent = new CChild();
	CChild* pChild = new CChild();

	delete pParent;
	delete pChild;

	return 0;
}
//*/

/*
	�м�
	
		-	pParent�� CChild Ÿ���� ��ü�� ����Ű�� ������

			CParent Ÿ���� �����ͷ� ����Ű�� �����Ƿ�

			CChild ��ü�� CPaent��ü�� �ν�.

	�ذ�

		-	~CParent()�� virtual�� ����.

		-	����.

			1)	CParent �Ҹ��� ȣ�� �õ�.

			2)	�Ҹ��ڰ� virtual �̹Ƿ� CChild �Ҹ��ڸ� ȣ��.

				-	��� �̸��� �ٸ�����( ~CParent(), ~CChild() )

					�Ѵ� �Ҹ����� ����� virtual �Լ��� �������̵� ��������

					������ �״�� ����.

			3)	CChild�� �Ҹ��ڴ� CParent�� ��ӹ����Ƿ� �ٽ� CParent�� �Ҹ��� ȣ��.

*/
//=================================================
/*
	Quiz - 2)
		
		�ٷ����� �̸��� �޿��� �����ϴ� ���α׷��� �����.

		1)	�߻�Ŭ������ �ٷ��� Ŭ������ �����,

			������, �Ͽ���, ��ƮŸ���� �ڽ� Ŭ������ �����.

		2)	�ٷ��� �Ŵ��� ���α׷��� �����.

			�ٷ��� �Ŵ����� �ٷ��ڸ� ����ϰ� ��ȸ�ϴ� ����� �ִ´�.

			�Ŵ����� �ٷ��ڸ� �ִ� 10�� ����ϵ��� �Ѵ�.

		
			������ - ����.

			�Ͽ��� - �ٹ� �ϼ� * �ϴ�.

			��Ʈ Ÿ�� - �� �ٹ� �ð� * �ð� ����.


		����)

			--- �ٷ��� ��� ---

			�̸� : �豸��

			1) ������	2) �Ͽ���	3) ��ƮŸ��
			���Ÿ�� : 1

			���� : 100

			
			--- �ٷ��� ��� ---

			�̸� : ���缮

			1) ������	2) �Ͽ���	3) ��ƮŸ��
			���Ÿ�� : 3

			�� �ٹ� �ð� : 10
			�ð����� : 3


			-- ��ȸ --

			1) �豸��	������		100����
			2) ���缮	��ƮŸ��	30����



*/




























































/*	Quiz - 1)
class CAnimal
{
	protected:
		char _szName[30];

	public:
		CAnimal(char* pszName) { strcpy(_szName, pszName); }
		const char* GetName() { return _szName; }
		virtual void MakeVoice() = 0;		// ���� �����Լ�.
};


class CCat : public CAnimal
{
	public:
		CCat(char *pszName) : CAnimal(pszName) {}
		virtual void MakeVoice() { cout << "Meow" << endl; }
};


class CDog : public CAnimal
{
public:
	CDog(char *pszName) : CAnimal(pszName) {}
	virtual void MakeVoice() { cout << "BowWow" << endl; }
};



int main()
{
	CCat cat("Nero");
	CDog dog("Baduk");

	CAnimal* pAnimal[2] = { &cat, &dog };

	for (int i = 0; i < 2; i++)
	{
		cout <<"�̸� : "<<pAnimal[i]->GetName() << endl;
		cout << "�Ҹ� : ";
		pAnimal[i]->MakeVoice();
		cout << endl;
	}

	return 0;
}
//*/