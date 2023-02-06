#include "syntax.h"

#include <map>
#include <string>
#include <vector>

#include "cmdstr.h"
#include "exceptions.h"
#include "lexer.h"

void Program::operator()() {
    cmd.consume(T_MAIN);
    cmd.consume("()");

    Block(cmd, asmText, asmData)();
    // TODO: Check end of file
}

void Block::operator()() {
    cmd.consume("{");
    while (cmd.peek() != '}') {
        Statement(cmd, asmText, asmData)();
    }
    cmd.consume("}");
}

void Statement::operator()() {
    switch (cmd.peek()) {
        case ';':
            cmd.next();
            break;
        case T_WHILE:
            cmd.next();
            cmd.consume("(");
            Expression(cmd, asmText, asmData)();
            cmd.consume(")");
            Block(cmd, asmText, asmData)();
            break;
        case T_IF:
            cmd.next();
            cmd.consume("(");
            Expression(cmd, asmText, asmData)();
            cmd.consume(")");
            cmd.consume(T_THEN);
            Block(cmd, asmText, asmData)();
            if (cmd.peek() == T_ELSE) {
                cmd.next();
                Block(cmd, asmText, asmData)();
            }
            break;
        case T_PRINT:
            cmd.next();
            cmd.consume("(");
            Expression(cmd, asmText, asmData)();
            cmd.consume(")");
            break;
        case '{':  // TODO: Make better
            Block(cmd, asmText, asmData)();
            break;
        default:
            if (islower(cmd.peek())) {
                Reference(cmd, asmText, asmData)();
                cmd.consume("=");
                Expression(cmd, asmText, asmData)();
                cmd.consume(";");
            } else {
                throw SyntaxError(cmd,
                                  "Unexpected character " + std::string(1, cmd.peek()) +
                                      ", expected one of ;, Block, Reference, WHILE, IF, PRINT",
                                  "Statement");
            }
            break;
    }
}

void Expression::operator()() {
    Disjunct(cmd, asmText, asmData)();
    while (cmd.peek() == '|') {
        cmd.next();
        cmd.consume('|');
        Disjunct(cmd, asmText, asmData)();
    }
}

void Disjunct::operator()() {
    Conjunct(cmd, asmText, asmData)();
    while (cmd.peek() == '&') {
        cmd.next();
        cmd.consume('&');
        Conjunct(cmd, asmText, asmData)();
    }
}

void Conjunct::operator()() {
    Term(cmd, asmText, asmData)();

    while (cmd.peek() == '>' || cmd.peek() == '<' || (cmd.peek(1) == '=' && cmd.peek(2) == '=') ||
           (cmd.peek(1) == '!' && cmd.peek(2) == '=')) {
        switch (cmd.peek()) {
            case '>':
                cmd.next();  // >
                if (cmd.peek() == '=') {
                    cmd.next();  // >=
                }
                break;
            case '<':
                cmd.next();  // <
                if (cmd.peek() == '=') {
                    cmd.next();  // <=
                }
                break;
            case '=':
                cmd.next();
                cmd.consume('=');  // ==
                break;
            case '!':
                if (cmd.peek(1) == '=') {
                    cmd.consume("!=");  // !=
                }
            default:
                throw SyntaxError(cmd,
                                  "Unexpected character " + std::string(1, cmd.peek()) + ", expected one of >, <, =, !",
                                  "Conjunct");
        }
        Term(cmd, asmText, asmData)();
    }
}

void Term::operator()() {
    if (cmd.peek() == '-' || cmd.peek() == '+') {
        switch (cmd.next()) {
            case '+':
                // TODO
                break;
            case '-':
                // TODO
                break;
        }
    }

    Summand(cmd, asmText, asmData)();

    while (cmd.peek() == '+' || cmd.peek() == '-' || cmd.peek() == '|') {
        switch (cmd.next()) {
            case '+':
                // TODO
                break;
            case '-':
                // TODO
                break;
            case '|':
                // TODO
                break;
        }
        Summand(cmd, asmText, asmData)();
    }
}

void Factor::operator()() {
    if (cmd.peek() == '(') {
        cmd.consume('(');
        Expression(cmd, asmText, asmData)();
        cmd.consume(")");
    } else if (islower(cmd.peek())) {
        Reference(cmd, asmText, asmData)();
    } else if (isdigit(cmd.peek())) {
        Integer(cmd, asmText, asmData)();
    } else if (cmd.peek() == T_INPUT) {
        // TODO
    } else {
        throw SyntaxError(
            cmd,
            "Unexpected character " + std::string(1, cmd.peek()) + ", expected one of Integer, Reference, '(' , INPUT",
            "Factor");
    }
}

void Summand::operator()() {
    Negation(cmd, asmText, asmData)();
    while (cmd.peek() == '*' || cmd.peek() == '/' || cmd.peek() == '&' || cmd.peek() == '%') {
        switch (cmd.next()) {
            case '*':
                // TODO
                break;
            case '/':
                // TODO
                break;
            case '&':
                // TODO
                break;
            case '%':
                // TODO
                break;
        }
        Negation(cmd, asmText, asmData)();
    }
}

void Negation::operator()() {
    if (cmd.peek() == '!' || cmd.peek() == '~') {
        switch (cmd.next()) {
            case '!':
                // TODO
                break;
            case '~':
                // TODO
                break;
        }
    }
    Factor(cmd, asmText, asmData)();
}

void Reference::operator()() {
    while (islower(cmd.peek())) {
        LowerLetter(cmd, asmText, asmData)();
    }
}

void Integer::operator()() {
    while (isdigit(cmd.peek())) {
        Digit(cmd, asmText, asmData)();
    }
}

void Digit::operator()() {
    if (isdigit(cmd.peek())) {
        char c = cmd.next();
    } else {
        throw SyntaxError(cmd, "Unexpected character " + std::string(1, cmd.peek()) + ", expected a digit", "Digit");
    }
}

void LowerLetter::operator()() {
    if (islower(cmd.peek())) {
        char c = cmd.next();
    } else {
        throw SyntaxError(cmd, "Unexpected character " + std::string(1, cmd.peek()) + ", expected a lower letter",
                          "LowerLetter");
    }
}

void Program::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of program");
}

void Block::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of block");
}

void Statement::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of statement");
}

void Expression::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of expression");
}

void Conjunct::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of conjunct");
}

void Term::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of term");
}

void Disjunct::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of disjunct");
}

void Factor::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of factor");
}

void Summand::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of summand");
}

void Negation::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of negation");
}

void Reference::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of reference");
}

void Integer::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of integer");
}

void Digit::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of digit");
}

void LowerLetter::genAsm() {
    static int labelCounter = 0;
    asmText.push_back("; Beginning of lower letter");
}
