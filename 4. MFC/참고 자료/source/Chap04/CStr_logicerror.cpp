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
    CStr u=s;//객체의 선언문에 사용된 대입 연산자는 복사 생성자를 호출한
             //다.

    f(u);//함수의 파라미터로 전달된 객체는 복사 생성자를 호출한다.
    s=t;//객체 간의 대입문은 복사 생성자를 호출하지 않는다. 다만 그대로 
        //복사(bitwise copy)된다.
    s.Print();
}