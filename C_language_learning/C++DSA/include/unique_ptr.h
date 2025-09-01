#include <concepts>
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

    template <typename T>
    class unique_ptr
    {
    public:
        unique_ptr() : m_pointer(nullptr){ }
        explicit unique_ptr(T* pointer) : m_pointer(pointer) {}

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
            custom_deleter<T> deleter;
            deleter(m_pointer);
        }

        [[nodiscard]]T* release()
        {
            return std::exchange(m_pointer, nullptr);
        }

        void reset(T* pointer = nullptr)
        {
            T* old_pointer = m_pointer;
            if(old_pointer){
                custom_deleter<T> deleter;
                deleter(old_pointer);
            }
            m_pointer = pointer;
        }

        T& operator*() const { return *m_pointer;}
        T* operator->() const { return m_pointer;}
        operator bool() const { return is_owning();}
    private:
        T* m_pointer;
        void stealfrom(unique_ptr&&other){
            m_pointer = std::exchange(other.pointer, nullptr);
        }
    };
}