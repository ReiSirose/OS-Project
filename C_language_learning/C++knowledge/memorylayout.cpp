#include <iostream>
int main() 
{
    int x = 1;
    std::cout << "One: " << &main
    << " Two: " << new int[10]
    << " Three: " << &x;
}