#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

template <typename T>
struct MyAtomic {
    T value;
    mutex value_mtx;
    MyAtomic() : value(T()){};

    operator T() const { return value; };

    T operator=(T newValue) {
        value_mtx.lock();
        value = newValue;
        value_mtx.unlock();
        return value;
    };

    T operator++() {
        value_mtx.lock();
        ++value;
        value_mtx.unlock();
        return value;
    };
};

class MyCounter {
   public:
    MyAtomic<int> val1;     // Normale Counter-Variable
    atomic<int> val2;  // Counter-Variable als atomic-Objekt
    MyCounter() { clear(); }
    void clear() {
        val1 = 0;
        val2 = 0;
    }
    void increment() {
        ++val1;
        ++val2;
    }
};

MyCounter cntr;

void doWork() {
    for (int i = 0; i < 10000; ++i) cntr.increment();
}

int main() {
    vector<thread> threads;

    for (int j = 0; j < 5; ++j) {
        threads.clear();
        cntr.clear();

        for (int i = 0; i < 10; ++i) threads.push_back(thread(&doWork));

        // ab C++11 sind range-based loops definiert
        for (auto& thread : threads) thread.join();

        cout << cntr.val1 << " " << cntr.val2 << endl;
    }
}
