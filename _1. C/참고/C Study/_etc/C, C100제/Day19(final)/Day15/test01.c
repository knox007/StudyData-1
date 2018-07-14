#include <stdio.h>

void main(){
	int i, j;
	int tot = 0;
	int max;
	int idxI;
	int idxJ;
	int arr[5] = {10, 20, 30, 40, 50};
	//문제1. 인덱스 번호 2개를 입력받아, 해당 인덱스번호의 요소를 교환해보자.  
	//문제2. int arr[3] = {10, 20, 30}; 이라는 배열이 있고, 
	//			포인터변수를 통하여 arr의 첫번째,두번째,세번째 요소를 각각 출력해보세요. 
	//문제3. int a = 100; 을 포인터변수를 이용하여 값을 5000으로 바꿔보자. 
	//문제4. int arr[3] = {10, 20, 30}; 에서  포인터 변수를 이용하여, 인덱스 1번요소의 값을 200으로 바꿔보자.
	//한반=3명 2개반 (전체 6명)이 시험을 봤는데 점수에대한 총점을 구해보자. 
	int arrStu[2][3] = {{80, 50, 99}, 
						{100, 20, 65}};
	/*
	for(i=0; i<2; i++){	//반
		for(j=0; j<3; j++){	//학생
			printf("점수= %d\n", arrStu[i][j]);
			tot += arrStu[i][j];
		}
	}
	*/
	max = arrStu[0][0];
	for(i=0; i<2; i++){	//반
		for(j=0; j<3; j++){	//학생
			//printf("점수= %d\n", arrStu[i][j]);
			if(max < arrStu[i][j]){
				max = arrStu[i][j];
				idxI = i;
				idxJ = j;
			}
		}
	}
	printf("최고점수는 %d점으로 %d반 %d번 학생입니다.\n", max, idxI+1, idxJ+1);

}