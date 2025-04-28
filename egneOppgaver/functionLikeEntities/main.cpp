#include<iostream>
#include<functional>
#include"functionPointers.h" // Assuming this header contains the function pointer type definition
#include"callBack.h" // Assuming this header contains the function pointer type definition

#include"lambdaFunc.h" // Assuming this header contains the function pointer type definition
#include"stdfunction.h" // Assuming this header contains the function pointer type definition
int main() {
    
    /*
    Operation operation = nullptr; // Initialize to nullptr
    int x = 5, y = 3; // Example values
    operation = add; // Your code here: assign to 'add'
    std::cout << "Add result: " << operation(x, y) /* Your code here: call the function pointer * / << std::endl;

    operation = subtract; // Your code here: assign to 'subtract'
    std::cout << "Subtract result: " << operation(x, y) /* Your code here: call the function pointer * / << std::endl;
    */

    // callBack(); // Call the callback function example

    lambdaFunc(); // Call the lambda function example
    stdfunction(); // Call the std::function example
    return 0;
}