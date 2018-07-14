#include <stdio.h>
// ***함수의 4가지 타입***
// 리턴x, 파라미터x
// void = 리턴이 없다. 
// () = 파라미터 X ==> 호출할때 인자도X
void showInfo(){								//헤더부문
	printf("내이름은 홍길동 입니다.\n");		//바디부분
}// 함수종료

// 리턴o, 파라미터X
// int = 정수를 리턴하는 함수다~
// return 10; = 함수를 종료하며, 정수 10을 호출한곳으로 돌려준다.
int getInteger(){
	printf("리턴타입 있는 함수\n");
	return 10;
}
// 리턴X, 파라미터o
void showAge(int b){
	printf("당신의 나이는 %d살 입니다.\n", b);
}
// 리턴o, 파라미터o
int sum(int a, int b){
	int tot;
	tot = a + b;
	return tot;
}

void main(){
	int num;
	int age = 0;
	int num1 = 10;
	int num2 = 20;

	//함수 호출
	showInfo();
	// num : getInteger()함수를 실행하고 return으로 돌려받은 값을 저장하는 변수
	// getInteger(); : 함수 호출. 
	num = getInteger();
	printf("%d\n", num);
	printf("당신의 나이를 입력하세요>>>");
	scanf("%d", &age);
	showAge(age);
	num = sum(num1, num2);
	printf("%d\n", num);
}


