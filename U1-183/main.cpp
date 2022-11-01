
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;

void sub1() {
    int a = 7; // Lege a fest
    int* b; // Deklariere ein Zeiger auf int
    double c = 3.14; // Lege c fest
    double* d; // Deklariere ein Zeiger auf double

    // Memory für b und d reservieren
    b = (int*)malloc(sizeof(int));
    d = (double*)malloc(sizeof(double));

    a = *b; // Kopiere den Wert von b nach a (a = 0)
    c = *d; // Kopiere den Wert von d nach c (c = 0.0)
    *b = a; // Kopiere den Wert von a nach b (b = 0)
    *d = c; // Kopiere den Wert von c nach d (d = 0.0)
    b = &a; // b zeigt nun auf a 
    d = &c; // d zeigt nun auf c
    *b = a; // Kopiere den Wert von a nach b (b zeigt auf a)
    *d = c; // Kopiere den Wert von c nach d (d zeigt auf c)
    (*b)++; // Erhöhe den Wert von b (also a) um 1 (a = 1)
    (*d)++; // Erhöhe den Wert von d (also c) um 1 (b = 1)
    *b = a; // Kopiere den Wert von a nach b (b zeigt auf a) 
    *d = c; // Kopiere den Wert von c nach d (d zeigt auf c)
    ++*b;   // Erhöhe den Wert von b (also a) um 1 (a = 2)
    ++*d;   // Erhöhe den Wert von b (also a) um 1 (b = 2)

    b = &a + 1; // b zeigt nun auf die Adresse &a + 4 Byte (b zeigt also auf sich selber)
    d = &c + 1; // d zeigt nun auf die Adresse &c + 8 Byte (d zeigt also auf sich selber)

    b = &a; // b zeigt nun wieder auf a
    d = &c;  // d zeigt nun wieder auf c
    *b++; // Hier wird zuerst b++ gerechnet, also &a + 1 = &a + 4 Bytes = &b: b zeigt nun auf sich selber. Der * operator verändert dabei b nicht. Wir kännten auch b++ schreiben.
    *d++;  // Gleiches spiel, d zeigt nun auf sich selber

    /** Die folgenden Zeilen erzeugen jeweiles einen seg fault, da die Zeiger gerade auf sich selber Zeigen und wir deswegen mittels *d und *b in eine unendliche Schleife kämen */
    //  *b = *&a+1; // Seg fault
    // *d = *&c+1; // Seg fault
    // *b = a+1; *d = c+1; // Seg fault
    //   *b = a++; *d = c++; // Seg fault

    printf("   Adresse        | Inhalt         | Inhalt \n");
    printf("   im RAM         | der Adresse    | des Ziels\n");
    printf("------------------+----------------+-----------------\n");
    printf("a: %14p | %14i |\n", &a, a);
    printf("b: %14p | %14p | %8i\n", &b, b, *b, *b);
    printf("c: %14p | %14f |\n", &c, c);
    printf("d: %14p | %14p | %8f\n", &d, d, *d, *d);
}

float func1(int x, float y) { return (x + y); }
float func2(int x, float y) { return (x - y); }

typedef float (*func)(int, float);

/** Wrapper wor func1 and func2*/
func w(int sel) {
    if (sel == 0) return &func1;
    if (sel == 1) return &func2;
    return NULL;
};

/** Swap refrences if compare evaluets to true*/
void dual_sort(int* x, int* y, bool (*cmp)(int, int)) {
    if (cmp(*x, *y)) {
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }
}

/** Compare functions */
bool compare_1(int x, int y) { return x > y; }
bool compare_2(int x, int y) { return sqrt(x * x) > sqrt(y * y); }

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

    // Variante 3 (mit wrapper)
    printf("w(0)(2, 3.14) = %f\n", (*w)(0)(2, 3.14));
    printf("w(0)(2, 3.14) = %f\n", (*w)(1)(2, 3.14));

    // Sort with compare function
    int a = 4;
    int b = -5;
    printf("a = %i, b = %i\n", a, b);

    dual_sort(&a, &b, &compare_1);
    printf("a = %i, b = %i\n", a, b);

    dual_sort(&a, &b, &compare_2);
    printf("a = %i, b = %i\n", a, b);
}

void varprint(int type, void* x) {
    switch (type) {
        case 0:
            printf("%i\n", *(int*)x);
            break;
        case 1:
            printf("%f\n", *(float*)x);
            break;
        case 2:
            printf("%c\n", *(char*)x);
            break;
        default:
            break;
    }
}

void sub3() {
    /** Allocate memory */
    void* a1 = malloc(sizeof(int));
    void* a2 = malloc(sizeof(float));
    void* a3 = malloc(sizeof(char));

    /** Set calues to see output*/
    *(int*)a1 = 10;
    *(float*)a2 = 1.1;
    *(char*)a3 = 'a';

    /** Dynamic prints */
    varprint(0, a1);
    varprint(1, a2);
    varprint(2, a3);
}

int main() {
    sub1();
    // sub2();
    // sub3();
}