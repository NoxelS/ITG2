#include "../headers/A.hpp"

#include <iostream>

#include "../headers/B.hpp"

A::A() { std::cout << " DFLT CTOR  A::A()\n"; };

A::A(double x) { std::cout << " CAST CTOR  A::A(double)\n"; };

A::A(B& b) { std::cout << " CAST CTOR  A::A(B&)\n"; };
A::A(const B& b) { std::cout << " CAST CTOR  A::A(const B&)\n"; };
