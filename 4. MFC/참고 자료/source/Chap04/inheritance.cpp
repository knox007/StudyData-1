#include <stdio.h>
#include <iostream.h>

class A {
    int i;
public:
    A() {
        i=0;
    }
    void Print() { cout << i << endl; }
};//class A

class B : public A {
    int i;
public:
    B() {
        i=1;
    }
    void Print() { cout << i << endl; }
};//class B

class C : public B {
    int i;
public:
    C() {
        i=2;
    }
    void Print() { cout << i << endl; }
};//class C

void main() {
    A* ap;
    B b;
    C c;
    ap=&b;//�� ������ �����Ѱ�?
    ap->Print();//�����ϴٸ�, ������ ȣ��Ǵ°�?
    ap=&c;
    ap->Print();
}//main