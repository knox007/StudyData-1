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
    static char lpszClassName[];//Ŭ������ �̸��� �޸𸮿� �� ���� ��
                                  //���ϸ� �ȴ�.
    virtual char* GetClassName() const {//���̽� Ŭ������ GetClassName�� 
                                        //�������̵��Ѵ�.
        return lpszClassName;//���� ��� ������ �����Ѵ�.
    }
};//class CMyClass

char CMyClass::lpszClassName[]="CMyClass";//���� ������ �ݵ�� Ŭ������ 
                                          //�ܺο��� �ʱ�ȭ�Ǿ�� �Ѵ�.

void main() {
    CObject *p;

    p=new CMyClass;//subtype principle�� ���� ���� Ŭ������ ����Ű�� ��
                   //�� ���� Ŭ������ �����͸� ����ϴ� ���� �����ϴ�.
    cout << p->GetClassName() << endl;
      //�������� ������� ��ü�� �̸��� ���� �� �ִ�!
    delete p;
}//main