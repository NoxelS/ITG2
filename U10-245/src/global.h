
#include <map>
#include <string>
#include <vector>

#define T_WHILE 0x10
#define T_IF 0x11
#define T_ELSE 0x12
#define T_FOR 0x13
#define T_THEN 0x14
#define T_PRINT 0x15
#define T_INPUT 0x16
#define T_MAIN 0x17

// Only used for debugging!
#define T_NEWLINE 0x18

#ifndef GLOBAL_H
#define GLOBAL_H GLOBAL_H

/** Map to store all tokens and binary value */
extern std::map<std::string, uint8_t> lexerTokens;
extern int lineCounter;

#endif