#include <iostream>
#include <type_traits>

class Class {};
class Classs : public Class {};

void algorithm_signed(int i) { /*...*/
}
void algorithm_unsigned(unsigned u) { /*...*/
}

//      is_base_of<Base, Derived>
//     is_convertible<From, To>
//     is_same<T, U>

typedef int Radius;

struct Diameter {
    double value;
    Diameter(double r) : value(r){};
};

struct Circle {
    double ara;
    template <typename T>
    Circle(T rd){
        if constexpr(std::is_same<decltype(rd), Radius>::value) {
            ara = 3.14 * rd * rd;
            std::cout << "Radius" << std::endl;
        } else if constexpr(std::is_same<decltype(rd), Diameter>::value) {
            std::cout << "Diameter" << std::endl;
            ara = 3.14 * rd.value * rd.value / 4;
        }
    };
};

template <typename T>
void algorithm(T t) {
    if constexpr (std::is_base_of<Class, T>::value) {
        std::cout << "algorithm() called with a type based on Class 'Class'" << std::endl;
    }

    if constexpr (std::is_same<T, int>::value) {
        std::cout << "algorithm() called with an int or unsigned" << std::endl;
    }

    // if constexpr (std::is_signed<T>::value)
    //     algorithm_signed(t);
    // else if constexpr (std::is_unsigned<T>::value)
    //     algorithm_unsigned(t);
    // else
    //     static_assert(std::is_signed<T>::value || std::is_unsigned<T>::value, "Must be signed or unsigned!");
}

// int main() {
//     std::cout << std::is_floating_point<Class>::value << '\n';
//     std::cout << std::is_floating_point<Classs>::value << '\n';
//     std::cout << std::is_floating_point<float>::value << '\n';
//     std::cout << std::is_floating_point<int>::value << '\n';
//     algorithm(3);  // T is int, include algorithm_signed()

//     unsigned x = 3;
//     Class a;
//     algorithm(a);  // T is unsigned int, include algorithm_unsigned()

//     Radius r = 10;

//     Circle c1((Diameter)3);
//     Circle c2((Radius)3);
//     Circle c3(r);
//     // algorithm("hello");  // T is string, build error!
// }