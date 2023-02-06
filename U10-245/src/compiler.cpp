
#include "compiler.h"

#include <fstream>
#include <map>
#include <sstream>

#include "cmdstr.h"
#include "exceptions.h"
#include "lexer.h"
#include "syntax.h"

#ifndef TEST_FLAG
#define TEST_FLAG 0
#endif

void compileString(std::vector<std::string>& asmText, std::vector<std::string>& asmData, std::string input) {
    // TODO: More debugging for lines
    compileLine(asmText, asmData, input);
}

void compileFile(std::vector<std::string>& asmText, std::vector<std::string>& asmData, std::string filename) {
    // TODO: More debugging for lines
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    compileString(asmText, asmData, content);
}

// TODO: missleading name, compiles a string
void compileLine(std::vector<std::string>& asmText, std::vector<std::string>& asmData, std::string line) {
    lineCounter = 0;
    std::vector<char> lineContainer;
    lex_line(lineContainer, line);
    cmdstr cmd(lineContainer);
    cmd.context = "Program";
    Program(cmd, asmText, asmData)();
}
