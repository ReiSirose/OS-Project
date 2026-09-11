#include <vector>
#include <algorithm>
#include <iostream>

int main () {
    std::vector<int> nums = {10, 20, 20, 20, 30, 40};
    auto lower = std::lower_bound(nums.begin(), nums.end(), 20);
    auto upper = std::upper_bound(nums.begin(), nums.end(), 20);

    std::cout << "lower_bound (20) index: " << std::distance(nums.begin(), lower) << '\n';
    std::cout << "upper_bound (20) index: " << std::distance(nums.begin(), upper) << '\n';

    auto count = std::distance(lower, upper);
    std::cout << "Count of 20 " << count << "\n";

    auto lower_missing = std::lower_bound(nums.begin(), nums.end(), 25);
    std::cout << "lower_bound (25) points to: " << *lower_missing << '\n';

}