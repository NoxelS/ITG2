
#include <string>
#include <vector>

#include "cmdstr.h"


#ifndef SYNTAX_H
#define SYNTAX_H SYNTAX_H


/**
 *  Error to be thrown when a syntax error occurs *
 */
class SyntaxError : public std::runtime_error {
   public:
    SyntaxError(cmdstr cstr, std::string msg);
    SyntaxError(cmdstr cstr, std::string msg, std::string block);
};

#endif