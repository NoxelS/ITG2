/******************************************************************/
#define NTASKS 64   // Anzahl Tasks
#define NPARTS 800  // Anzahl Particles
#define XMAX 80     // screen width
#define YMAX 25     // screen height
/******************************************************************/

#include <unistd.h>

#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

/////////////////////////
// System und Teilchen //
/////////////////////////
#define BC_COUNT 2  // 0: PBC, 1: RBC
int bc_type = 1;
int pot_type = 1;        // 1: attractive, -1: repulsive
float charge_rate = .5;  // = N- / (N- + N+)

int8_t board[XMAX][YMAX] = {0};
mutex board_mtx;

struct position {
    position() : position(0, 0) {}
    position(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

struct Particle {
    Particle() = delete;
    Particle(int id) : id(id), pos(0, 0), charge(1) { board[0][0] = 1; }
    Particle(int id, int x, int y) : id(id), pos(x, y), charge(1) { board[x][y] = 1; }
    Particle(int id, int x, int y, float c) : id(id), pos(x, y), charge(c) { board[x][y] = 1; }
    Particle(const Particle& p) {
        id = p.id;
        pos = p.pos;
        charge = p.charge;
    }
    int id;
    mutex mtx;
    position pos;
    int charge;
};

vector<Particle> suspension;

void interact(int task_id, Particle& p1, Particle& p2) {
    scoped_lock(p1.mtx, p2.mtx, board_mtx);  // alle drei Mutexe müssen gelockt werden
    int dx = p2.pos.x - p1.pos.x;
    int dy = p2.pos.y - p1.pos.y;
    float alpha = pot_type * p1.charge * p2.charge;
    int p1x_new, p1y_new, p2x_new, p2y_new;

    switch (bc_type) {
        case 0:  // Periodic Boundary Conditions
            p1x_new = (p1.pos.x + XMAX + int(alpha * dx / 4)) % XMAX;
            p1y_new = (p1.pos.y + YMAX + int(alpha * dy / 4)) % YMAX;
            p2x_new = (p2.pos.x + XMAX - int(alpha * dx / 4)) % XMAX;
            p2y_new = (p2.pos.y + YMAX - int(alpha * dy / 4)) % YMAX;
            break;
        case 1:  // Rigid Boundary Conditions
            p1x_new = max(min((p1.pos.x + int(alpha * dx / 4)), XMAX - 1), 0);
            p1y_new = max(min((p1.pos.y + int(alpha * dy / 4)), YMAX - 1), 0);
            p2x_new = max(min((p2.pos.x - int(alpha * dx / 4)), XMAX - 1), 0);
            p2y_new = max(min((p2.pos.y - int(alpha * dy / 4)), YMAX - 1), 0);
            break;
    }

    if (board[p1x_new][p1y_new] == 0) {
        board[p1.pos.x][p1.pos.y] = 0;
        board[p1x_new][p1y_new] = p1.charge;
        p1.pos.x = p1x_new;
        p1.pos.y = p1y_new;
    }

    if (board[p2x_new][p2y_new] == 0) {
        board[p2.pos.x][p2.pos.y] = 0;
        board[p2x_new][p2y_new] = p2.charge;
        p2.pos.x = p2x_new;
        p2.pos.y = p2y_new;
    }

    // willkürliche Verlangsamung
    usleep(1000);
}

////////////////
// Task-Queue //
////////////////
typedef function<void(void)> fktelem;  // Funktor-Elemente ÜT=void und RT=void
deque<fktelem> TaskQueue;              // Container mit Funktor-Elementen
mutex TaskQueue_mtx;

/////////////////
// Thread-Pool //
/////////////////
const int max_act_thrds = thread::hardware_concurrency();
vector<thread> ThreadPool;

void wait_loop(int thread_id) {
    fktelem task;
    bool have_task;

    while (true) {
        TaskQueue_mtx.lock();
        if (!TaskQueue.empty()) {
            task = TaskQueue.front();
            TaskQueue.pop_front();
            have_task = true;
        } else {
            have_task = false;
        }
        TaskQueue_mtx.unlock();

        if (have_task) {
            task();
        }
    }
};

/////////////////
// IO-Routinen //
/////////////////
void input() {
    char ch;
    while (true) {
        ch = getchar();
        switch (ch) {
            case 'p':
                pot_type *= -1;
                break;
            case 'b':
                bc_type = (bc_type + 1) % BC_COUNT;
                break;
            case '+':
                charge_rate = min(charge_rate + 0.1, 1.);
                for (auto& p : suspension) p.charge = (1. * rand() / RAND_MAX > charge_rate) ? 1 : -1;
                break;
            case '-':
                charge_rate = max(charge_rate - 0.1, 0.);
                for (auto& p : suspension) p.charge = (1. * rand() / RAND_MAX > charge_rate) ? 1 : -1;
                break;
            case 'q':
                exit(0);
        }
    }
}

void output() {
    while (true) {
        system("clear");
        cout << "\n\n\n\n\n\n\n\n\n";

        cout << "   (q)uit  "
             << "  (p)otential: " << (pot_type == 1 ? "att" : "rep") << "  (b)ounds: " << (bc_type == 0 ? "PBC" : "RBC")
             << "  (+/-)-rate: " << charge_rate << "  task#: " << TaskQueue.size() << "\n   ";

        for (int i = 0; i < XMAX; ++i) cout << '_';
        cout << '\n';

        for (int y = 0; y < YMAX; ++y) {
            cout << "  |";
            for (int x = 0; x < XMAX; ++x) cout << (board[x][y] == 1 ? '+' : (board[x][y] == -1 ? '-' : ' '));
            //        cout << (board[x][y] ? 'o' : ' ');
            cout << "|\n";
        }

        cout << "  |";
        for (int i = 0; i < XMAX; ++i) cout << '_';
        cout << "|\n";

        usleep(100000);
    }
}

int main() {
    // Erzeuge Suspension
    srand(time(NULL));
    for (int i = 0; i < NPARTS; ++i) {
        int x = rand() % XMAX;
        int y = rand() % YMAX;
        int c = (1. * rand() / RAND_MAX > charge_rate) ? 1 : -1;
        suspension.emplace_back(i, x, y, c);
    }

    // Input-Thread
    thread keyinput(input);
    keyinput.detach();

    // Ausgabe-Thread
    thread monitor(output);
    monitor.detach();

    // Thread-Pool
    for (int i = 0; i < max_act_thrds; ++i) {
        ThreadPool.emplace_back(wait_loop, i).detach();
    }

    // Task-Double-Ended-Queue (deque)
    // Links Tasks einfügen, rechts Tasks rausnehmen
    while (1) {
        while (TaskQueue.size() < NTASKS) {
            int i = (i + 1) % NTASKS;
            int n1 = rand() % NPARTS;
            int n2 = n1;
            while (n2 == n1) n2 = rand() % NPARTS;
            TaskQueue_mtx.lock();
            TaskQueue.emplace_back(bind(interact, i, ref(suspension[n1]), ref(suspension[n2])));
            TaskQueue_mtx.unlock();
        }
    }
}
