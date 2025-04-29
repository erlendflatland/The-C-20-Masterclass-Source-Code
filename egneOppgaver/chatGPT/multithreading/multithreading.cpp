// File: multithreading_tasks.cpp

#include "multithreading.h"

namespace Multithreading {

// Task 1: skeleton implementation for launching threads
void task1() {
    std::cout << "Task 1 (multithreading): launching threads..." << std::endl;

    std::vector<std::jthread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i]() {
            std::cout << "Hello from thread " << i << std::endl;
        });
    }
    // Example: start several threads that print their ID
    // std::vector<std::thread> threads;
    // for (int i = 0; i < 5; ++i) {
    //     threads.emplace_back([i]() {
    //         std::cout << "Hello from thread " << i << std::endl;
    //     });
    // }
    // for (auto& t : threads) t.join();
}

// Task 2: skeleton for mutex usage
void task2() {
    std::cout << "Task 2 (mutex): protect shared data..." << std::endl;
    static int counter = 0;
    static std::mutex mtx;

        // Example skeleton:
    std::jthread t1([&]() {
         std::lock_guard<std::mutex> lock(mtx);
         ++counter;
    });
    std::jthread t2([&]() {
         std::lock_guard<std::mutex> lock(mtx);
         ++counter;
    });

    // Example skeleton:
    // std::thread t1([&]() {
    //     std::lock_guard<std::mutex> lock(mtx);
    //     ++counter;
    // });
    // std::thread t2([&]() {
    //     std::lock_guard<std::mutex> lock(mtx);
    //     ++counter;
    // });
    // t1.join();
    // t2.join();
}

// Task 3: skeleton for deadlock scenario
void task3() {
    std::cout << "Task 3 (deadlock): demonstrate deadlock or avoid it..." << std::endl;
    static std::mutex m1, m2;
    // To avoid deadlock, use std::scoped_lock(m1, m2) in both threads instead.
    std::jthread t3([]() {
        std::scoped_lock lock(m1, m2);
        std::cout << "Thread 1 acquired both locks safely\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });
    std::jthread t4([]() {
        std::scoped_lock lock(m1, m2);
        std::cout << "Thread 2 acquired both locks safely\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });

    /*

        std::jthread t1([]() {
        std::lock_guard<std::mutex> lock1(m1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock2(m2);
        std::cout << "Thread 1 acquired both locks\n";
    });

    std::jthread t2([]() {
        std::lock_guard<std::mutex> lock2(m2);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock1(m1);
        std::cout << "Thread 2 acquired both locks\n";
    });
    */
    // Example: two threads locking m1 then m2 and vice versa -> deadlock.
    // This can cause a deadlock because each thread locks one mutex and waits for the other.



}

// Task 4: skeleton for std::jthread and stop_token
void task4() {
    std::cout << "Task 4 (jthread/stop_token): cancellable task..." << std::endl;
    // Example: Use std::jthread with a loop checking stop_token:
    std::jthread worker([](std::stop_token st){
         while (!st.stop_requested()) {
             // do work...
             std::this_thread::sleep_for(std::chrono::milliseconds(100));
         }
         std::cout << "Thread exiting on stop request\n";
    });
    // // Request stop after some time
    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.request_stop();
}

// Task 5: thread-safe queue methods skeleton
void ThreadSafeQueue::enqueue(int value) {
    std::lock_guard<std::mutex> lock(mtx);
    data.push_back(value); //     std::deque<int> data;
    cv.notify_one();
}
bool ThreadSafeQueue::dequeue(int& result) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]{ return !data.empty(); });
    result = data.front();
    data.pop_front();
    return true;
    //return false;
}

} // namespace MultithreadingTasks
