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
    return (*pfnCreateObject)();//�Լ� �����͸� �̿��Ͽ�
                                //���������� �Լ��� ȣ���Ѵ�.
}//CRuntimeClass::CreateObject()
//}}struct CRuntimeClass------------------------------------------------

//{{class CObject-------------------------------------------------------
class CObject {
    //CObject�� ���� �����Լ��� �������� �����Ƿ�
    //�߻� Ŭ������ �ƴϴ�. ������, �����ڰ� protected�� �����Ǿ����Ƿ�,
    //CObject��ü�� ������ �� ����.
public:
    virtual CRuntimeClass* GetRuntimeClass() const { return NULL; }
      //�Ļ� Ŭ�������� �ݵ�� ������ �ʿ䰡 �����Ƿ�
      //���������Լ��� �ƴϴ�.
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
      //struct RuntimeClass�� CreateObject()�� ȣ�������
      //IMPLEMENT_DYNCREATE ��ũ�ο� ���� CAlpha�� &OnCreate()��
      //���ԵǾ� �����Ƿ�, �ᱹ�� CAlpha�� OnCreate()�� ȣ��Ǿ�
      //�������� ��ü�� �����ϰ� �ȴ�.
      //������ Ǫ�� ����� �ٷ� '�Լ� ������'�̴�.
    printf("CAlpha class=%s\n",
	 pObj1->GetRuntimeClass()->m_lpszClassName);

    //Create CBeta
    CRuntimeClass* pRTCBeta=RUNTIME_CLASS(CBeta);
    CObject* pObj2;
    
    pObj2=pRTCBeta->CreateObject();
    printf("CBeta class=%s\n",
	pObj2->GetRuntimeClass()->m_lpszClassName);
      //�ϰ��� ������� Ŭ������ ����� �����ϴ� �Ϳ� �ָ��϶�.

    delete pObj1;
    delete pObj2;
}//main