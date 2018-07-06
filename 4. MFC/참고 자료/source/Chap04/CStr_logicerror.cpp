#include <stdio.h>
#include <string.h>

class CStr {
    char *str;
  public:
    CStr(char *s="") {
        str=new char[strlen(s)+1];
        strcpy(str,s);
        printf("normal constructor\n");
    }
    CStr (const CStr &s) {//copy constructor
        str=new char[strlen(s.Get())+1];
        strcpy(str,s.Get());
        printf("copy constructor\n");
    }
    ~CStr() {
        delete[] str;
        printf("destructor\n");
    }
    char *Get() const { return str; }
    void Print() { printf("%s\n",str); }
};//class CStr

void f(CStr s) {
    s.Print();
}

void main() {
    CStr s("hello"),
         t("world");
    CStr u=s;//��ü�� ���𹮿� ���� ���� �����ڴ� ���� �����ڸ� ȣ����
             //��.

    f(u);//�Լ��� �Ķ���ͷ� ���޵� ��ü�� ���� �����ڸ� ȣ���Ѵ�.
    s=t;//��ü ���� ���Թ��� ���� �����ڸ� ȣ������ �ʴ´�. �ٸ� �״�� 
        //����(bitwise copy)�ȴ�.
    s.Print();
}