/*
	---------------
	1.	인라인 함수
	---------------

		1.	매크로 함수의 정의와 장점

			예)	
			
				#define SQUARE(x)	((x) * (x))
				int main()
				{
					cout << SQUARE(5) << endl;
					return 0;
				}

				위의 코드는 전처리과정으로 통해

				int main()
				{
					cout << ((5) * (5)) << endl;
					return 0;
				}
				
				로 변경됨.

			-	전처리기에 의해 함수 호출 문장이 함수의 몸체 부분으로 완전히 대치되버림.

				-	함수의 인라인화.

					-	장점

						-	함수호출과정이 사라지므로 성능상의 이점 발생.

							-	함수호출은 스택 메모리 공간의 할당을 요구하며 그에 대한 시간이 소요됨.

					-	단점

						-	함수의 구현이 까다롭고 디버깅이 어려움.

						-	구현하고자하는 함수의 크기가 크다면 프로그램의 크기도 커짐.

							-	구현 내용의 소스가 그대로 대치되기 때문.

		2.	참고

			컴파일러에 따라서 inline 선언이 오히려 성능 향상에 해가 된다고 판단될 경우,

			그냥 무시하기도 함.

*/
#include<iostream>

using namespace std;

inline int SQUARE(int x)
{
	return x * x;
}

int main()
{
	cout << SQUARE(5) << endl;

	return 0;
}
 