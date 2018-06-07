#if !defined(_03_Debug_New_Defined_)
#define _03_Debug_New_Defined_

#if defined(_DEBUG)
//#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

static class CRT_MEMORY_CHECK
{
public:
    CRT_MEMORY_CHECK()
    {
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    }//CRT_MEMORY_CHECK()
} _crt_memory_check;

void* operator new(size_t size, const char* filename, int line)
{
    printf( "operator new() called\n" );
    printf( "%s(%d)\n", filename, line );
    return ::operator new(size, _NORMAL_BLOCK, filename, line);
}//operator new()

#define THIS_FILE   __FILE__
#define DEBUG_NEW   new(THIS_FILE, __LINE__)

#endif // defined(_DEBUG)

#endif // !defined(_03_Debug_New_Defined_)