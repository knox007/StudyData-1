//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	Ŭ���� (���)
//	
//	[5 - 5]	�� ��.
//=================================================
/* 
	1 - 1.	���� ���.

		-	����

			-	�ϳ��� Ŭ������ 2�� �̻��� �θ� Ŭ�����κ���

				��� �޴� ��.

		-	������ ������� ����.

			-	Ŭ������ ���谡 �������� ���ɼ�.

			-	������ �����.

			-	���� ����� �ؾ߸� �ذ��� �� �ִ� ������ ����
				
				��ü ����.

		-	����
			
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
	1 - 2.	���� ����� ��ȣ��.

		��� 1)

			class CA { void Attack() { .... } }
			class CB { void Attack() { .... } }
			class CC : public CA, public CB { ..... }

			int main()
			{
				CC c;
				c.Attack();
			}

			-	�ذ�

				-	c.CA::Attack();



		��� 2)

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

			-	CD ���忡�� CA�� ���������� 2�� ����� ��.

				-	Attack1()�� 2�� ����.

				-	 void Attack()�� Attack1()�� CB�� ������, CC�� ������

					�ָŸ�ȣ.

			-	�ذ�

				-	�������� ��η� �ϳ��� Ŭ������ �ι� ����� ���� ����.

					-	�θ� �ѹ��� ��ӵǵ��� ����.

				-	class CB : virtual public CA { .... }
					class CC : virtual public CA { .... }

		-	���.

			-	������ ������� ����..!!!
*/
//=================================================
/*
	2.	������ �����ε�.

		-	ö��

			-	��ü�� �⺻�ڷ��� ����ó�� �������.

				-	�����ȣ�� �̿��� ����ó���� �����ϵ��� ����.


		-	����

			-	��ȯ��	operator ������ ( �Ű����� )

		-	���� ����

			1)	".", ".*", "::", "?:", "sizeof" ���� ����.

				-	C++�� ���� ��Ģ�� ��� ���� �����ϱ� ����.

			2)	�� �ǵ��� ��� ������ �����ε��� ����.

				-	+�����ڷ� -������ ������.

			3)	������ �켱 �켱 ������ ���ռ��� �ٲܼ��� ����.

			4)	����Ʈ �Ű� ���� ���� �Ұ���.

				-	int operator + ( int a = 3 )

			5)	�����ڵ��� �⺻ ����� ������ʰ� �Ѵ�.

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
	Quiz)	�� Ŭ������ ������ ��Ģ���굵 ������ �����ε��� �����Ѵ�.
*/