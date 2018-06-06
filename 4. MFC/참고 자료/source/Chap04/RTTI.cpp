//RTTI(run time type information) example
#include <iostream.h>

class CObject {
public:
    virtual char* GetClassName() const { 
        return NULL; 
    }
};//class CObject

class CMyClass : public CObject {
public:
    static char lpszClassName[];//클래스의 이름은 메모리에 한 번만 할
                                  //당하면 된다.
    virtual char* GetClassName() const {//베이스 클래스의 GetClassName을 
                                        //오버라이드한다.
        return lpszClassName;//정적 멤버 변수를 리턴한다.
    }
};//class CMyClass

char CMyClass::lpszClassName[]="CMyClass";//정적 변수는 반드시 클래스의 
                                          //외부에서 초기화되어야 한다.

void main() {
    CObject *p;

    p=new CMyClass;//subtype principle에 의해 하위 클래스를 가리키기 위
                   //해 상위 클래스의 포인터를 사용하는 것이 가능하다.
    cout << p->GetClassName() << endl;
      //동적으로 만들어진 객체의 이름을 구할 수 있다!
    delete p;
}//main