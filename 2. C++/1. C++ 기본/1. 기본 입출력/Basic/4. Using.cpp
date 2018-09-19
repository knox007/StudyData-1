/*
	using namespace 영역이름;

	-	해당 namespace안에 선언되어있는 변수나 함수를

		namespace에 대한 선언 없이 사용.
*/

/*
#include <iostream>

using namespace std;

int main()
{
	cout << "Hello World !! " << endl;
	cout << "Hello " << "World !!" << endl;
	cout << 11 << 't' << "hStreet" << endl;

	return 0;
}
//*/



/*
	" 지역변수는 전역변수를 가린다 !!! "
*/

#include <iostream>

using namespace std;

int val = 100;

int main()
{
	int val = 50;
	 
	val += 1;

	printf("%d\n", val);

	return 0;
}