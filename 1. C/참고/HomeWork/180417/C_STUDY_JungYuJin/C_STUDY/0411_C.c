#include <stdio.h>

/*
void main() {

	// 문제 1. 2개의 정수를 입력 받아 뺄셈 곱셈의 결과를 출력 하시오.
	int num1, num2;

	printf("2개의 정수를 입력하세요 : ");
	scanf("%d %d", &num1, &num2);
	printf("뺄셈 : %d - %d = %d \n", num1, num2, num1-num2);
	printf("곱셈 : %d * %d = %d \n", num1, num2, num1*num2);
}
*/

/*
void main() {

	// 문제 2. 3개의 정수를 입력받아 첫번째와 두번째는 곱한 후 세번째 값을 더한 값을 출력 하시오. 
	int num1, num2, num3;

	printf("3개의 정수를 입력하세요 : ");
	scanf("%d %d %d", &num1, &num2, &num3);
	printf("결과 값 : %d * %d + %d = %d \n", num1, num2, num3, (num1*num2)+num3);
}
*/

/*
void main() {

	// 문제 3. 하나의 정수를 입력받아 해당 수를 제곱 한 값을 출력 하시오. ex) 2 = 4, 9 = 81
	int num;

	printf("정수 하나를 입력하세요 : ");
	scanf("%d", &num);
	printf("결과 값 : %d \n", num*num);
}
*/

/*
void main() {

	// 문제 4. 2개의 정수를 입력받아 몫과 나머지를 출력 하시오.
	int num1, num2;

	printf("2개의 정수를 입력하세요 : ");
	scanf("%d %d", &num1, &num2);
	printf("몫 : %d \n", num1/num2);
	printf("나머지 : %d \n", num1%num2);
}
*/

/*
void main() {

	// 문제5. 3개의 정수를 입력받아 해당 식의 값을 출력하시오. (num1-num2)*(num2+num3)*(num3%num1)
	int num1, num2, num3;

	printf("3개의 정수를 입력하세요 : ");
	scanf("%d %d %d", &num1, &num2, &num3);
	printf("결과 값 : %d \n", (num1-num2)*(num2+num3)*(num3%num1));
}
*/

/*
void main() { 

	// 문제 6. 10진수 20을 8진수, 16진수로 출력하시오.
	printf("10진수 : 20 \n");
	printf("8진수 : %o \n", 20);
	printf("16진수 : %x \n", 20);
}
*/

/*
void main() { 

	// 문제 7. 정사각형의 변 길이를 하나 입력받고 해당 정사각형의 넓이를 출력하시오.
	int num;

	printf("정사각형의 변의 길이를 입력하세요 : ");
	scanf("%d", &num);
	printf("넓이 : %d \n", num*num);
}
*/

/*
void main() {

	// 문제 8. 2개의 실수를 입력받아 출력하시오.
	double d1, d2;

	printf("2개의 실수를 입력하세요 : ");
	scanf("%lf %lf", &d1, &d2);
	printf("출력 값 : %lf , %lf \n", d1, d2);
}
*/

/*
void main() {

	// 문제 9. 알파벳 A와 y의 정수값을 출력하시오.
	char ch1 = 'A', ch2 = 'y';

	printf("알파벳 A와 y의 정수값 : %d , %d \n", ch1, ch2);
}
*/

/*
void main() {

	// 문제 10. 사용자로부터 정수를 입력받아 아스키코드문자로 출력하시오.
	int num;

	printf("정수를 입력하세요 : ");
	scanf("%d", &num);
	printf("아스키코드문자 출력 : %c \n", num);
}
*/

/*
void main() {

	// 문제 11. 사용자로부터 문자를 입력받아 정수로 출력하시오.
	char ch;

	printf("문자를 입력하세요 : ");
	scanf("%c", &ch);
	printf("정수 출력 : %d \n", ch);
}
*/
	

// ---------- [for문 사용] ----------

/*
void main() {

	// 문제 12. 2개의 정수를 입력받아 두 정수 사이의 값을 모두 더한 값을 출력하시오. ex) 2와 5입력 하면 2+3+4+5 
	int i, num1, num2, sum = 0;

	printf("2개의 정수를 입력하세요 : ");
	scanf("%d %d", &num1, &num2);

	for (i=num1; i<=num2; i++) {
		sum += i;
		printf("%d \n", i);
	}
	printf("더한 값 : %d \n", sum);
}
*/

/*
void main() {

	// 문제 13. 1개의 정수를 입력받아 팩토리얼을 구하시오. ex) 5입력 하면 1*2*3*4*5  3입력 하면 1*2*3
	int i, num, sub = 1;

	printf("정수 한개를 입력하세요 : ");
	scanf("%d", &num);

	for (i=1; i<=num; i++) {
		sub *= i;
		printf("%d \n", i);
	}
	printf("곱한 값 : %d \n", sub);
}
*/

