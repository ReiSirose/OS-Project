#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>


struct Sample {
    double ts;
    std::vector<std::string> stacks;
};

struct Event {
    std::string kind;
    double ts;
    std::string name;


    void printEvent() const {
        std::cout << "Kind: " << kind << std::endl;
        std::cout << "Timestamp: " << ts << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "---------" << std::endl;
    }
};

// Implement this
std::vector<Event> convertToTrace(const std::vector<Sample>& samples){
    // Expected output
    // Event {"start", 7.4 , "main"};
    // Event {"start", 9.7 , "func1"};
    // Event {"start", 9.7 , "func2"};
    // Event {"end", 10.4 , "func2"};
    // Event {"end", 10.4 , "func1"};
    // Event {"end", 12.3 , "main"};
}

int main () {
    Sample s1 {7.4, {"main"}};
    Sample s2 {9.7, {"main", "func1", "func2"}};
    Sample s3 {10.4, {"main"}};
    Sample s4 {12.3, {}};

    std::vector<Sample> samples = {s1,s2,s3,s4};
    auto events = convertToTrace(samples);
    for (const auto& event : events){
        event.printEvent();
    }
}


// 7.4 -> main
// put this into unordered_set, if unique:
    // main -> stack
    // push start -  ts - name
// 9.7 - {main, func1, func2};
// iterating through vector: if unique put into unordered_set
    // put onto the stack

// need to find the way to check the samples list if the 
// 1. loop through the sample stack check if unique in the unordered_set, if not put into unordered_set
    // 2. if unique, push on top of the stack
        // 3. push to the vector events (start - ts - name)
    // 2. if not unique, ignore
// 4. how to check for the end function

