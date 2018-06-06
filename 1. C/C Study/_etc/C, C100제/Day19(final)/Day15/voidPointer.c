#include <stdio.h>
/*
	*포인터 : 주소 / 포인터 변수 : 주소를 저장하는 변수 (4byte)
	int a;  double d;  char ch; 
	int* p; double* p; char* p; void* p;
	p = &a;
	p++; 4byte뒤에꺼 지정
	printf("%d\n", *p); => 내가 저장한 a변수의 주소로 날라가서 4byte읽어와야한다. 

	*** void 포인터 ***
	주소를 받아올 대상의 타입이 정해지지 않았다, 즉 임의의 대상체에 대한 포인터형.
	# 타입이 없어 몇바이트를 읽어와야 할지 몰라, *연산자를 통해 데이터를 읽어올 수 없다. 
	# 증감 연산자 또한 사용할 수 없다. 
	단순히 주소만 받아야 할때
*/

void main(){

	void *vp;
	int *p;
	double *dp;

	int i = 1234;

	// 둘다 가능하다. 타입이 없어서 어떠한 주고 받을 수 있다. (연산은 안된다)
	//vp = p;
	//vp = dp;

	// 반대는 형변환 필요!!
	//p = (int*)vp;
	//dp = (double*)vp;

	vp = &i;
	printf("%d\n", *(int*)vp);

}