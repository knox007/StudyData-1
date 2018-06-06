//RTTI(run time type information) example
#include <stdio.h>
#include <iostream.h>

//{{RTTI macros---------------------------------------------------------
#define RUNTIME_CLASS(class_name) (&class_name::class##class_name)
#define DECLARE_DYNAMIC(class_name)	static\
		CRuntimeClass class##class_name;
#define IMPLEMENT_DYNAMIC(class_name) CRuntimeClass\
                    class_name::class##class_name = {\
                        (#class_name),\
                        sizeof(class_name),\
                    class_name::CreateObject };
#define DECLARE_DYNCREATE(class_name) static CObject* CreateObject();
#define IMPLEMENT_DYNCREATE(class_name) CObject*\
			 class_name::CreateObject() {\
                    return new class_name; }
//}}RTTI macros---------------------------------------------------------
  
class CObject;//forward declaration of CObject

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
    DECLARE_DYNAMIC(CObject)
      //static CRuntimeClass classCObject;
    virtual ~CObject(){}
protected:
    CObject(){ printf("CObject constructor\n"); }
};//class CObject

CRuntimeClass CObject::classCObject={
    "CObject",sizeof(CObject),NULL
};
//}}class CObject-------------------------------------------------------

//{{class CAlpha--------------------------------------------------------
class CAlpha : public CObject {
public:
    virtual CRuntimeClass* GetRuntimeClass() const {
        return &classCAlpha;
    }
    DECLARE_DYNAMIC(CAlpha)
      //static CRuntimeClass classCAlpha;
    DECLARE_DYNCREATE(CAlpha)
      //static CObject* CreateObject();
protected:
    CAlpha() { printf("CAlpha constructor\n"); }
};//class CAlpha

IMPLEMENT_DYNAMIC(CAlpha)
  //CRuntimeClass CAlpha::classCAlpha = {
  //    "CAlpha", sizeof(CAlpha), CAlpha::CreateObject
  //};

IMPLEMENT_DYNCREATE(CAlpha)
  //CObject* CAlpha::CreateObject() {
  //    return new CAlpha;
  //}
//}}class CAlpha--------------------------------------------------------

//{{class CBeta---------------------------------------------------------
class CBeta : public CObject {
public:
    virtual CRuntimeClass* GetRuntimeClass() const {
        return &classCBeta;
    }
    DECLARE_DYNAMIC(CBeta)
      //static CRuntimeClass classCBeta;
    DECLARE_DYNCREATE(CBeta)
      //static CObject* CreateObject();
protected:
    CBeta() { printf("CBeta constructor\n"); }
};//class CBeta

IMPLEMENT_DYNAMIC(CBeta)
  //CRuntimeClass CBeta::classCBeta = {
  //    "CBeta", sizeof(CBeta), CBeta::CreateObject
  //};

IMPLEMENT_DYNCREATE(CBeta)
  //CObject* CBeta::CreateObject() {
  //    return new CBeta;
  //}
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

    delete pObj1;//delete pRTCAlpha�� �� (����) �����ΰ�?
    delete pObj2;
}//main