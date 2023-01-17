using namespace std;
#include <math.h>

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

// Prototypes
class cmdstr;
double expression(cmdstr&);
void definition(cmdstr&);
double addend(cmdstr&);
double factor(cmdstr&);
double number(cmdstr&);
double factorial(double);
void plot(cmdstr&);

/** History container */
vector<pair<string, double>> history;

class cmdstr {
   public:
    vector<char> str = vector<char>();
    int pos = 0;

    cmdstr(string s = "") {
        for (int i = 0; i < s.length(); i++) {
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
    return os;
}

/** Globals */
map<char, cmdstr> fktlist;
map<char, char> varlist;  // Keep track of variable names of functions
map<char, double> constlist;

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
                case '\0':
                    end = true;
                    break;
                case '#':  // Plot a function
                    cmd.next();
                    plot(cmd);
                    break;
                case ':':
                    cmd.next();
                    if (cmd.peek() == '\0') {
                        // Loop over function defs and constants and print them
                        cout << "FUNCTIONS:" << endl;
                        for (auto it = fktlist.begin(); it != fktlist.end(); it++) {
                            cout << it->first << "(" << varlist[it->first] << ") = " << it->second << endl;
                        }
                        cout << "CONSTANTS:" << endl;
                        for (auto it = constlist.begin(); it != constlist.end(); it++) {
                            cout << it->first << " = " << it->second << endl;
                        }
                    } else {
                        definition(cmd);
                    }
                    break;
                case ';':
                    // Loop over history and print
                    cout << "HISOTRY:" << endl;
                    for (int i = 0; i < history.size(); i++) {
                        cout << "[" << i << "]: " << history[i].first << " = " << history[i].second << endl;
                    }
                    break;
                default:
                    double result = expression(cmd);
                    history.push_back(pair<string, double>(currentLine, result));
                    cout << result;
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
                s = fmod(s, factor(cmd));
                break;
        }

    return (s);
}

double factor(cmdstr& cmd) {
    double f;

    if (cmd.peek() == '[') {
        /* [Line refrence ]*/
        cmd.next();
        int lineRef = expression(cmd);
        if (cmd.next() != ']') throw std::invalid_argument("Syntax error: Missing closing bracket!");
        if (lineRef < 0 || lineRef >= history.size())
            throw std::invalid_argument("Syntax error: Line reference out of range!");
        return history[lineRef].second;
    } else if (cmd.peek() == '(') {
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

            // Parse the substring but add parentheses
            substring.str.push_back(')');
            substring.str.insert(substring.str.begin(), '(');
            f = expression(substring);

            if (cmd.next() != ')') throw std::invalid_argument("Syntax error: Missing closing parenthese!");
        } else {
            throw std::invalid_argument("Syntax error: Missing parenthese!");
        }
    } else {
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

    if (cmd.peek() ==
        '.') {  // || cmd.peek() == ',') { <- This wont be used because we need the , for function arguments
        cmd.next();
        double p = 1;
        while (isdigit(cmd.peek())) {
            p *= 10;
            z += double(cmd.next() - '0') / p;
        }
    }

    return (z);
}

double factorial(double n) {
    // use gamme function for floating point numbers
    if (n != static_cast<int>(n)) return tgamma(n + 1);
    if (n < 0) throw std::invalid_argument("Syntax error: Factorial of negative number!");
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

/*
 * Usage: #F, a, b, c
 */
void plot(cmdstr& cmd) {
    cout << "THIS FUNCTION IS NOT PROPERLY IMPLEMENTED YET!" << endl;
    if (!isupper(cmd.peek())) throw std::invalid_argument("Syntax error: Missing function name!");
    char identifier = cmd.next();
    if (cmd.next() != ',') throw std::invalid_argument("Syntax error: Missing comma!");

    double start = expression(cmd);
    if (cmd.next() != ',') throw std::invalid_argument("Syntax error: Missing comma!");

    double end = expression(cmd);
    if (cmd.next() != ',') throw std::invalid_argument("Syntax error: Missing comma!");

    double step = expression(cmd);

    std::map<double, double> xy;

    for (double i = start; i <= end; i += step) {
        cmdstr substring = fktlist.at(identifier).subst(i, varlist.at('F'));
        double value = expression(substring);
        xy[i] = value;
    }

    // Find max and min
    double max = xy[0];
    double min = xy[0];

    for (auto& p : xy) {
        if (p.second > max) max = p.second;
        if (p.second < min) min = p.second;
    }

    // Find the range
    double range = max - min;

    // Find the scale
    double scale = 1;

    while (range / scale > 20) scale *= 10;
    while (range / scale < 2) scale /= 10;

    // Make the plot
    cout << endl << endl;
    for (double y = max; y >= min; y -= scale) {
        cout << y << "\t|";
        for (auto& p : xy) {
            if (p.second > y - scale / 2 && p.second <= y + scale / 2) {
                cout << " .";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    cout << " \t+";
    for (auto& p : xy) {
        cout << "--";
    }
    cout << endl;

    cout << " \t ";
    for (auto& p : xy) {
        cout << " " << p.first;
    }
    cout << endl;
}