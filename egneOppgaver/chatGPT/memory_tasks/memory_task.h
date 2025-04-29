// File: memory_tasks.h

#ifndef MEMORY_TASKS_H
#define MEMORY_TASKS_H

#include <memory>
#include <iostream>

namespace MemoryTasks {

// Task 1: Use std::unique_ptr to manage a dynamically allocated integer.
// Hint: use std::make_unique to create unique_ptr and automatically manage memory.
void uniquePtrTask();

// Task 2: Use std::shared_ptr to manage shared ownership of dynamically allocated resources.
// Hint: use std::make_shared and observe reference counts or sharing behavior.
void sharedPtrTask();

// Task 3: Resolve cyclic dependency using std::weak_ptr.
// Hint: break reference cycle between std::shared_ptr-managed objects using std::weak_ptr.
void cyclicDependencyTask();

// Task 4: Implement the Rule of Five in a class managing dynamic memory.
class RuleOfFive {
public:
    RuleOfFive();                             // default constructor
    ~RuleOfFive();                            // destructor
    RuleOfFive(const RuleOfFive& other);            // copy constructor
    RuleOfFive(RuleOfFive&& other) noexcept;        // move constructor
    RuleOfFive& operator=(const RuleOfFive& other); // copy assignment
    RuleOfFive& operator=(RuleOfFive&& other) noexcept; // move assignment

private:
    int val;
    std::string test;
    std::unique_ptr<int[]> unique_data; // smart pointer for automatic memory management
};

// Task 5: Demonstrate a memory leak scenario.
// Hint: allocate memory without deleting it, then fix by using smart pointers.
void memoryLeakTask();

} // namespace MemoryTasks

#endif // MEMORY_TASKS_H
