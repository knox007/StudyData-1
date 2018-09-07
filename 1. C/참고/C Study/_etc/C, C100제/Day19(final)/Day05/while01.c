#include <stdio.h>
/*
	#제어문
	1. 조건문 : if, switch-case
	2. 반복문 : for, while*
	3. 보조제어문: break, continue

	1. while문 (반복문)
		1) 조건식을 먼저 검사한 후 실행하는 반복문(루프)
			for문과 같은 (초기식;조건식;증감식) 구조가 없다. 
			if문과 비슷한 형태를 취한다. 
			실행문영역{} 안에서 루프를 종료할 수 있게 만들어 줘야한다. 
			for = 반복의 횟수를 알때 자주 사용
			while = 무한적으로 반복을하되, 사용자나 어떤 조건에 의해 종료를 하게 만들때,
		2) 구조
			int i;	선언
			i = 0;	초기화
			while(조건문){
				실행문1;
				실행문2;
				실행문3;
				....
				증감문;
			}
			
			#무한반복
			while(참){
				
				조건에 맞으면,
				break;	// break는 가장 가까운 while문을 종료시킨다. 

			}
			참 == true == 1
			거짓 == false == 0
*/
void main(){

	// 10회 반복하기 
	int a;
	int i = 0;	// 조건을 검사할 기준이될 변수 선언과 초기화
	while(i < 10){	// 조건식
		printf("안녕하세요\n");	// 실행문들...
		printf("%d\n", i);
		i++;	// 증감식빼먹으면, 무한반복되서 컴퓨터 다운됩니다. 
	}
	// 위에꺼랑 동이란 for문
	for(i = 0; i < 10; i++){
		printf("안녕하세요\n");
		printf("%d\n", i);
	}
	// 무한반복
	while(1){
		printf("숫자입력>>>");
		scanf("%d", &a);
		if(a == 5){
			printf("while문 종료!!\n");
			break;
		}
	}
	
}