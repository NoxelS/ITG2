#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**************************************************/
// Parser: syntactical analysis
/**************************************************/

// Tokenstring class
class tokenstr {
   public:
    vector<char> str;
    vector<char>::iterator chr;
    tokenstr() { rewind(); }

    template <typename T>  // for vecotr<char> and string
    tokenstr(T instr) {
        for (typename T::iterator it = instr.begin(); it != instr.end(); ++it)
            if (*it != ' ' && *it != '\0') str.push_back(*it);
        rewind();
    }

    tokenstr& rewind() {
        chr = str.begin();
        return *this;
    }

    bool next() {
        ++chr;
        return (chr != str.end());
    }
};

// output tokenstring
ostream& operator<<(ostream& s, vector<char> v) {
    for (vector<char>::iterator it = v.begin(); it != v.end(); ++it) s << *it;
    return (s);
}

// Shunting-Yard-algorithm
//
// Prototypes
int satz(tokenstr&);
int objekt(tokenstr&);
int praedikat(tokenstr&);
int subjekt(tokenstr&);
int substantiv(tokenstr&);
int adjektiv(tokenstr&);
int artikel(tokenstr&);

int parser(tokenstr& cs) {
    int ret = 0;
    ret = satz(cs);
    return ret;
}

int satz(tokenstr& cs) {
    int ret = 0;
    ret += subjekt(cs);                // Required
    ret += praedikat(cs);              // Required
    if (cs.next()) ret += objekt(cs);  // Optional
    return ret;
}

int objekt(tokenstr& cs) { return artikel(cs) + adjektiv(cs) + substantiv(cs); }

int subjekt(tokenstr& cs) { return artikel(cs) + adjektiv(cs) + substantiv(cs); }

int praedikat(tokenstr& cs) {
    int ret = 0;
    if (*cs.chr == '1') {
        cs.next();
    } else if (*cs.chr == '2') {
        cs.next();
    } else {
        cout << "Error: expected praedikat but got" << *cs.chr << endl;
        ret = -1;
    }
    return ret;
}

int substantiv(tokenstr& cs) {
    int ret = 0;
    if (*cs.chr == 'A') {
        cs.next();
    } else if (*cs.chr == 'B') {
        cs.next();
    } else {
        cout << "Error: expected substantiv but got" << *cs.chr << endl;
        ret = -1;
    }
    return ret;
}

int adjektiv(tokenstr& cs) {
    int ret = 0;
    if (*cs.chr == 'a') {
        cs.next();
    } else if (*cs.chr == 'b') {
        cs.next();
    } else if (*cs.chr == 'c') {
        cs.next();
    }
    return ret;
}

int artikel(tokenstr& cs) {
    int ret = 0;
    if (*cs.chr == 'x') {
        cs.next();
    } else if (*cs.chr == 'y') {
        cs.next();
    }
    return ret;
}

/**************************************************/
// Scanner: lexical analysis
/**************************************************/

// definition of alphabet, lexems, and tokens
#define TOKENNUM 9  // number of tokens
#define SYMBNUM 26  // 'a'-'z'
string lexem[TOKENNUM] = {"hund", "katze", "jagt", "jault", "der", "die", "kleine", "bissige", "grosse"};
char token[TOKENNUM] = {'A', 'B', '1', '2', 'x', 'y', 'a', 'b', 'c'};

// node structure for lexer-tree
// type:
// = -2: root node
// = -1: normal node
// >= 0: leaf node, coding position in token[]-list
#define TYPE_ROOT -2
#define TYPE_NODE -1
#define TYPE_LEAF 0
class node {
   public:
    int type;
    node* son[SYMBNUM];
    node(int t) {
        type = t;
        for (int i = 0; i < SYMBNUM; ++i) son[i] = NULL;
    }
};

int lexer(const string input, node* const tree, tokenstr& cs) {
    uint16_t i, idx, ret = 0;
    node* temp = tree;
    string word = "";

    // clean tokenstr object
    cs.str.clear();

    // strip input from blanks, convert to lower case letters
    for (uint16_t i = 0; i < input.length(); ++i)
        if (input[i] != ' ') word += tolower(input[i]);

    // replace lexems by tokens according to lexer-tree
    for (i = 0; i < word.length(); ++i) {
        idx = word[i] - 'a';
        if (temp->son[idx] == NULL) {
            cout << "Error: unknown lexem " << word[i] << endl;
            return -1;
        }
        temp = temp->son[idx];
        if (temp->type >= TYPE_LEAF) {
            cs.str.push_back(token[temp->type - TYPE_LEAF]);
            temp = tree;
        }
    }

    // Check if all lexems have been replaced by tokens
    if (temp != tree) {
        cout << "Error: unexpected lexem in input string" << endl;
        return -1;
    }

    return ret;
}

void create_tree(node* root) {
    uint16_t i, j, idx;
    node* temp;

    for (i = 0; i < SYMBNUM; i++) root->son[i] = NULL;

    // lexem based subtree
    for (i = 0; i < TOKENNUM; ++i) {
        temp = root;
        for (j = 0; j < lexem[i].length(); ++j) {
            idx = lexem[i][j] - 'a';
            if (temp->son[idx] == NULL) temp->son[idx] = new node(TYPE_NODE);
            temp = temp->son[idx];
        }
        temp->type = TYPE_LEAF + i;
    }
}

void print_tree(node* root, int level = 0) {
    for (int i = 0; i < SYMBNUM; ++i) {
        if (root->son[i] != NULL) {
            for (int j = 0; j < level; ++j) cout << "  ";
            cout << (char)('a' + i) << "  " << root->son[i]->type << endl;
            print_tree(root->son[i], level + 1);
        }
    };
};

int main() {
    string input;
    tokenstr cs;

    // create total lexer-tree at root_node
    node* lexer_tree = new node(TYPE_ROOT);
    create_tree(lexer_tree);

    // print_tree(lexer_tree); // for debugging

    while (true) {
        cout << "\n>> ";
        getline(std::cin, input);
        if (input.size() == 0) return 0;

        int retL = lexer(input, lexer_tree, cs);
        int retP = parser(cs.rewind());
        cout << input << "  \n\t=>  lexer = " << (retL == 0 ? "ok" : "error") << " (tokens = " << cs.str
             << ")  \n\t=>  parser = " << (retP == 0 ? "ok" : "error") << endl;
    }
}
