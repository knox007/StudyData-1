#include <stdio.h>
#include "MyAfx.h"

static char _szAfxVectorInl[] = "VectorCpp.inl";
#undef THIS_FILE
#define THIS_FILE _szAfxVectorInl

struct CVector2
{
    float   _x;
    float   _y;

#if defined(__cplusplus)
#include "VectorCpp.inl"
#endif // defined(__cplusplus)
};

#undef THIS_FILE
#define THIS_FILE   __FILE__

void Test(CVector2 v)
{
    printf( "(%g,%g)\n", v._x, v._y );
    ASSERT(0);
}

void main()
{
#if defined(__cplusplus)
    CVector2    v(0.f,0.f);
    CVector2    v2(1.f,1.f);
    CVector2    v3(2.f,2.f);
    
    v = v2 + v3;
#else
    CVector2    v;
    CVector2    v2;
    CVector2    v3;

    v._x = v._y = 0.f;
    v2._x = v2._y = 1.f;
    v3._x = v3._y = 2.f;

    v._x = v2._x + v3._x;
    v._y = v2._y + v3._y;
#endif // defined(__cplusplus)
    Test( v );
}//main()