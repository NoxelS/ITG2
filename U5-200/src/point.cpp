#include "point.hpp"

#include <iostream>
#include <string>

double point::get_x() const { return x; };

double point::get_y() const { return y; };

void point::input() {
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;
};

void point::print() const { std::cout << this << ": " << this->to_string() << std::endl; };

std::string point::to_string() const { return "P(" + std::to_string(x) + ", " + std::to_string(y) + ")"; };