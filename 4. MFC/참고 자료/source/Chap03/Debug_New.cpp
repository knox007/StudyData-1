#include <stdio.h>
#include <stdlib.h>
#include "03_Debug_New.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#endif // defined(_DEBUG)

void main()
{    
    int* p = new int(); // (1)
    *p = 1;
    printf( "%i\n", *p );
    //delete p; // (2)
}//main()