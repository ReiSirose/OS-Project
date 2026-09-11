// vector.h
template<typename T>
class vector {
public:
    T& at(int);
};

// Definition still in the header
template<typename T>
T& vector<T>::at(int i) {
    // some code
    return i;
}