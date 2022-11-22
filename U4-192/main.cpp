#include <iostream>
using namespace std;

#define EXEC(x)                           \
    cout << "\"" << #x << "\"\r\t\t\t\t"; \
    x;                                    \
    cout << endl;

struct B {
    int b;
    B() : b(1) { cout << "DFLT CTOR B::B()           "; }
    B(int x) : b(x) { cout << "CAST CTOR B::B(int)        "; }
    B(const B& x) : b(x.b) { cout << "COPY CTOR B::B(const B&)   "; }
};

struct A {
    int a;
    A() : a(2) { cout << "DFLT CTOR A::A()           "; }
    A(int x) : a(x) { cout << "CAST CTOR A::A(int)        "; }
    A(const B& x) : a(x.b) { cout << "CAST CTOR A::A(const B&)   "; }
};

A a1(B z) { return (A)z; };
A a2(B(z)) { return (A)z; };

int main() {
    EXEC(B b1; cout << b1.b;) // b1 wird mit dem DFLT-CTOR initialisiert
    EXEC(B(b2); cout << b2.b;) // b2 wird mit dem DFLT-CTOR initialisiert da b2 kein Objekt ist
    EXEC(B b3(8); cout << b3.b;) // b3 wird mit dem CAST-CTOR initialisiert
    EXEC(B(b4) = 9; cout << b4.b;) // b4 wird mit dem CAST-CTOR initialisiert

    // EXEC(B(b3);) // Error: b3 wurde bereits initialisiert
    EXEC(B b5 = B(b3); cout << b5.b;) // b5 wird mit dem COPY-CTOR initialisiert (wie in der VL besprochen)
    EXEC(B b6((B)b3); cout << b6.b;) // (B)b3 ist redundant = b3 also ist das hier einfach ein COPY-CTOR

    EXEC(B b7(B(b3)); cout << b7);  // B(b3) ist ein Objekt und wird mit dem COPY-CTOR initialisiert, danach wird b7 mit dem COPY-CTOR initialisiert
    //EXEC(cout << b7.b;)  // Error: Warum auch immer ist b7 vom typ "B (*)(B b3)"
    // EXEC(cout << b7*(32);) // Error: b7(B) hat keinen operator().

    EXEC(cout << a1(42).a;) // 42 wird in ein B-Objekt mit dem CAST CTOR umgewandelt und dann mit dem CAST CTOR in ein A-Objekt umgewandelt
    EXEC(cout << a1(b3).a;)  // b3 wird in ein lokales Object mit dem COPY CTOR kopiert und dann mit dem CAST CTOR in ein
                             // A-Objekt umgewandelt
    EXEC(cout << a2(42).a;) // Selbes prinzip wie bei a1(42), nur dass explizit ein lokales Objekt erzeugt wird
    EXEC(cout << a2(b3).a;) // Selbes prinzip wie bei a1(b3), nur dass explizit ein lokales Objekt erzeugt wird
}
