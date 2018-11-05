//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	���丮 ����
	---------------

		-	�ʿ伺

			-	���� ���ü��� �ְų� å���� ���� Ŭ�������� �������ִ� 

				Ŭ������ ��ä�������� �߰��� �ξ� ���⵵�� ���δ�.


			-	�ַ� �θ� Ŭ������ ���� ���� �ٸ� Ŭ������ �����Ҷ� 

				���.
				
*/
//=================================================

//	�θ� Ŭ����.
class CWarrior
{
public:
	CWarrior() {};
	virtual ~CWarrior() {};
	virtual void Attack() { cout << "Warrior Attack" << endl; };

};

//	���� Ŭ����.
class CMarine : public CWarrior
{
public:
	CMarine() {};
	virtual ~CMarine() {};
	virtual void Attack() { cout << "Marine Attack" << endl; };
};

//	���� Ŭ����.
class CZerg : public CWarrior
{
public:
	CZerg() {};
	virtual ~CZerg() {};
	virtual void Attack() { cout << "Zerg Attack" << endl; };
};

//	�����佺 Ŭ����.
class CProtos : public CWarrior
{
public :
	CProtos() {};
	virtual ~CProtos() {};
	virtual void Attack() { cout << "Protos Attack" << endl; };
};

//	���� Ŭ���� ����.(���丮 ����)
enum eWARRIOR
{
	MARINE,
	ZERG,
	PROTOS
};
class CWarriorFactory
{
public :
	CWarriorFactory() {};
	virtual ~CWarriorFactory() {};

	CWarrior * Create(eWARRIOR eWarrior);
};

CWarrior* CWarriorFactory::Create(eWARRIOR eWarrior)
{
	CWarrior* pWarrior = NULL;

	switch (eWarrior)
	{
	case eWARRIOR::MARINE:
		pWarrior = new CMarine();
		break;

	case eWARRIOR::ZERG:
		pWarrior = new CZerg();
		break;

	case eWARRIOR::PROTOS:
		pWarrior = new CProtos();
		break;		
	}

	return pWarrior;
}

int main()
{
	CWarriorFactory warriorFactory;

	CWarrior* pWarrior = warriorFactory.Create(eWARRIOR::MARINE);
	pWarrior->Attack();

	pWarrior = warriorFactory.Create(eWARRIOR::ZERG);
	pWarrior->Attack();

	pWarrior = warriorFactory.Create(eWARRIOR::PROTOS);
	pWarrior->Attack();

	return 0;
}
