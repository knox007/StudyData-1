#include <stdio.h>
//double 리턴타입 : 리턴으로 보내줄 데이터의 타입과 일치하게 
//2.
double div(int a, int b){
	double tot;
	// 만약에 b가 0일 경우에 에러를 막기위하여 조건문으로 에러처리해기.
	//3-1
	if (b == 0){	// b가 0일경우 이것만 실행하고, 0을 리턴해줌
		printf("0으로 나눌 수 없습니다.\n");
		return 0;
	}else{			// 3-2정상적으로 나눗셈 실행
		tot = (double)a / b;
		return tot;
	}
}

void main(){
	//문제1. 사칙연산 함수를 만들어보세요. 덧셈(sum).뺄셈(sub).곱셈(mul).나눗셈(div) 함수 4개 필요
	//		숫자 두개 보내서 결과값 받기
	int num1 = 30;
	int num2 = 0;
	double result;	// 나눗셈 실수로 받기위해 double로 선언해줌.
	//4.			1.		
	result = div(num1, num2);
	//5.
	printf("%.2lf", result);
	

	//문제2-0. num1과 num2의 값을 바꿔보세요
	//문제2-1. swap이라는 함수를 통하여 num1과 num2의 값을 바꿔보세요.  
	
}