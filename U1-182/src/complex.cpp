#include "complex.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

/** Constructor */
complex::complex() {
    real = 0;
    imag = 0;
    eulerForm = false;
}

/** Get the argument of a complex number */
double complex::arg() { return atan2(imag, real); }

/** Get the norm of a complex number */
double complex::abs() { return sqrt(real * real + imag * imag); }

/** Get the nth square root of the complex number */
complex* complex::nsqrt(int n) {
    complex* roots = new complex[n];
    double r = abs();
    double phi = arg();
    for (int i = 0; i < n; i++) {
        roots[i].real = pow(r, 1.0 / n) * cos((phi + 2 * M_PI * i) / n);
        roots[i].imag = pow(r, 1.0 / n) * sin((phi + 2 * M_PI * i) / n);
    }
    return roots;
}

/** Add another complex number or double to this one */
void complex::add(double d) { real += d; }
void complex::add(complex c) {
    real += c.real;
    imag += c.imag;
}

// Getters
double complex::getReal() { return real; }
double complex::getImag() { return imag; }

// Setters
void complex::setReal(double r) { real = r; }
void complex::setImag(double i) { imag = i; }

/** Add two complex numbers */
complex c_add(complex c1, complex c2) {
    complex c;
    c.setReal(c1.getReal() + c2.getReal());
    c.setImag(c1.getImag() + c2.getImag());
    return c;
}

/** Multiply two complex numbers */
complex c_mul(complex c1, complex c2) {
    complex c;
    c.setReal(c1.getReal() * c2.getReal() - c1.getImag() * c2.getImag());
    c.setImag(c1.getReal() * c2.getImag() + c1.getImag() * c2.getReal());
    return c;
}

/** 
 * Print a complex number
*/
void c_print(complex c) {
    if (c.eulerForm) {
        std::cout << c.abs() << " * exp(" << c.arg() << "i)" << std::endl;
    } else {
        std::cout << c.real << " + " << c.imag << "i" << std::endl;
    }
}