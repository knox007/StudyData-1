#include <stdio.h>

void main() {
#line 1 "main.cpp"
    int i=2,j=3,k=4;

    printf("%d,%d,%d\n",i,j,k);
    printf("%s, %d\n",__FILE__,__LINE__);
    printf("%d\n",__LINE__);
#line 3897
    printf("%s, %d\n",__FILE__,__LINE__);
}