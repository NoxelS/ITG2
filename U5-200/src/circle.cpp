#include "circle.hpp"

#include <iostream>

#include "area.hpp"
#include "point.hpp"

void circle::input() {
    point* p1_tmp = new point;
    std::cout << "Enter center Point: " << std::endl;
    p1_tmp->input();
    std::cout << "Enter r: ";
    std::cin >> r;
    x_0 = *p1_tmp;
    delete p1_tmp;

    /** Calculate Area */
    set_area(3.14159265358979323846 * r * r);

    /** Calculate Center of Area */
    set_coa(*p1_tmp);
};

void circle::print() const {
    std::cout << "Point x_0: " << x_0.to_string() << std::endl;
    std::cout << "Radius: " << std::to_string(r) << std::endl;
    std::cout << "Area: " << this->get_area() << std::endl;
    std::cout << "Center of area: " << this->get_coa().to_string() << std::endl;
};