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
    CStr& operator=(CStr &s) {//return reference to object
    //CStr operator=(CStr &s) {//return object itself
        delete[] str;
        str=new char[strlen(s.Get())+1];
        strcpy(str,s.Get());
        printf("= operator\n");
        return *this;
    }
};//class CStr

void f(CStr s) {
    s.Print();
}

void main() {
    CStr s("hello"),
         t("world");
    CStr u=s;

    f(u);
    s=t;
    s.Print();
}