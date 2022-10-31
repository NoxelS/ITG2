#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "complex.h"

using namespace std;

void demo(complex u, complex v) {
    printf("We declare two complex numbers: \n");
    printf("u = ");
    c_print(u);
    printf("v = ");
    c_print(v);

    printf("\nAddition: \n");
    complex w = c_add(u, v);
    w.eulerForm = u.eulerForm;
    printf("w = u + v = ");
    c_print(w);

    printf("\nMultiplication: \n");
    complex x = c_mul(u, v);
    x.eulerForm = u.eulerForm;
    printf("x = u * v = ");
    c_print(x);

    printf("\nSquare roots: \n");
    printf("y1 = u^(1/4) =\n");
    complex* y1 = u.nsqrt(4);
    for (int i = 0; i < 4; i++) {
        printf("(%i.): ", i + 1);
        y1[i].eulerForm = u.eulerForm;
        c_print(y1[i]);
    }
    printf("y2 = v^(1/4) =\n");
    complex* y2 = v.nsqrt(4);
    for (int i = 0; i < 4; i++) {
        printf("(%i.): ", i + 1);
        y2[i].eulerForm = u.eulerForm;
        c_print(y2[i]);
    }

    printf("\nAddition of a double: \n");
    printf("u = u + 2 (element function) =\n");
    u.add(2);
    c_print(u);
    printf("u = u + 2 (global function) =\n");
    complex k;
    k.setReal(2);
    c_add(u, k);
    c_print(u);
}

int main() {
    complex u, v;

    /** Set initial values*/
    u.setImag(42);
    u.setReal(7);
    v.setImag(2.2);
    v.setReal(1.8);

    demo(u, v);

    printf("\nIn euler form: \n");
    u.eulerForm = true;
    v.eulerForm = true;
    demo(u, v);
}
