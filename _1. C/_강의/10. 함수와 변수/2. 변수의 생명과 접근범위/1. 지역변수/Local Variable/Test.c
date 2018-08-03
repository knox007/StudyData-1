//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Local Variable
*/


/*
int TestOne()
{
	int num = 10;	//	2)	메모리 상에 num이 할당되고 10로 초기화.
	num++;
	printf("TestOne num : %d\n", num);

	return 0;		//	3)	반환후 num 소멸
}

int TestTwo()
{
	int num1 = 20;	//	4)	메모리 상에 num1, num2가 할당되고 각각 20,30으로 초기화.
	int num2 = 30;

	num1++, num2--;
	printf("TestTwo num1 : %d   num2 : %d\n", num1, num2);
	
	return 0;		//	5)	반환후 num1, num2 소멸
}

int main()
{
	int num = 30;	//	1)	메모리 상에 num이 할당되고 17로 초기화.
					//		main 함수내에서 생성되었으므로 main함수가 종료될때까지 
					//		메모리 상에 존재하게 됨.
	
	TestOne();
	TestTwo();

	printf("main() num : %d\n", num);
	
	return 0;		//	6)	반환후 num 소멸
}
//*/


/*
2.	Local Variable의 흐름에 따른 지역변수의 할당과 소멸

	-	번호 참고.

	-	지역변수는 해당 선언문이 실행될 때 메모리 공간에 할당,

		선언문이 존재하는 함수가 반환하거나 종료하면 메모리 공간에서 소멸된다.
*/
//======================================================
/*
3.	다양한 형태의 지역변수 (1)

	-	중괄호 내에 선언되는 변수는 모두 지역변수.

	-	반복문이나 조건문의 중괄호도 포함.
*/



/*

int main()
{
	int cnt;

	for (cnt = 0; cnt < 3; ++cnt)
	//for (int cnt = 0; cnt < 3; ++cnt)
	{
		int num = 0;	//	지역 변수 num 생성
						//	범위를 벗어나면 소멸.

		++num;

		printf("%d 번째 반복, 지역변수 num은 %d. \n", cnt + 1, num);

	}//	for (cnt = 0; cnt < 3; ++cnt)


	if (cnt == 3)
	{
		int num = 7;
		num++;

		printf("if문에 존재하는 지역변수 num은 %d \n", num);

	}//	if (cnt == 3)

	return 0;
}

//*/

//======================================================
/*
3.	다양한 형태의 지역변수 (2)

	-	지역변수는 외부에 선언된 동일한 이름의 변수를 가린다.

*/


/*
int main()
{
	int num = 1;

	if (num == 1)
	{
		int num = 7;	//	주석처리후 비교할것.
		num += 1;
		printf("if문안의 지역변수 num : %d\n", num);

	}//	if (num == 1)

	printf("main함수안의 지역변수 num : %d\n", num);

	return 0;

}
//*/

//======================================================
/*
3.	다양한 형태의 지역변수 (3)

	-	매개변수도 지역변수의 일종이다.

	
*/
//======================================================