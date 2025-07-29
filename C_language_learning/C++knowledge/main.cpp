#include "vector.cpp"
#include <iostream>
#include <iostream>
#include <string>

struct MyClass {
    int x;
    std::string s;

    // Constructor
    MyClass() : x(0), s() {
        std::cout << "Default constructed with " << x << ", " << s << "\n";
    }

    MyClass(int x, std::string s) : x(x), s(s) {
        std::cout << "Constructed with " << x << ", " << s << "\n";
    }

    // 1. Destructor
    ~MyClass() {
        std::cout << "Destroyed with " << x << ", " << s << "\n";
    }

    // 2. Copy Constructor
    MyClass(const MyClass& other) : x(other.x), s(other.s) {
        std::cout << "Copy constructed with " << x << ", " << s << "\n";
    }

    // 3. Copy Assignment Operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            x = other.x;
            s = other.s;
            std::cout << "Copy assigned with " << x << ", " << s << "\n";
        }
        return *this;
    }

    // 4. Move Constructor
    MyClass(MyClass&& other) noexcept : x(other.x), s(std::move(other.s)) {
        other.x = 0; // Reset moved-from state
        std::cout << "Move constructed with " << x << ", " << s << "\n";
    }

    // 5. Move Assignment Operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            x = other.x;
            s = std::move(other.s);
            other.x = 0; // Reset moved-from state
            std::cout << "Move assigned with " << x << ", " << s << "\n";
        }
        return *this;
    }
};

int main (){
    Vector<MyClass> vec;
    // vec.emplace_back(42, "Hello"); // Constructs MyClass(42, "Hello") in-place
    // vec.emplace_back(100, "World"); // Constructs MyClass(100, "World") in-place

    // MyClass hello;
    // vec.push_back(hello);
    // vec.push_back(MyClass(42,"Hello"));
    // vec.emplace_back(100, "C++");
    Vector <int> vect;
    vect.push_back(2);
    vect.emplace_back(3);
    for(int i = 0; i < vect.get_size(); i++){
        std::cout << "Vector position " << i << ": " << vect.at(i) << std::endl;
    }

    
    return 0;
}