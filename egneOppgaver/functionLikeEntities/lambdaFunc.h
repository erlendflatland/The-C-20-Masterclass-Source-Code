#include <iostream>

// 1. Define a functor that multiplies a value by 2
struct MultiplyBy2 {
    void operator()(double& value) const {
        value *= 2;
    }
};

int lambdaFunc() {
    // 2. Create an array of values to modify
    double values[] = {1.0, 2.0, 3.0, 4.0};

    // 3. Use the MultiplyBy2 functor to modify values in the array
    MultiplyBy2 multiplyBy2;
    // Your code here: modify array using the functor
    for (double& val : values) {
        multiplyBy2(val);
    }

    // 4. Output modified values after functor application
    std::cout << "Modified values with functor: ";
    for (double val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 5. Use a lambda function to modify values in the array
    auto lambdaSubtract = [](double value) { return value - 1; };
    // Your code here: modify array using the lambda
    for (double& val : values) {
        val = lambdaSubtract(val);
    }
    // 6. Output modified values after lambda application
    std::cout << "Modified values with lambda: ";
    for (double val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
