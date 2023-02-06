
#ifndef SYNTAX_HPP
#define SYNTAX_HPP SYNTAX_HPP

#include <map>
#include <string>
#include <vector>

#include "cmdstr.h"

using namespace std;

class Syntax {
   public:
    /** Asm instructions */
    enum ASM { ldi, Test2 };
    map<ASM, string> ASMI = {{ldi, "test"}, {Test2, "test2"}};  // Usage: ASMI[ldi]

    /** References */
    cmdstr& cmd;
    vector<string>& asmText;
    vector<string>& asmData;

    /** Constructor */
    Syntax(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData)
        : cmd(cmd), asmText(asmText), asmData(asmData){};

    /** Parse the string and insert assembler code */
    void virtual operator()(cmdstr& cmd) = 0;
};

class Program : public Syntax {
   public:
    Program(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Block : public Syntax {
   public:
    Block(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Statement : public Syntax {
   public:
    Statement(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Assignment : public Syntax {
   public:
    Assignment(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};	

class Expression : public Syntax {
   public:
    Expression(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Conjunct : public Syntax {
   public:
    Conjunct(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Term : public Syntax {
   public:
    Term(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Disjunct : public Syntax {
   public:
    Disjunct(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Factor : public Syntax {
   public:
    Factor(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};

class Summand : public Syntax {
   public:
    Summand(cmdstr& cmd, vector<string>& asmText, vector<string>& asmData) : Syntax(cmd, asmText, asmData){};
    void operator()(cmdstr& cmd);
};



#endif