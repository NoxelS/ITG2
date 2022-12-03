#include <concepts>
#include <iostream>
#include <type_traits>

struct Circle {
    double radius;
    Circle(double radius) : radius(radius){};
    double calculateArea() const { return 3.14 * radius * radius; };
};

struct Plainarea {
    double area;
    Plainarea(double area_) : area(area_){};
    double calculateArea() const { return area; };
}; 

struct X {};

/** Use concept to only allow areas*/
template <typename T>
concept has_calculate_area = requires(T t) {
    { t.calculateArea() } -> std::convertible_to<double>;
};

template <has_calculate_area A>
double calculateArea(const A& area) {
    if constexpr (std::is_same<A, Plainarea>::value) {
        return 99;
    }
    return area.calculateArea();
    std::pointer_traits<A>::
}

// int main() {
//     Circle c(3);
//     Plainarea p(4);
//     X x;

//     std::cout << calculateArea(c) << std::endl;
//     std::cout << calculateArea(p) << std::endl;
//     // std::cout << calculateArea(x) << std::endl;
// }