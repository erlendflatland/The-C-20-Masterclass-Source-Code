// File: multithreading_main.cpp
#include <iostream>
#include "multithreading.h"

int main() {
    std::cout << "=== Multithreading Tasks ===" << std::endl;
    Multithreading::task1();
    Multithreading::task2();
    Multithreading::task3();
    Multithreading::task4();

    Multithreading::ThreadSafeQueue q;
    q.enqueue(10);
    int value;
    q.dequeue(value);

    return 0;
}
