#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> data = {14, 3, 27, 8, 19};

    auto [min_it, max_it] = std::minmax_element(data.begin(), data.end());
    if (min_it != data.end()) {
        std::cout << "Min: " << *min_it << '\n'; // 3
        std::cout << "Max: " << *max_it << '\n'; // 27
    }
}