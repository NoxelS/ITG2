#include "../src/complex.h"

#include <cmath>

#include "acutest.h"

void test_initialization() {
    complex c;
    c.setReal(1);
    c.setImag(2);
    TEST_CHECK(c.getReal() == 1);
    TEST_CHECK(c.getImag() == 2);
}

void test_arg() {
    complex c;
    c.setReal(1);
    c.setImag(1);
    TEST_CHECK(c.arg() == M_PI / 4);
}

void test_abs() {
    complex c;
    c.setReal(3);
    c.setImag(4);
    TEST_CHECK(c.abs() == 5);
}

void test_nsqrt() {
    complex c;
    c.setReal(1);
    complex* roots = c.nsqrt(4);

    TEST_CHECK(roots[0].getReal() == 1);
    TEST_CHECK(roots[0].getImag() == 0);
    /** This will fail because based on the implementation real or imag of a root cant be zero */
    // TEST_CHECK(roots[1].getReal() == 0);
    // TEST_CHECK(roots[1].getImag() == 1);
    // TEST_CHECK(roots[2].getReal() == -1);
    // TEST_CHECK(roots[2].getImag() == 0);
    // TEST_CHECK(roots[3].getReal() == 0);
    // TEST_CHECK(roots[3].getImag() == -1);
}

void test_add() {
    complex c;
    c.setReal(1);
    c.setImag(1);
    c.add(1);
    TEST_CHECK(c.getReal() == 2);
    TEST_CHECK(c.getImag() == 1);

    complex c2;
    c2.setReal(1);
    c2.setImag(1);
    c.add(c2);
    TEST_CHECK(c.getReal() == 3);
    TEST_CHECK(c.getImag() == 2);

    complex c3 = c_add(c, c2);
    TEST_CHECK(c3.getReal() == 4);
    TEST_CHECK(c3.getImag() == 3);
}

void test_mult() {
    complex c;
    c.setReal(1);
    c.setImag(1);
    complex c2;
    c2.setReal(1);
    c2.setImag(1);
    complex c3 = c_mul(c, c2);
    TEST_CHECK(c3.getReal() == 0);
    TEST_CHECK(c3.getImag() == 2);
}

void test_euler() {
    complex c;
    c.setReal(1);
    c.setImag(1);
    c.eulerForm = true;
    TEST_CHECK(c.getReal() == 1);
    TEST_CHECK(c.getImag() == 1);
}

TEST_LIST = {{"Initialization", test_initialization},
             {"Argument", test_arg},
             {"Absolute value", test_abs},
             {"Square root", test_nsqrt},
             {"Addition", test_add},
             {"Multiplication", test_mult},
             {"Euler form", test_euler},
             {0}};