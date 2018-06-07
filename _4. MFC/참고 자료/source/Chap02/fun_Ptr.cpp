#include <stdio.h>

int Sum(int a, int b)
{
    return a+b;
}//Sum()

void main()
{
    int (*fp)(int,int);
    int i;

    fp = Sum; // Sum()함수의 시작 주소를 fp에 대입한다.
    i = fp(2,3); // fp(2,3) == Sum(2,3)
    printf( "%d\n", i );
}//main()