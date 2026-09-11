#include <iostream>

template <typename T, size_t size>
class Fixed_vector {
    private:
        T m_vec[size];

    public:
        T* begin() { return m_vec; }
        const T* begin() const { return m_vec; }
        T* end() { return m_vec + size; }
        const T* end() const { return m_vec + size; }
        
        Fixed_vector() {};

        template <typename O, size_t O_size>
        explicit Fixed_vector(const Fixed_vector<O, O_size>& other) {
            std::cout << "Copy\n";
            std::copy(other.begin(), other.end(), begin());
        }
};

int main() {
    const Fixed_vector<int, 5> v1{};
    Fixed_vector<int, 5> v2(v1);
}