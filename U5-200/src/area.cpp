#include "area.hpp"

point area::get_coa() const { return coa; }

double area::get_coa_x() const { return coa.get_x(); }

double area::get_coa_y() const { return coa.get_y(); }

double area::get_area() const { return area; }

void area::set_area(double area) { this->area = area; }
void area::set_coa(point coa) { this->coa = coa; }