//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	팩토리 패턴
	---------------

		-	필요성

			-	서로 관련성이 있거나 책임이 같은 클래스들을 생성해주는 

				클래스를 객채생성과정 중간에 두어 복잡도를 줄인다.


			-	주로 부모 클래스가 같은 서로 다른 클래스를 생성할때 

				사용.
				
*/
//=================================================

//	부모 클래스.
class CWarrior
{
public:
	CWarrior() {};
	virtual ~CWarrior() {};
	virtual void Attack() { cout << "Warrior Attack" << endl; };

};

//	마린 클래스.
class CMarine : public CWarrior
{
public:
	CMarine() {};
	virtual ~CMarine() {};
	virtual void Attack() { cout << "Marine Attack" << endl; };
};

//	저그 클래스.
class CZerg : public CWarrior
{
public:
	CZerg() {};
	virtual ~CZerg() {};
	virtual void Attack() { cout << "Zerg Attack" << endl; };
};

//	프로토스 클래스.
class CProtos : public CWarrior
{
public :
	CProtos() {};
	virtual ~CProtos() {};
	virtual void Attack() { cout << "Protos Attack" << endl; };
};

//	병사 클래스 생성.(팩토리 패턴)
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
