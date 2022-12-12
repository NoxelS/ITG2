#include <iostream>
using namespace std;

int counter = 0;

void mprint(int** ref) {
  cout << "mprint: " << counter << endl;
    (*ref) = new int[counter];
}

template <class... T>
void mprint(int** ref, double arg, T... rest) {
    int previousCounter = counter++;
    mprint(ref, rest...);
    (*ref)[previousCounter] = arg;
}

int main() {
    int* a = new int;
    mprint(&a, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    for (int i = 0; i < counter; i++) {
        cout << a[i] << endl;
    }
}
