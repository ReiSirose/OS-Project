#include <utility>
int main()
{
    const int a {0};
    int b = std::move(a);
}