#include <stdio.h>

class CBase
{
public:
    void Print()
    {
        printf( "pre virtual\n" );
        OverrideMe(); // ���� �Լ��� �׻� ����ÿ� ���ε��ȴ�.
// ��, �� ������ �׻� CBase�� OverrideMe()�Լ��� ȣ���ϴ� ���� �ƴϴ�
        printf( "post virtual\n" );
    }//Print()

    virtual void OverrideMe()
    {
        printf( "CBase\n" );
    }//OverrideMe()
};//class CBase

class CDerive : public CBase
{
public:
    void Draw()
    {
        printf( "draw\n" );
    }//Draw()

    virtual void OverrideMe()
    {
        CBase::OverrideMe(); // ���� �Լ��� �Ϲ����� ���� ��Ģ�� ����
//�� Ŭ������ ���� �Լ��� ����� Ȯ���ϴ� ���̴�.
        printf( "CDerive\n" );
    }//OverrideMe()
};//class CDerive

void main()
{
    CDerive d;

    d.Print();
}//main()