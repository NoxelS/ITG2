
#include "exceptions.h"

#include <string>
#include <vector>

#include "cmdstr.h"
#include "global.h"
#include "lexer.h"

#ifndef TEST_FLAG
#define TEST_FLAG 0
#endif

SyntaxError::SyntaxError(cmdstr cstr, std::string msg) : std::runtime_error("Syntax Error") {
    if (TEST_FLAG) {
        // Running in unit test mode, TODO: more debugging
    } else {
        // Only because we call the first row 1
        lineCounter++;

        int charCount = 50;
        int begin = cstr.pos - charCount > 0 ? cstr.pos - charCount : 0;
        int end = cstr.pos + charCount < cstr.str.size() ? cstr.pos + charCount : cstr.str.size();
        int arrow = 0;
        bool foundError = false;
        int rowCount = 0;
        for (int i = begin; i < cstr.pos; i++) {
            if (cstr.str[i] == T_NEWLINE) {
                ++rowCount;
            }
        }

        std::cout << std::endl << "Syntax error occured while parsing" << std::endl;
        if (lineCounter - rowCount > 1) std::cout << "... |\t..." << std::endl;
        if (lineCounter - rowCount < 10) {
            std::cout << "00";
        } else if (lineCounter - rowCount < 100) {
            std::cout << "0";
        }
        std::cout << lineCounter - rowCount << " |\t";
        for (int i = begin; i < end; i++) {
            if (cstr.str[i] == T_NEWLINE) {
                if (foundError) {
                    break;
                } else {
                    arrow = 0;
                    std::cout << std::endl;

                    // line number to three digits
                    if (lineCounter - rowCount < 10) {
                        std::cout << "00";
                    } else if (lineCounter - rowCount < 100) {
                        std::cout << "0";
                    }

                    rowCount--;
                    std::cout << lineCounter - rowCount << " |\t";
                }
            } else {
                if (is_token(cstr.str[i])) {
                    std::cout << token_to_string(cstr.str[i]);
                    if (cstr.str[i] == cstr.peek()) {
                        foundError = true;
                    } else if (!foundError) {
                        arrow += token_to_string(cstr.str[i]).length();
                    }
                } else {
                    std::cout << cstr.str[i];
                    if (cstr.str[i] == cstr.peek()) {
                        foundError = true;
                    } else if (!foundError) {
                        arrow++;
                    }
                }
            }
        }
        std::cout << std::endl << "\t";
        for (int i = 0; i < arrow; i++) std::cout << " ";
        std::cout << "^- " << msg << std::endl;
    }
};

SyntaxError::SyntaxError(cmdstr cstr, std::string msg, std::string block) : SyntaxError(cstr, msg) {
    if (!TEST_FLAG) {
        if (block != "") std::cout << "in " << block << std::endl;
    }
};