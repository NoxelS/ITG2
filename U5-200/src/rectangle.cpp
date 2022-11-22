#include "rectangle.hpp"

#include <iostream>

#include "area.hpp"
#include "point.hpp"

void rectangle::input() {
    point* p1_tmp = new point;
    point* p2_tmp = new point;
    std::cout << "Enter Point 1: " << std::endl;
    p1_tmp->input();
    std::cout << "Enter Point 2: " << std::endl;
    p2_tmp->input();
    p1 = *p1_tmp;
    p2 = *p2_tmp;
    delete p1_tmp;
    delete p2_tmp;

    /** Calculate Area */
    set_area(abs(p2.get_x() - p1.get_x()) * abs(p2.get_y() - p1.get_y()));

    /** Calculate Center of Area */
    point* coa_tmp = new point((p1.get_x() + p2.get_x()) / 2, (p1.get_y() + p2.get_y()) / 2);
    set_coa(*coa_tmp);
    delete coa_tmp;
};

void rectangle::print() const {
    std::cout << "Point 1: " << p1.to_string() << std::endl;
    std::cout << "Point 2: " << p2.to_string() << std::endl;
    std::cout << "Area: " << this->get_area() << std::endl;
    std::cout << "Center of area: " << this->get_coa().to_string() << std::endl;
};