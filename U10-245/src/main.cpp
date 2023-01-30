using namespace std;
#include <math.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "assembler.cpp"

#define FILEPATH "out.asm"

// Prototypes
void expression(char&);
void addend(char&);
void factor(char&);
void number(char&);

// Assembler output stream
ofstream _(FILEPATH);  // Remove file content
ofstream aso(FILEPATH, aso.app);

vector<string> aso_text(0);
vector<string> aso_data(0);

// Constants the user can use in the program
long constants[26] = {0};

int main() {
    char c, tmp;
    bool end = false;

    cout << "Taschenrechner (q = quit)\n";

    while (!end) {
        cin.get(c);

        switch (c) {
            case '\n':
                end = true;
                break;
            case 'q':
                end = true;
                break;
            default:
                expression(c);
                break;
        }
    }

    /** Write to file */
    aso << ".text\n";
    for (auto line : aso_text) {
        aso << line;
    }
    aso << "\thlt;\n";
    aso << ".data\n";
    for (auto line : aso_data) {
        aso << line;
    }
}

void expression(char& c) {
    switch (c) {
        case '+':
            cin.get(c);
            break;
        case '#':
            cin.get(c);
            cout << c;
            cout << 0;
            cout << '-';
            // TODO: make this work
            cin.get(c);
            break;
        default:
            addend(c);
            break;
    }

    while (c == '+' || c == '-') switch (c) {
            case '+':
                cin.get(c);
                addend(c);
                aso_text.push_back(assembler::add());
                break;
            case '-':
                cin.get(c);
                addend(c);
                aso_text.push_back(assembler::sub());
                break;
        }
}

void addend(char& c) {
    factor(c);
    while (c == '*' || c == '/' || c == '%') switch (c) {
            case '*':
                cin.get(c);
                factor(c);
                aso_text.push_back(assembler::mult());
                break;
            case '/':
                cin.get(c);
                factor(c);
                aso_text.push_back(assembler::div());
                break;
            case '%':
                cin.get(c);
                factor(c);
                aso_text.push_back(assembler::modulo());
                break;
        }
}

void factor(char& c) {
    switch (c) {
        case '(':
            cin.get(c);
            expression(c);
            switch (c) {
                case ')':
                    cin.get(c);
                    break;
                default:
                    throw std::invalid_argument("Parentheses do not match!");
                    break;
            }
            break;
        default:
            number(c);
            break;
    }
}

void number(char& c) {
    long z = 0;
    while (isdigit(c)) {
        z = 10 * z + long(c - '0');
        cin.get(c);
    }

    aso_text.push_back(assembler::number(z));
}