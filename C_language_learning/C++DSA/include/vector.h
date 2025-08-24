#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <type_traits>

namespace dev
{
    template <typename T>
    class Vector
    {

        template <typename PointerType>
        class Iterator
        {

        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = typename std::remove_const<typename std::remove_pointer<PointerType>::type>::type; // T
            using difference_type = std::ptrdiff_t;
            using pointer = PointerType;
            using reference = typename std::add_lvalue_reference<value_type>::type; // T& or const T&
            // Constructor
            Iterator() : m_ptr{nullptr} {}
            Iterator(pointer p) : m_ptr{p} {}

            // Operator
            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // prefix-increment
            Iterator &operator++()
            {
                ++m_ptr;
                return *this;
            }
            // postfix-increment
            Iterator operator++(int)
            {
                auto temp{*this};
                ++m_ptr;
                return temp;
            }
            Iterator &operator--()
            {
                --m_ptr;
                return *this;
            }
            Iterator operator--(int)
            {
                auto temp{*this};
                --m_ptr;
                return temp;
            }
            Iterator operator+(difference_type n) const { return Iterator(m_ptr + n); }
            Iterator operator-(difference_type n) const { return Iterator(m_ptr - n); }
            difference_type operator-(Iterator &rhs) const { return m_ptr - rhs.m_ptr; }

            // Comparison
            bool operator==(const Iterator &rhs) const { return m_ptr == rhs.m_ptr; }
            bool operator!=(const Iterator &rhs) const { return m_ptr != rhs.m_ptr; }
            bool operator<(const Iterator &rhs) const { return m_ptr < rhs.m_ptr; }
            bool operator<=(const Iterator &rhs) const { return m_ptr <= rhs.m_ptr; }
            bool operator>(const Iterator &rhs) const { return m_ptr > rhs.m_ptr; }
            bool operator>=(const Iterator &rhs) const { return m_ptr >= rhs.m_ptr; }

        private:
            pointer m_ptr;
        };

    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator = Iterator<pointer>;
        using const_iterator = Iterator<const const_pointer>;
        // Constructor
        Vector() : m_data{nullptr}, m_capacity{0}, m_size{0} {}

        explicit Vector(size_type count) : m_capacity{count}, m_size{count}
        {
            if (count > 0)
            {
                m_data = static_cast<pointer>(::operator new(count * sizeof(value_type))); // Raw allocation
            }
            else
            {
                m_data = nullptr;
            }
        }

        Vector(size_type count, reference value) : m_capacity{count}, m_size{count}
        {
            if (count > 0)
            {
                m_data = static_cast<pointer>(::operator new(count * sizeof(value_type))); // Raw allocation
                std::uninitialized_fill(m_data, m_data + count, value);
            }
            else
            {
                m_data = nullptr;
            }
        }
        Vector(std::initializer_list<value_type> init) : m_capacity{init.size()}, m_size{init.size()}
        {
            if (m_capacity > 0)
            {
                m_data = static_cast<pointer>(::operator new(m_capacity * sizeof(value_type)));
                std::copy(init.begin(), init.end(), m_data);
            }
            else
            {
                m_data = nullptr;
            }
        }

        // Destructor
        ~Vector()
        {
            // TODO: add destructor for non-trivial data type
            delete[] m_data;
        }

        // Copy Constructor
        Vector(const Vector &other) : m_capacity{other.m_capacity}, m_size{other.m_size}
        {
            if (m_capacity > 0)
            {
                m_data = static_cast<pointer>(::operator new(m_capacity * sizeof(value_type)));
                std::copy(other.begin(), other.end(), m_data);
            }
            else
            {
                m_data = nullptr;
            }
        }

        // Copy Assignment Operator
        Vector &operator=(const Vector &other)
        {
            // Hint: Check if this != &other, deallocate current data,
            // allocate new memory, and copy element
            if (this != &other)
            {
                delete[] m_data;
                m_capacity = other.capacity;
                m_size = other.size;
                if (m_capacity > 0)
                {
                    m_data = static_cast<pointer>(::operator new(m_capacity * sizeof(value_type)));
                    std::copy(other.begin(), other.end(), m_data);
                }
                else
                {
                    m_data = nullptr;
                }
            }
            return *this;
        }

        // Move Constructor // Hint: Transfer data, capacity, and size, then set other.data to nullptr
        Vector(Vector &&other) noexcept : m_data(std::exchange(other.m_data, nullptr)), m_capacity(std::exchange(other.capacity, 0)), m_size(std::exchange(other.size, 0)) {}

        // Move Assignment Operator
        Vector &operator=(Vector &&other) noexcept
        {
            // Hint: Similar to move constructor, but first free current resources
            // TODO: use std::move function to implement this
            Vector(std::move(other)).swap(*this);
            return *this;
        }
        void assign(size_type count, const_reference value_type) = default;
        void assign(std::initializer_list<T> ilist) = default;
        // Accessors
        bool empty() const { return m_size == 0; }
        bool full() const { return m_size == m_capacity; }
        size_type size() const { return m_size; }
        size_type capacity() const { return m_capacity; }

        reference operator[](size_type index) { return m_data[index]; }
        const_reference operator[](size_type index) const { return m_data[index]; }

