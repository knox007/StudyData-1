#include <stdio.h>
#include <stdlib.h>

void main(){
	// 학생수를 입력받고, 학생별 수학성적을 입력하세요.
	// 수학 총점과 평균을 구해보세요. 
	//1. 학생수 입력받기
	int stNum, i;
	int* arrScore;
	int sum = 0;

	printf("학생수 입력: ");
	scanf("%d", &stNum);
	//2. 학생수만큼 메모리 할당하기
	arrScore = (int*)malloc(stNum * sizeof(int));
	//3. 수학점수 입력받아 저장하기
	for(i=0;i<stNum;i++){
		printf("%d번 학생의 수학점수 입력: ", i+1);
		scanf("%d", &arrScore[i]);
	}
	//4. 총점, 평균 구하기
	for(i=0;i<stNum;i++){
		sum += arrScore[i];
	}
	printf("\n총점은 %d점이고, 평균은 %d점입니다.\n",sum, (sum/stNum));

	//해제
	free(arrScore);
}