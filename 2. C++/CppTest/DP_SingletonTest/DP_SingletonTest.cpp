// DP_SingletonTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//



#include "stdafx.h"
#include "CTest.h"
#include "SingleTon.h"

int main()
{	
	// 문제 제기	
	ScoreManager scoreMgr;
	scoreMgr.AddScore(10);
	scoreMgr.ShowData();

	ScoreManager scoreMgr2;
	scoreMgr2.AddScore(10);
	scoreMgr2.ShowData();

    return 0;
}


// answer is as follows....

















/*
https://jackielee2.blog.me/10041855200
http://jackielee2.blog.me/10016894099

1. 싱글톤 패턴 용도.
- 전역 데이터 관리
: 클래스의 객체가 단 한 개여야만 할때.
: 매니저 클래스.

2. 구현
- 생성자를 Private이나 Protected로 만든다.
	- 외부에서 또다른 객체를 만들지 못하기 위해...

- static으로 자신을 가리키는 포인터 멤버변수(이하 A)를 private으로 만든다.
	- 전역메모리 관리를 위해...

- A를 관리하는 멤버함수를 만든다.
	- 전역 메모리 접근 및 해제를 위해...

- A를 초기화 한다.
*/









/*
ScoreManager *pScoreMgr1 = ScoreManager::getInstance();
ScoreManager *pScoreMgr2 = ScoreManager::getInstance();

pScoreMgr1->AddScore(10);
pScoreMgr1->ShowData();

pScoreMgr2->AddScore(10);
pScoreMgr2->ShowData();
ScoreManager::Destroy();
*/








/*
CTest *pTest1 = CTest::GetInstance();
CTest *pTest2 = CTest::GetInstance();
CTest *pTest3 = CTest::GetInstance();

pTest1->AddValue(10);
pTest1->ShowData();

pTest2->AddValue(10);
pTest2->ShowData();

pTest3->AddValue(10);
pTest3->ShowData();

CTest::DestroyInstance();
*/
