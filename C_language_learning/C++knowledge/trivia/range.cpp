// Type your code here, or load an example.
#include <iostream>
#include <vector>
#include<string>
std::vector<int> numbers;
std::string name {"Hello World"};
std::vector<bool> flags = {true, false, true};

struct RingBuffer {
    float data[256];
    int start = 0;
    int count = 256;

    // Raw pointers are perfectly valid iterators
    float* begin() { return data + start; }
    float* end()   { return data + start + count; }
};

static void fill_buffer(RingBuffer& buffer){
    memset(buffer.data, 1.0f, 256);
}

int main()
 {
    numbers.push_back(1);
    numbers.push_back(2);
    for(const auto& number : numbers){
        // numbers.push_back(3);
        std::cout << number << std::endl;
    }

    for (auto& ch : name.substr(0, 5)) {
    // get_string()'s return value is kept alive by auto&& __range
    // but substr() returns a NEW temporary that dies immediately
        std::cout << ch;
    }

    for (auto&& f : flags) {    // ERROR: can't bind lvalue ref to proxy
        f = true;
    }

    
    RingBuffer buf; 
    fill_buffer(buf);
    for (const auto& sample : buf) {
        std::cout << sample << " " << std::endl;
    }

 }

