#include <cstddef> // For size_t
#include <stdexcept> // For exceptions

template <typename T>
class Vector {
private:
    T* data;          // Pointer to the dynamic array
    size_t capacity;  // Total allocated memory
    size_t size;      // Number of elements currently in the vector

public:
    // Constructor
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        // TODO: Free the allocated memory
        // Hint: Loop through elements to call destructors if T is non-trivial,
        // then deallocate the memory using delete[]s
        delete [] data;
    }

    // Copy Constructor
    Vector(const Vector& other) : data(nullptr), capacity(0), size(0) {
        // TODO: Allocate memory for 'capacity' elements and copy elements from 'other'
        // Hint: Set capacity and size to match 'other', allocate new memory,
        // and copy each element using a loop or placement new
        capacity = other.capacity;
        size = other.size;
        data = new T  [capacity];
        for(int i = 0; i < size; i++){
            data[i] = other[i];
        }
    }

    // Copy Assignment Operator
    Vector& operator=(const Vector& other) {
        // TODO: Handle self-assignment, free existing resources,
        // and copy data from 'other'
        // Hint: Check if this != &other, deallocate current data,
        // allocate new memory, and copy elements
        if(this != &other){
           delete [] data;
           capacity = other.capacity;
           size = other.size;
           data = new T [capacity];
           for(int i = 0; i < size; i++){
            data[i] = other.data[i];
           }
        }
        return *this;
    }

    // Move Constructor
    Vector(Vector&& other) noexcept : data(nullptr), capacity(0), size(0) {
        // TODO: Steal resources from 'other' and set 'other' to a valid empty state
        // Hint: Transfer data, capacity, and size, then set other.data to nullptr
        data = other.data;
        capacity = other.capacity;
        size = other.size;

        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    // Move Assignment Operator
    Vector& operator=(Vector&& other) noexcept {
        // TODO: Handle self-assignment, free existing resources,
        // and steal resources from 'other'
        // Hint: Similar to move constructor, but first free current resources
        if(this != &other){
            delete [] data;
            data = other.data;
            capacity = other.capacity;
            size = other.size;

            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    // Push back an element (copy)
    void push_back(const T& value) {
        // TODO: Add element to the end of the vector
        // Hint: Check if size == capacity; if so, resize (e.g., double capacity),
        // then copy-construct the new element at data[size] and increment size
        if(size == capacity){
            if(capacity == 0) capacity = 1;
            else capacity *= 2;
            reallocate(capacity);
        }
        data[size++] = value;
    }

    // Push back an element (move)
    void push_back(T&& value) {
        // TODO: Move element to the end of the vector
        // Hint: Similar to push_back(const T&), but use move constructor
        // to avoid unnecessary copying
        if(size == capacity){
            if(capacity == 0) capacity = 1;
            else capacity *= 2;
            reallocate(capacity);
        }
        data[size++] = std::move(value);
    }

    // Emplace back (construct in-place)
    template <typename... Args>
    void emplace_back(Args&&... args) {
        // TODO: Construct element in-place at the end of the vector
        // Hint: Resize if needed, then use placement new to construct
        // the element at data[size] with the forwarded arguments
        if(size == capacity){
            if(capacity == 0) capacity = 1;
            else capacity *= 2;
            reallocate(capacity);
        }
        new (&data[size]) T(std::forward<Args>(args)...);
        size++;
    }

    // Pop back (remove last element)
    void pop_back() {
        // TODO: Remove the last element
        // Hint: Check if size > 0, call destructor on data[size-1], and decrement size
        if(size > 0){
            data[size--].~T();
        }
    }

    // Access element at index (with bounds checking)
    T& at(size_t index) {
        // TODO: Return element at index, throw if out of bounds
        // Hint: Check if index >= size, throw std::out_of_range if true,
        // otherwise return data[index]
        if (index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    const T& at(size_t index) const {
        // TODO: Const version of at()
        // Hint: Same as above, but return const reference
        if (index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // Access element at index (no bounds checking)
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    
    size_t get_size() const { return size; }

    
    size_t get_capacity() const { return capacity; }

    // Resize the vector (change size)
    void resize(size_t new_size) {
        // TODO: Change the size to new_size
        // Hint: If new_size > capacity, reallocate with new capacity;
        // if new_size < size, destroy excess elements; if new_size > size,
        // default-construct new elements
        if(new_size > capacity){
            reallocate(new_size);
        }
        if(new_size > size){
            for(int i = size; i < new_size; i++){
                new (&data[i]) T();
            }
        }
        else if (new_size < size){
            for(int i = new_size; i < size; i++){
                data[i].~T();
            }
        }
        size = new_size;
    }

    // Reserve memory (change capacity)
    void reserve(size_t new_capacity) {
        // TODO: Ensure the vector has at least new_capacity
        // Hint: If new_capacity > capacity, allocate new memory,
        // move existing elements, and free old memory
        if(new_capacity > capacity){
            reallocate(new_capacity);
        }
    }

    // Clear the vector (remove all elements)
    void clear() {
        // TODO: Remove all elements but keep capacity
        // Hint: Call destructors for all elements and set size to 0
        for(int i = 0; i < size; i++){
            data[i].~T();
        }
        size = 0;
    }

private:
    // Helper function to reallocate memory
    void reallocate(size_t new_capacity) {
        // TODO: Allocate new memory and move elements
        // Hint: Allocate new array, move elements using move constructor,
        // free old memory, and update data, capacity
        T* new_data = new T[new_capacity];
        for(int i = 0; i < size; i++){
            new_data[i] = std::move(data[i]);
        }
        capacity = new_capacity;
        delete [] data;
        data = new_data;
        new_data = nullptr;
    }
};
/*  
    Thing I take from this
    1. move operator
    2. placement new
    3. template
    4. varadic template
*/ 