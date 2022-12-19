#include <inttypes.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "thread.hpp"

using namespace std;

int counter = 0;

void show(vector<int>& v) {
    for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) cout << (*i) << " ";
    cout << endl;
}

void sum(vector<int>& v, int* s0) {
    ++counter;
    show(v);
    int* s1 = new int;
    int* s2 = new int;
    if (v.size() <= 1) {
        *s0 = v.front();
    } else {
        vector<int> v1(v.begin(), v.begin() + v.size() / 2);
        vector<int> v2(v.begin() + v.size() / 2, v.end());

        thread t1(sum, ref(v1), s1);
        thread t2(sum, ref(v2), s2);

        if (t1.joinable()) t1.join();
        if (t2.joinable()) t2.join();

        *s0 = *s1 + *s2;
    }
    delete s1;
    delete s2;
}


void msort(vector<int>& a) {
    if (a.size() > 1) {
        vector<int> a1(a.begin(), a.begin() + a.size() / 2);
        vector<int> a2(a.begin() + a.size() / 2, a.end());

        cout << "Funktion: " << a.size() << endl;
        thread t1(msort, ref(a1));
        thread t2(msort, ref(a2));

        if (t1.joinable()) t1.join();
        if (t2.joinable()) t2.join();

        // 1s suspend,
        // ohne Threads: => Laufzeit = n*1s
        // mit  Threads: => Laufzeit = log2(n)*1s
        sleep(1);
        a.clear();

        while (a1.size() > 0 && a2.size() > 0) {
            if (a1.front() <= a2.front()) {
                a.push_back(a1.front());
                a1.erase(a1.begin());
            } else {
                a.push_back(a2.front());
                a2.erase(a2.begin());
            }
        }

        while (a1.size() > 0) {
            a.push_back(a1.front());
            a1.erase(a1.begin());
        }

        while (a2.size() > 0) {
            a.push_back(a2.front());
            a2.erase(a2.begin());
        }
    }
}

void dummyPrint(int i) {
    cout << "Hello World: " << i << endl;
}

int main() {
    // const int len = 15;
    // vector<int> list;
    // list.reserve(len);
    // for (int i = 1; i <= len; ++i) list.push_back(i);

    // show(list);

    // int* summe = new int;
    // sum(list, summe);
    // cout << *summe << " = " << len * (len + 1) / 2 << "  Threads: " << counter << endl;
    // vector<int> feld = {7, 5, 3, 9, 2, 10, 3, 12, -1, 8, 7, 3, 4, 10, 10, -4};
    // show(feld);
    // msort(feld);
    // show(feld);
    {
        ThreadDummy t([] { cout << "Hello World" << endl; });
    }
}
