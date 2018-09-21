//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	재귀 함수

	-	함수 내에서 자기 자신을 다시 호출하는 함수.


2.	형식

	-	void RecursiveFunc()
		{
			printf( "Recursive!!\n" );

			RecursiveFunc();
		}

	-	원리

		-	함수를 구성하는 명령문은 cpu로 복사가 되어 실행.

		-	함수 중간에 다시 자기 자신을 만나면 복사본을 cpu로 넘겨서 실행.

3.	주의 사항

	-	재귀함수를 정의할때 탈출조건을 명시할 것.
		
*/


/*
void Recursive(int num)
{
	if (num <= 0)
		return;

	printf("Recursive Call!! %d\n", num);

	Recursive(num - 1);
}

int main(void)
{
	Recursive(3);

	return 0;
}
//*/
//======================================================
/*
quiz)	입력한 수 이하 양의 정수의 합을 구하는 재귀 함수

*/















/*
int Recursive(int num)
{
	if (num == 0)
		return num;
	else
		return num + Recursive(num - 1);
}

int main(void)
{
	//int num = Recursive(100);
	int num = Recursive(3);

	printf("%d\n", num);

	return 0;
}
//*/