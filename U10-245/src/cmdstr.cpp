
#include "cmdstr.h"

#include <ostream>
#include <string>
#include <vector>

#include "exceptions.h"
#include "global.h"
#include "lexer.h"

cmdstr::cmdstr(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ' && s[i] != '\0') str.push_back(s[i]);
    }
}

cmdstr::cmdstr(const cmdstr& s) {
    str = s.str;
    pos = s.pos;
}

cmdstr cmdstr::subst(long n, char identifier = 'x') const {
    std::string s = "";

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == identifier) {
            s += std::to_string(n);
        } else {
            s += str[i];
        }
    }

    return cmdstr(s);
}

char cmdstr::next() {
    if (pos < str.size()) {
        while (str[pos] == T_NEWLINE) {
            ++lineCounter;
            ++pos;
        }
        return str[pos++];
    } else {
        return '\0';
    }
}

char cmdstr::peek() const {
    if (pos < str.size()) {
        if (str[pos] == T_NEWLINE) {
            return peek(2);
        } else {
            return str[pos];
        }
    } else {
        return '\0';
    }
}

char cmdstr::peek(int f) const {
    if (pos + f - 1 < str.size() && str[pos + f - 1 < str.size()] == T_NEWLINE) {
        return peek(f + 1);
    } else {
        if (pos + f - 1 < str.size()) {
            return str[pos + f - 1];
        } else {
            return '\0';
        }
    }
}

void cmdstr::consume(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        consume(s[i]);
    }
}

void cmdstr::consume(char c) {
    while (str[pos] == T_NEWLINE) {
        ++pos;
        ++lineCounter;
    }

    if (peek() == c) {
        next();
    } else {
        if (is_token(c)) {
            for (auto x : lexerTokens)
                if (x.second == c)
                    throw SyntaxError(*this,
                                      "Expected token \"" + x.first + "\"(0x" + std::to_string((int)x.second) +
                                          ") but got \"" + std::string(1, peek()) + "\"",
                                      context);
        } else {
            throw SyntaxError(
                *this, "Expected \"" + std::string(1, c) + "\" but got \"" + std::string(1, peek()) + "\"", context);
        }
    }
}

// Ostream for cmdlist
std::ostream& operator<<(std::ostream& os, const cmdstr& s) {
    for (int i = 0; i < s.str.size(); i++) {
        os << s.str[i];
    }
    os << std::endl;
    return os;
}
