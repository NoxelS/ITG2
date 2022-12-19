
#include <iostream>
#include <thread>

struct ThreadDummy {
    std::thread t_;
    ThreadDummy(auto f) {
        // t_ = std::thread([]() { std::cout << "Hello from thread" << std::endl; });
        t_ = std::thread(f);
    };
    ~ThreadDummy() {
        // if (t_.joinable()) t_.join();
    };
};