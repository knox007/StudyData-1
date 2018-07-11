#include <stdio.h>
/*
switch case문

int num = 1;
* 조건의 값과 case의 값이 일치할경우 case 안의 실행문이 실행된다. 
* case안에 break; 키워드가 있을경우, switch-case문이 종료된다. 

switch(조건){
case 조건의값:	case의 값은 주로 , 상수나 문자하나만 적용이된다. 
	실행문들...
	break;
case 값:
	실행문들...
	break;
case 값:
	실행문들...
	break;
default:
	실행문들...
	// 위에 조건들이 실행되지 않을경우 기본적으로 실행되는 영역.
}
*/

void main(){

	int num;
	printf("값을 입력해주세요");
	scanf("%d", &num);
	switch(num){
	case 1:
		printf("1을 입력하셨습니다\n");
		break;
	case 2:
		printf("2를 입력하셨습니다\n");
		break;
	case 3:
		printf("3을 입력하셨습니다\n");
		break;
	default:
		printf("1,2,3이 아닌 다른수를 입력하셨습니다.\n");
	}
	// 문제 : if 문으로 바꿔보세요. 


}