#include <stdio.h>
#include <stdlib.h>

void main(){
	// �л����� �Է¹ް�, �л��� ���м����� �Է��ϼ���.
	// ���� ������ ����� ���غ�����. 
	//1. �л��� �Է¹ޱ�
	int stNum, i;
	int* arrScore;
	int sum = 0;

	printf("�л��� �Է�: ");
	scanf("%d", &stNum);
	//2. �л�����ŭ �޸� �Ҵ��ϱ�
	arrScore = (int*)malloc(stNum * sizeof(int));
	//3. �������� �Է¹޾� �����ϱ�
	for(i=0;i<stNum;i++){
		printf("%d�� �л��� �������� �Է�: ", i+1);
		scanf("%d", &arrScore[i]);
	}
	//4. ����, ��� ���ϱ�
	for(i=0;i<stNum;i++){
		sum += arrScore[i];
	}
	printf("\n������ %d���̰�, ����� %d���Դϴ�.\n",sum, (sum/stNum));

	//����
	free(arrScore);
}