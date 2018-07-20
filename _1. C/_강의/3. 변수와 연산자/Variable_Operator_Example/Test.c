#include <stdio.h>

//======================================================
/*	1.	대입연산자, 산술 연산자 ( =, +, -, *, /, % )

int main(void)
{
	int n1 = 10, n2 = 3;

	printf("%d + %d = %d\n", n1, n2, n1 + n2);
	printf("%d - %d = %d\n", n1, n2, n1 - n2);
	printf("%d * %d = %d\n", n1, n2, n1 * n2);
	printf("%d - %d = %d\n", n1, n2, n1 / n2);
	printf("%d %% %d = %d\n", n1, n2, n1 % n2);
	
	return 0;
}
//*/
//======================================================



//======================================================
/*	2.	복합 대입 연산자( +=, -=, %=, -= )
//		복합 비트 대입 연산자( <<=, >>=, &=, ^=, |= )

int main(void)
{
	int n1 = 10;

	printf("n1 = %d\n", n1);
	n1 += 3;
	printf("n1 += 3 -> n1 = n1 + 3 -> %d\n", n1);

	n1 -= 3;
	printf("n1 -= 3 -> n1 = n1 - 3 -> %d\n", n1);

	n1 *= 3;
	printf("n1 *= 3 -> n1 = n1 * 3 -> %d\n", n1);

	n1 /= 3;
	printf("n1 /= 3 -> n1 = n1 / 3 -> %d\n", n1);

	n1 %= 3;
	printf("n1 %%= 3 -> n1 = n1 %% 3 -> %d\n", n1);

	return 0;
}
//*/
//======================================================


//======================================================
/*	3.	부호 연산자
int main(void)
{
	int n1 = +5;
	int n2 = -10;
	
	printf("-------- before -----------\n");
	printf("n1 = %d\n", n1);
	printf("n2 = %d\n", n2);
	printf("-------- after -----------\n");
	n1 = -n1;
	printf("n1 = %d\n", n1);
	n2 = -n2;
	printf("n2 = %d\n", n2);

	return 0;
}
//*/
//======================================================


//======================================================
/*	4.	부호 연산자
int main(void)
{
	int n1 = +5;
	int n2 = -10;

	printf("-------- before -----------\n");
	printf("n1 = %d\n", n1);
	printf("n2 = %d\n", n2);
	printf("-------- after -----------\n");
	n1 = -n1;
	printf("n1 = %d\n", n1);
	n2 = -n2;
	printf("n2 = %d\n", n2);

	return 0;
}
//*/
//======================================================


//======================================================
/*	5.	증감 연산자
int main(void)
{
	int n1 = 10, n2 = 20;

	printf("n1 = %d\n", n1);
	printf("n1++ = %d\n", n1++);
	printf("n1 = %d\n\n", n1);

	printf("n2 = %d\n", n2);
	printf("n2++ = %d\n", ++n2);
	printf("n2 = %d\n\n", n2);

	
	int n3 = 5;
	printf("n3 = %d\n", n3);
	printf("-------- after -----------\n");
	int n4 = (n3--) + 5;	//	int n4 = n3-- + 5;
	printf("n3 = %d\n", n3);
	printf("n4 = %d\n", n4);


	return 0;
}
//*/
//======================================================


//======================================================
/*	6.	관계 연산자
int main(void)
{
	int n1 = 3, n2 = 12;
	int res1 = (n1 == n2);
	int res2 = (n1 <= n2);
	int res3 = (n1 > n2);

	printf("res1 = %d\n", res1);
	printf("res2 = %d\n", res2);
	printf("res3 = %d\n", res3);

	if (res1)
		printf("res1 is true\n");
	else
		printf("res1 is false\n");

	if (res2)
		printf("res2 is true\n");
	else
		printf("res2 is false\n");

	if (res3)
		printf("res3 is true\n");
	else
		printf("res3 is false\n");
	
	return 0;
}
//*/
//======================================================


//======================================================
//*	7.	논리 연산자
int main(void)
{

	return 0;
}
//*/
//======================================================
