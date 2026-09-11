#include <iostream>
#include <vector>
#include <algorithm>

void printVector(const std::vector<int>& nums) {
    for(const auto& num : nums) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> doubled;

    std::transform(nums.begin(), nums.end(), std::back_inserter(doubled), [](const auto& n) {return n * 2;});
    printVector(nums);
    printVector(doubled);

    std::transform(nums.begin(), nums.end(), nums.begin(), [](const auto& n) {return n * n;});
    printVector(nums);
    printVector(doubled);
}