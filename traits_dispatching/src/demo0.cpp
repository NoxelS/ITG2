#include <concepts>
#include <iostream>
#include <type_traits>
#include <typeinfo>

struct A {
    int value;
};
struct B {
    int value;
};
struct C {
    int value;
    int value2;
};

struct optimizable_tag {};
struct unoptimizable_tag {};

template <typename T>
void algorithm(const T& u, unoptimizable_tag) {
    std::cout << "algorithm(" << typeid(T).name() << " u) -> unoptimiert" << std::endl;
};

template <typename T>
void algorithm(const T& u, optimizable_tag) {
    std::cout << "algorithm(" << typeid(T).name() << " u) -> optimiert" << std::endl;
};

template <typename T>
void algorithm(const T& u) {
    if constexpr (std::is_same_v<T, C>) {
        algorithm(u, optimizable_tag{});
    } else {
        algorithm(u, unoptimizable_tag{});
    }
};

int main() {
    A a(1);
    B b(2);
    C c(3, 4);
    C c2(3, 4);

    algorithm(a);
    algorithm(b);
    algorithm(c);
}