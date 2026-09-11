#include <iostream>

class Singleton final{
    private:
        Singleton() {};
        ~Singleton() {}

    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        Singleton(Singleton&& ) = delete;
        Singleton& operator=(Singleton&&) = delete;

        static Singleton& create() { 
            static Singleton singleton;
            return singleton;
        }

         void doSomething () {
            std::cout << "Hello" << std::endl;
        }
};



int main () {
    Singleton& ref = Singleton::create();
    ref.doSomething();
    return 0;
}