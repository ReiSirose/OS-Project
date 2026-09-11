// Primary template
#include <iostream>

template <typename T>
void process(T value) {
    std::cout << "Primary template\n";
}

// Overload for pointers
template <typename T>
void process(T* value) {
    std::cout << "Pointer overload\n";
}

// Full specialization of primary template
template <>
void process<int*>(int* value) {
    std::cout << "int* specialization\n";
}

int main() {
    int x = 42;
    int* ptr = &x;
    
    process(ptr);  // What gets called?
    // Answer: "Pointer overload" - NOT the specialization!
    // The overload is more specialized than the primary template,
    // so the specialization of the primary template is never considered
}