#include <math.h>

#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cmdstr.h"
#include "compiler.h"
#include "lexer.h"
#include "syntax.h"

int main(int arc, char* argv[]) {
    /** Container for ASM output */
    std::vector<std::string> asmText;
    std::vector<std::string> asmData;

    if (arc > 1) {
        compileFile(asmText, asmData, argv[1]);

    } else {
        std::string input = "MAIN() {\n";
        std::string currentLine;
        int lineCount = 1;
        std::cout << "Inline mode: Enter code to compile. Enter 'exit()' to exit." << std::endl << lineCount << " |\t";
        while (std::getline(std::cin, currentLine) && currentLine != "exit()") {
            input += currentLine + "\n";
            lineCount++;
            std::cout << lineCount << " |\t";
        }
        input += "\n}";
        try {
            compileString(asmText, asmData, input);
        } catch (const SyntaxError& e) {
            // TODO
        }
    }
}
