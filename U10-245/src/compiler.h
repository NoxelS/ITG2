
#include <string>
#include <vector>

#ifndef PARSER_H
#define PARSER_H PARSER_H

/**
 *  Parses the input string splitting it in lines and generate assembler code
 */
void compileString(std::vector<std::string>& asmText, std::vector<std::string>& asmData, std::string input);

/**
 *  Parses the input and generate assembler code
 */
void compileLine(std::vector<std::string>& asmText, std::vector<std::string>& asmData, std::string line);

/**
 *  Read a file and generate assembler code
 */
void compileFile(std::vector<std::string>& asmText, std::vector<std::string>& asmData, std::string filename);

#endif
