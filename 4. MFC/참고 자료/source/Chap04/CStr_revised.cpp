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
        strcpy(str,s.Get());//const 객체는 const 멤버 함수만을 호출할 수 
                            //있다.
        printf("copy constructor\n");
    }
    ~CStr() {
        delete[] str;
        printf("destructor\n");
    }
    char *Get() const {//함수 뒤의 const는 이 함수가 어떠한 멤버도 변경
                       //시켜서는 안됨을 지시한다.‘변경자’와 ‘this포인
                       //터’에서 자세히 설명할 것이다.
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