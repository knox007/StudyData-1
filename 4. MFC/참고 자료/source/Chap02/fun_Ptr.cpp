#include <stdio.h>

int Sum(int a, int b)
{
    return a+b;
}//Sum()

void main()
{
    int (*fp)(int,int);
    int i;

    fp = Sum; // Sum()�Լ��� ���� �ּҸ� fp�� �����Ѵ�.
    i = fp(2,3); // fp(2,3) == Sum(2,3)
    printf( "%d\n", i );
}//main()