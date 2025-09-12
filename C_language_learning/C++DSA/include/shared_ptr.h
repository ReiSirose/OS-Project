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

        shared_ptr(const shared_ptr& other) noexcept : m_ptr{other.m_ptr}, m_control_block{other.m_control_block}
        {
            if(m_control_block){
                std::scoped_lock lock(m_control_block->mutex_);
                ++m_control_block->count_;
            }
        }

        shared_ptr& operator=(const shared_ptr& other) noexcept
        {
            if(this != &other){
                reset(m_ptr);
                m_ptr = other.m_ptr;
                m_ptr = other.m_control_block;
            }
            
            return *this;
        }

        shared_ptr(shared_ptr&& other) noexcept : m_ptr{std::exchange(other.m_ptr, nullptr)}, m_control_block{std::exchange(other.m_control_block, nullptr)}
        {
            
        }

        shared_ptr& operator=(shared_ptr&& other) noexcept
        {
            reset(m_ptr);
            m_ptr = std::exchange(other.m_ptr, nullptr);
            m_control_block = std::exchange(other.m_control_block, nullptr);
        }

        ~shared_ptr()
        {
            reset(nullptr);
        }

        void reset(T* pointer)
        {
            if(m_ptr == pointer){
                return;
            }
            if(m_control_block){
                std::scoped_lock lock(m_control_block->mutex_);
                --m_control_block->count_;
                if(m_control_block->count_ == 0){
                    delete m_ptr;
                    delete m_control_block;
                }
            }
            m_ptr = pointer;
            if(m_ptr){
                m_control_block = new control_block {1, std::mutex{}};
            }
            else{
                m_control_block = nullptr;
            }
        }


        size_t get_count() const
        {
            if(m_control_block){
                return m_control_block->count_;
            }
            return 0;
        }

        T* operator->() const {return m_ptr; }
        T& operator*() const {return *m_ptr; }
        operator bool() const noexcept {return m_ptr != nullptr; }

    private:
        T* m_ptr;
        control_block* m_control_block;
    };
}