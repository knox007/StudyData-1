//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	Literal Size

	int ������ ǥ���� ������ ������ ����� int ������ �޸� ������ �����ϱ�� ����.

	double ������ ǥ���� ������ �Ǽ��� ����� double ������ �޸� ������ �����ϱ�� ����.

	������ ����� ��� �����Ϸ��� ���� ������ ��ȯ�ǹǷ� int������ ǥ���ȴ�.

*/
/*
int main(void)
{
	printf("literal int size : %d\n", sizeof(10));
	printf("literal double size : %d\n", sizeof(3.14));
	printf("literal char size : %d\n", sizeof('A'));

	return 0;
}
//*/
//======================================================



//======================================================
/*
2.	�ɺ��� ���
*/
//*
#define BULLET_SPEED 20

const int BULLET_COUNT = 10;
int g_nCurBulletCount = 0;

void Shoot()
{
	if (g_nCurBulletCount > BULLET_COUNT)
//	if (g_nCurBulletCount > 10)
		return;

	++g_nCurBulletCount;
}

int main(void)
{
	const int BULLET_POW = 100;	

	printf("�Ѿ��� �ӵ�  : %d\n", BULLET_SPEED);
	printf("�Ѿ��� ���ݷ�  : %d\n", BULLET_POW);
	
	return 0;
}

//*/
//======================================================