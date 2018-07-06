#include <stdio.h>

class CBase
{
public:
    CBase()
    {
        DoVirtual(); // 가상함수를 호출할 것인가? No!
    }//CBase()

    virtual ~CBase()
    {
        DoVirtual(); // 가상함수를 호출할 것인가? No!
    }//~CBase()

    void DoIt()
    {
        DoVirtual(); // 가상함수를 호출할 것인가? Yes!
    }//DoIt()

    virtual void DoVirtual()
    {
        printf( "CBase\n" );
    }//DoVirtual()
};//class CBase

class CDerive : public CBase
{
public:
    virtual void DoVirtual()
    {
        printf( "CDerive\n" );
    }//DoVirtual()
};//class CDerive

void main()
{
    CDerive b;

    b.DoIt();
}//main()