#include <iostream>

#include "stack.h"

using namespace std;

#define PRINT(x)                             \
    cout << #x << ": ";                      \
    while (x.size()) cout << x.pop() << " "; \
    cout << endl;

struct A {
    double a;
    A(double a) : a(a){};
};
struct B {
    double a;
    B(A a) : a(a.a){};
};

ostream &operator<<(ostream &os, A a) {
    os << a.a;
    return os;
};

ostream &operator<<(ostream &os, B b) {
    os << b.a;
    return os;
};

int main() {
    stack<double> S0;
    S0.push(11.1);
    S0.push(12.2);
    S0.push(13.3);
    S0.push(14.4);

    stack<char> S1;
    S1.push('a');
    S1.push('b');
    S1.push('c');
    S1.push('d');
    S1.push('x');
    S1.push('A');

    // Cast stack<char> to stack<int>
    stack<int> S2(S1);

    stack<A> S3;
    S3.push(A(1.1));
    S3.push(A(2.2));
    S3.push(A(3.3));

    // Cast stack<A> to stack<B> with cast constructor
    stack<B> S4(S3);

    PRINT(S0);
    PRINT(S2);
    PRINT(S4);
}
