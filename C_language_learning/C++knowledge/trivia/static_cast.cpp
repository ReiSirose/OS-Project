#include <iostream>

int main (){
    std::cout << "Enter a signle character: " << std::endl;
    char word {};
    std::cin >> word;
    std::cout << "You entered '" << word << "', which has ASCII code " << static_cast<int>(word) << std::endl; 
}