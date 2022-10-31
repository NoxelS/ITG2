
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;

void sub1() {
    int a = 7;
    int* b;
    double c = 3.14;
    double* d;

    b = (int*)malloc(sizeof(int));
    d = (double*)malloc(sizeof(double));

    //  a = *b; c = *d;
    //  *b = a; *d = c;
    //  b = &a; d = &c;
    //  *b=a; *d=c; (*b)++; (*d)++;
    //  *b=a; *d=c; ++*b; ++*d;

    //  b = &a+1; d = &c+1;
    //  b=&a; d=&c; *b++; *d++;
    //  *b = *&a+1; *d = *&c+1;
    //  *b = a+1; *d = c+1;
    //  *b = a++; *d = c++;

    printf("   Adresse        | Inhalt         | Inhalt \n");
    printf("   im RAM         | der Adresse    | des Ziels\n");
    printf("------------------+----------------+-----------------\n");
    printf("a: %14p | %14i |\n", &a, a);
    printf("b: %14p | %14p | %8i\n", &b, b, *b);
    printf("c: %14p | %14f |\n", &c, c);
    printf("d: %14p | %14p | %8f\n", &d, d, *d);
}

float func1(int x, float y) { return (x + y); }
float func2(int x, float y) { return (x - y); }

void sub2() {
    // Variante 1
    float (*f_ptr)(int, float);
    f_ptr = &func1;
    printf("f_ptr(2, 3.14) = %f\n", (*f_ptr)(2, 3.14));
    f_ptr = &func2;
    printf("f_ptr(2, 3.14) = %f\n", (*f_ptr)(2, 3.14));

    // Variante 2 (ohne & und *)
    float (*g_ptr)(int, float);
    g_ptr = func1;
    printf("g_ptr(2, 3.14) = %f\n", g_ptr(2, 3.14));
    g_ptr = func2;
    printf("g_ptr(2, 3.14) = %f\n", g_ptr(2, 3.14));
}

void sub3() {
    int a1 = 42;
    float a2 = 3.14;
    int* b;
    float* c;
    void* d = malloc(sizeof(void));

    d = &a1;
    b = d;
    printf("%d\n", *b);
    d = &a1;
    c = d;
    printf("%f\n", *c);

    d = &a2;
    b = d;
    printf("%d\n", *b);
    d = &a2;
    c = d;
    printf("%f\n", *c);
}

int main() {
    sub1();
    sub2();
    sub3();
}