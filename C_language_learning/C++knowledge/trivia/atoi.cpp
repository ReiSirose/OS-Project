#include <iostream>

int atoi (const char* str) {
    int sign {1};
    int result {0};

    int i = 0;

    // check leading whitespace and special character
    while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13 )){
        ++i;
    }

    // check the sign
    if(str[i] == '-'){
        sign = -1;
        ++i;
    }

    // convert string numerical -> int, ignore everything else
    while(str[i] >= '0' && str[i] <= '9'){
        result = result * 10 + (str[i] - '0');
        ++i;
    }
    return sign * result;
}


int main () {
    const char* str {"\n \t -9842 "};
    std::cout << atoi(str)<< std::endl;

}