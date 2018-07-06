#include <iostream.h>
#include <stdio.h>
#include <string.h>

class A {
    char* a;
public:
    A(char* s) {
        a=new char[strlen(s)+1];
        strcpy(a,s);
    }
    virtual ~A() {//가상 소멸자
        delete[] a;
        printf("Destructor of class A\n");
    }
    virtual void Print() {
        printf("%s\n",a);
    }
};

class B : public A {
    char* b;
public:
    B(char* s,char* t) : A(t) {
        b=new char[strlen(s)+1];
        strcpy(b,s);
    }
    virtual ~B() {
        delete[] b;
        printf("Destructor of class B\n");
    }
    virtual void Print() {
        A::Print();
        printf("%s\n",b);
    }
};

void main() {
    A* pA;
    pA=new B("hello","world");
    pA->Print();
    delete pA;//소멸자가 가상이 아니면 A클래스의 소멸자만이 호출된다.
}