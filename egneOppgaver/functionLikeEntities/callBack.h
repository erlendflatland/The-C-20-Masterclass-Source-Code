#include <iostream>

// 1. Declare a callback function type alias (takes a reference to an integer)
using Callback = void(*)(int &);

// 2. Implement a function that processes an array using the callback
void processArray(int* arr, size_t size, Callback callback) {
    for(int i = 0; i < size; ++i) {
        callback(arr[i]); // Call the callback function on each element
    }
}

// 3. Define a callback function that increments a number
void increment(int& value) {
    value++;
}

int callBack() {
    // 4. Create an array of integers to modify
    int arr[] = {1, 2, 3, 4, 5};
    Callback callback = increment; // Assign the callback function
    // 5. Process the array using the callback function
    processArray(arr, 5, callback);

    // 6. Output the modified array
    for (int num : arr) {
        std::cout << num << " ";
    }

    return 0;
}
