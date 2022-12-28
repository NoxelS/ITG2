/******************************************************************/
#define SLOW_DOWN       // insert additional sleeps to slow down speed
#define XMAX 1800        // screen width
#define YMAX 315        // screen height
#define MAX_ITER 10000  // maximale Anzahl Iterationen
#define X0 -2.1         // window parameters
#define X1 0.8
#define Y0 -1.4
#define Y1 1.4
/******************************************************************/

#include <unistd.h>

#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

////////////////////
// complex-Klasse //
////////////////////
struct complex {
    double re, im;
    complex() : complex(0, 0) {}
    complex(double d) : complex(d, 0) {}
    complex(double re, double im) : re(re), im(im) {}
    complex operator+(complex z) { return complex(re + z.re, im + z.im); }
    complex operator*(complex z) { return complex(re * z.re - im * z.im, re * z.im + im * z.re); }
    double abs() { return sqrt(re * re + im * im); }
};

//////////////////////////
// Mandelbort-Iteration //
//////////////////////////
int board[XMAX][YMAX];
mutex board_mtx;

struct iterate {
    void operator()() {
        complex z = complex();
        complex c(X0 + i * dx, Y0 + j * dy);

        for (int n = 0; n < 100 && z.abs() < 10; ++n) z = z * z + c;
        // usleep(10000);
        board_mtx.lock();
        board[i][j] = z.abs();
        board_mtx.unlock();

        // cout << i << ", " << j << "TASK: ";
    }
    double dx = (X1 - X0) / XMAX;
    double dy = (Y1 - Y0) / YMAX;
    int i;
    int j;
};

////////////////
// Task-Queue //
////////////////
deque<iterate> TaskQueue;  // Container mit Funktor-Elementen
mutex TaskQueue_mtx;
int done_tasks = 0;  // abgearbeitete Tasks

/////////////////
// Thread-Pool //
/////////////////
const int pool_length = thread::hardware_concurrency();
vector<thread> ThreadPool;
vector<bool> TP_activity;
mutex TP_activity_mtx;

void wait_loop(int thread_id) {
    while (done_tasks < XMAX * YMAX) {
        TaskQueue_mtx.lock();
        if (TaskQueue.empty()) {
            TaskQueue_mtx.unlock();
            continue;
        }
        // Grab new task
        auto task = TaskQueue.front();
        TaskQueue.pop_front();

        // Unlock the mutex so other tasks can look for tasks
        TaskQueue_mtx.unlock();

        // Do stuff
        TP_activity_mtx.lock();
        TP_activity[thread_id] = true;
        TP_activity_mtx.unlock();
        task();
        TP_activity_mtx.lock();
        TP_activity[thread_id] = false;
        TP_activity_mtx.unlock();

        // Increment the number of finished tasks
        ++done_tasks;
    }
};

/////////////
// Ausgabe //
/////////////
void print_board() {
    ofstream myfile;
    while (true) {
        myfile.open("mandelbrot");
        // system("clear");
        // cout << "\n\n\n\n\n\n\n\n\n   ";

        for (int i = 0; i < XMAX; ++i) myfile << '_';
        myfile << '\n';

        const char palette[] = {
            '$', '@', 'B', '%', '8', '&',  'W', 'M', '#', '*', 'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q',
            'w', 'm', 'Z', 'O', '0', 'Q',  'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x',
            'r', 'j', 'f', 't', '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']', '?', '-', '_', '+',
            '~', '<', '>', 'i', '!', 'l',  'I', ';', ':', ',', '"', '^', '`', '.'};
        const int palette_len = sizeof(palette) / sizeof(char);
        char ch;
        for (int j = 0; j < YMAX; ++j) {
            myfile << "  |";
            for (int i = 0; i < XMAX; ++i) {
                int v = board[i][j];
                if (v >= MAX_ITER || v == 0)
                    ch = ' ';
                else
                    ch = palette[v % palette_len];
                myfile << ch;
            }
            myfile << "|\n";
        }

        myfile << "  |";
        for (int i = 0; i < XMAX; ++i) myfile << '_';
        myfile << "|\n";

        // active threads in pool
        int act_tasks = 0;
        myfile << "   act: [";
        for (int i = 0; i < pool_length; ++i) myfile << (TP_activity[i] ? ++act_tasks, '+' : '.');
        cout << "] act/tot = " << setw(2) << act_tasks << "/" << done_tasks << endl;

        myfile.close();
        sleep(1);
    }
}

int main() {
    // Ausgabe
    thread monitor(print_board);

    // Fill Task Queue
    for (int j = 0; j < YMAX; ++j) {
        for (int i = 0; i < XMAX; ++i) {
            TaskQueue_mtx.lock();
            iterate iter = iterate();
            iter.i = i;
            iter.j = j;
            TaskQueue.push_front(iter);
            TaskQueue_mtx.unlock();
        }
    }

    // Thread-Pool
    TP_activity.reserve(pool_length);
    for (int id = 0; id < pool_length; ++id) {
        ThreadPool.emplace_back(wait_loop, id);
    }

    for (auto& th : ThreadPool) th.detach();

    monitor.join();
}
