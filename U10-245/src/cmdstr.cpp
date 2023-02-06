
#include "cmdstr.h"

#include <ostream>
#include <string>
#include <vector>

using namespace std;

cmdstr::cmdstr(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ' && s[i] != '\0') str.push_back(s[i]);
    }
}

cmdstr::cmdstr(const cmdstr& s) {
    for (int i = s.pos; i < s.str.size(); i++) {
        str.push_back(s.str[i]);
    }
}

cmdstr cmdstr::subst(long n, char identifier = 'x') const {
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

char cmdstr::next() {
    if (pos < str.size()) {
        return str[pos++];
    } else {
        return '\0';
    }
}

char cmdstr::peek() const {
    if (pos < str.size()) {
        return str[pos];
    } else {
        return '\0';
    }
}

// Ostream for cmdlist
ostream& operator<<(ostream& os, const cmdstr& s) {
    for (int i = 0; i < s.str.size(); i++) {
        os << s.str[i];
    }
    os << endl;
    return os;
}
