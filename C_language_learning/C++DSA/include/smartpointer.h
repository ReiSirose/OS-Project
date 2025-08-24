#include <iostream>

// Sample class to test the custom smart pointers
class TestResource {
public:
    TestResource(const char* name) : name_(name) {
        std::cout << "TestResource " << name_ << " created\n";
    }
    ~TestResource() {
        std::cout << "TestResource " << name_ << " destroyed\n";
    }
    void doSomething() const {
        std::cout << "Doing something with " << name_ << "\n";
    }
private:
    const char* name_;
};


// ------------------------------- UNIQUE POINTER ---------------------------------------------------
// CustomUniquePtr: Mimics std::unique_ptr for exclusive ownership
template <typename T>
class CustomUniquePtr {
public:
    // Constructor: Takes ownership of a raw pointer
    explicit CustomUniquePtr(T* ptr = nullptr) : ptr_(ptr) {}

    // Destructor: Automatically deletes the managed object
    ~CustomUniquePtr() {
        // TODO: Delete the managed object
        // Hint: Use delete on ptr_ if it's not nullptr
    }

    // Delete copy constructor and copy assignment to ensure exclusive ownership
    CustomUniquePtr(const CustomUniquePtr&) = delete;
    CustomUniquePtr& operator=(const CustomUniquePtr&) = delete;

    // Move constructor
    CustomUniquePtr(CustomUniquePtr&& other) noexcept : ptr_(other.ptr_) {
        // TODO: Implement move constructor
        // Hint: Set other.ptr_ to nullptr after transferring ownership
    }

    // Move assignment
    CustomUniquePtr& operator=(CustomUniquePtr&& other) noexcept {
        // TODO: Implement move assignment
        // Hint: Delete current ptr_, assign other.ptr_ to ptr_, then set other.ptr_ to nullptr
        return *this;
    }

    // TODO: Access the managed object
    // Hint: Return a reference to the object if ptr_ is not nullptr, else handle error
    T& operator*() const {
        // TODO: Implement dereference operator
        // Hint: Check ptr_ and return *ptr_
        return *ptr_;
    }

    // TODO: Access the raw pointer
    // Hint: Return ptr_ for use in method calls
    T* operator->() const {
        // TODO: Implement arrow operator
        // Hint: Return ptr_ if valid
        return ptr_;
    }

    // TODO: Check if the pointer is valid
    // Hint: Return true if ptr_ is not nullptr
    bool isValid() const {
        // TODO: Implement validity check
        // Hint: Return ptr_ != nullptr
        return false;
    }

    // TODO: Release the managed object without deleting
    // Hint: Return ptr_ and set ptr_ to nullptr
    T* release() {
        // TODO: Implement release
        // Hint: Store ptr_, set ptr_ to nullptr, return stored pointer
        return nullptr;
    }

    // TODO: Reset to a new pointer or nullptr
    // Hint: Delete current ptr_ and assign new_ptr
    void reset(T* new_ptr = nullptr) {
        // TODO: Implement reset
        // Hint: Delete ptr_, assign new_ptr to ptr_
    }

private:
    T* ptr_;
};


// ------------------------------- SHARE POINTER ---------------------------------------------------
// CustomSharedPtr: Mimics std::shared_ptr with reference counting
template <typename T>
class CustomSharedPtr {
public:
    // Constructor: Takes ownership of a raw pointer
    explicit CustomSharedPtr(T* ptr = nullptr) : ptr_(ptr), ref_count_(ptr ? new unsigned(1) : nullptr) {}

    // Copy constructor: Shares ownership
    CustomSharedPtr(const CustomSharedPtr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        // TODO: Implement copy constructor
        // Hint: Increment ref_count_ if not nullptr
    }

    // Copy assignment
    CustomSharedPtr& operator=(const CustomSharedPtr& other) {
        // TODO: Implement copy assignment
        // Hint: Decrease ref_count_ of current ptr_, assign other's ptr_ and ref_count_, increment ref_count_
        return *this;
    }

    // Destructor: Decrements reference count and deletes if zero
    ~CustomSharedPtr() {
        // TODO: Implement destructor
        // Hint: Decrease ref_count_, delete ptr_ and ref_count_ if ref_count_ reaches 0
    }

    // TODO: Access the managed object
    // Hint: Return a reference to the object if ptr_ is not nullptr
    T& operator*() const {
        // TODO: Implement dereference operator
        // Hint: Check ptr_ and return *ptr_
        return *ptr_;
    }

    // TODO: Access the raw pointer
    // Hint: Return ptr_ for method calls
    T* operator->() const {
        // TODO: Implement arrow operator
        // Hint: Return ptr_ if valid
        return ptr_;
    }

    // TODO: Get the reference count
    // Hint: Return the value of ref_count_ if it exists, else 0
    unsigned getCount() const {
        // TODO: Implement reference count retrieval
        // Hint: Return *ref_count_ if ref_count_ is not nullptr, else 0
        return 0;
    }

private:
    T* ptr_;
    unsigned* ref_count_;
};



// ------------------------------- WEAK POINTER ---------------------------------------------------
// CustomWeakPtr: Mimics std::weak_ptr for non-owning references
template <typename T>
class CustomWeakPtr {
public:
    // Constructor: Takes a CustomSharedPtr to reference
    CustomWeakPtr(const CustomSharedPtr<T>& shared) : ptr_(shared.ptr_), ref_count_(shared.ref_count_) {
        // TODO: Initialize weak pointer
        // Hint: Copy ptr_ and ref_count_ from shared, but don't increment ref_count_
    }

    // Destructor: No resource cleanup
    ~CustomWeakPtr() {
        // TODO: Implement destructor
        // Hint: No need to delete ptr_ or ref_count_, as weak_ptr doesn't own them
    }

    // TODO: Check if the resource is still valid
    // Hint: Check if ref_count_ exists and is greater than 0
    bool isExpired() const {
        // TODO: Implement expiration check
        // Hint: Return true if ref_count_ is nullptr or *ref_count_ is 0
        return true;
    }

    // TODO: Access the resource if not expired
    // Hint: Create a temporary CustomSharedPtr if not expired
    CustomSharedPtr<T> lock() const {
        // TODO: Implement lock
        // Hint: Return CustomSharedPtr<T>(ptr_) if not expired, else empty CustomSharedPtr
        return CustomSharedPtr<T>();
    }

private:
    T* ptr_;
    unsigned* ref_count_;
};