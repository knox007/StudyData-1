//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	추상 팩토리
	---------------

		-	필요성
			
			-	관련성 있는 객체 집합을 생성하는 인터페이스를 제공하는 방법.

			-	컨트롤 중심의 팩토리가 아닌 스타일 중심의 팩토리에 주로 적용.
				
*/
//=================================================
/*
	Quiz)
		1)	네모 버튼, 별 버튼, 세모 버튼등 모양이 다른 버튼들을 
			
			생성해야 할 경우 팩토리 패턴을 적용해야한다면 어떻게 해야하나?


		2)	1)과 같이 서로 다른 버튼 뿐 아니라 텍스트 박스, 프로그래스 바 등

			UI 컨트롤의 타입과 기능은 동일하지만 형태가 서로 다른 UI를 이용하여

			윈도우 UI를 만드는 경우 추상 팩토리 패턴을 적용해야한다면 어떻게 해야하나?
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
//	윈도우 UI 부모 클래스.
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