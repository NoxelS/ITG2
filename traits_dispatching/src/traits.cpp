#include <concepts>
#include <iostream>
#include <type_traits>

struct A { int value; };
struct B { char value; };
struct C { int data; };

template <typename T>
concept has_value = requires(T t) { { t.value }; };

int main() {
    std::cout << has_value<A> << std::endl; // 1
    std::cout << has_value<B> << std::endl; // 1
    std::cout << has_value<C> << std::endl; // 0
}
