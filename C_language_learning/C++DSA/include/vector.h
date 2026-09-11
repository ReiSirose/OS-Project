#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

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
            using value_type = typename std::remove_const<typename std::remove_pointer<PointerType>::type>::type;
            using difference_type = std::ptrdiff_t;
            using pointer = PointerType;
            using reference = decltype(*std::declval<PointerType>());

            Iterator() : m_ptr{nullptr} {}
            Iterator(pointer p) : m_ptr{p} {}

            template <typename OtherPointer, typename = std::enable_if_t<std::is_convertible_v<OtherPointer, PointerType>>>
            Iterator(const Iterator<OtherPointer>& other) : m_ptr{other.m_ptr} {}
            
            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }
            reference operator[](difference_type n) const { return m_ptr[n]; }

            Iterator& operator++() { ++m_ptr; return *this; }
            Iterator operator++(int) { auto temp{*this}; ++m_ptr; return temp; }
            Iterator& operator--() { --m_ptr; return *this; }
            Iterator operator--(int) { auto temp{*this}; --m_ptr; return temp; }
            
            Iterator operator+(difference_type n) const { return Iterator(m_ptr + n); }
            Iterator operator-(difference_type n) const { return Iterator(m_ptr - n); }
            Iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
            Iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

            friend Iterator operator+(difference_type n, const Iterator& it) { return Iterator(it.m_ptr + n); }


            difference_type operator-(const Iterator &rhs) const { return m_ptr - rhs.m_ptr; }


            bool operator==(const Iterator &rhs) const { return m_ptr == rhs.m_ptr; }
            bool operator!=(const Iterator &rhs) const { return m_ptr != rhs.m_ptr; }
            bool operator<(const Iterator &rhs) const { return m_ptr < rhs.m_ptr; }
            bool operator<=(const Iterator &rhs) const { return m_ptr <= rhs.m_ptr; }
            bool operator>(const Iterator &rhs) const { return m_ptr > rhs.m_ptr; }
            bool operator>=(const Iterator &rhs) const { return m_ptr >= rhs.m_ptr; }

        private:
            template <typename> friend class Iterator;
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
        using const_iterator = Iterator<const_pointer>;

        Vector() : m_data{nullptr}, m_capacity{0}, m_size{0} {}

        explicit Vector(size_type count) : m_capacity{count}, m_size{count}
        {
            if (count > 0)
            {
                m_data = static_cast<pointer>(::operator new(count * sizeof(value_type)));
                std::uninitialized_default_construct_n(m_data, count);
            }
            else
            {
                m_data = nullptr;
            }
        }

        Vector(size_type count, const_reference value) : m_capacity{count}, m_size{count}
        {
            if (count > 0)
            {
                m_data = static_cast<pointer>(::operator new(count * sizeof(value_type)));
                std::uninitialized_fill_n(m_data, count, value);
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
                std::uninitialized_copy(init.begin(), init.end(), m_data);
            }
            else
            {
                m_data = nullptr;
            }
        }

        ~Vector()
        {
            clear();
            ::operator delete(m_data);
        }

        Vector(const Vector &other) : m_capacity{other.m_capacity}, m_size{other.m_size}
        {
            if (m_capacity > 0)
            {
                m_data = static_cast<pointer>(::operator new(m_capacity * sizeof(value_type)));
                std::uninitialized_copy(other.begin(), other.end(), m_data);
            }
            else
            {
                m_data = nullptr;
            }
        }

        Vector &operator=(const Vector &other)
        {
            if (this != &other)
            {
                clear();
                ::operator delete(m_data);

                m_capacity = other.m_capacity;
                m_size = other.m_size;
                if (m_capacity > 0)
                {
                    m_data = static_cast<pointer>(::operator new(m_capacity * sizeof(value_type)));
                    std::uninitialized_copy(other.begin(), other.end(), m_data);
                }
                else
                {
                    m_data = nullptr;
                }
            }
            return *this;
        }

        Vector(Vector &&other) noexcept 
            : m_data(std::exchange(other.m_data, nullptr)), 
              m_capacity(std::exchange(other.m_capacity, 0)), 
              m_size(std::exchange(other.m_size, 0)) {}

        Vector &operator=(Vector &&other) noexcept
        {
            if (this != &other)
            {
                clear();
                ::operator delete(m_data);

                m_data = std::exchange(other.m_data, nullptr);
                m_capacity = std::exchange(other.m_capacity, 0);
                m_size = std::exchange(other.m_size, 0);
            }
            return *this;
        }

        // Accessors
        bool empty() const { return m_size == 0; }
        bool full() const { return m_size == m_capacity; }
        size_type size() const { return m_size; }
        size_type capacity() const { return m_capacity; }

        reference operator[](size_type index) { return m_data[index]; }
        const_reference operator[](size_type index) const { return m_data[index]; }

        reference at(size_type index)
        {
            if (index >= m_size)
                throw std::out_of_range("Index out of bounds");
            return m_data[index];
        }

        const_reference at(size_type index) const
        {
            if (index >= m_size)
                throw std::out_of_range("Index out of bounds");
            return m_data[index];
        }

        reference front() { return m_data[0]; }
        const_reference front() const { return m_data[0]; }

        reference back() { return m_data[m_size - 1]; }
        const_reference back() const { return m_data[m_size - 1]; }

        pointer data() { return m_data; }
        const_pointer data() const { return m_data; }

        iterator begin() { return iterator(m_data); }
        iterator end() { return iterator(m_data + m_size); }
        const_iterator begin() const { return const_iterator(m_data); }
        const_iterator end() const { return const_iterator(m_data + m_size); }
        const_iterator cbegin() const { return const_iterator(m_data); }
        const_iterator cend() const { return const_iterator(m_data + m_size); }

        void push_back(const_reference value)
        {
            if (full() || m_capacity == 0)
            {
                grow_capacity();
            }
            new (&m_data[m_size]) value_type(value);
            m_size++;
        }

        void push_back(value_type &&value)
        {
            if (full() || m_capacity == 0)
            {
                grow_capacity();
            }
            new (&m_data[m_size]) value_type(std::move(value));
            m_size++;
        }

        template <typename... Args>
        void emplace_back(Args &&...args)
        {
            if (full() || m_capacity == 0)
            {
                grow_capacity();
            }
            new (&m_data[m_size]) value_type(std::forward<Args>(args)...);
            m_size++;
        }

        void pop_back()
        {
            if (m_size > 0)
            {
                m_size--;
                m_data[m_size].~T();
            }
        }

        void resize(size_type new_size)
        {
            if (new_size == m_size)
                return;

            if (new_size > m_capacity)
            {
                allocate_and_transfer(new_size);
            }

            if (new_size > m_size)
            {
                for (size_type i = m_size; i < new_size; ++i)
                {
                    new (&m_data[i]) value_type();
                }
            }
            else
            {
                for (size_type i = new_size; i < m_size; ++i)
                {
                    m_data[i].~value_type();
                }
            }
            m_size = new_size;
        }

        void clear()
        {
            for (size_type i = 0; i < m_size; ++i)
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

        void reserve(size_type new_capacity)
        {
            if (new_capacity > m_capacity)
            {
                allocate_and_transfer(new_capacity);
            }
        }

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

        void allocate_and_transfer(size_type new_capacity)
        {
            if (new_capacity < m_size)
                return;

            pointer new_data = static_cast<pointer>(::operator new(new_capacity * sizeof(value_type)));

            try
            {
                if constexpr (std::is_nothrow_move_constructible_v<value_type>)
                {
                    std::uninitialized_move_n(m_data, m_size, new_data);
                }
                else
                {
                    std::uninitialized_copy_n(m_data, m_size, new_data);
                }
            }
            catch (...)
            {
                ::operator delete(new_data);
                throw;
            }

            for (size_type i = 0; i < m_size; ++i)
            {
                m_data[i].~value_type();
            }
            ::operator delete(m_data);

            m_capacity = new_capacity;
            m_data = new_data;
        }

        void grow_capacity()
        {
            constexpr size_type DEFAULT_VECTOR_SIZE = 4;
            size_type new_capacity = (m_capacity > 0) ? m_capacity * 2 : DEFAULT_VECTOR_SIZE;
            allocate_and_transfer(new_capacity);
        }
    };
}