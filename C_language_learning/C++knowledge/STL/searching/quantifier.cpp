#include <iostream>
#include <vector>
#include <algorithm>

int main () {
    std::vector<int> scores = {85, 92, 78, 90, 88};

    // is all of the score >= 70
    bool all_passed = std::all_of(scores.begin(), scores.end(), [](int score) { return score >= 70;});

    // has any score >= 90
    bool has_ace = std::any_of(scores.begin(), scores.end(), [](int score) { return score >= 90;});

    // Are there zero failing grades? (< 60)
    bool zero_fail = std::none_of(scores.begin(), scores.end(), [](int score) { return score < 60;});

    std::cout << std::boolalpha;
    std::cout << "All passed? " << all_passed << '\n';   // true
    std::cout << "Has ace? "     << has_ace << '\n';      // true
    std::cout << "Zero fails? "  << zero_fail << '\n';  // true

    return 0;
}