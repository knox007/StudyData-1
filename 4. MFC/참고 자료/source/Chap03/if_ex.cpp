#include <stdio.h>

#define DEBUG

#ifdef DEBUG
void f(int i) {
    printf("%d\n",i);
}
#endif

void main() {
    int i=2,j=3,k=4;
    k=i*j*k;
  #ifdef DEBUG
    f(k);
  #endif
    printf("%d,%d,%d\n",i,j,k);
}