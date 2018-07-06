#include <stdio.h>

#define PI          3.141592
#define A           B, C
#define begin       {
#define end         }
#define procedure   void

int B=1,C=2;

procedure PrintPI()
begin
    printf("%f\n",PI);
end

void main()
begin
    PrintPI();
    printf("%d,%d\n",A);
end