#include <stdio.h>

#define LINE1(x) #x
#define LINE(x) LINE1(x)
#define TODO(msg) message ( __FILE__ "(" LINE(__LINE__)  "): [TODO] " msg )

void main()
{   
#pragma TODO( "implement main()\n" )
    printf( "hello\n" );
    printf( "world\n" );
}//main()