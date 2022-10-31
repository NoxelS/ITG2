#include <iostream>

/** Apparently, we need this to make sure it only is compiled once */
#ifndef COMPLEX_H
#define COMPLEX_H

/**
 * @file complex.h
 * @brief Complex number
 */
class complex {
   private:
    double real;
    double imag;

   public:
    /** Constructor */
    complex();

    /**
     * @brief Get the argument of a complex number
     */
    double arg();

    /**
     * @brief Get the norm of a complex number
     */
    double abs();

    /**
     * @brief Get the nth square root of the complex number
     */
    complex* nsqrt(int);

    /**
     * @brief Add another complex number or double to this one
     */
    void add(double);
    void add(complex);

    /**
     * @brief Overload the << operator to print a complex number
     */
    friend void c_print(complex);

    /**
     * Set to true if the complex number should be printed in euler form. Default is false.
     */
    bool eulerForm;

    // Getters
    double getReal();
    double getImag();

    // Setters
    void setReal(double);
    void setImag(double);
};

/** @brief Add two complex numbers */
complex c_add(complex, complex);

/** @brief Multiply two complex numbers */
complex c_mul(complex, complex);

/** @brief Print a complex number */
void c_print(complex);

#endif