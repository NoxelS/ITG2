
#ifndef CMDSTR_HPP
#define CMDSTR_HPP CMDSTR_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class cmdstr {
   public:
    /** Internal std::vector for the std::string */
    std::vector<char> str = std::vector<char>();
    int pos = 0;

    /** Only used for debugging errors*/
    std::string context = "";

    /** Constructor */
    cmdstr() : cmdstr(""){};
    cmdstr(std::string s);
    cmdstr(const cmdstr& s);
    cmdstr(std::vector<char> s) : str(s){};
    cmdstr(std::vector<char> s, std::string line) : str(s){};

    /** Return next character and increment pointer */
    char next();

    /** Substitute an identitfier in the str and return a nre cmdstr*/
    cmdstr subst(long n, char identifier) const;

    /** Return the character f in front of the pointer without incrementing pointer*/
    char peek() const;
    char peek(int f) const;

    /** Consumes a char or a sequence of chars and throws an error if its not the next character */
    void consume(char c);
    void consume(std::string s);
};

std::ostream& operator<<(std::ostream& os, const cmdstr& s);

#endif