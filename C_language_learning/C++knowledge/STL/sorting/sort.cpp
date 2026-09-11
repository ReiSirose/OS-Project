#include <iostream>
#include <algorithm>
#include <vector>


struct Player {
    std::string name;
    int score;
};

void printVector(const std::vector<int>& nums) {
    for(const auto& num : nums) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
void printVector(const std::vector<Player>& players) {
    for(const auto& player : players) {
        std::cout << player.name << " ";
    }
}

int main () {
    std::vector<int> nums = {5, 2, 8, 1, 9};
    std::sort(nums.begin(), nums.end());
    printVector(nums);

    std::sort(nums.begin(), nums.end(), [](int a, int b) {return a > b;});
    printVector(nums);

    std::vector<Player> players {{"Alice", 150}, {"Bob", 200}, {"Charlie", 120}};
    std::sort(players.begin(), players.end(), [](const auto& a, const auto& b) {return a.score > b.score;});
    printVector(players);

    std::cout << std::endl;
}