#include <iostream>
#define MESSAGE "Hello World!"
int main (){
    
#if 0
    std::cout << "Debug mode" << std::endl;
#endif
    std::cout << MESSAGE << std::endl;
    return 0;
}