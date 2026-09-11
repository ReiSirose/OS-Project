#include <iostream>
#include <chrono>
using namespace std;

// Use Cases for final Classes
/*
1. Utility Classes with Static Methods
Classes that only contain static helper functions should be final.

2. Value Objects / Data Transfer Objects (DTOs)
Simple data containers that represent immutable values.

3. Implementation Classes (Not Interfaces)
Concrete implementations that should not be further specialized.

4. Security-Critical Classes
Classes where inheritance could compromise security or correctness.
*/

// Use Cases for final Methods
/*
1. Template Method Pattern — Fixed Steps
When certain steps in an algorithm must never change.

2. Performance-Critical Methods
Methods that are optimized and should not be overridden.

3. Preventing Accidental Override
Methods that work correctly and should not be accidentally broken.

4. Ensuring Contract Compliance
When a method implements a critical contract that must be maintained.
*/

// When NOT to Use final
/*
1. Library/Framework Base Classes
Classes designed to be extended by users.

2. When Extensibility is a Feature
Classes that are meant to be customized.

3. Early in Development
Don’t use final prematurely before the design stabilizes.

4. When Testing Requires Mocking
Classes that need to be mocked for unit testing.
*/


class NonFinalClass {
public:
    virtual int compute(int x) {
        return x * x;
    }
};

class FinalClass {
public:
    virtual int compute(int x) final {
        return x * x;
    }
};

int main() {
    NonFinalClass nfc;
    FinalClass fc;
    
    const int iterations = 100000000;
    
    // Non-final method call
    auto start = chrono::high_resolution_clock::now();
    int sum1 = 0;
    for(int i = 0; i < iterations; i++) {
        sum1 += nfc.compute(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    // Final method call (potentially optimized)
    start = chrono::high_resolution_clock::now();
    int sum2 = 0;
    for(int i = 0; i < iterations; i++) {
        sum2 += fc.compute(i);
    }
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Non-final time: " << duration1.count() << "ms" << endl;
    cout << "Final time: " << duration2.count() << "ms" << endl;
    
    return 0;
}