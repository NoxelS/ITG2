
using namespace std;
#include <cmath>
#include <iostream>

#include "complex.h"

template <class T, int n>
class Vektor {
   private:
    /** For inizialization */
    int pos = n;

    /** Data*/
    T data[n];

    /** Pointers */
    T* begin_ptr;
    T* end_ptr;
    size_t size_v;
    size_t capcacity_v;

   public:
    /** Constructors */
    Vektor(T erst) { data[--pos] = erst; };
    template <class U, class... V>
    Vektor(U erst, V... rest) : Vektor(rest...) {
        data[--pos] = erst;
    };

    /** Getter and Setter */
    size() { return size_v; };
    capcaity() { return capcaity_v; };
};

template <typename T, int V>
std::ostream& operator<<(std::ostream& os, const Vektor<T, V>& v) { return os; }

int main() {
    Vektor<int, 4> u1(1, 2, 3, 4);
    //  cout << u1 << endl << u2 << endl << u3 << endl << u1 + u2 + u3 << endl;
    //  cout << abs(u3) << "\n\n";

    //  Vektor<Vektor<double, 4>, 2> v1(u1, u2), v2(u2, u3), v3 = v1 + v2;
    //  cout << v1 << endl << v2 << endl << v3 << endl << v1 + v2 + v3 << endl;
    //  cout << abs(v3) << "\n\n";

    //  complex z1(1, 2), z2(3, 4), z3 = z1 + z2;
    //  Vektor<complex, 4> w1(z1, z2, z3, z1 + z2), w2(z1, z2, z3 + z1, z1), w3(1, 1, 1, complex(0, -1));
    //  cout << w1 << endl << w2 << endl << w3 << endl << w1 + w2 + w3 << endl;
    //  cout << abs(w3) << "\n\n";
}
