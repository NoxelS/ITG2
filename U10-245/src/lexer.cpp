
#include "lexer.h"

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "cmdstr.h"
#include "exceptions.h"
#include "global.h"

void lex_line(std::vector<char>& container, std::string line) {
    // Remove comments
    if (line.find("#") != std::string::npos) line.erase(line.find("#"));

    // Replace newlines with special token
    while (line.find("\n") != std::string::npos) {
        line.replace(line.find("\n"), 1, std::string(1, lexerTokens.at("NEWLINE")));
    }

    // Remove whitespace
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

    // Replace tokens with their binary value
    for (std::pair<std::string, uint8_t> token : lexerTokens) {
        while (line.find(token.first) != std::string::npos) {
            line.replace(line.find(token.first), token.first.length(), std::string(1, token.second));
        }
    }

    // Add to container
    for (char c : line) container.push_back(c);
}

bool is_token(uint8_t c) {
    for (std::pair<std::string, uint8_t> token : lexerTokens) {
        if (token.second == c) return true;
    }
    return false;
}

std::string token_to_string(uint8_t c) {
    for (std::pair<std::string, uint8_t> token : lexerTokens) {
        if (token.second == c) return token.first;
    }
    return "";
}