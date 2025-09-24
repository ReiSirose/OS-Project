#include <iostream>
class Singleton
{
private:
    static Singleton s_instance;
    Singleton()
    {
        std::cout << "instance instantiate" << std::endl;
    }
    

public:
    Singleton(const Singleton &instance) = delete;
    Singleton &operator=(const Singleton &instance) = delete;
    static Singleton& Get()
    {
        return s_instance;
    }
    void Function(){std::cout << "singleton function" << std::endl;}
};
Singleton Singleton::s_instance;

int main()
{
    Singleton::Get().Function();
}