/*
void main() {
	
	// 문제 14. 0~100까지 짝수의 합을 구하시오. 2550이 나와야 한다.
	int i, sum = 0;

	for (i=0; i<=100; i++) {
		if (i % 2 == 0) {
			sum += i;
		}
	}
	printf("짝수의 합 : %d \n", sum);
}
*/

/*
void main() { 

	// 문제 15. 5개의 정수를 입력받아 정수의 합을 출력하시오.
	int i, sum = 0, num;

	for (i=0; i<5; i++) {
		printf("정수를 입력하세요 : ");
		scanf("%d", &num);

		sum += num;
	}
	printf("%d \n", sum);
}
*/

//void main() { // --------------------------------------------------------
//	
//	// 문제 16. 별찍기
//	/*
//			*
//			 *
//			  *
//			   *
//				*
//	*/
//}


// ---------- [while문 사용] ----------

/*
void main() {

	// 문제 17. 정수 하나를 입력받고 입력받은 정수 만큼 "Hello world!" 를 출력하시오.
	int i = 0, num;

	printf("정수 하나를 입력하세요 : ");
	scanf("%d", &num);

	while (i<num) {
		printf("Hello world \n");
		i++;
	}
}
*/

/*
void main() {	

	// 문제 18. 정수 하나를 입력받고 해당 수만큼 3의 배수를 입력 하시오.   ex) 5입력 3 6 9 12 15   3입력 3 6 9
	int i = 1, num;

	printf("정수 하나를 입력하세요 : ");
	scanf("%d", &num);

	while (i<=num) {
		printf("%d ", 3*i);
		i++;
	}
}
*/

/*
void main() {

	// 문제 19. 정수를 입력받고 해당 정수를 계속 더한 값을 출력하시오. 단 0을 입력하면 프로그램을 종료
	int num, sum = 0;

	while (1) {
		printf("정수를 입력하세요 : ");
		scanf("%d", &num);

		if (num == 0) {
			break;
		} else {
			sum += num;
			printf("%d \n", sum);
		}
	}
}	
*/

/*
void main() {

	// 문제 20. 정수 하나를 입력받고 해당 정수의 구구단을 출력하시오. 단 구구단을 출력하되 역순으로 출력
	int i = 9, num;

	printf("정수 하나를 입력하세요 : ");
	scanf("%d", &num);

	while (i>0) {
		printf("%d * %d = %d \n", num, i, num*i);
		i--;
	}
}
*/

/*
void main() { 

	// 문제 21. 사용자로부터 몇개의 정수를 입력받을 것인지 묻고, 해당 갯수만큼 정수를 입력 받은뒤 평균을 출력하시오. 단 평균의 소수점은 2번째 자리까지만 출력한다.

	int i = 0, num, score, sum = 0;

	printf("몇 개의 정수를 받을 것인지 입력하세요 : ");
	scanf("%d", &num);

	while (i<num) {
		printf("해당 갯수만큼 점수를 입력하세요 : ");
		scanf("%d", &score);
		sum += score;
		i++;
	}
	printf("평균 : %d \n", sum/num);
}
*/

/*
void main() {

	// 문제 22. 1이상 100미만의 정수 중에서 7의 배수와 9의 배수를 출력하는 프로그램을 작성 하시오. 단 7의 배수이면서 동시에 9의 배수인 정수는 한번만 출력한다.
	int i = 1;

	while (i<100) {
		if (i % 7 == 0 && i % 9 == 0) {
			printf("7과 9의 배수 : %d \n", i);
		} else if (i % 9 == 0) {
			printf("9의 배수 : %d \n", i);
		} else if (i % 7 == 0) {
			printf("7의 배수 : %d \n", i);
		}
		i++;
	}
}
*/

/*
void main() {
	
	// 23. 두개의 정수를 입력받아 두수의 차를 구하는 프로그래을 작성하시오. 단 입력된 정수의 순서와 관계없이 큰 수에서 작은 수를 빼야 한다.
	int num1, num2;

	printf("정수 2개를 입력하세요 : ");
	scanf("%d %d", &num1, &num2);

	if (num1 < num2) {
		printf("두수의 차 : %d \n", num2-num1);
	} else {
		printf("두수의 차 : %d \n", num1-num2);
	}
}
*/

