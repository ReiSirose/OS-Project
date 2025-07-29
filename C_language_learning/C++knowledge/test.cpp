// main.cpp
#include "constant.h"
#include <iostream>

extern const int MAX_VALUE;
int main() {
    std::cout << "The external constant is: " << MAX_VALUE  << std::endl;
    // std::cout << "Another constexpr is: " << ANOTHER_CONST_EXPR << std::endl; // If defined in header

    // MY_EXTERNAL_CONST = 100; // ERROR: cannot modify a const variable
    return 0;
}