// File main.cpp

#include <math.h>

#include <iostream>

#include "vector3d.h"
using namespace std;

int main() {
    vector3d a(1, 2, 3);
    vector3d b(4, 5, 6);
    double c = 1.5;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "-a = " << -a << endl;
    cout << "+a = " << +a << endl;
    cout << "a - a = " << a - a << endl;
    cout << "a + (-a) = " << a + (-a) << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a * c = " << a * c << endl;
    cout << "c * a = " << c * a << endl;
    cout << "a / c = " << a / c << endl;
    double d = a % b;
    cout << "double d = a % b = " << d << endl;
    vector3d e = a % b;
    cout << "vector3d e = a % b = " << e << endl;
    cout << "a == b = " << (a == b) << endl;
    cout << "a != b = " << (a != b) << endl;
    cout << "a == a = " << (a == a) << endl;
    cout << "a != a = " << (a != a) << endl;
    cout << "a += b = " << (a += b) << endl;
    cout << "a += c = " << (a += c) << endl;
    cout << "a[0] = " << a[0] << endl;
    cout << "a[1] = " << a[1] << endl;
    cout << "a[2] = " << a[2] << endl;
    cout << "a.abs() = " << a.abs() << endl;
}
