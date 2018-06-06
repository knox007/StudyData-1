#include <stdio.h>


/*
	***2중배열 (다차원배열)***
	 
	type 배열명[크기1][크기2];

	2차원 배열의 총크기 : sizeof(타입) * 크기1 * 크기2

	int arr[2][3] = {1,2,3,4,5,6};
	int arr[2][3] = {{1,2,3},		==> arr[0] 
					{4,5,6}}		==> arr[1]

	arr[0][2] ==> 3
	arr[1][0] ==> 4
*/



void main(){
	/*
	int i,j;
	int arr[3] = {1,2,3};
	int arr2[2][3] = {{1,2,3},
					  {4,5,6}};
	
	printf("%d\n", arr2[0][0]);

	for(i=0;i<sizeof(arr2)/sizeof(arr2[0]);i++){
		for(j=0; j<sizeof(arr2[0])/sizeof(int);j++){
			printf("%d\n", arr2[i][j]);
		}
	}
	*/
	// 문제A.
	// 방이 5개가있는 2개층의 집을 만들고 {10,20,30,40,50,60,70,80,90,100}를 넣어주세요
	int arr[2][5] = {10,20,30,40,50,60,70,80,90,100};
	// 문제1. 1층의 3번방의 값을 출력
	// 문제2. 2층의 4번방의 값을 출력
	// 문제3. 전체 방의 값을 출력
	// 문제4. 1층 2번방의 값을 35로 변경하기
	// 문제5. 2층 1번방과 5번방의 값을 서로 교환하여 저장하기
	// 문제6. 1층 1번방과 2층 5번방의 값을 더하여 출력하기
	
	// 문제7. 1층의 값만 다 더하여 출력하기
	// 문제8. 2층의 값만 다 더하여 출력하기

	// 문제9. 모든방의 값을 다 더하여 출력하기
	// 문제10. 모든방의 값을 다 더하여 평균을 구해서 출력.

	// 문제B.
	// 1반 3명, 2반 3명 학생이 있습니다. 수학시험의 각각 점수를 넣어놓은 배열 데이터를 만들자. 
	// 문제1. 반별 총점과 평균 구하여 출력
	// 문제2. 전체 총점과 평균 구하여 출력
	// 문제3. (심화)최고득점한 학생이 몇반의 몇번학생인지 몇점을 받았는지 출력하기.

}