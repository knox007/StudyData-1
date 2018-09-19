
/*
	namespace ( 이름공간 )
	
	-	설명.
	
		-	특정영역의 범위를 지정하고 이름을 붙여준것.

		-	이름공간이 다르면 같은 이름의 변수나 함수의 선언이 허용.


	-	등장배경.

		-	프로그램의 대형화가 되어가며 이름충돌에 대한 문제 발생.

			예)	
			
				1)	은행관리 시스템을 개발하는데 A,B,C라는 회사가 참여.

				2)	각각 작업파트를 나눠 독립적으로 진행후 한개의 프로젝트로 

					합치기로 결정.

				3)	각각의 회사가 구현한 모듈을 하나로 묶고 수정보완하기 시작.

				4)	문제 발생!!
				
					-	A 회사에서 만든 함수중 일부의 이름이 B 회사에서 만든 함수의 이름과

						똑같아 충돌 발생.

					-	C 회사에서 작업한 소스 일부중 다른 회사의 함수를 차용해서 사용했는데

						그 중 일부가 A, B 회사의 함수와 이름이 같아 충돌 발생.

	-	선언 방법.

		-	namespace 영역이름
			{
				구현.
			}

*/


#include <iostream>

namespace COMPANY_A
{
	void Func()	{ std::cout << "A 회사 함수" << std::endl; }
}

namespace COMPANY_B
{
	void Func() { std::cout << "B 회사 함수" << std::endl; }
}

int main()
{
	/*
		::( 범위 지정 연산자 )

		-	COMPANY_A::Func()

			-	COMPANY_A라는 namespace에 선언되어 있는 Func() 호출.

		-	전역변수에 접근용.

			예)	::val = 100;

				
	*/
	COMPANY_A::Func();
	COMPANY_B::Func();

	return 0;
}

/*
	std::cout, std::cin, std::endl

	-	std라는 이름 공간에 존재.
*/