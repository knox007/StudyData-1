//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[5 - 5]	그 외.
//=================================================
/* 
	1 - 1.	다중 상속.

		-	정의

			-	하나의 클래스가 2개 이상의 부모 클래스로부터

				상속 받는 것.

		-	가급적 사용하지 말것.

			-	클래스의 관계가 복잡해질 가능성.

			-	관리의 어려움.

			-	다중 상속을 해야만 해결할 수 있는 문제는 없음
				
				대체 가능.

		-	선언
			
			class CDad
			{
				.......
			};

			class CMom
			{
				......
			};

			class CChild : public CDad, public CMom
			{
				......
			}

*/
//=================================================
/*
	1 - 2.	다중 상속의 모호성.

		사례 1)

			class CA { void Attack() { .... } }
			class CB { void Attack() { .... } }
			class CC : public CA, public CB { ..... }

			int main()
			{
				CC c;
				c.Attack();
			}

			-	해결

				-	c.CA::Attack();



		사례 2)

			class CA { void Attack1(){ ... } }
			class CB : public CA { void Attack2(){ ... } }
			class CC : public CA { void Attack3(){ ... } }
			class CD : public CB, public CC
			{
				void Attack()
				{
					Attack1();
					Attack2();
					Attack3();
				}
			}

			main()
			{
				CD cd;
				cd.Attack();
			}

			-	CD 입장에선 CA를 간접적으로 2번 상속한 셈.

				-	Attack1()을 2개 지님.

				-	 void Attack()의 Attack1()은 CB의 것인지, CC의 것인지

					애매모호.

			-	해결

				-	간접적인 경로로 하나의 클래스를 두번 상속한 것이 원인.

					-	부모가 한번만 상속되도록 유도.

				-	class CB : virtual public CA { .... }
					class CC : virtual public CA { .... }

		-	결론.

			-	가급적 사용하지 말자..!!!
*/
//=================================================
/*
	2.	연산자 오버로딩.

		-	철학

			-	객체도 기본자료형 변수처럼 취급하자.

				-	연산기호를 이용한 연산처리가 가능하도록 지원.


		-	형식

			-	반환형	operator 연산자 ( 매개변수 )

		-	주의 사항

			1)	".", ".*", "::", "?:", "sizeof" 등은 제외.

				-	C++의 문법 규칙을 어느 정도 보존하기 위함.

			2)	본 의도를 벗어난 연산자 오버로딩은 지양.

				-	+연산자로 -연산은 비상식적.

			3)	연산자 우선 우선 순위와 결합성을 바꿀수는 없음.

			4)	디폴트 매개 변수 설정 불가능.

				-	int operator + ( int a = 3 )

			5)	연산자들의 기본 기능을 벗어나지않게 한다.

				-	int operator ( int a, int b )
					{
						return a + b + 20;
					}
*/
//=================================================
/*
class CPoint
{
	int _x, _y;
public :
	CPoint(int x = 0, int y = 0) { _x = x, _y = y; }
	CPoint operator + (int val)
	{
		CPoint tmp(_x + val, _y + val);
		return tmp;
	}
	void ShowData() { cout << _x << " " << _y << endl; }
};

int main()
{
	CPoint pt(1, 2);
	CPoint tmp = pt.operator+(10);
	//CPoint tmp = pt + 10;
	tmp.ShowData();

	return 0;
}
//*/
//=================================================
/*
	Quiz)	위 클래스에 나머지 사칙연산도 연산자 오버로딩을 적용한다.
*/