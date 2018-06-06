// 선행처리부 : #include, 함수의 원형, #define NULL 0, enum, struct(구조체)
#include <stdio.h>			//.h 헤더파일.
void showInfo();			//함수의 원형 : 컴파일러에게 미리 이 함수가 있다고 선언을 해주는 것.

void main(){				//헤더부분
	// 함수의 사용(호출)	//바디부분
	showInfo();
	
}
// 함수의 정의(구현)
// 리턴x, 파라미터x
void showInfo(){			//헤더부문
	printf("내이름은 홍길동 입니다.\n");		//바디부분
}

// 함수의 4가지 타입
// 리턴X, 파라미터X
// 리턴o, 파라미터X
// 리턴X, 파라미터o
// 리턴o, 파라미터o

