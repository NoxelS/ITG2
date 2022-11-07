using namespace std;
#include <iostream>

int f(int a) { return 1; }
int g(int& a) { return 2; }
int h(int* a) { return 3; }

int x = 0;
int* y = &x;

int main() {
    cout << f(x) << " ";
    // cout << f(y) << " "; // f(int a) erwartet eine rvalue und keinen Pointer

    // cout << f(*x) << " ";  // x ist kein pointer und lässt sich nicht dereferenzieren
    cout << f(*y) << " ";

    // cout << f(&x) << " "; // f(int a) erwartet eine rvalue und keinen Pointer
    // cout << f(&y) << " "; // f(int a) erwartet eine rvalue und keinen Pointer

    cout << g(x) << " ";
    // cout << g(y) << " "; // g(int& a) erwartet eine lvalue und keine rvalue

    // cout << g(*x) << " "; // x ist kein pointer und lässt sich nicht dereferenzieren
    cout << g(*y) << " ";

    // cout << g(&x) << " "; // g(int& a) erwartet eine lvalue und keine rvalue
    // cout << g(&y) << " "; // g(int& a) erwartet eine lvalue und keine rvalue

    // cout << h(x) << " "; // h(int* a) erwartet einen Pointer und nicht eine rvalue
    cout << h(y) << " ";

    // cout << h(*x) << " "; // x ist kein pointer und lässt sich nicht dereferenzieren
    // cout << h(*y) << " "; // *y ist eine rvalue und kein pointer

    cout << h(&x) << " ";
    // cout << h(&y) << " "; // h(int* a) erwartet einen Pointer und nicht einen Pointer auf einen Pointer (int**)
}
