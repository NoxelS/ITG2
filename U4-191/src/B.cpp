#include "../headers/B.hpp"

#include <iostream>

#include "../headers/A.hpp"

B::B() {
    std::cout << " DFLT CTOR B::B()\n";
    b = 1;
}
B::B(A& x) {
    std::cout << " CAST CTOR B::B(A&)\n";
    b = -x.a;
}

B::operator A() const {
    std::cout << " CAST OP B::operator A()\n";
    return A(-b);
}