#include <stdio.h>

void main(){
	// 포인터 끼리 덧셈은 안되나, 뺄셈은 된다. 
	//1.
	/*char ar[] = "Example";
	char *p1, *p2;

	
	p1 = &ar[0];
	p2 = &ar[6];
	printf("%d\n", p1);
	printf("%d\n", p2);
	printf("%c와 %c의 거리는 %d\n", *p1, *p2, p2-p1);
	*/
	//2.
	int arr[] = {1,2,3,4,5};
	int *p1, *p2, *p3; 

	p1 = &arr[0];
	p2 = &arr[4];
	p3 = p1 + (p2-p1)/2;
	printf("중간요소 = %d\n", *p3);

	//주말동안숙제
	// 1. for문 부터 (Day04) 개념정리 한번씩 손으로 써보기
	// 2. 문제 전부다풀어보기. (모르는 문제는 어디를 잘 모르겠다 표시하고)
	//    문제 전부 푼것 메일로 보내주세요. (월요일 오전까지)

}