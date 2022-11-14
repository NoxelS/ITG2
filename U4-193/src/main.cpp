#include <iostream>

#include "stack.h"
using namespace std;

class proxy {
   private:
    double x;

   public:
    proxy(int x) : x(x) {}
    operator int() const { return 2 * (int)x; };
    operator double() const { return 1.1 * (double)x; };
};

proxy f(int x) { return proxy(x); };

class complex {
   private:
    double re, im;

   public:
    complex(double r, double i) : re(r), im(i) {}
    complex(double r) : re(r), im(0) {}
    complex() : re(0), im(0) {}
    double real() const { return re; }
    double imag() const { return im; }
    complex operator++() {
        re++;
        im++;
        return *this;
    }
    complex operator++(int) {
        complex old = *this;
        re++;
        im++;
        return old;
    }
    string operator<<(complex c) {
        return "()";
    }
};

#define PRINT(x)                             \
    cout << #x << ": ";                      \
    while (x.size()) cout << x.pop() << " "; \
    cout << endl;

int main() {
    int a = f(10);
    double b = f(10);
    cout << a << "\t" << b << endl;
    complex c(1, 2);
    cout << c.real() << "\t" << c.imag() << endl;
    cout << (c++).real() << endl;
    cout << (++c).real() << endl;
}
