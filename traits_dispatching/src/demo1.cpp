#include <concepts>
#include <iostream>
#include <type_traits>
#include <typeinfo>

struct A { int value; };
struct B { double value; };
struct C { char value; int value2; };

template <typename T>
concept has_value = requires(T t) {
                        { t.value } -> std::convertible_to<double>;
                    };

template <typename T>
concept is_optimizable = requires(T t) {
                             { t.value } -> std::convertible_to<double>;
                             { t.value2 } -> std::convertible_to<double>;
                         };

template <has_value T>
void algorithm(const T& u) {
    if constexpr (is_optimizable<T>) {
        std::cout << typeid(T).name() << " -> optimiert" << std::endl;
        // ...
    } else {
        std::cout << typeid(T).name() << " -> unoptimiert" << std::endl;
        // ...
    }
}

int main() {
    A a(1);
    B b(2.);
    C c('a', 4);

    algorithm(a);  // A -> unoptimiert
    algorithm(b);  // B -> unoptimiert
    algorithm(c);  // C -> optimiert
    // algorithm(10);  // error: ... required for the satisfaction of ‘has_value<T>’ [with T = int]
}