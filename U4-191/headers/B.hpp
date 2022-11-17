
struct B;

#ifndef B_H
#define B_H B_H
#include "A.hpp"

struct B {
    double b;
    B();
    B(A& x);
    operator A() const ;
};

#endif