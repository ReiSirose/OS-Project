
#include <utility>
#include <stdexcept>

namespace dev 
{
    template <typename T>
    struct custom_deleter
    {
        void operator()(T* pointer) const
        {
            delete pointer;
        }
    };

    template <typename T, typename Deleter = custom_deleter<T>>
    class unique_ptr
    {
        using element_type = T;
        using pointer = T*;
        using reference = T&;
        
    public:
        unique_ptr(): m_pointer(nullptr){}
        unique_ptr(T* pointer): m_pointer(pointer){}

        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        unique_ptr(unique_ptr&& other) noexcept
        {
            m_pointer = other.release();
        }

        unique_ptr& operator=(unique_ptr&& other) noexcept
        {
            if(this != &other){
                reset(other.release());
            }
            return *this;
        }

        ~unique_ptr()
        {
            m_deleter(m_pointer);
        }

        //modifier
        pointer release() noexcept
        {
            return std::exchange(m_pointer, nullptr);
        }

        void reset(pointer pointer) noexcept
        {
            if(m_pointer){
                m_deleter(m_pointer);
            }
            m_pointer = pointer;
        }

        void swap(unique_ptr& other){
            m_pointer = std::exchange(other.release(), release());
            m_deleter = std::exchange(other.getDeleter(), getDeleter());
        }

        //observer
        operator bool() const {return m_pointer != nullptr;}

        // deference overload
        reference operator*() const {return &m_pointer; }
        pointer operator->() const {return m_pointer; }
        Deleter& getDeleter() const {return m_deleter;}
        const Deleter& getDeleter const {return m_deleter;}

    private:
        pointer m_pointer;
        Deleter m_deleter;
    };
}

template <class T, class ... Args>
dev::unique_ptr<T> make_unique(Args&& ...){
    return dev::unique(new T (std::forward<Args>(Args)...));
}