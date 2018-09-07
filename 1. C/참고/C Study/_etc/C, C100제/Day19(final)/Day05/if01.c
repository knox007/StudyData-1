#include <stdio.h> // printf(), scanf()
#include <stdlib.h> // rand(), srand()
#include <time.h>	// 시간을 사용할때 필요한 헤더파일
//#define NULL 0
/*
	* 논리 연산자 *
	1. &&	: and : A && B : A도 참이고 B도 참이면, 참이다. 
	2. ||	: or  : A || B : A가 참이거나 B가 참이면, 참이다. 
	3. !	: not : !A	   : A가 거짓이면 참이다.

	*랜덤(random)*
	1. 랜덤 : 난수 : 임의의 값을 돌려주는 함수
	2. #include <stdlib.h> : 어딘가에 저장되어있는 라이브러리를 포함시켜
							그곳에 정의되어있는 함수를 이용하겠다. 
*/

void main(){
	/*
	int num1=20, num2=10, num3=10, num4=20;
	if(num1 < num2 && num3 > num4){
		printf("참1\n");
	}
	
	if(num1 < num2 || num3 > num4){
		printf("참2\n");
	}
	
	if(!(num1 < num2) && !(num3 > num4)){
		printf("참3\n");
	}*/
	
	// 문제1) 가위 바위 보 게임 만들기
	// 1. 가위(0), 바위(1), 보(2) 중에서 하나를 골라주세요
	// 2. comnum은 항상 바위(1) 입니다. 
	// 3. mynum과 comnum을 비교해서
	//    이겼다/졌다/비겼다를 출력해보세요.
	/*
	int mynum;
	int comnum = 1;
	if(mynum > comnum){
		printf("이겼다\n");
	}else if(mynum == comnum){
		printf("비겼다\n");
	}else{
		printf("졌다\n");
	}
	*/
	// 문제1-1) comnum이 random 값으로 가위,바위,보 중에 뭘 내던지
	//		올바른 판결이 나게 바꿔보세요. 
	int mynum = 0;
	int comnum = 0;
	srand(time(0));	
	//srand() :랜덤의 seed값을 바꿔주는 함수다. seed값은 random을 어디부터 시작할지.
	//			그 시작점을 말한다. 
	// time(0) : 현재 시간을 받아와서 그 숫자를 seed값으로 지정
	//				=> 랜덤의 시작점을 계속 바꿔줘서 실제로 랜덤같이 만들어준다. 
	// rand() : seed값을 연속적으로 바꿔주지 않으면 가짜랜덤, 고정된 랜덤값만 돌려준다.  
	comnum = rand() % 3;	// 3으로 나눈 나머지가 0,1,2밖에 안되기 때문에. 
	printf("%d\n", comnum);

	//문제2-1) comnum에 0~99까지의 숫자를 램덤으로 저장해보자.
	comnum = rand() % 100; // 100단위를 쳐내겠다. 
	//문제2-2) comnum에 10~15사이의 숫자를 랜덤으로 저장해보자.
	comnum = rand() % 6 + 10;	// 0+10, 1+10, 2+10, 3+10, 4+10, 5+10
	//문제 2-3 ) 6~12사이의 숫자를 
	comnum = rand() % 7 + 6		// 0+6, 1, 2, 3, 4, 5+6, 6+6
	// 문제2) 업다운게임
	// 1. 컴퓨터가 임의의 숫자를 받는다. 1~100사이
	// 2. 사용자는 10번의 기회가 있고
	// 3. 사용자가 컴퓨터가 갖고 있는 숫자보다 적게 입력했을경우 "Up!"
	//		컴퓨터보다 많은 숫자를 입력했을경우 "Down!" 출력.








}