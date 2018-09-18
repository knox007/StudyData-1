//==========================================
/*
	1.	C++ 기본 문법
		
		-	출력
*/
//==========================================
/*
	1)	c언어에서는 stdio.h를 포함.
		
		구버전에서는 iostream.h를 포함했으나

		신버전에서는 iostream으로 변경.
*/
#include <iostream>

int main()
{
	/*	2-1)	std::

			-	네임 스페이스 std

			-	범위 지정 연산자 ::

	*/
	
	/*	2-2)	출력함수	
			-	cout << 출력 대상;
	*/
	std::cout << "Hello World !! " << std::endl;

	/*	2-3)	출력 대상을 연속으로 표시가능.

				-	출력할 대상이 2이상이라면 << 연산자를 이용하여 연속으로 출력가능.

				-	cout << 출력 대상 1<< 출력 대상 2<< 출력 대상 3 ....
	*/
	/*
		3)	개행문자 endl;
	*/
	std::cout << "Hello " <<"World !!"<< std::endl;
	std::cout << 11 << 't' << "hStreet" << std::endl;

	return 0;
}




