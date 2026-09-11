#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int score;      
};
int main () {
    std::vector<int> numbers {10, 20, 30, 40, 50};
    std::vector<std::string> words {"Hello", "I'm", "The Goat"};

    auto it = std::find(numbers.begin(), numbers.end(), 30);
    auto wit = std::find(words.begin(), words.end(), "I'm");

    if (it != numbers.end()) {
        std::cout << "Found 30 at index: " << std::distance(numbers.begin(), it) << '\n';
    }
    else {
        std::cout << "Value not found.\n";
    }
    if (wit != words.end()) {
        std::cout << "I'm at position " << std::distance(words.begin(), wit) << "\n";
    }
    else {
        std::cout << "Value not found.\n";
    }
// ---------------------------------------- CONDITIONAL SEARCH --------------------------------------------------
    std::vector<Student> students {{"Alice", 82}, {"Bob", 94}, {"Charlie", 78}};
    
    auto sit = std::find_if(students.begin(), students.end(), [](const auto& student) { return student.score >= 90;});
    if(sit != students.end()) {
        std::cout << "First high scorer: " << sit->name << '\n';
    }

    


    return 0;
}