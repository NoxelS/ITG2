
#ifndef CMDSTR_HPP
#define CMDSTR_HPP CMDSTR_HPP

using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <ostream>

class cmdstr {
   public:
   /** Internal vector for the string */
    vector<char> str = vector<char>();
    int pos = 0;

    /** Constructor */
    cmdstr() : cmdstr(""){};
    cmdstr(string s);
    cmdstr(const cmdstr& s);

    /** Return next character and increment pointer */
    char next();

    /** Substitute an identitfier in the str and return a nre cmdstr*/
    cmdstr subst(long n, char identifier) const;
    
    /** Return next character without incrementing pointer */
    char peek() const;
};

ostream& operator<<(ostream& os, const cmdstr& s);

#endif