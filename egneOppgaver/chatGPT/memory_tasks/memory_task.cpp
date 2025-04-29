// File: memory_tasks.cpp

#include "memory_task.h"
#include <algorithm>

namespace MemoryTasks {

// Task 1: demonstration of std::unique_ptr
void uniquePtrTask() {
    std::cout << "Task 1 (unique_ptr): ";
    // Example: manage dynamic integer with unique_ptr
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
}

// Task 2: demonstration of std::shared_ptr
void sharedPtrTask() {
    std::cout << "Task 2 (shared_ptr): ";
    // Example: shared ownership of an integer
    std::shared_ptr<int> ptr1 = std::make_shared<int>(100);
    std::shared_ptr<int> ptr2 = ptr1;
    std::cout << "Use count: " << ptr1.use_count() << std::endl;
}

// Task 3: skeleton for breaking cyclic dependency
void cyclicDependencyTask() {
    std::cout << "Task 3 (weak_ptr): ";
    // Example: two classes A and B holding shared_ptr to each other -> cycle
    // Use std::weak_ptr to break the cycle weak_ptr

    struct B;
    struct A;

    struct A { std::weak_ptr<B> bptr; };
    struct B { std::shared_ptr<A> aptr; };
}

// Task 4: Rule of Five class usage (definitions)
RuleOfFive::RuleOfFive() : unique_data(std::make_unique<int[]>(10)) {
    // TODO: allocate resource (e.g., data = new int[10])
    // Initialize the unique_data with some values
    for (int i = 0; i < 10; ++i) {
        unique_data[i] = i;
    }
    std::cout << "RuleOfFive default constructor called." << std::endl;
}

/*     RuleOfFive();                             // default constructor
    ~RuleOfFive();                            // destructor
    RuleOfFive(const RuleOfFive&);            // copy constructor
    RuleOfFive(RuleOfFive&&) noexcept;        // move constructor
    RuleOfFive& operator=(const RuleOfFive&); // copy assignment
    RuleOfFive& operator=(RuleOfFive&&) noexcept; // move assignment
*/
RuleOfFive::~RuleOfFive() {

}



// Copy constructor
RuleOfFive::RuleOfFive(const RuleOfFive& other)
    : unique_data(std::make_unique<int[]>(10)) {
    // Deep copy the contents

    if(!other.unique_data) {
        throw std::runtime_error("Null pointer exception");
    }

    std::copy_n(other.unique_data.get(), 10, unique_data.get());

}

RuleOfFive::RuleOfFive(RuleOfFive&& other) noexcept : unique_data(std::move(other.unique_data)) {
    // TODO: steal resource from other
}



RuleOfFive& RuleOfFive::operator=(const RuleOfFive& other) {
    // TODO: copy-and-swap or deep copy assignment
    if (this == &other) {
        return *this;
    }

    unique_data = std::make_unique<int[]>(10);
    std::copy_n(other.unique_data.get(), 10, unique_data.get());

    return *this;
}


RuleOfFive& RuleOfFive::operator=(RuleOfFive&& other) noexcept {

    if (this == &other) {
        return *this;
    }
    // TODO: move assignment

    unique_data = std::move(other.unique_data); // Move unique_ptr

    return *this;

}

// Task 5: demonstration of a memory leak (to be fixed)
void memoryLeakTask() {
    std::cout << "Task 5 (memory leak): ";
    // Example of leak: allocate memory but do not delete
    // int* leaked = new int[5];
    // TODO: fix leak by using std::unique_ptr<int[]> or delete[] leaked
}

} // namespace MemoryTasks
