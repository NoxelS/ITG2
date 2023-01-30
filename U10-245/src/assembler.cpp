using namespace std;
#include <math.h>

#include <bitset>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

namespace assembler {

size_t count = 0;

string instruction(string s) {
    string line = "\t";
    line.append(s);
    line.append(";\n");
    return line;
}

class astring : public string {
   public:
    using string::string;

    astring appendi(string b) {
        append(instruction(b));
        return *this;
    }

    astring appendi(string b, const string& comment) {
        append(instruction(b.append(";\t").append(comment)));
        return *this;
    }

    astring appendl(string label, int count = 0) {
        append(label + to_string(count) + ":\n");
        return *this;
    }
};

/** Add number on stack */
string number(long z) {
    astring out = "";
    char cmd[to_string(z).length()];
    snprintf(cmd, 12, "ldi A 0x%X", z);
    out.appendi(string(cmd), "Setze \"" + to_string(z) + "\" auf den Stack");
    out.appendi("push A");
    return out;
}

/** Add two numbers*/
string add() {
    astring out = "";
    out.appendi("pop A", "Addiere die obersten zwei Elemente auf dem Stack");
    out.appendi("pop B");
    out.appendi("add");
    out.appendi("push A", "Legen das Ergebnis auf den Stack");
    return out;
}
/** Subtract two numbers*/
string sub() {
    astring out = "";
    out.appendi("pop B", "Subtrahiere die obersten zwei Elemente auf dem Stack");
    out.appendi("pop A");
    out.appendi("sub");
    out.appendi("push A", "Legen das Ergebnis auf den Stack");
    return out;
}

/** Multiply two numbers*/
string mult() {
    astring out = "";
    out.appendi("pop D", "Multipliziere die obersten zwei Elemente auf dem Stack (a*b)");
    out.appendi("pop B");
    out.appendi("ldi C 0", "c als Akkumulator");
    out.appendl("mult_loop", count);
    // Mult_loop startet mit B = b und C = c, D = a
    out.appendi("ldi A 0");
    out.appendi("cmp", "Zeroflag ist gesetzt, wenn B = 0");
    out.appendi("jz \%mult_end" + to_string(count), "Ende der Multiplikation");
    out.appendi("mov A C", "Akkumulator auf A");
    out.appendi("mov E B");
    out.appendi("mov B D");
    out.appendi("add", "c += a");
    out.appendi("mov D B", "Schiebe a zurück auf D");
    out.appendi("mov C A");
    out.appendi("mov A E");
    out.appendi("dec", "b--");
    out.appendi("mov B A");
    out.appendi("jmp \%mult_loop" + to_string(count));
    out.appendl("mult_end", count);
    out.appendi("push C", "Akkumulator auf den Stack");

    count++;
    return out;
}

/** Divide two numbers*/
string div() {
    astring out = "";
    out.appendi("pop B", "Dividiere a/b: Zähler vom Stack");
    out.appendi("pop A", "Nenner vom Stack");
    out.appendi("ldi C 0", "c als Counter");
    out.appendl("div_loop", count);
    // Div_loop startet mit B = b und C = c, A = a
    out.appendi("cmp");
    out.appendi("jc \%div_end" + to_string(count), "Ende der Division");
    out.appendi("sub");
    out.appendi("push A");
    out.appendi("mov A C");
    out.appendi("inc");
    out.appendi("mov C A");
    out.appendi("pop A");
    out.appendi("jmp \%div_loop" + to_string(count));
    out.appendl("div_end", count);
    out.appendi("push C", "Counter auf den Stack");

    count++;
    return out;
}
/** Modulo two numbers*/
string modulo() {
    astring out = "";
    out.appendi("pop A", "Modulo a%b: Zähler vom Stack");
    out.appendi("pop B", "Nenner vom Stack");
    out.appendi("ldi C 0", "c als Counter");
    out.appendl("mod_loop", count);
    // Mod_loop startet mit B = b und C = c, A = a
    out.appendi("cmp");
    out.appendi("jc \%mod_end" + to_string(count), "Ende der Division");
    out.appendi("sub");
    out.appendi("push A");
    out.appendi("mov A C");
    out.appendi("inc");
    out.appendi("mov C A");
    out.appendi("pop A");
    out.appendi("jmp \%mod_loop" + to_string(count));
    out.appendl("mod_end", count);
    out.appendi("push A", "Rest auf den Stack");
    count++;
    return out;
}

}  // namespace assembler
