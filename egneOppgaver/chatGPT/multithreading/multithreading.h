// File: multithreading_tasks.h

#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <chrono>
#include <stop_token>
#include <condition_variable>
#include <deque>

namespace Multithreading {

// Task 1: Create multiple std::thread instances that print messages concurrently.
// Hint: use std::thread and join them after launching.
void task1();

// Task 2: Protect shared data using std::mutex in a multi-threaded context.
// Hint: use std::lock_guard or std::unique_lock to avoid data races.
void task2();

// Task 3: Demonstrate deadlock scenario with two threads acquiring two mutexes in opposite order.
// Hint: avoid deadlock by consistent locking order or std::scoped_lock.
void task3();

// Task 4: Use std::jthread and std::stop_token to implement a cancellable task.
// Hint: regularly check std::stop_token within the thread and stop when requested.
void task4();

// Task 5: Implement a thread-safe queue class skeleton.
// Hint: use std::mutex to protect internal data and std::condition_variable for notifications.
class ThreadSafeQueue {
public:
    void enqueue(int value);
    bool dequeue(int& result);
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::deque<int> data;
};

} // namespace MultithreadingTasks

#endif // MULTITHREADING_H
