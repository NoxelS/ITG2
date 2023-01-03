using namespace std;
#include <math.h>

#include <iostream>
#include <stdexcept>
#include <string>

// Prototypes
void expression(char&);
void addend(char&);
void factor(char&);
void number(char&);

// Constants the user can use in the program
double constants[26] = {0};

int main() {
    char c, tmp;
    bool end = false;

    while (!end) {
        cout << "\n>> ";
        cin.get(c);

        switch (c) {
            case '\n':
                end = true;
                break;
            default:
                expression(c);
                break;
        }
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
                cout << '+';
                break;
            case '-':
                cin.get(c);
                addend(c);
                cout << '-';
                break;
        }
}

void addend(char& c) {
    factor(c);
    while (c == '*' || c == '/' || c == '%') switch (c) {
            case '*':
                cin.get(c);
                factor(c);
                cout << '*';
                break;
            case '/':
                cin.get(c);
                factor(c);
                cout << '/';
                break;
            case '%':
                cin.get(c);
                factor(c);
                cout << '%';
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
    double z = 0;
    while (isdigit(c)) {
        z = 10 * z + double(c - '0');
        cin.get(c);
    }

    cout << z;
}