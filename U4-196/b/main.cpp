#include <iostream>
using namespace std;

struct klasseA {
    int j = 0;
    int w = 0, x = 0, y = 0, z = 0;
    klasseA(int a, int b, int c, int d) : klasseA(a,b,c) {
        cout << "CTOR 4: " << j++ << " " << this << endl;
        z = d;
    }
    klasseA(int a, int b, int c) : klasseA(a,b) {
        cout << "CTOR 3: " << this << endl;
        y = c;
    }
    klasseA(int a, int b): klasseA(a) {
        cout << "CTOR 2: " << this << endl;
        // Explizites Casting des Übergabeparameters 'a', da Compiler sonst
        // 'klasseA(a)' als Instanziierungs- und nicht als Cast-Konstruktor
        // interpretiert.
        // sonst: error, declaration of 'klasseA a' shadows a parameter
        x = b;
        ++j;
    }
    klasseA(int a): klasseA() {
        cout << "CTOR 1: " << this << endl;
        w = a;
        ++j;
    }
    klasseA() { cout << "CTOR 0: " << this << endl; }
    void print() const { cout << this << ": " << j << " = " << w << " " << x << " " << y << " " << z << "\n\n"; }
};

int main() {
    klasseA M1(10, 20, 30, 40);
    M1.print();
    klasseA M2(11, 21, 31);
    M2.print();
    klasseA M3(12, 22);
    M3.print();
    klasseA M4(13);
    M4.print();
    klasseA M5;
    M5.print();
}
