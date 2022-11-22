#include <iostream>
using namespace std;

struct X {
    int* dat;

    X() {
        cout << "=> X-DFLT-CTOR\n";
        dat = new int;
        *dat = 9;
    }

    // common DTOR
    ~X() {
        delete dat;
        cout << "=> X-DFLT-DTOR\n";
    }

    // copy semantics
    X(const X& rhs) {
        cout << "=> X-COPY-CTOR (const)\n";
        dat = new int;
        *this = rhs;
    }  // delegate to copy-op

    X& operator=(const X& rhs) {
        cout << "=> X-COPY-OTOR (const)\n";
        *dat = *(rhs.dat);  // deep copy
        return *this;
    }

    // move semantics
    X(X&& rhs) {
        cout << "=> X-MOVE-CTOR\n";
        dat = move(rhs.dat);  // flat copy
        rhs.dat = NULL;
    }

    X& operator=(X&& rhs) {
        cout << "=> X-MOVE-OP\n";
        if (this != &rhs) {
            delete dat;
            dat = move(rhs.dat);  // flat copy
            rhs.dat = NULL;
        }
        return *this;
    }
};

struct Y {
    X* res;

    Y() { cout << "DFLT-CTOR\n"; };
    ~Y() { cout << "DFLT-DTOR\n"; };

    // Copy-Semantics
    Y(const Y& rhs) {
        cout << "=> COPY-CTOR\n";
        res = new X;
        *this = rhs;
    };

    Y& operator=(const Y& rhs) {
        cout << "=> COPY-OP\n";
        *res = *(rhs.res);
        return *this;
    };
};

int main() {
    cout << "\n  === Init (vars) ===\n";
    Y y1, y2;

    cout << "\n  === Init (const) ===\n";
    const Y y3(y1);

    cout << "\n  === Copy-Operator: y1 = const y3 ===\n";
    y1 = y3;

    cout << "\n  === Copy-Operator: y1 = y2 ===\n";
    y1 = y2;

    cout << "\n  === Move-Operator: y1 = move(const y3) ===\n";
    y1 = move(y3);

    cout << "\n  === Move-Operator: y1 = move(y2) ===\n";
    y1 = move(y2);

    cout << "\n  === ENDE\n";
}
