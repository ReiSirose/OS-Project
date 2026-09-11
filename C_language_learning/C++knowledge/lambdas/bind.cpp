#include <functional>
#include <iostream>

int add(int a, int b) { return a + b; }

int add3 (int a, int b, int c) {return a + b + c;}

int main() {
    using namespace std::placeholders;

    // "Lock in" the first argument as 10.
    // _1 means "fill this in later with the first arg you give me."
    auto add_ten = std::bind(add, 10, _1);
    auto add_two = std::bind(add3, 10, _1, _2);

    std::cout << add_ten(5) << "\n";   // 15
    std::cout << add_ten(20) << "\n";  // 30
    std::cout << add_two(20, 30) << "\n";
    std::cout << add_two(5,4) << "\n";

}