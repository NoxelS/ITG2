#include <iostream>

#include "area.hpp"
#include "circle.hpp"
#include "plainarea.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

namespace shape {
enum shape {
    circle = 1,
    rectangle = 2,
    triangle = 3,
    plainarea = 4,
};
std::string get_shape_name(int shape) {
    switch (shape) {
        case shape::circle:
            return "Circle";
        case shape::rectangle:
            return "Rectangle";
        case shape::triangle:
            return "Triangle";
        case shape::plainarea:
            return "Plainarea";
        default:
            return "Unknown";
    }
}
}  // namespace shape
int main() {
    int n = 0;
    std::cout << "Number of areas: ";
    std::cin >> n;
    area** areas = new area*[n];

    std::cout << "Valid area types:" << std::endl;
    for (int j = 1; j <= 4; j++) {
        std::cout << shape::get_shape_name(j) << " - " << shape::shape(j) << std::endl;
    }
    std::cout << "-------------------" << std::endl;
    int id = 0;
    for (int i = 0; i < n; i++) {
        std::cout << "Select area type: ";
        std::cin >> id;

        switch (id) {
            case shape::rectangle:
                areas[i] = new rectangle;
                break;
            case shape::circle:
                areas[i] = new circle;
                break;
            case shape::triangle:
                areas[i] = new triangle;
                break;
            case shape::plainarea:
                areas[i] = new plainarea;
                break;

            default:
                std::cout << "Invalid area type!" << std::endl;
                break;
        }

        areas[i]->input();
    }
    std::cout << "-----Calculated-----" << std::endl;
    for (int i = 0; i < n; i++) {
        areas[i]->print();
    }
};
