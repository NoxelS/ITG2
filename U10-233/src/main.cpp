using namespace std;
#include <math.h>

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class cmdstr {
   public:
    vector<char> str = vector<char>();
    int pos = 0;

    cmdstr(string s = "") {
        for (int i = 0; i < s.length(); i++) {
            // Push stripped
            if (s[i] != ' ' && s[i] != '\0') str.push_back(s[i]);
        }
    }

    cmdstr(const cmdstr& s) {
        for (int i = s.pos; i < s.str.size(); i++) {
            str.push_back(s.str[i]);
        }
    }

    cmdstr subst(long n, char identifier = 'x') {
        string s = "";

        for (int i = 0; i < str.size(); i++) {
            if (str[i] == identifier) {
                s += to_string(n);
            } else {
                s += str[i];
            }
        }

        return cmdstr(s);
    }

    char next() {
        if (pos < str.size()) {
            return str[pos++];
        } else {
            return '\0';
        }
    }

    char peek() {
        if (pos < str.size()) {
            return str[pos];
        } else {
            return '\0';
        }
    }
};

// Ostream for cmdlist
ostream& operator<<(ostream& os, const cmdstr& s) {
    for (int i = 0; i < s.str.size(); i++) {
        os << s.str[i];
    }
    os << endl;
    for (int i = 0; i < s.str.size(); i++) {
        if (i == s.pos) {
            os << "^";
        } else {
            os << " ";
        }
    }
    return os;
}

map<char, cmdstr> fktlist;
map<char, char> varlist; // Keep track of variable names of functions
map<char, double> constlist;

// Prototypes
double expression(cmdstr&);
void definition(cmdstr&);
double addend(cmdstr&);
double factor(cmdstr&);
double number(cmdstr&);
double factorial(double);

int main() {
    string currentLine;
    cmdstr cmd;
    bool end = false;

    while (!end) {
        cout << "\n>> ";
        getline(cin, currentLine);
        cmd = cmdstr(currentLine);

        try {
            switch (cmd.peek()) {
                case 'q':
                    end = true;
                    break;
                case ':':
                    cmd.next();
                    definition(cmd);
                    break;
                default:
                    cout << expression(cmd);
                    break;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what();
        }
    }
}

void definition(cmdstr& cmd) {
    char identifier = cmd.next();

    if (islower(identifier)) {
        if (cmd.next() != '=')
            throw std::invalid_argument("Syntax error in definition, expected '=' after identifier!");
        constlist.insert(pair<char, double>(identifier, expression(cmd)));

    } else if (isupper((identifier))) {
        if (cmd.next() != '(')
            throw std::invalid_argument("Syntax error in definition, exptected paranthese after identifier!");
        char variableName = cmd.next();
        if (!islower(variableName))
            throw std::invalid_argument("Syntax error in definition, variable names can only be variable names!");
        if (cmd.next() != ')') throw std::invalid_argument("Syntax error in definition, missing closing paranthese!");
        if (cmd.next() != '=') throw std::invalid_argument("Syntax error in definition, expected '='!");

        // Create a new cmdstr for the rext
        cmdstr def = cmdstr(cmd);

        // Add the new function to the list
        fktlist.insert(pair<char, cmdstr>(identifier, def));
        varlist.insert(pair<char, char>(identifier, variableName));

                cout
            << "Added new function " << identifier << "(" << variableName << ")";
    } else {
        throw std::invalid_argument(
            "Syntax error: Invalid variable name in definition, exptected lower- or uppercase letter!");
    }
}

double expression(cmdstr& cmd) {
    double a;

    switch (cmd.peek()) {
        case '+':
            cmd.next();
            a = +addend(cmd);
            break;
        case '-':
            cmd.next();
            a = -addend(cmd);
            break;
        default:
            a = addend(cmd);
            break;
    }

    while (cmd.peek() == '+' || cmd.peek() == '-') switch (cmd.next()) {
            case '+':
                a += addend(cmd);
                break;
            case '-':
                a -= addend(cmd);
                break;
        }

    return (a);
}

double addend(cmdstr& cmd) {
    double s = factor(cmd);
    while (cmd.peek() == '*' || cmd.peek() == '/' || cmd.peek() == '%') switch (cmd.next()) {
            case '*':
                s *= factor(cmd);
                break;
            case '/':
                s /= factor(cmd);
                break;
            case '%':
                // This down cast wont destroy floating point numbers because we dont support them anyway
                s = (double)(static_cast<int>(s) % static_cast<int>(factor(cmd)));
                break;
        }

    return (s);
}

double factor(cmdstr& cmd) {
    double f;

    if (cmd.peek() == '(') {
        /* ( Ausdruck )*/
        cmd.next();
        f = expression(cmd);
        if (cmd.next() != ')') throw std::invalid_argument("Syntax error: Missing closing parenthese!");
    } else if (islower(cmd.peek())) {
        /* LowerLetter */
        try {
            f = constlist.at(cmd.next());
        } catch (const std::out_of_range& e) {
            throw std::invalid_argument("Syntax error: Undefined variable name!");
        }

    } else if (isupper(cmd.peek())) {
        char identifier = cmd.next();
        /* UpperLetter ( Ausdruck ) */
        if (cmd.next() == '(') {
            long valueAt = expression(cmd);
            cmdstr substring;
            try {
                substring = fktlist.at(identifier).subst(valueAt, varlist.at(identifier));
            } catch (const std::out_of_range& e) {
                throw std::invalid_argument("Syntax error: Undefined function name!");
            }
            // Parse the substring but add the parentheses back
            substring.str.push_back(')');
            substring.str.insert(substring.str.begin(), '(');
            f = expression(substring);

            if (cmd.next() != ')') throw std::invalid_argument("Syntax error: Missing closing parenthese!");
        } else {
            throw std::invalid_argument("Syntax error: Missing parenthese!");
        }
    } else {
        /** Number */
        f = number(cmd);
    }

    // Check if there is a ! or ^ after the number
    while (cmd.peek() == '!') {
        f = factorial(f);
        cmd.next();
    }

    if (cmd.peek() == '^') {
        cmd.next();
        f = pow(f, factor(cmd));
    }

    return (f);
}

double number(cmdstr& cmd) {
    double z = 0;
    while (isdigit(cmd.peek())) z = 10 * z + double(cmd.next() - '0');
    return (z);
}

double factorial(double n) {
    if (n == 0)
        return (1);
    else
        return (n * factorial(n - 1));
}