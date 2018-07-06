#include <stdio.h>

class CBase
{
public:
    void Print()
    {
        printf( "pre virtual\n" );
        OverrideMe(); // 가상 함수는 항상 실행시에 바인딩된다.
// 즉, 이 문장은 항상 CBase의 OverrideMe()함수를 호출하는 것은 아니다
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
        CBase::OverrideMe(); // 가상 함수의 일반적인 설계 규칙은 베이
//스 클래스의 가상 함수에 기능을 확장하는 것이다.
        printf( "CDerive\n" );
    }//OverrideMe()
};//class CDerive

void main()
{
    CDerive d;

    d.Print();
}//main()