#include <stdio.h>
/*
switch case��

int num = 1;
* ������ ���� case�� ���� ��ġ�Ұ�� case ���� ���๮�� ����ȴ�. 
* case�ȿ� break; Ű���尡 �������, switch-case���� ����ȴ�. 

switch(����){
case �����ǰ�:	case�� ���� �ַ� , ����� �����ϳ��� �����̵ȴ�. 
	���๮��...
	break;
case ��:
	���๮��...
	break;
case ��:
	���๮��...
	break;
default:
	���๮��...
	// ���� ���ǵ��� ������� ������� �⺻������ ����Ǵ� ����.
}
*/

void main(){

	int num;
	printf("���� �Է����ּ���");
	scanf("%d", &num);
	switch(num){
	case 1:
		printf("1�� �Է��ϼ̽��ϴ�\n");
		break;
	case 2:
		printf("2�� �Է��ϼ̽��ϴ�\n");
		break;
	case 3:
		printf("3�� �Է��ϼ̽��ϴ�\n");
		break;
	default:
		printf("1,2,3�� �ƴ� �ٸ����� �Է��ϼ̽��ϴ�.\n");
	}
	// ���� : if ������ �ٲ㺸����. 


}