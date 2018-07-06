#include <stdio.h>
#include <string.h>
#include <conio.h>

class CStr {
    char *str;
  public:
    CStr(char *s="") {
        str=new char[strlen(s)+1];//EOS�� ���� +1�� �ʿ��ϴ�.
        strcpy(str,s);//str=s;��� ���� �ʵ��� ����.
        printf("constructor\n");
    }
    ~CStr() {
        delete[] str;//delete str;�̶�� ���� �ʵ��� ����.
        printf("destructor\n");
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