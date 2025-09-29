#include <iostream>

class A {
    public: A(int a) {std::cout << a;}
};

class B: virtual public A{
    public: B(int b):A(4) {std::cout << b;}
};

class C : virtual public A{
    public: C(int c): A(3) {std::cout << c;}
};

class D : public B, public C {
    public: D(): B(1), C(2), A(0) {std::cout << "D";}
};

int main (){
    D d;
}