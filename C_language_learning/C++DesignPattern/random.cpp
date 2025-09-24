#include <iostream>
class Random
{
private:
    float m_random_generator;
    Random()
    {
        std::cout << "instance instantiate" << std::endl;
    }
    float IFloat() {return m_random_generator;}

public:
    Random(const Random &instance) = delete;
    Random &operator=(const Random &instance) = delete;
    static Random& Get()
    {
        static Random s_instance;
        return s_instance;
    }
    static float Float() {return Get().IFloat();}
    
};


int main()
{
    
}