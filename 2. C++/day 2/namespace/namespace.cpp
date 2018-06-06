#include <iostream>
//----------------------------------------------
//	namespace : 이름 공간의 범위 설정
//----------------------------------------------
/* 문제 발생
void Test() { std::cout << "This is Test_A" << std::endl; }
void Test() { std::cout << "This is Test_B" << std::endl; }

int main()
{
	Test();
	return 0;
}
*/
//----------------------------------------------
// 수정 후
/*
//	namespace : 이름 공간의 범위 설정
//	:: 범위 지정 연산자
//	2개 이상의 함수및 변수 정의도 가능.
namespace TEST_A { void Test()	{ std::cout << "This is Test_A" << std::endl; } }
namespace TEST_B { void Test()	{ std::cout << "This is Test_B" << std::endl; } }

int main()
{
	TEST_A::Test();
	TEST_B::Test();

	return 0;
}
*/




//----------------------------------------------
//	using
//----------------------------------------------
/* 1-2
namespace TEST_A { void Test() { std::cout << "This is Test_A" << std::endl; } }
namespace TEST_B { void Test() { std::cout << "This is Test_B" << std::endl; } }

using TEST_A::Test;	//	-> Test라는 이름을 참조하는 코드는 TEST_A의 Test라는 이름을 참조한다.

int main()
{
	Test();	

	return 0;
}
*/

/* 2-2
namespace TEST_A { void Test() { std::cout << "This is Test_A" << std::endl; } }
namespace TEST_B { void Test() { std::cout << "This is Test_B" << std::endl; } }

using namespace TEST_A;	//	-> TEST_A안에 선언되어 있는 이름을 참조하는 경우 이름공간에 대한 선언 없이 참조한다.

int main()
{
	Test();

	return 0;
}
*/
//----------------------------------------------
//	::(범위 지정 연산자)의 또 다른 용도
//----------------------------------------------
/*
// 문제 발생
int val = 100;
int main()
{
	int val = 50;
	val += 1;
	std::cout << "val = " << val << std::endl;

	return 0;
}
*/

/*
// 수정 후.
int val = 100;
int main()
{
	int val = 50;
	::val += 1;
	std::cout << "val = " << ::val << std::endl;
	
	return 0;
}
*/