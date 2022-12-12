#include <iostream>
#include "vektor.hpp"

using namespace std;

int main() {
    Vektor<int> v(10);
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    return 0;
}
