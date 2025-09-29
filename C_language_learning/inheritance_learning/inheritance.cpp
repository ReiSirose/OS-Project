#include <iostream>

class A {
    public: A() {std::cout << "A";}
};

class B:  public A{
    public: B(){std::cout << "B";}
};

class C :  public A{
    public: C() {std::cout << "C";}
};

class D : public B, public C {
    public: D() {std::cout << "D";}
};

int main (){
    D d;
}
// AABACD