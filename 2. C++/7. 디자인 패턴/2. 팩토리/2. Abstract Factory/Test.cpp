//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	�߻� ���丮
	---------------

		-	�ʿ伺
			
			-	���ü� �ִ� ��ü ������ �����ϴ� �������̽��� �����ϴ� ���.

			-	��Ʈ�� �߽��� ���丮�� �ƴ� ��Ÿ�� �߽��� ���丮�� �ַ� ����.
				
*/
//=================================================
/*
	Quiz)
		1)	�׸� ��ư, �� ��ư, ���� ��ư�� ����� �ٸ� ��ư���� 
			
			�����ؾ� �� ��� ���丮 ������ �����ؾ��Ѵٸ� ��� �ؾ��ϳ�?


		2)	1)�� ���� ���� �ٸ� ��ư �� �ƴ϶� �ؽ�Ʈ �ڽ�, ���α׷��� �� ��

			UI ��Ʈ���� Ÿ�԰� ����� ���������� ���°� ���� �ٸ� UI�� �̿��Ͽ�

			������ UI�� ����� ��� �߻� ���丮 ������ �����ؾ��Ѵٸ� ��� �ؾ��ϳ�?
*/
//=================================================



/*
	---------------------------------------------
	CRectButton				CStarButton
	---------------------------------------------
	CRectTextBox			CStarTextBox
	---------------------------------------------
	CRectProgress			CStarProgress
	---------------------------------------------

						vs

	---------------------------------------------
	CRectButton			|	CStarButton
	---------------------------------------------
	CRectTextBox		|	CStarTextBox
	---------------------------------------------
	CRectProgress		|	CStarProgress
	---------------------------------------------
*/

























/*
//	������ UI �θ� Ŭ����.
class IUIFactory
{
public :
	virtual CBaseButton* CreateButton() = 0;
	virtual CBaseTextBox* CreateTextBox() = 0;
	virtual CBaseProgressBar* CreateProgressBar() = 0;
	virtual void Display()
	{
		CBaseButton* pButton = CreateButton();
		CBaseTextBox* pTextBox = CreateTextBox();
		CBaseProgressBar* pProgressBar = CreateProgressBar();

		......
	}
};

class CRectControl : IUIFactory
{
public:
	virtual CRectButton* CreateButton() { return new CRectButton();}
	virtual CRectTextBox* CreateTextBox() { return new CRectTextBox ();	}
	virtual CRectProgressBar* CreateProgressBar() { return new CRectProgressBar(); }
};

class CStarControl : IUIFactory
{
public:
	virtual CStarButton* CreateButton() { return new CStarButton(); }
	virtual CStarTextBox* CreateTextBox() { return new CStarTextBox(); }
	virtual CStarProgressBar* CreateProgressBar() { return new CStarProgressBar(); }
};

....
*/