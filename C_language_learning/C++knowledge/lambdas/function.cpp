#include <functional>
#include <iostream>

// A plain function
int add(int a, int b) { return a + b; }

// A functor
struct Multiplier {
    int operator()(int a, int b) const { return a * b; }
};

int main() {
    // All three fit in the SAME type
    std::function<int(int, int)> op;

    op = add;                              // free function
    std::cout << op(3, 4) << "\n";         // 7

    op = Multiplier{};                     // functor object
    std::cout << op(3, 4) << "\n";         // 12

    op = [](int a, int b) { return a - b; }; // lambda
    std::cout << op(3, 4) << "\n";         // -1
}