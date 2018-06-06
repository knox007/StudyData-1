//RTTI(run time type information) example
#include <stdio.h>
#include <iostream.h>

#define RUNTIME_CLASS(class_name) (&class_name::class##class_name)

class CObject;

//{{struct CRuntimeClass------------------------------------------------
struct CRuntimeClass {
    char m_lpszClassName[21];
    int m_nObjectSize;
    CObject* (*pfnCreateObject)();

    CObject* CreateObject();
};//struct CRunTimeClass

CObject* CRuntimeClass::CreateObject() {
    return (*pfnCreateObject)();//함수 포인터를 이용하여
                                //간접적으로 함수를 호출한다.
}//CRuntimeClass::CreateObject()
//}}struct CRuntimeClass------------------------------------------------

//{{class CObject-------------------------------------------------------
class CObject {
    //CObject는 순수 가상함수를 포함하지 않으므로
    //추상 클래스가 아니다. 하지만, 생성자가 protected로 설정되었으므로,
    //CObject객체를 생성할 수 없다.
public:
    virtual CRuntimeClass* GetRuntimeClass() const { return NULL; }
      //파생 클래스에서 반드시 구현할 필요가 없으므로
      //순수가상함수가 아니다.
    static CRuntimeClass classCObject;
      //DECLARE_DYNAMIC(CObject)
    virtual ~CObject(){}
protected:
    CObject(){ printf("CObject constructor\n"); }
};//class CObject

CRuntimeClass CObject::classCObject={//IMPLEMENT_DYNAMIC(CObject)
    "CObject",sizeof(CObject),NULL
};
//}}class CObject-------------------------------------------------------

//{{class CAlpha--------------------------------------------------------
class CAlpha : public CObject {
public:
    virtual CRuntimeClass* GetRuntimeClass() const {
        return &classCAlpha;
    }
    static CRuntimeClass classCAlpha;
      //DECLARE_DYNAMIC(CAlpha)
    static CObject* CreateObject();
      //DECLARE_DYNCREATE(CAlpha)
protected:
    CAlpha() { printf("CAlpha constructor\n"); }
};//class CAlpha

CRuntimeClass CAlpha::classCAlpha = {//IMPLEMENT_DYNAMIC(CAlpha)
    "CAlpha", sizeof(CAlpha), CAlpha::CreateObject
};

CObject* CAlpha::CreateObject() {//IMPLEMENT_DYNCREATE(CAlpha)
    return new CAlpha;
}
//}}class CAlpha--------------------------------------------------------

//{{class CBeta---------------------------------------------------------
class CBeta : public CObject {
public:
    virtual CRuntimeClass* GetRuntimeClass() const {
        return &classCBeta;
    }
    static CRuntimeClass classCBeta;
      //DECLARE_DYNAMIC(CBeta)
    static CObject* CreateObject();
      //DECLARE_DYNCREATE(CBeta)
protected:
    CBeta() { printf("CBeta constructor\n"); }
};//class CBeta

CRuntimeClass CBeta::classCBeta = {//IMPLEMENT_DYNAMIC(CBeta)
    "CBeta", sizeof(CBeta), CBeta::CreateObject
};

CObject* CBeta::CreateObject() {//IMPLEMENT_DYNCREATE(CBeta)
    return new CBeta;
}
//}}class CBeta---------------------------------------------------------

void main() {
    //Create CAlpha 
    CRuntimeClass* pRTCAlpha=RUNTIME_CLASS(CAlpha);
    CObject* pObj1;
    
    pObj1=pRTCAlpha->CreateObject();
      //struct RuntimeClass의 CreateObject()가 호출되지만
      //IMPLEMENT_DYNCREATE 매크로에 의해 CAlpha의 &OnCreate()가
      //대입되어 있으므로, 결국은 CAlpha의 OnCreate()가 호출되어
      //동적으로 객체를 생성하게 된다.
      //문제를 푸는 열쇠는 바로 '함수 포인터'이다.
    printf("CAlpha class=%s\n",
	 pObj1->GetRuntimeClass()->m_lpszClassName);

    //Create CBeta
    CRuntimeClass* pRTCBeta=RUNTIME_CLASS(CBeta);
    CObject* pObj2;
    
    pObj2=pRTCBeta->CreateObject();
    printf("CBeta class=%s\n",
	pObj2->GetRuntimeClass()->m_lpszClassName);
      //일관된 방법으로 클래스를 만들고 해제하는 것에 주목하라.

    delete pObj1;
    delete pObj2;
}//main