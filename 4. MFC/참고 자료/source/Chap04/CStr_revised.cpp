#include <stdio.h>
#include <string.h>

class CStr {
    char *str;
  public:
    CStr(char *s="") {
        str=new char[strlen(s)+1];
        strcpy(str,s);
        printf("constructor\n");
    }
    CStr (const CStr &s) {//copy constructor
        str=new char[strlen(s.Get())+1];
        strcpy(str,s.Get());//const ��ü�� const ��� �Լ����� ȣ���� �� 
                            //�ִ�.
        printf("copy constructor\n");
    }
    ~CStr() {
        delete[] str;
        printf("destructor\n");
    }
    char *Get() const {//�Լ� ���� const�� �� �Լ��� ��� ����� ����
                       //���Ѽ��� �ȵ��� �����Ѵ�.�������ڡ��� ��this����
                       //�͡����� �ڼ��� ������ ���̴�.
        return str;
    }
    void Print() { printf("%s\n",str); }
};//class CStr

void f(CStr s) {
    s.Print();
}

void main() {
    CStr s("hello");
    f(s);
}