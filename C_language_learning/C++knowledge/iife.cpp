#include <iostream>

int main (){
    // immediately imvocable lambda
    // you can inialize const variable with tenary operator if there only 2 option
    // but if there 3 or more option you can use lambda to initalized with switch statement (can't without the lambda)
    const int id = 1;
    const std::string name = [](int id){
        switch (id)
        {
        case 0:
            return "Zero";
        case 1:
            return "One";
        case 2:
            return "Two";
        default:
            return "Unsuported";
        }
    }(id);
    std::cout << name << std::endl;
}