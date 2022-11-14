#include <iostream>

using namespace std;

struct A {
    double a;
    A() { cout << " DFLT CTOR  A::A()\n"; }
    A(double x) { cout << " CAST CTOR  A::A(double)\n"; }
};

struct B {
    double b;
    B() {
        cout << " DFLT CTOR B::B()\n";
        b = 1;
    }
    B(A& x) {
        cout << " CAST CTOR B::B(A&)\n";
        b = -x.a;
    }
    operator A() {
        cout << " CAST OTOR B::operator A()\n";
        return A(-b);
    }
};

int main() {
    cout << endl << "A z1;\n";
    A z1;

    cout << endl << "B z2;\n";
    B z2;

    cout << endl << "z2 = B(z1);\n";
    z2 = B(z1);

    cout << endl << "z1 = A(z2);\n";
    z1 = A(z2);
}