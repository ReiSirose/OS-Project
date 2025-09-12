#include <utility>
#include <stdexcept>
#include <mutex>
namespace dev 
{
    struct control_block
    {
        size_t count_{ };
        mutable std::mutex mutex_;
    };

    template <typename T>
    class shared_ptr
    {
    public:
        shared_ptr(): m_ptr{nullptr}, m_control_block{nullptr} { }
        shared_ptr(T* pointer): m_ptr{pointer}
        {
            if(pointer){
                m_control_block = new control_block{1, std::mutex{}};
            }
        }

        shared_ptr(const shared_ptr& other) noexcept : m_ptr{other.m_ptr}, m_control_block{m_control_block}
        {
            if(m_control_block){
                std::scoped_lock lock(m_control_block->mutex_);
                ++m_control_block->count_;
            }
        }

        shared_ptr& operator=(const shared_ptr& other) noexcept
        {
            
        }

        shared_ptr(shared_ptr&& other) noexcept
        {

        }

        shared_ptr& operator=(shared_ptr&& other) noexcept
        {

        }

        ~shared_ptr()
        {

        }

        void reset(T* pointer)
        {

        }


        size_t get_count() const
        {
            return m_control_block->count_;
        }

        T* operator->() const { }
        T& operator*() const { }
        operator bool() const noexcept { }

    private:
        T* m_ptr;
        control_block* m_control_block;
    };
}