#include <iostream>

// 1. Declare a function pointer type alias for arithmetic operations (returns a double, takes two doubles as parameters)
using Operation = double(*)(double, double);

// 2. Define a function that performs addition
double add(double x, double y) {
    return x + y; // Your code here: implement addition
}

// 3. Define a function that performs subtraction
double subtract(double x, double y) {
    return x - y; // Your code here: implement subtraction
}

