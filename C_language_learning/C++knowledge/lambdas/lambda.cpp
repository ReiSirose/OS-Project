#include <iostream>
using namespace std;


int main () {
    int x = 10, y = 20;

    auto lambda1 = [x]() {
        cout << x << endl;
    };

    auto lambda2 = [&x]() {
        cout << "Original x = " << x << endl;
        x = 15; // OK: can modify x
        cout << "Modified x = " << x << endl;
    };

    lambda1();
    lambda2();
    cout << "x after lambda2: " << x << endl << endl;
    x = 10;
    auto lambda3 = [x, &y]() {
        cout << "x = " << x << ", y = " << y << endl;
        //x = 100; // ERROR: cannot modify x (captured by value) const
        y = 25; // OK: can modify y (captured by reference)
    };

    lambda3();
    cout << "y after lambda3: " << y << endl << endl;

    auto lambda4 = [=]() {
        cout << "x = " << x << ", y = " << y << endl;
         //x = 50; // ERROR: cannot modify x (captured by value)
         //y = 50; // ERROR: cannot modify y (captured by value)
    };
    lambda4();
    
    auto lambda5 = [&]() {
        cout << "Before: x = " << x << ", y = " << y << endl;
        x = 30; // OK: can modify x
        y = 40; // OK: can modify y
        cout << "After: x = " << x << ", y = " << y << endl;
    };
    lambda5();
    cout << "After lambda5: x = " << x << ", y = " << y << endl << endl;

    // [=, &y] - Capture all by value except y (by reference)
    auto lambda6 = [=, &y]() {
        cout << "x = " << x << ", y = " << y << endl;
        //x = 100; // ERROR: cannot modify x (captured by value)
        y = 50; // OK: can modify y (captured by reference)
    };
    lambda6();
    cout << "y after lambda6: " << y << endl << endl;

    auto lambda7 = [&, x]() {
        cout << "x = " << x << ", y = " << y << endl;
        // x = 200; // ERROR: cannot modify x (captured by value)
        y = 60; // OK: can modify y (captured by reference)
    };
    lambda7();
    cout << "After lambda7: x = " << x << ", y = " << y << endl;

    auto lambda8 = [x]() mutable{
        x = 20; // ERROR: cannot modify
        cout << "x = " << x << endl;
    };
    lambda8();
    cout << "After lambda8: x = " << x << ", y = " << y << endl;
}

/*
int x = 10, y = 20;

[x]        // Capture x by value (read-only by default)
[&x]       // Capture x by reference (can be modified)
[x, &y]    // Capture x by value, y by reference
[=]        // Capture all used variables by value
[&]        // Capture all used variables by reference
[=, &y]    // Capture all by value except y (by reference)
[&, x]     // Capture all by reference except x (by value)

*/