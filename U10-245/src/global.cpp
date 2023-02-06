
#include "global.h"

#include <map>
#include <string>
#include <vector>

/** Map to store all tokens and binary value */
std::map<std::string, uint8_t> lexerTokens = {{"WHILE", T_WHILE}, {"IF", T_IF},     {"ELSE", T_ELSE},
                                              {"FOR", T_FOR},     {"THEN", T_THEN}, {"PRINT", T_PRINT},
                                              {"INPUT", T_INPUT}, {"MAIN", T_MAIN}, {"NEWLINE", T_NEWLINE}};

int lineCounter = 0;