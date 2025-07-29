#include <iostream>

void function(int [][3]);

int main () {
    int a[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    function(a);
    std::cout << a[0][1] << a[1][1] << a[2][1];
    //              2           3           9
}

void function (int b [][3]){
    ++b;
    // b is the pointer to the first array
    // b + 1 implied the pointer to the second array
    // so now b is pointer to the second array
    // b[1][1] in second array perspective will be at location of original b[2][1]
    // b [0][1] in second array perspective will be at location of original b[1][1]
    b[1][1] = 9;
    b[0][1] = 3;
}