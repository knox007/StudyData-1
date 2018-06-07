//RTTI(run time type information) example
#include <iostream.h>

#define DECLARE_CLASSNAME(s) static char lpszClassName[]
#define IMPLEMENT_CLASSNAME(s) char s##::lpszClassName[]=(#s)

class CObject {
public:
    virtual char* GetClassName() const { 
        return NULL; 
    }
};//class CObject

class CMyClass : public CObject {
public:
    //static char lpszClassName[];
    DECLARE_CLASSNAME(CMyClass);
    virtual char* GetClassName() const {
        return lpszClassName;
    }
};//class CMyClass

//char CMyClass::lpszClassName[]="CMyClass";
IMPLEMENT_CLASSNAME(CMyClass);

void main() {
    CObject *p;

    p=new CMyClass;
    cout << p->GetClassName() << endl;
    delete p;
}//main