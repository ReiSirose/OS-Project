#include <iostream>
#include <sstream>

int main () {
    std::stringstream buf1; 
    buf1 << 7;
    int n = 0;
    buf1 >> n;
    std::cout << "buf1 = " << buf1.str() << " n = " << n << '\n';

    std::istringstream ss {"-10"};
    ss >> n;
    std::cout << "n = " << n << '\n';
    
    n++;
    std::ostringstream os;
    os << n;
    std::cout << "os = " << os.str() << " n = " << n << '\n';
    return 0;
}