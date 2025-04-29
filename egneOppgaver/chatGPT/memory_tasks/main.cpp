// File: memory_main.cpp
#include <iostream>
#include "memory_task.h"

int main() {
    std::cout << "=== Memory Management Tasks ===" << std::endl;
    MemoryTasks::uniquePtrTask();
    MemoryTasks::sharedPtrTask();
    MemoryTasks::cyclicDependencyTask();

    MemoryTasks::RuleOfFive obj1;
    MemoryTasks::RuleOfFive obj2 = obj1; // Copy constructor
    MemoryTasks::RuleOfFive obj3 = std::move(obj1); // Move constructor
    MemoryTasks::RuleOfFive obj4;
    obj4 = obj2; // Copy assignment
    obj4 = std::move(obj2); // Move assignment

    // MemoryTasks::memoryLeakTask();
    return 0;
}