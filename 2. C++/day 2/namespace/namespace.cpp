#include <iostream>
//----------------------------------------------
//	namespace : �̸� ������ ���� ����
//----------------------------------------------
/* ���� �߻�
void Test() { std::cout << "This is Test_A" << std::endl; }
void Test() { std::cout << "This is Test_B" << std::endl; }

int main()
{
	Test();
	return 0;
}
*/
//----------------------------------------------
// ���� ��
/*
//	namespace : �̸� ������ ���� ����
//	:: ���� ���� ������
//	2�� �̻��� �Լ��� ���� ���ǵ� ����.
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

using TEST_A::Test;	//	-> Test��� �̸��� �����ϴ� �ڵ�� TEST_A�� Test��� �̸��� �����Ѵ�.

int main()
{
	Test();	

	return 0;
}
*/

/* 2-2
namespace TEST_A { void Test() { std::cout << "This is Test_A" << std::endl; } }
namespace TEST_B { void Test() { std::cout << "This is Test_B" << std::endl; } }

using namespace TEST_A;	//	-> TEST_A�ȿ� ����Ǿ� �ִ� �̸��� �����ϴ� ��� �̸������� ���� ���� ���� �����Ѵ�.

int main()
{
	Test();

	return 0;
}
*/
//----------------------------------------------
//	::(���� ���� ������)�� �� �ٸ� �뵵
//----------------------------------------------
/*
// ���� �߻�
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
// ���� ��.
int val = 100;
int main()
{
	int val = 50;
	::val += 1;
	std::cout << "val = " << ::val << std::endl;
	
	return 0;
}
*/