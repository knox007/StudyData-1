#include <stdio.h>

typedef unsigned int HANDLE;

class CHandle
{
private:
    HANDLE  m_handle;
    int     m_data;

public:
    CHandle()
    {
        m_handle = 0;
        m_data   = 1;
    }
//    HANDLE GetHandle() const
//    {
//        printf( "GetHandle()\n" );
//        return m_handle;
//    }
    operator HANDLE() const 
    // 변환연산자 함수는 리턴타입이 operator
    // 뒤에 명시됨을 주의하자. 리턴타입 자리는 반드시 비워둔다.
    {
        printf( "operator HANDLE()\n" );
        return m_handle;
    }
    void FromHandle(HANDLE handle)
    {
        m_handle = handle;
        // construct etc. members from handle
    }
};//class CHandleMap

void Test(HANDLE handle)
{
    printf( "handle = %i\n", handle );
}//Test()

void main()
{
    CHandle     handleObject;
    HANDLE      handle;

    handle = 2;
    handleObject.FromHandle(handle);
    //Test( handleObject.GetHandle() );
    Test( handleObject );
}//main()