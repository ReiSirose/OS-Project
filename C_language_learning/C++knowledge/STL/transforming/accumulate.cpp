#include <numeric>
#include <algorithm>
#include <execution>
#include <vector>
#include <iostream>

int main () {
    std::vector<float> data {3.24, 42.52, 21.51, 47.2 , 14.4};

    float sum_acc = std::accumulate(data.begin(), data.end(), 0.0f);

    float sum_reduce = std::reduce(data.begin(), data.end(), 0.0f);
    std::cout << sum_acc << '\n';
    std::cout << sum_reduce << std::endl;

}