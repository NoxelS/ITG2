#include <cmath>
#include <iostream>

#include "../src/Vektor.hpp"
#include "../src/complex.h"  // um komplexere Objekte in den Container zu stecken
#include "acutest.h"

using namespace std;

void main_test() {
    ////////////////////////////////
    // Container aus Doubles
    Vektor<double> U(4);
    U.push_back(3.14);
    U.push_back(2.7);
    U.push_back(-1);
    U.push_back(42);
    Vektor<double>::iterator Uit;
    cout << U.size() << ":  ";
    TEST_CHECK(U.size() == 4);
    for (Uit = U.begin(); Uit != U.end(); ++Uit) {
        cout << (*Uit) << " ";
    }
    cout << endl;

    // Test if the values are correct
    double* TESTVALUES = new double[4]{3.14, 2.7, -1, 42};
    for (int i = 0; i < 4; i++) {
        TEST_CHECK(U.data[i] == TESTVALUES[i]);
    }
    ////////////////////////////////

    ////////////////////////////////
    // Verschiedene iterator-Konstruktoren
    Vektor<double>::iterator itX(&U.data[2]);  // Element-Konstruktor
    Vektor<double>::iterator itY(U);           // Container-Konstruktor
    cout << "itX = " << (*itX) << "   itY = " << (*itY) << endl;
    TEST_CHECK(*itX == -1);
    TEST_CHECK(*itY == 3.14);
    ////////////////////////////////

    ////////////////////////////////
    // Container aus komplexen Zahlen
    Vektor<complex> V1(5);
    V1.push_back(complex(11, 1));
    V1.push_back(complex(22, 2));
    V1.push_back(complex(33, 3));
    V1.push_back(complex(44, 4));
    V1.push_back(complex(55, 5));
    V1.push_back(complex(66, 6));
    V1.push_back(complex(77, 7));
    TEST_CHECK(V1.size() == 7);
    
    Vektor<complex>::iterator Vit;
    cout << V1.size() << ":  ";
    for (Vit = V1.begin(); Vit != V1.end(); ++Vit) cout << (*Vit) << " ";
    cout << endl;

    // Test if the values are correct
    complex* TESTVALUES2 = new complex[7]{complex(11, 1), complex(22, 2), complex(33, 3), complex(44, 4), complex(55, 5), complex(66, 6), complex(77, 7)};
    for (int i = 0; i < 7; i++) {
        TEST_CHECK(V1.data[i] == TESTVALUES2[i]);
    }
    ////////////////////////////////

    ////////////////////////////////
    // Zeiger auf Container ...
    Vektor<complex>* V2;
    V2 = new Vektor<complex>;
    V2->push_back(complex(1, 11));
    V2->push_back(complex(2, 22));
    V2->push_back(complex(3, 33));
    TEST_CHECK(V2->size() == 3);


    // wir verwenden Vit von oben...
    cout << V2->size() << ":  ";
    for (Vit = V2->begin(); Vit != V2->end(); ++Vit) cout << (*Vit) << " ";
    cout << endl;

    // Test if the values are correct
    complex* TESTVALUES3 = new complex[3]{complex(1, 11), complex(2, 22), complex(3, 33)};
    for (int i = 0; i < 3; i++) {
        TEST_CHECK(V2->data[i] == TESTVALUES3[i]);
    }
    ////////////////////////////////

    ////////////////////////////////
    // ... und Zeiger auf Iterator
    Vektor<complex>::iterator* Vit_ptr = new Vektor<complex>::iterator;
    cout << V2->size() << ":  ";
    for (*Vit_ptr = V2->begin(); *Vit_ptr != V2->end(); ++*Vit_ptr)
        // ACHTUNG: unterschiedliche Bedeutung der beiden *-Operatoren
        cout << (**Vit_ptr) << " ";
    cout << endl;

    // Test if the values are correct
    complex* TESTVALUES4 = new complex[3]{complex(1, 11), complex(2, 22), complex(3, 33)};
    for (int i = 0; i < 3; i++) {
        TEST_CHECK(V2->data[i] == TESTVALUES4[i]);
    }
    ////////////////////////////////

    ////////////////////////////////
    // Container aus Containern
    Vektor<Vektor<complex>> W(0);
    W.push_back(V1);
    W.push_back(*V2);
    cout << W << endl;
    TEST_CHECK(W.size() == 2);

    Vektor<Vektor<complex>>::iterator Wit;
    for (Wit = W.begin(); Wit != W.end(); ++Wit) {
        // ACHTUNG: nicht Wit->size(), da -> nicht überladen wurde
        cout << (*Wit).size() << ":  ";
        // bzw. falls -> explizit überladen wurde (s.o.)
        //    cout << Wit->size() << ":  ";
        // Vit als 'innerer' Iterator für Container Wit
        for (Vit = (*Wit).begin(); Vit != (*Wit).end(); ++Vit) cout << (*Vit) << " ";
        cout << endl;
    }
 }

TEST_LIST = {{"Initialization", main_test}, {0}};