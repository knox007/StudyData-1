#include <stdio.h>

#define TYPE 1

void main() {
    int i=2,j=3;
  #if (TYPE!=0)
  #error You must define TYPE to 0
  #endif
    printf("%d,%d\n",i,j);
}