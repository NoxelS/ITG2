#include <unistd.h>  // für sleep()

#include <atomic>
#include <functional>  // für bind() und function<>
#include <iomanip>     // für setw()
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#define NTASKS 100

using namespace std;

int activity[NTASKS];
atomic<int> done_tasks = 0;
vector<array<int, 2>> done_log;
queue<function<int(void)>> TaskQueue;
mutex TaskQueue_mtx;

int doStuff(int task_id) {
    // set task state to "in progress"
    activity[task_id] = 1;

    // do hard work...
    int load = 200 + rand() % 600;
    for (long j = 0; j < load; ++j) usleep(15000);

    // set task state to "completed"
    activity[task_id] = 2;

    return load;
}

/**
 *  Monitor all tasks and print status
 */
void aprint() {
    int act_tasks, ts = 0;
    while (done_tasks < NTASKS || act_tasks != 0) {
        system("clear");
        cout << "Your system has " << thread::hardware_concurrency() << " cores.\n";
        cout << " t Tasks 1.." << NTASKS << " ('.'=waiting, '+'=running) | active/finished Tasks\n";
        act_tasks = 0;
        cout << setw(2) << ts++ << ' ';
        for (int j = 0; j < NTASKS; ++j) {
            switch (activity[j]) {
                case 0:
                    cout << '.';
                    break;
                case 1:
                    cout << '+';
                    ++act_tasks;
                    break;
                case 2:
                    cout << ' ';
                    break;
            }
        }
        cout << setw(3) << act_tasks << "/" << done_tasks << endl;

        // Print the last three done tasks
        cout << "Latest activity:" << endl;
        for (int i = done_log.size() - 5; i < done_log.size(); ++i) {
            if (i < 0) continue;
            cout << "Thread " << done_log[i][0] << " finished a task in " << done_log[i][1] << " work units." << endl;
        }

        sleep(1);
    }
}

void wait_loop(int id) {
    while(done_tasks < NTASKS) {
        TaskQueue_mtx.lock();
        if(TaskQueue.empty()) {
            TaskQueue_mtx.unlock();
            continue;
        }
        // Grab new task
        auto task = TaskQueue.front();
        TaskQueue.pop();

        // Unlock the mutex so other tasks can look for tasks
        TaskQueue_mtx.unlock();

        // Do stuff
        int load = task();

        // Add to done log
        done_log.push_back(array<int,2>({id, load}));

        // Increment the number of finished tasks
        ++done_tasks;
    }
}

int main() {
    srand(time(NULL));

    // zur Ausgabe
    thread monitor(aprint);

    // Thread-Pool
    int max_act_thrds = thread::hardware_concurrency();
    vector<thread> ThreadPool;
    for (int i = 0; i < max_act_thrds; ++i) ThreadPool.emplace_back(wait_loop, i);
    // ist analog zu
    // ThreadPool.push_back(thread(wait_loop, i));
    // es wird jedoch kein temporary thread angelegt, da
    // emplace_back(Args&...) variadic Args übernimmt und sie
    // perfect forwarded an 'Args'. Achtung. Gilt nicht für
    // emplace_back(Arg&&) in MSVC. Microsoft hat es noch nicht
    // geschafft, variadics in Visual C++ zu implementieren. ;)
    for (auto& th : ThreadPool)  // Detach infinite loop-threads
        th.detach();

    // Task-Queue (2. part after 7s)
    TaskQueue_mtx.lock();
    for (int i = 0; i < NTASKS / 3; ++i) TaskQueue.push(bind(doStuff, i));
    TaskQueue_mtx.unlock();

    sleep(7);
    cout << "Looking into the queue for an akward long time" << endl;
    TaskQueue_mtx.lock();
    sleep(7);
    TaskQueue_mtx.unlock();

    TaskQueue_mtx.lock();
    for (int i = NTASKS / 3; i < NTASKS; ++i) TaskQueue.push(bind(doStuff, i));
    TaskQueue_mtx.unlock();

    monitor.join();
}
