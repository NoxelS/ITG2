/////////////////////////////////////////////////////
// Allgemeine Vektormusterklasse
// für bel. Elementdatentyp und bel. Länge

#include <cmath>
#include <iostream>

#include "Vektor.hpp"
#include "complex.h"  // um komplexere Objekte in den Container zu stecken

using namespace std;

int main() {
    ////////////////////////////////
    // Container aus Doubles
    Vektor<double> U(4);
    U.push_back(3.14);
    U.push_back(2.7);
    U.push_back(-1);
    U.push_back(42);
    Vektor<double>::iterator Uit;
    cout << U.size() << ":  ";
    for (Uit = U.begin(); Uit != U.end(); ++Uit) cout << (*Uit) << " ";
    cout << endl;
    ////////////////////////////////

    ////////////////////////////////
    // Verschiedene iterator-Konstruktoren
    Vektor<double>::iterator itX(&U.data[2]);  // Element-Konstruktor
    Vektor<double>::iterator itY(U);           // Container-Konstruktor
    cout << "itX = " << (*itX) << "   itY = " << (*itY) << endl;
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

    Vektor<complex>::iterator Vit;
    cout << V1.size() << ":  ";
    for (Vit = V1.begin(); Vit != V1.end(); ++Vit) cout << (*Vit) << " ";
    cout << endl;
    ////////////////////////////////

    ////////////////////////////////
    // Zeiger auf Container ...
    Vektor<complex>* V2;
    V2 = new Vektor<complex>;
    V2->push_back(complex(1, 11));
    V2->push_back(complex(2, 22));
    V2->push_back(complex(3, 33));

    // wir verwenden Vit von oben...
    cout << V2->size() << ":  ";
    for (Vit = V2->begin(); Vit != V2->end(); ++Vit) cout << (*Vit) << " ";
    cout << endl;
    ////////////////////////////////

    ////////////////////////////////
    // ... und Zeiger auf Iterator
    Vektor<complex>::iterator* Vit_ptr = new Vektor<complex>::iterator;
    cout << V2->size() << ":  ";
    for (*Vit_ptr = V2->begin(); *Vit_ptr != V2->end(); ++*Vit_ptr)
        // ACHTUNG: unterschiedliche Bedeutung der beiden *-Operatoren
        cout << (**Vit_ptr) << " ";
    cout << endl;
    ////////////////////////////////

    ////////////////////////////////
    // Container aus Containern
    Vektor<Vektor<complex>> W(0);
    W.push_back(V1);
    W.push_back(*V2);
    cout << W << endl;
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

    ////////////////////////////////
    return 0;
}
