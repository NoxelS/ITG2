#include "plainarea.hpp"

#include <iostream>

#include "area.hpp"
#include "point.hpp"

void plainarea::input() {
    double area_tmp = 0;
    point* coa_tmp = new point;
    std::cout << "Enter area: ";
    std::cin >> area_tmp;
    std::cout << "Enter center of area:" << std::endl;
    coa_tmp->input();
    set_coa(*coa_tmp);
    set_area(area_tmp);
    delete coa_tmp;
};

void plainarea::print() const {
    std::cout << "Area: " << this->get_area() << std::endl;
    std::cout << "Center of area: " << this->get_coa().to_string() << std::endl;
};