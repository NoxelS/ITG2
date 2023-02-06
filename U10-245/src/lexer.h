
#include <map>
#include <string>
#include <vector>
#include "global.h"

#ifndef LEXER_H
#define LEXER_H LEXER_H

/**
 *  Removes whitespace and comments from a line, then replaces Tokens with their corresponding binary value
 */
void lex_line(std::vector<char>& container, std::string line);

/** Return true if c is a token binary value */
bool is_token(uint8_t c);

/** Return the string representation of a token binary value */
std::string token_to_string(uint8_t c);

#endif