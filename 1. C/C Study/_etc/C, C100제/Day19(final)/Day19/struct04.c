#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	*** 구조체 배열 ***
	0. 구조체 
	struct Person p1;
	p1.age = 20;

	1. 구조체가 배열의 요소
	Person타입의 구조체 변수 10개를 모아 주소록을 만들고 싶다.

	struct Person aP[10];
	aP[3].age = 30;

	배열의 첨자연산자 []와 멤버연산자 .을 같이 사용하여 데이터 활용.
	두가지 [] , . 연산자 우선순위가 모두 1순위 , 왼쪽우선순이기때문에
	순서대로 적어주면 된다. 

	2. 배열이 구조체의 요소(멤버)
	struct Person p;
	p.name[0] = 'A';

	3. 구조체가 배열의 요소이며 그 요소안에 배열이 있을경우
	struct Person aP[10];
	aP[1].name[2] = 'B';	//경로를 순서대로 나열하면 된다.

	4. 구조체 포인터배열
	struct Person *pP;        ==> 구조체 하나를 가르키는 포인터
	struct Person *parP[10];  ==> 10개방의 배열안에 구조체를 가르키는 포인터가 10개 들어있다. 
	parP[3]->age = 20;
	(*parP[3]).age = 20;
	(**(parP+3)).age = 20;

*/
struct Person{
	char name[10];
	int age;
	int mobile;
};

void main(){
	/*
	int a;
	int *a;
	struct Person *p2; // 구조체를 가르키는 포인터

	//배열
	int ar[3];
	//구조체 배열
	struct Person arP[3];

	struct Person p1;
	struct Person arp[10];
	*/
	/*
	// 이름크기만큼 메모리 할당할때, 포인터사용 
	char *name;
	name = (char*)malloc(name_len * sizeof(char));

	//구조체를 가르키는 포인터들의 배열 : 구조체 가르키는 포인터가 10개 들어있는 배열
	struct Person *pSt;
	pSt = (struct Person*)malloc(sizeof(struct Person));
	*/

	//#할당
	// 구조체 10개를 포인터를 이용해서 할당하여 체계적으로 데이터를 저장/활용하자. 
	struct Person *parP[10];
	int i;
	for(i=0;i<10;i++){
		parP[i] = (struct Person*)malloc(sizeof(struct Person));
	}// 구조체를 초기화 해주기 위해 malloc함수로 동적할당.
	// 구조체를 가리키도록 초기화 하는 가장 쉬운 방법. 

	parP[3]->age = 20;
	printf("%d\n", parP[3]->age);

	//#해제
	for(i=0;i<10;i++){
		free(parP[i]);
	}

}