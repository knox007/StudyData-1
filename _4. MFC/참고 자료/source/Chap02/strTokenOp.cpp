#include <iostream.h>

// #define charit(x) #@x//이 연산자 #@는 각자가 사용하는 컴파일러의 도움말
// 을 참고하라(궁금하다면).
#define stringit(x) #x
#define tokencat(x,y) x##y

void main(void)
{
    int i=1,j=2,ij=3;

    cout << stringit(hello) << '\n';
    cout << tokencat(i,j) << '\n';
}