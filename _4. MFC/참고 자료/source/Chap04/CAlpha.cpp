#include <stdio.h>
#include <iostream.h>
#include "afx.h"

//{{class CAlpha--------------------------------------------------------
class CAlpha : public CObject {
public:
    virtual CRuntimeClass* GetRuntimeClass() const {
        return &classCAlpha;
    }
    DECLARE_DYNAMIC(CAlpha)
    DECLARE_DYNCREATE(CAlpha)
protected:
    CAlpha() { printf("CAlpha constructor\n"); }
};//class CAlpha

IMPLEMENT_DYNAMIC(CAlpha)
IMPLEMENT_DYNCREATE(CAlpha)
//}}class CAlpha--------------------------------------------------------

//{{class CBeta---------------------------------------------------------
class CBeta : public CObject {
public:
    virtual CRuntimeClass* GetRuntimeClass() const {
        return &classCBeta;
    }
    DECLARE_DYNAMIC(CBeta)
    DECLARE_DYNCREATE(CBeta)
protected:
    CBeta() { printf("CBeta constructor\n"); }
};//class CBeta

IMPLEMENT_DYNAMIC(CBeta)
IMPLEMENT_DYNCREATE(CBeta)
//}}class CBeta---------------------------------------------------------

void main() {
    //Create CAlpha 
    CRuntimeClass* pRTCAlpha=RUNTIME_CLASS(CAlpha);
    CObject* pObj1;
    
    pObj1=pRTCAlpha->CreateObject();
    printf("CAlpha class=%s\n",
	 pObj1->GetRuntimeClass()->m_lpszClassName);

    //Create CBeta
    CRuntimeClass* pRTCBeta=RUNTIME_CLASS(CBeta);
    CObject* pObj2;
    
    pObj2=pRTCBeta->CreateObject();
    printf("CBeta class=%s\n",
	 pObj2->GetRuntimeClass()->m_lpszClassName);

    delete pObj1;
    delete pObj2;
}//main