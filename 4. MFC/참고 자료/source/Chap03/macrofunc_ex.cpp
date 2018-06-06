#include <stdio.h>

#define MUL_DEFINED
#define MUL(a,b) a*b

void main() {
    printf("%d\n",MUL(2+3,4));//20을 예상하는가?
}