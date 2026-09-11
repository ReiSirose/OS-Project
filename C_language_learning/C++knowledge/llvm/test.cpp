#include <iostream>

int square(int x) { return x * x; }

int main() {
    int value = 5;
    int result = square(value);
    
    std::cout << "The square of " << value << " is " << result << std::endl;
    
    return 0;
}