//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	팩토리 메소드
	---------------

		-	목적

			-	인터페이스는 부모 클래스에서 정하지만

				구체적인 객체 생성은 보다 적합한 자식 클래스에서 

				생성.

			-
			-----------------------------------------------------------------------------------------------------------------
								|	생성 기준	|	클래스 객체 수			|	객체 생성 방법								|
			-----------------------------------------------------------------------------------------------------------------
				팩토리			|	기능		|	단일 클래스 객체		|	객체 생성 함수.								|
			-----------------------------------------------------------------------------------------------------------------
				추상 팩토리		|	스타일		|	다중 클래스 객체 집합.	|	각 구성요소의 객체 생성 함수.				|
			-----------------------------------------------------------------------------------------------------------------
				팩토리 메소드	|	스타일		|	다중 클래스 객체 집합.	|	기본 클래스 또는 다른 클래스 상속 후 재정의	|
			-----------------------------------------------------------------------------------------------------------------
*/
//=================================================
/*
	Quiz)	툴바를 만들려고 한다.

			구성 요소는 테두리, 버튼, 구분자가 있다.

			테두리		-	얇은 테두리, 두꺼운 테두리, ....

			버튼		-	네모 버튼, 원형 버튼, ....

			구분자		-	수직 구분자, 물결 구분자, ....

			라고 할때, 

			
			기본툴바( 얇은 테두리, 원형 버튼, 수직 구분자 )

			두꺼운 툴바( 두꺼운 테두리, 원형 버튼, 수직 구분자 )

			네모 툴바( 얇은 테두리, 네모 버튼, 수직 구분자 )

			두꺼운 네모 툴바( 두꺼운 테두리, 네모 버튼, 수직 구분자 )

			......

			등을 만들려고 한다.


			팩토리 메소드를 이용하여 디자인해보자.
*/
//=================================================























/*
	1)	기본 툴바를 생성.

	2)	구성하려는 툴바를 만들기 위해 기본툴바나 다른 자식 클래스를 상속 받는다.

	3)	디자인이 다른 구성요소만 재정의한다.
*/



















/*
class CToolBar
{
	CFrame* _pFrame;
	CButton* _pButton;
	CSeperator* _pSeperator;

public :
	CToolBar() {};
	virtual ~CToolBar() {};

	virtual CFrame* CreateFrame() { return new CThinFrame(); }
	virtual CButton* CreateButton() { return new CCircleButton(); }
	virtual CSeperator* CreateSeperator() { return new CVerticalSeperator(); }

	virtual void Build()
	{
		_pFrame = CreateFrame();
		_pButton = CreateButton();
		_pSeperator = CreateSeperator();

		......
	}
};
*/