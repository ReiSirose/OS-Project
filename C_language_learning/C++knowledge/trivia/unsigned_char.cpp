#include <iostream>

int main() {
    std::cout << "Enter a number:";

    int x = 10;
    uint8_t y;
    std::cin >> y;

    x *= y;
    std::cout << x;

    return 0;
}

/*
so it will take in a unsigned char (uint8_t)
-> 11, y = '1'
-> y = 49;
-> x *= 49 * 10
-> x = 490
*/