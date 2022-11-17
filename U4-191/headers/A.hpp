
struct A;

#ifndef A_H
#define A_H A_H
#include "B.hpp"

struct A {
    double a;
    A();
    A(double x);
    A(B& b);
    A(const B& b);
};

#endif