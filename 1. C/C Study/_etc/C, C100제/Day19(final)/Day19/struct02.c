#include <stdio.h>
#include <string.h>

/*

	*** 구조체 ***
	# 포인터 멤버 연산자.

	struct Person a;
	struct Person *p;
	p = &a;
	a의 주소를 받는 포인터 p를 통하여,
	a가 가지고 있는 age라는 멤버에 접근하기 위해서 
	a.age = 20;
	(*p).age = 20;
	이런식으로 작성을 해야지만 정확하게 접근이 가능한데, 가독성이 떨어지기 때문에
	포인터 멤버 연산자를 만들어었다. 
	' -> ' 화살표이다.  : "~ 주소의 구조체멤버 ~" 라고 기억하자!
	p -> age = 20;		: p주소의 구조체 멤버 age에 20을 대입하자;


	#연산자 우선순위
	최우선연산자 : . -> [] ()
	단항연산자 : ! ~ + - ++ -- * & sizeof() (자료형)
	산술연산자
	관계연산자
	논리연산자
	삼항연산자
	대입연산자
	콤마연산자
*/

struct Person{
	char name[10];
	int age;
	double height;
};

void func(struct Person *p){
	printf("이름: %s\n", p->name);
	printf("나이: %d\n", p->age);
	printf("키  : %.1lf\n", p->height);
}

void main(){

	//사용자 정의 자료형
	//int a = 10;
	//int* pa;
	//pa = &a;
	//*pa = 20;

	struct Person p1;
	struct Person *pP1;

	// 구조체 포인터를 통하여 값 대입시키기
	pP1 = &p1;
	strcpy(pP1->name, "홍길동");
	pP1->age = 20;
	pP1->height = 160.5;

	func(pP1);

	/* 일반 구조체에 값 대입시키기
	strcpy(p1.name, "홍길동");
	p1.age = 20;
	p1.height = 160.5;
	*/
}