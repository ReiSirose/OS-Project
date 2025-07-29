#include <iostream>

int main (){
    std::cout << 2["123\0"];
    std::cout << "123"[2];
    std::cout << *("123" + 2);
    //they all similar
    // #[] -> *([] + #)
}