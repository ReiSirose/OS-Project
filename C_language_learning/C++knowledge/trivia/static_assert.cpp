#include <iostream>
#include <type_traits>

// A template function meant ONLY for integral numbers (int, long, short, etc.)
template <typename T>
void processInteger(T value) {
    // The compiler checks std::is_integral<T>::value before instantiating the template
    static_assert(std::is_integral<T>::value, 
                  "Error: processInteger can only be used with integer types!");
    
    std::cout << "Processing: " << value << "\n";
}

int main() {
    processInteger(42);    // Compiles successfully
    
    processInteger(3.14); // UNCOMMENT TO SEE ERROR: 
    // "Error: processInteger can only be used with integer types!"
    
    return 0;
}