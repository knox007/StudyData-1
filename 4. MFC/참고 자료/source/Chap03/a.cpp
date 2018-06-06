//a.cpp
#include <stdio.h>
#include "macro.h"
#include "b.cpp"
void main() {
    int i;
    i=f(2);
    PRINT(i);
}