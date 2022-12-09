#include <cmath>
#include <iostream>
using namespace std;

#define PRINT(x) cout << #x << "\r\t\t\t\t ==> " << x << endl

template <class T>
T Summe(T Erst) {
    return (Erst);
}

template <class T1, class... T2>
T1 Summe(T1 Erst, T2... Rest) {
    return (Erst + Summe(Rest...));
}

template <class T>
T Norm(T Erst) {
    return (Erst);
}

template <class T1, class... T2>
double Norm(T1 Erst, T2... Rest) {
    return (sqrt(Erst * Erst + Norm(Rest...) * Norm(Rest...)));
}

int main() {
    PRINT(Norm(2));
    PRINT(Norm(2, 3));
    PRINT(Norm(2, 3, 4));
    PRINT(Norm(1, 1, 0, 1));
    PRINT(Norm(1., 1.2, 0.5, 1.5));
    PRINT(Norm('i', 't', 'g', 2));
    // PRINT(Norm("ab", 't', 'g', 2));
    string a = "Hallo ";
    PRINT(Summe(a, string("Welt"), '!'));
}
