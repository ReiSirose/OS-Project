#include <iostream>
#include <cstring>  // for strlen and strcpy
using std::cout, std::endl;

class Mystring {
private:
    char* m_string;
    int size;
public:
    //default constructor
    Mystring() : m_string(nullptr), size(0) {}

    //user-defined constructor (changed to accept const char*)
    Mystring(const char* buffer) {
        size = strlen(buffer);
        m_string = new char[size + 1];
        strcpy(m_string, buffer);
    }

    //copy constructor
    Mystring(const Mystring& rhs) {
        size = strlen(rhs.m_string);
        m_string = new char[size + 1];
        strcpy(m_string, rhs.m_string);
    }

    //move constructor
    Mystring(Mystring && rhs) noexcept {
        if(this != &rhs) {
            size = rhs.size;
            m_string = rhs.m_string;
            rhs.m_string = nullptr;
            rhs.size = 0;
        }
    }

    //assignment overload
    Mystring& operator= (const Mystring& rhs) {
        if(this != &rhs) {
            size = rhs.size;
            delete[] m_string;
            m_string = new char[size + 1];
            strcpy(m_string, rhs.m_string);
        }
        return *this;
    }

    //move assignment
    Mystring& operator= (Mystring&& rhs) {
        if(this != &rhs) {
            size = rhs.size;
            rhs.size = 0;
            delete[] m_string;
            m_string = rhs.m_string;
            rhs.m_string = nullptr;
        }
        return *this;
    }

    // << overload
    friend std::ostream& operator<<(std::ostream& os, const Mystring& string) {
        os << string.m_string;
        return os;
    }

    ~Mystring() {
        delete[] m_string;
        size = 0;
    }
};

int main (int argc, char** argv) {
    Mystring str1 = "Hello World";
    Mystring str2 = std::move(str1);
    // Mystring str3 = "Hello";
    // str1 = str3;
    // str3 = "No longer Hello";


    cout << str1 << endl;
    cout << str2 << endl;
    // cout << str3 << endl;
}
