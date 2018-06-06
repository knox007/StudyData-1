#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	// 이름 크기만큼 입력받기.
	char buffer[100] = {0};
	int name_len;
	char *name;
	//1. 이름을 버퍼변수에 입력받고 => buffer배열, malloc(), 포인터변수, 길이재서 저장할 변수
	printf("이름 입력");
	scanf("%s", buffer);
	//2. 길이를 재서 그 길이만큼 메모리를 할당하고 이름복사하기. 
	name_len = strlen(buffer);
	name = (char*)malloc(name_len * sizeof(char));
	strcpy(name, buffer);
	printf("%s\n", name);

	// 문제. 학생수 입력받고, 그 학생수 만큼 학생의 이름을 크기만큼 정확히 공간을 만들어 저정하고 출력해보자. 
}