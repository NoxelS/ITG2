#define TEST_FLAG = 1

#include <math.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../src/cmdstr.h"
#include "../src/compiler.h"
#include "../src/exceptions.h"
#include "../src/global.h"
#include "../src/lexer.h"
#include "../src/syntax.h"
#include "acutest.h"

void lexer_remove_whitespaces() {
    std::vector<char> container;
    std::string line = "A B CD  E   \tF \t G \tH \t\tI \t\t\t\tJ";
    lex_line(container, line);
    for (size_t i = 0; i < container.size(); i++) {
        TEST_CHECK(container[i] == char(int('A') + i));
    }
    TEST_CHECK(container.size() == 10);
}

void lexer_remove_comments() {
    std::vector<char> container;
    std::string line = "A B CD  E   \tF \t G \tH \t\tI #\t\t\t\tJ";
    std::string line2 = "#";
    std::string line3 = "123#abc";
    std::string line4 = "123#abc#";
    std::string line5 = "123#abc#123##";
    lex_line(container, line);
    for (size_t i = 0; i < container.size(); i++) {
        TEST_CHECK(container[i] == char(int('A') + i));
    }
    container.erase(container.begin(), container.end());
    lex_line(container, line2);
    TEST_CHECK(container.size() == 0);
    container.erase(container.begin(), container.end());
    lex_line(container, line3);
    for (size_t i = 0; i < container.size(); i++) {
        TEST_CHECK(container[i] == char(int('1') + i));
    }
    TEST_CHECK(container.size() == 3);
    container.erase(container.begin(), container.end());
    lex_line(container, line4);
    for (size_t i = 0; i < container.size(); i++) {
        TEST_CHECK(container[i] == char(int('1') + i));
    }
    TEST_CHECK(container.size() == 3);
    container.erase(container.begin(), container.end());
    lex_line(container, line5);
    for (size_t i = 0; i < container.size(); i++) {
        TEST_CHECK(container[i] == char(int('1') + i));
    }
    TEST_CHECK(container.size() == 3);
}

void test_token(std::vector<char>& container, std::string token) {
    std::string preline = "A B C 1 2 3 ( ) { } ; \t ";
    std::string line = preline + token + " # comment";
    lex_line(container, line);
    TEST_CHECK(container.size() == 12);
    TEST_CHECK(container[11] == lexerTokens.at(token));
}

void lexer_tokenize() {
    std::vector<char> container;
    for (auto token : lexerTokens) {
        container.erase(container.begin(), container.end());
        test_token(container, token.first);
    }
}

void compiler_start() {
    std::string line = "MAIN(){}";
    std::vector<std::string> asmText;
    std::vector<std::string> asmData;

    compileLine(asmText, asmData, line);
}

void test_all_valid_file() {
    std::vector<std::string> asmText;
    std::vector<std::string> asmData;

    /** Valid files */
    for (auto entry : std::filesystem::directory_iterator("./tests/test_files/valid")) {
        compileFile(asmText, asmData, entry.path().string());
    }
}

void test_all_invalid_file() {
    std::vector<std::string> asmText;
    std::vector<std::string> asmData;

    /** Invalid files */
    for (auto entry : std::filesystem::directory_iterator("./tests/test_files/invalid")) {
        TEST_EXCEPTION(compileFile(asmText, asmData, entry.path().string()), SyntaxError);
    }
}

TEST_LIST = {{"a) Lexer - Whitespace", lexer_remove_whitespaces},
             {"a) Lexer - Comments", lexer_remove_comments},
             {"b) Lexer - Tokenize", lexer_tokenize},
             {"c) Compiler - Start", compiler_start},
             {"d) Compiler - Test all valid dicc files", test_all_valid_file},
             {"d) Compiler - Test all invalid dicc files", test_all_invalid_file},
             {0}};