#include <iostream>
#include <vector>

template <typename It, typename Pred>
It find_if(It first, It last, Pred pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it))  // We only pass ONE parameter to pred!
            return it;
    }
    return last;
}



int main () {
    int n;
    std::cin >> n;

    auto lessThanN = [n](int x) {
        return x < n;
    };
    std::vector<int> ints = {1, 0, 6};
    auto it = find_if(ints.begin(), ints.end(), lessThanN);

}


