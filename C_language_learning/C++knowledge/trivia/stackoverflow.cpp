#include <iostream>
int main()
{
    int hugeArray[10000000];
    hugeArray[0] = 5;
    hugeArray[1] = 10;

    std::cout << (hugeArray[0] + hugeArray[1]);

    return 0;
}