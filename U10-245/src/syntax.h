
#ifndef SYNTAX_HPP
#define SYNTAX_HPP SYNTAX_HPP

#include <map>
#include <string>
#include <vector>

#include "cmdstr.h"
#include "exceptions.h"

/**
 *
 *
 */
class Syntax {
   public:
    /** Asm instructions */
    enum ASM {
        nop,
        hlt,
        call,
        ret,
        cmp,
        mout,
        min,
        add,
        adc,
        sub,
        inc,
        dec,
        and_,
        or_,
        xor_,
        shl,
        shr,
        rol,
        ror,
        not_,
        mlo,
        mhi,
        sqrt,
        ldi,
        ldx,
        stx,
        lda,
        sta,
        push,
        pop,
        jmp,
        jz,
        jnz,
        je,
        jne,
        jc,
        jnc,
        rout,
        rin,
        mov,
    };

    /**
     *  Description for each instruction:
     *  - nop: No operation
     *  - hlt: Halt
     *  - call: (call D) Aufruf der Subroutine bei D
     *  - ret: Return from subroutine
     *  - cmp: A - B kein Update von A, nur Flags setzen
     *  - mout: Memory out
     *  - min: Memory in
     *  - add: Addition
     *  - adc: Addition with carry
     *  - sub: Subtraction
     *  - inc: Increment
     *  - dec: Decrement
     *  - and_: Bitwise and
     *  - or_: Bitwise or
     *  - xor_: Bitwise xor
     *  - shl: Bitwise shift left
     *  - shr: Bitwise shift right
     *  - rol: Bitwise rotate left
     *  - ror: Bitwise rotate right
     *  - not_: Bitwise not
     *  - mlo: Memory low
     *  - mhi: Memory high
     *  - sqrt: Square root
     *  - ldi: (ldi R I) Lade Konstante I in Register R
     *  - ldx: (ldx R D) Kopiere Daten von RAM-Adr. D nach Reg. R
     *  - stx: (stx R D) Kopiere Daten von Reg. R nach RAM-Adr. D
     *  - lda: (lda R) Kopiere Daten von RAM-Adr. in Reg_A nach Reg. R
     *  - sta: (sta R) Kopiere Daten von Reg. R nach RAM-Adr. in Reg_A
     *  - push: Push to stack
     *  - pop: Pop from stack
     *  - jmp: Jump
     *  - jz: Jump if zero
     *  - jnz: Jump if not zero
     *  - je: Jump if equal
     *  - jne: Jump if not equal
     *  - jc: Jump if carry
     *  - jnc: Jump if not carry
     *  - rout: Read output
     *  - rin: Read input
     *  - mov: (mov R2 R1) Kopiere Register R1+ nach R2
     */
    const std::map<ASM, std::string> ASMI = {
        {nop, "nop"},   {hlt, "hlt"},   {call, "call"}, {ret, "ret"}, {cmp, "cmp"}, {mout, "mout"}, {min, "min"},
        {add, "add"},   {adc, "adc"},   {sub, "sub"},   {inc, "inc"}, {dec, "dec"}, {and_, "and"},  {or_, "or,"},
        {xor_, "xor"},  {shl, "shl"},   {shr, "shr"},   {rol, "rol"}, {ror, "ror"}, {not_, "not"},  {mlo, "mlo"},
        {mhi, "mhi"},   {sqrt, "sqrt"}, {ldi, "ldi"},   {ldx, "ldx"}, {stx, "stx"}, {lda, "lda"},   {sta, "sta"},
        {push, "push"}, {pop, "pop"},   {jmp, "jmp"},   {jz, "jz,"},  {jnz, "jnz"}, {je, "je,"},    {jne, "jne"},
        {jc, "jc,"},    {jnc, "jnc"},   {rout, "rout"}, {rin, "rin"}, {mov, "mov"},
    };

    /** References */
    cmdstr& cmd;
    std::vector<std::string>& asmText;
    std::vector<std::string>& asmData;

    /** Constructor */
    Syntax(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : cmd(cmd), asmText(asmText), asmData(asmData){};

    /** Parse the std::string and insert assembler code */
    void virtual operator()() = 0;

    /** Generate assembler code */
    void virtual genAsm() = 0;
};

class Program : public Syntax {
   public:
    Program(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Block : public Syntax {
   public:
    Block(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Statement : public Syntax {
   public:
    Statement(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Expression : public Syntax {
   public:
    Expression(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Conjunct : public Syntax {
   public:
    Conjunct(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Term : public Syntax {
   public:
    Term(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Disjunct : public Syntax {
   public:
    Disjunct(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Factor : public Syntax {
   public:
    Factor(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Summand : public Syntax {
   public:
    Summand(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Negation : public Syntax {
   public:
    Negation(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Reference : public Syntax {
   public:
    Reference(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Integer : public Syntax {
   public:
    Integer(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class Digit : public Syntax {
   public:
    Digit(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

class LowerLetter : public Syntax {
   public:
    LowerLetter(cmdstr& cmd, std::vector<std::string>& asmText, std::vector<std::string>& asmData)
        : Syntax(cmd, asmText, asmData){};
    void operator()();
    void virtual genAsm();
};

#endif