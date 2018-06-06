#include <stdio.h>
#include <string.h>
#include <conio.h>

class CStr {
    char *str;
  public:
    CStr(char *s="") {
        str=new char[strlen(s)+1];//EOS를 위해 +1이 필요하다.
        strcpy(str,s);//str=s;라고 쓰지 않도록 하자.
        printf("constructor\n");
    }
    ~CStr() {
        delete[] str;//delete str;이라고 쓰지 않도록 하자.
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