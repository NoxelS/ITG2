#include <iostream>

#include "../headers/A.hpp"
#include "../headers/B.hpp"

using namespace std;

int main() {
    cout << endl << "A z1;\n";
    A z1;

    cout << endl << "B z2;\n";
    B z2;

    cout << endl << "z2 = B(z1);\n";
    z2 = B(z1);

    cout << endl << "z1 = A(z2);\n";
    z1 = A(z2);

    /*
     * Die letzte Aufgabe verstehe ich nicht ganz, da Gnu immer den Cast Konstruktor ausführen wird und nicht den Cast
     * Operator. Laut Styleguide soll auch immer der Cast Konstruktor bevorzugt werden.
     * Die einzige Möglichkeit um den Cast Operator zu verwenden wäre es, wenn keine Signatur für den Cast Konstruktor
     * exisitert.
     */
}