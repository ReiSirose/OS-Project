#include "logger.h"
#include <iostream>

void log_message(const std::string& msg){
    std::cout << "[LOG]: " << msg << std::endl;
}