
#include <utility>
#include <stdexcept>

namespace getcracked 
{
    template <typename T>
    struct custom_deleter
    {
        void operator()(T* pointer) const
        {
            delete pointer;
        }
    };

    template <typename T, typename custom_deleter = custom_deleter<T>>
    class unique_ptr
    {
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

        T* release()
        {
            return std::exchange(m_pointer, nullptr);
        }

        void reset(T* pointer)
        {
            if(m_pointer){
                m_deleter(m_pointer);
            }
            m_pointer = pointer;
        }


        T& operator*() const {return &m_pointer; }
        T* operator->() const {return m_pointer; }
        operator bool() const {return m_pointer != nullptr;}

    private:
        T* m_pointer;
        custom_deleter m_deleter;
    };
}