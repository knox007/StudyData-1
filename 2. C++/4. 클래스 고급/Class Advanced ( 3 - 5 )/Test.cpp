//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[3 - 5]	상속과 다형성
//=================================================
/* 
	1.	상속을 해야하는 적절한 상황.

		-	IS - A 관계

			-	상속을 디자인할때 가장 기본적인 관계.

			-	"Student is Person" ( O )

				예)	class CStudent : public CPerson ( O )

				"Person is Student" ( X )

				예)	class CPerson : public CStudent ( X )

				-	Person 이라는 클래스를 통해 Student라는 클래스를 상속 받을수는 있지만

					Student를 상속 받아서 Person을 만드는 건 논리적으로도 맞지 않다.

				-	클래스 디자인은 현실 세계에 맞게 디자인 한다.



		-	HAS - A ( HAVE - A ) 관계

			-	소유 관계

			-	"Police has a gun"

			-	예제 소스 - 1)참고

			-	소유 관계를 상속으로 구현하게 되면

				필요없는 속성이 자식 클래스에 들어갈 수도 있다.

				-	대안은???

					-	예제 소스 - 2) 참고

	-	결론

		-	대부분의 상속은 IS - A 관계를 나타내기 위한 수단이어야 함.

*/
//=================================================
/*	예제 소스 - 1)
class CGun
{
public :
	void Shot() { cout<<"탕탕!!"<<endl; }
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
/*	예제 소스 - 2)
class CGun
{
public:
	void Shot() { cout << "탕탕!!" << endl; }
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
	2.	상속된 객체와 포인터( 레퍼런스도 마찬가지 )

		1)	A 클래스의 포인터는 A 객체의 주소값 뿐만 아니라

			A 를 상속하는 자식 클래스 객체의 주소값도 저장이 가능함.

		
		2)	A 의 객체 포인터는 A 클래스에 선언된 멤버와 

			A 가 상속한 클래스의 멤버에만 접근 가능.
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
	//	2)	CPerson*이 가리키는 대상은
	//		컴파일러 입장에선 CPerson 객체로 인식.
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