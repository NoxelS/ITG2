#include <iostream>

#include "area.hpp"
#include "point.hpp"
#include "triangle.hpp"

void triangle::input() {
    point* p1_tmp = new point;
    point* p2_tmp = new point;
    point* p3_tmp = new point;
    std::cout << "Point p1: " << std::endl;
    p1_tmp->input();
    std::cout << "Point p2: " << std::endl;
    p2_tmp->input();
    std::cout << "Point p3: " << std::endl;
    p3_tmp->input();
    p1 = *p1_tmp;
    p2 = *p2_tmp;
    p3 = *p3_tmp;
    delete p1_tmp;
    delete p2_tmp;
    delete p3_tmp;

    /** Calculate Area */
    set_area(0.5 * abs((p1.get_x() * (p2.get_y() - p3.get_y()) + p2.get_x() * (p3.get_y() - p1.get_y()) + p3.get_x() * (p1.get_y() - p2.get_y()))));

    /** Calculate Center of Area */
    point* coa_tmp = new point((p1.get_x() + p2.get_x() + p3.get_x()) / 3, (p1.get_y() + p2.get_y() + p3.get_y()) / 3);
    set_coa(*coa_tmp);
    delete coa_tmp;
};

void triangle::print() const {
    std::cout << "Point 1: " << p1.to_string() << std::endl;
    std::cout << "Point 2: " << p2.to_string() << std::endl;
    std::cout << "Area: " << this->get_area() << std::endl;
    std::cout << "Center of area: " << this->get_coa().to_string() << std::endl;
};