        reference at(size_type index)
        {
            if (index >= size)
                throw std::out_of_range("Index out of bounds");
            return data[index];
        }
        const_reference at(size_type index)
        {
            if (index >= size)
                throw std::out_of_range("Index out of bounds");
            return data[index];
        }
        reference front() { return m_data[0]; }
        const_reference front() const { return m_data[0]; }

        reference back() { return m_data[m_size - 1]; }
        const_reference back() const { return m_data[m_size - 1]; }

        pointer data() { return m_data; }
        const_pointer data() const { return m_data; }

        // Iterator
        iterator begin() { return iterator(m_data); }
        iterator end() { return iterator(m_data + m_size); }
        const_iterator begin() const { return const_iterator(m_data); }
        const_iterator end() const { return const_iterator(m_data + m_size); }
        const_iterator cbegin() const { return const_iterator(m_data); }
        const_iterator cend() const { return const_iterator(m_data + m_size); }

        // Modifier
        // Push back an element (copy)
        void push_back(const_reference value)
        {
            // Hint: Check if size == capacity; if so, resize (e.g., double capacity),
            // then copy-construct the new element at data[size] and increment size
            if (full() || capacity() == 0)
            {
                grow_capacity();
            }
            
            new (&m_data[m_size]) value_type(value);
            m_size++;
        }

        // Push back an element (move)
        void push_back(value_type &&value)
        {
            if (full() || capacity() == 0)
            {
                grow_capacity();
            }

            new (&m_data[m_size]) value_type(std::move(value));
            m_size++;
        }

        // Emplace back (construct in-place)
        template <typename... Args>
        void emplace_back(Args &&...args)
        {
            // Hint: Resize if needed, then use placement new to construct
            // the element at data[size] with the forwarded arguments
            if (full() || capacity() == 0)
            {
                grow_capacity();
            }
            new (&data[m_size]) value_type(std::forward<Args>(args)...);
            m_size++;
        }

        // Pop back (remove last element)
        void pop_back()
        {
            // Hint: Check if size > 0, call destructor on data[size-1], and decrement size
            if (m_size > 0)
            {
                m_size--;
                data[m_size].~T();
            }
        }

        iterator insert(const_iterator pos, const_reference value) = default;
        iterator erase(iterator pos) = default;
        iterator erase(const_iterator pos) = default;

        // Resize the vector (change size)
        void resize(size_type new_size)
        {
            // TODO: Change the size to new_size
            // Hint: If new_size > capacity, reallocate with new capacity;
            // if new_size < size, destroy excess elements; if new_size > size,
            // default-construct new elements
            if (new_size == m_size)
            {
                return;
            }

            if (new_size > capacity)
            {
                allocate_and_transfer(new_size);
            }
            if (new_size > m_size)
            {
                for (int i = m_size; i < new_size; i++)
                {
                    new (&data[i]) value_type();
                }
            }
            else if (new_size < m_size)
            {
                for (int i = new_size; i < size; i++)
                {
                    m_data[i].~T();
                }
            }
            m_size = new_size;
        }
        // Clear the vector (remove all elements)
        void clear()
        {
            // TODO: use iterator and destroy for better optimization
            // Hint: Call destructors for all elements and set size to 0
            for (int i = 0; i < m_size; i++)
            {
                m_data[i].~value_type();
            }
            m_size = 0;
        }

        void swap(Vector &other)
        {
            using std::swap;
            swap(m_data, other.m_data);
            swap(m_capacity, other.m_capacity);
            swap(m_size, other.m_size);
        }

        // Capacity
        // Reserve memory (change capacity)
        void reserve(size_type new_capacity)
        {
            // Hint: If new_capacity > capacity, allocate new memory,
            // move existing elements, and free old memory
            if (new_capacity > m_capacity)
            {
                allocate_and_transfer(new_capacity);
            }
        }
        // Shrink so capacity == size
        void shrink_to_fit()
        {
            if (m_capacity > m_size)
            {
                allocate_and_transfer(m_size);
            }
        }

    private:
        pointer m_data;
        size_type m_capacity;
        size_type m_size;
        // Helper function to reallocate memory
        void allocate_and_transfer(size_type new_capacity)
        {
            if (new_capacity <= m_size)
            {
                return;
            }
            pointer new_data = nullptr;
            try
            {
                new_data = static_cast<pointer>(::operator new(new_capacity * sizeof(value_type)));
            }
            catch (...)
            {
                throw;
            }

            try
            {
                if (std::is_nothrow_move_constructible<value_type>::value)
                {
                    std::uninitialized_move(begin(), end(), new_data);
                }
                else
                {
                    std::uninitialized_copy(begin(), end(), new_data);
                }
            }
            catch (...)
            {
                ::operator delete(new_data) throw;
            }
            for (Vector::iterator it = begin(); it < end(); ++it)
            {
                m_data[i].~value_type();
            }
            ::operator delete(m_data);
            // TODO: change/invalidate the iterator
            m_capacity = new_capacity;
            m_data = new_data;
        }
        void grow_capacity()
        {
            static const int DEFAULT_VECTOR_SIZE = 4;
            size_type new_capacity{m_capacity};
            if (m_capacity > 0)
            {
                new_capacity *= 2;
            }
            else
            {
                new_capacity = DEFAULT_VECTOR_SIZE;
            }
            allocate_and_transfer(new_capacity);
        }
    };
    /*
        Thing I take from this
        1. move operator
        2. placement new
        3. template
        4. varadic template
    */
}