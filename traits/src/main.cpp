#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

class X {};

template <typename T>
concept isClass = std::is_class<T>::value;

template <typename T>
concept bool is_printable = (T a) {
    { std::cout << a };
};

template <is_printable T>
void f(T t) {
    std::cout << t << std::endl;
};

using namespace std;

int main() {
    cout << "Hello World!" << endl;
    f(2);
    return 0;
}
