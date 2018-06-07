#include <stdio.h>

class CBase
{
public:
    CBase()
    {
        DoVirtual(); // �����Լ��� ȣ���� ���ΰ�? No!
    }//CBase()

    virtual ~CBase()
    {
        DoVirtual(); // �����Լ��� ȣ���� ���ΰ�? No!
    }//~CBase()

    void DoIt()
    {
        DoVirtual(); // �����Լ��� ȣ���� ���ΰ�? Yes!
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