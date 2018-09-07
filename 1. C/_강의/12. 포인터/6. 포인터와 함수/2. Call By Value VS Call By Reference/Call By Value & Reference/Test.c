//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	Call By Value	

		-	함수 호출시 매개변수로 단순히 값을 전달하는 형태의 호출 방식.

		-	값 전달 방식.

	2.	Call By Reference

		-	함수 호출시 매개변수로 메모리 접근에 사용되는 주소값을 전달하는 호출 방식.

		-	주소 전달 방식.

*/

/*	
//------------------
//	다음 예제의 문제점은?

//	그리고 바르게 작동시키도록 하려면?

//------------------
//	n1과 n2를 바꾸는 함수.
void Swap(int n1, int n2)
{
	int tmp = n1;
	n1 = n2;
	n2 = tmp;

	printf("n1 = %d,   n2 = %d\n", n1, n2);
}

int main(void)
{
	int n1 = 10;
	int n2 = 20;
	printf("n1 = %d,   n2 = %d\n", n1, n2);

	Swap(n1, n2);

	printf("n1 = %d,   n2 = %d\n", n1, n2);

	return 0;	
}
//*/
//======================================================












/*
void SwapPtr(int *pn1, int *pn2)
{
	int tmp = *pn1;
	*pn1 = *pn2;
	*pn2 = tmp;
}
*/


//======================================================
/*
	scanf의 원리 이해.

	예)
		int num;
		scanf("%d", &num);

		-	scanf는 변수 num의 주소로 접근하여 값을 채워넣는다.

		char szTmp[30];
		scanf("%s", szTmp);			
		
		-	scanf("%s", &szTmp);	( X )

		-	szTmp 자체가 주소값이기 때문.

			-	배열의 이름은 배열 첫 요소의 주소와 같다.

*/

//======================================================
/*
	quiz)
		세변수에 값을 바꾸는 함수를 만들자.

		Swap( &num1, &num2, &num3 );
				
		 num1	->	num2
		 num2	->	num3
		 num3	->	num1
*/










/*
void Swap(int *ptr1, int *ptr2, int *ptr3)
{
	int tmp = *ptr3;

	*ptr3 = *ptr2;
	*ptr2 = *ptr1;
	*ptr1 = tmp;
}

int main()
{
	int n1 = 10, n2 = 20, n3 = 30;

	printf("%d,  %d,  %d\n", n1, n2, n3);
	Swap(&n1, &n2, &n3);
	printf("%d,  %d,  %d\n", n1, n2, n3);

	return 0;
}

//*/