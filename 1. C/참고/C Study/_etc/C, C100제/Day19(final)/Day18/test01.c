#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	// �̸� ũ�⸸ŭ �Է¹ޱ�.
	char buffer[100] = {0};
	int name_len;
	char *name;
	//1. �̸��� ���ۺ����� �Է¹ް� => buffer�迭, malloc(), �����ͺ���, �����缭 ������ ����
	printf("�̸� �Է�");
	scanf("%s", buffer);
	//2. ���̸� �缭 �� ���̸�ŭ �޸𸮸� �Ҵ��ϰ� �̸������ϱ�. 
	name_len = strlen(buffer);
	name = (char*)malloc(name_len * sizeof(char));
	strcpy(name, buffer);
	printf("%s\n", name);

	// ����. �л��� �Է¹ް�, �� �л��� ��ŭ �л��� �̸��� ũ�⸸ŭ ��Ȯ�� ������ ����� �����ϰ� ����غ���. 
}