#include "logger.h"
#include "math_utils.h"
#include <iostream>

int main(){
    log_message("Starting program.");
    int result = add(5, 7);
    std::cout << "5 + 7 = " << result;
    return 0;
}