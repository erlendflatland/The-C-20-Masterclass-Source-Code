
#include <functional>
#include <iostream>

//YOUR CODE WILL GO BELOW THIS LINE
//DON'T MODIFY ANYTHING ABOVE THIS LINE

// Modifying an array of scores using a std::function
inline void modify(double* scores, std::function<double(double)> modifier, int length) {
    // YOUR CODE: Loop through the array and apply 'modifier' to each element
    for (int i = 0; i < length; ++i) {
        // Apply the modifier to each element
        scores[i] = modifier(scores[i]);
    }
}

//YOUR CODE WILL GO ABOVE THIS LINE
//DON'T MODIFY ANYTHING BELOW THIS LINE

// Functor to multiply by 2
struct Multiply_by_2 {
    double operator()(double value) const {
        return value * 2;
    }
};

// Function to add 1 to a number
inline double add_1(double value) {
    return value + 1;
}

int stdfunction() {
    // Example 1: Using a functor to multiply by 2
    double scores[] = {11.2, 22.1, 33.4, 44.3};
    Multiply_by_2 multiply_by_2;
    modify(scores, multiply_by_2, 4); // FUNCTOR

    std::cout << "Scores after functor: ";
    for (double score : scores) {
        std::cout << score << " ";
    }
    std::cout << std::endl;

    // Example 2: Using a function pointer to add 1
    double scores2[] = {11.2, 22.1, 33.4, 44.3};
    modify(scores2, add_1, 4); // FUNCTION POINTER

    std::cout << "Scores after function pointer: ";
    for (double score : scores2) {
        std::cout << score << " ";
    }
    std::cout << std::endl;

    // Example 3: Using a lambda to subtract 1
    double scores3[] = {11.2, 22.1, 33.4, 44.3};
    modify(scores3, [](double value) { return value - 1; }, 4); // LAMBDA

    std::cout << "Scores after lambda: ";
    for (double score : scores3) {
        std::cout << score << " ";
    }
    std::cout << std::endl;

    return 0;
}