/*
void main() {

	// 문제 24. 학생의 국어, 영어, 수학점수를 순서대로 입력받고 해당 점수들이 평균이 90점 이상이면 A 80점 이상이면 B 70점 이상이면 C 50점 이상이면 D 50미만이면 F를 출력
	int num1, num2, num3, result = 0;

	printf("국어, 영어, 수학점수를 입력하세요 : ");
	scanf("%d %d %d", &num1, &num2, &num3);

	result = (num1 + num2 + num3) / 3;

	if (result >= 90) {
		printf("A \n");
	} else if (result >= 80) {
		printf("B \n");
	} else if (result >= 70) {
		printf("C \n");
	} else if (result >= 50) {
		printf("D \n");
	} else {
		printf("F \n");
	}
}
*/

/*
void main() { 
	
	// 문제 25. 해당식이 만족하는 수를 모두 출력하시오. ab + ba = 99 ex) a = 1 b = 8 일때 성립
	int i, j;

	for (i=0; i<=9; i++) {
		for (j=0; j<=9; j++) {
			
			if ((i*10+j) + (j*10+i) == 99) {
				printf("%d + %d = 99 \n", (i*10+j), (j*10+i));
			}		
		}
	}
}
*/

/*
int big_result(int num1, int num2, int num3);
void main() { // --------------------------------------------------------

	// 문제 26. 세개의 정수를 입력받고 가장 큰수와 작은수를 반환하는 함수를 만들고 결과 값을 출력하시오.
	int num1, num2, num3, box;

	printf("정수 3개를 입력하세요 : ");
	scanf("%d %d %d", &num1, &num2, &num3);

	box = big_result(num1, num2, num3);
	printf("가장 큰 수 : %d \n", box);
}

int big_result(int num1, int num2, int num3) {
	int result = 0;
	if (num1 > result) {
		result = num1;
	}
	if (num2 > result) {
		result = num2;
	}
	if (num3 > result) {
		result = num3;
	}
	
	return result;
	
}
*/

/*
double chage(int num);
void main() {

	// 문제 27. 섭씨(온도)를 입력받으면 화씨(온도)로 변형하는 함수를 만들어 메인에서 결과 값을 출력하시오. 섭씨를 화씨로 만드는 공식은 1.8 * 입력받은 수 + 32
	int num;
	double result;

	printf("섭씨를 입력하세요 : ");
	scanf("%d", &num);
	result = chage(num);
	printf("화씨 : %.2lf \n", result);
}

double chage(int num) {
	double result = 1.8 * num + 32;
	return result;
}
*/


// ---------- [최종 테스트 문제!] ----------

/*
void main() {

	// 문제 1. 10진수를 입력받아 16진수로 출력하시오.
	int num;

	printf("10진수를 입력하세요 : ");
	scanf("%d", &num);
	printf("16진수 : %x \n", num);
}
*/

/*
void main() {

	// 문제 2. 사용자로부터 정수 2개를 입력받아 두 정수 사이의 구구단을 출력하는 함수를 만들어 출력하시오. ex) 2 5 입력하면 구구단 2단 3단 4단 5단을 출력하시오.
	int i, j, num1, num2;

	printf("정수 2개를 입력하세요 : ");
	scanf("%d %d", &num1, &num2);

	for (i=num1; i<=num2; i++) {
		printf("--- %d단 --- \n", i);
		for (j=1; j<10; j++) {
			printf("%d * %d = %d \n", i, j, i*j);
		}
	}
}
*/

//void main() { // --------------------------------------------------------
//
//	// 문제 3. 현재 내 잔액이 3500원이 있다. 크림빵은 500원 새우깡은 700원 콜라는 400원이다.
//	//         내가 잔액을 하나도 남기지 않고 음식들을 하나 이상씩 살 때 어떤 경우가 있는지 모두 출력하시오.
//	//         ex) 크림빵 1개(500원) 새우깡 2개(1400원) 콜라 4개(1600)을 산다. 이런식으로 모든 경우의 수를 출력하시오.
//
//}
	 
//void main() { // --------------------------------------------------------
//
//	// 문제 4. 소수(나와 1로밖에 나누지 못하는 수)를 10개 출력하시오. 결과 값이 2 3 5 7 11 13 17 19 23 29 이다.
//	int i;
//
//	for (i=2; i<50; i++) {
//		if (i == 2 || i % 2 != 0) {
//			printf("%d \n", i);
//		}
//	}
//
//}	

/*
void main() {

	// 문제 5. 사용자로 부터 초(시간)을 입력받고 시 분 초 로 출력하시오. ex) 3615 입력 1시 0분 15초
	int sec;

	printf("초를 입력하세요 : ");
	scanf("%d", &sec);
	printf("%d시 \n", sec/3600);
	printf("%d분 \n", sec%3600/60);
	printf("%d초 \n", sec%60/);
}
*/	