//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	Ŭ���� (���)
//	
//	[3 - 5]	��Ӱ� ������
//=================================================
/* 
	1.	����� �ؾ��ϴ� ������ ��Ȳ.

		-	IS - A ����

			-	����� �������Ҷ� ���� �⺻���� ����.

			-	"Student is Person" ( O )

				��)	class CStudent : public CPerson ( O )

				"Person is Student" ( X )

				��)	class CPerson : public CStudent ( X )

				-	Person �̶�� Ŭ������ ���� Student��� Ŭ������ ��� �������� ������

					Student�� ��� �޾Ƽ� Person�� ����� �� �������ε� ���� �ʴ�.

				-	Ŭ���� �������� ���� ���迡 �°� ������ �Ѵ�.



		-	HAS - A ( HAVE - A ) ����

			-	���� ����

			-	"Police has a gun"

			-	���� �ҽ� - 1)����

			-	���� ���踦 ������� �����ϰ� �Ǹ�

				�ʿ���� �Ӽ��� �ڽ� Ŭ������ �� ���� �ִ�.

				-	�����???

					-	���� �ҽ� - 2) ����

	-	���

		-	��κ��� ����� IS - A ���踦 ��Ÿ���� ���� �����̾�� ��.

*/
//=================================================
/*	���� �ҽ� - 1)
class CGun
{
public :
	void Shot() { cout<<"����!!"<<endl; }
};

class CPolice : public CGun
{
public :
	void UseWeapon() { Shot(); }
};

int main()
{
	CPolice police;

	police.UseWeapon();

	return 0;
}
//*/
//=================================================
/*	���� �ҽ� - 2)
class CGun
{
public:
	void Shot() { cout << "����!!" << endl; }
};

class CPolice
{
	CGun* _pGun;
public :
	CPolice() { _pGun = new CGun; }
	~CPolice() { delete _pGun; }
	void UseWeapon() { _pGun->Shot(); }
};

int main()
{
	CPolice police;
	police.UseWeapon();

	return 0;
}

//*/
//=================================================
/*
	2.	��ӵ� ��ü�� ������( ���۷����� �������� )

		1)	A Ŭ������ �����ʹ� A ��ü�� �ּҰ� �Ӹ� �ƴ϶�

			A �� ����ϴ� �ڽ� Ŭ���� ��ü�� �ּҰ��� ������ ������.

		
		2)	A �� ��ü �����ʹ� A Ŭ������ ����� ����� 

			A �� ����� Ŭ������ ������� ���� ����.
*/
//=================================================
/*
class CPerson
{
public :
	void Sleep() { cout << "Zzz.." << endl; }
};

class CStudent : public CPerson
{
public:
	void Study() { cout << "Study!!" << endl; }
};

class CPartStudent : public CStudent
{
public:
	void Work() { cout << "Work!!" << endl; }
};

int main()
{
	//--------------------------
	//	1)
	CPerson* p1 = new CPerson;
	CPerson* p2 = new CStudent;
	CPerson* p3 = new CPartStudent;
	//--------------------------

	p1->Sleep();
	p2->Sleep();
	p3->Sleep();

	//--------------------------
	//	2)	CPerson*�� ����Ű�� �����
	//		�����Ϸ� ���忡�� CPerson ��ü�� �ν�.
	//p1->Study();
	//p1->Work();

	//CStudent* student = new CStudent;
	//student->Sleep();
	//student->Study();
	//delete student;
	//--------------------------
		
	delete p1;
	delete p2;
	delete p3;

	return 0;
}
//*/
//=================================================