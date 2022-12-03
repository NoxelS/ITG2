#include <iostream>
#include <type_traits>

class A {}; class B: public A {}; class C: public B {};

int main() {
    std::cout << std::is_same<int, int>::value << std::endl;     // true
    std::cout << std::is_same<int, double>::value << std::endl;  // false
    std::cout << std::is_base_of<A, A>::value << std::endl;      // true
    std::cout << std::is_base_of<A, B>::value << std::endl;      // true
    std::cout << std::is_base_of<A, C>::value << std::endl;      // true
    std::cout << std::is_base_of<C, A>::value << std::endl;      // false
}
