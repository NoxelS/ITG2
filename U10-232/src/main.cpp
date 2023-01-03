using namespace std;
#include <math.h>

#include <iostream>
#include <stdexcept>
#include <string>

// Prototypes
double expression(char&);
double definition(char&);
double addend(char&);
double factor(char&);
double number(char&);
double factorial(double);
double func(double);

// Constants the user can use in the program
double constants[26] = {0};

int main() {
    char c;
    bool end = false;

    while (!end) {
        cout << "\n>> ";
        cin.get(c);

        switch (c) {
            case '\n':
                end = true;
                break;
            case ':':
                cout << definition(c);
                break;
            default:
                cout << expression(c);
                break;
        }
    }
}

double definition(char& c) {
    cin.get(c);
    char tmp = c;
    if (!islower(c)) cout << "Expression error!\n";

    cin.get(c);
    if (c != '=') cout << "Expression error!\n";

    cin.get(c);

    constants[(int)tmp - 'a'] = expression(c);

    return constants[(int)tmp - 97];
}

double expression(char& c) {
    double a;

    switch (c) {
        case '+':
            cin.get(c);
            a = +addend(c);
            break;
        case '-':
            cin.get(c);
            a = -addend(c);
            break;
        default:
            a = addend(c);
            break;
    }

    while (c == '+' || c == '-') switch (c) {
            case '+':
                cin.get(c);
                a += addend(c);
                break;
            case '-':
                cin.get(c);
                a -= addend(c);
                break;
        }

    return (a);
}

double addend(char& c) {
    double s = factor(c);
    while (c == '*' || c == '/' || c == '%') switch (c) {
            case '*':
                cin.get(c);
                s *= factor(c);
                break;
            case '/':
                cin.get(c);
                s /= factor(c);
                break;
            case '%':
                cin.get(c);
                // This down cast wont destroy floating point numbers because we dont support them anyway
                s = (double)(static_cast<int>(s) % static_cast<int>(factor(c)));
                break;
        }

    return (s);
}

double factor(char& c) {
    double f;

    switch (c) {
        case '(':
            cin.get(c);
            f = expression(c);
            switch (c) {
                case ')':
                    cin.get(c);
                    break;
                default:
                    throw std::invalid_argument("Parentheses do not match!");
                    break;
            }
            break;
        case 'F':
            cin.get(c);
            if (c == '(') {
                cin.get(c);
                f = func(expression(c));
                if (c == ')') {
                    cin.get(c);
                } else {
                    throw std::invalid_argument("Parentheses do not match!");
                }
            } else {
                throw std::invalid_argument("The function F() is missing the parentheses!");
            }
            break;
        default:
            f = number(c);
            break;
    }

    // Check if there is a ! or ^ after the number
    while (c == '!') {
        f = factorial(f);
        cin.get(c);
    }

    if (c == '^') {
        cin.get(c);
        f = pow(f, factor(c));
    }

    return (f);
}

double number(char& c) {
    double z = 0;

    // Check if the user means a variable
    if (islower(c)) {
        z = constants[int(c) - 'a'];
        cin.get(c);
        return z;
    }

    // Check if the user means a number
    while (isdigit(c)) {
        z = 10 * z + double(c - '0');
        cin.get(c);
    }

    return (z);
}

double factorial(double n) {
    if (n == 0)
        return (1);
    else
        return (n * factorial(n - 1));
}

double func(double x) { return (x * x); }