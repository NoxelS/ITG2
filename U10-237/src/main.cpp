#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// definition of alphabet, lexems, and tokens
#define TOKENNUM 4
#define SYMBNUM 26
string lexem[TOKENNUM] = {"for", "fill", "if", "find"};
char token[TOKENNUM] = {'5', 'a', '1', 'X'};

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
    char symbol;
    node(int t) {
        type = t;
        symbol = '\0';
        for (int i = 0; i < SYMBNUM; ++i) son[i] = NULL;
    }
};

void travel(node* start, int depth = 1) {
    // Ist nicht perfekt, die Einrückung stimmt für parallele Nodes mit depth > 0 nicht aber das ist ja nur formatierung :)
    if (start->type >= TYPE_LEAF) {
        for (int j = 0; j < depth; ++j) cout << "  ";
        cout << "\\ovalbox{\\textbf{\\textsf " << token[start->type] << "}}";
    } else if (start->type == TYPE_NODE) {
        for (int i = 0; i < SYMBNUM; ++i) {
            if (start->son[i]) {
                for (int j = 0; j < depth; ++j) cout << "  ";
                cout << "[. \\framebox{" << start->son[i]->symbol << "}\n";
                travel(start->son[i], depth + 1);
                cout << "\n";
                for (int j = 0; j < depth; ++j) cout << "  ";
                cout << "]";
                if (depth == 1) cout << "\n";
            }
        }
    } else if (start->type == TYPE_ROOT) {
        cout << "\\Tree\n";
        cout << "[. \\textbf{\\textsf root}\n";
        for (int i = 0; i < SYMBNUM; ++i) {
            if (start->son[i]) {
                for (int j = 0; j < depth; ++j) cout << "  ";
                cout << "[. \\framebox{" << start->son[i]->symbol << "}\n";
                travel(start->son[i], depth + 1);
                cout << "\n";
                for (int j = 0; j < depth; ++j) cout << "  ";
                cout << "]";
                if (depth == 1) cout << "\n";
            }
        }
        cout << "]\n";
    }
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
            if (!temp->son[idx]) {
                temp->son[idx] = new node(TYPE_NODE);
                temp->son[idx]->symbol = lexem[i][j];
            }
            temp = temp->son[idx];
        }
        temp->type = i;
    }
}

int main() {
    node* lexer_tree = new node(TYPE_ROOT);
    create_tree(lexer_tree);
    cout << "\\documentclass{letter}\n\n\\usepackage{tikz-qtree}\n";
    cout << "\\usepackage{fancybox}\n\n\\begin{document}\n";
    travel(lexer_tree);
    cout << "\n\\end{document}\n";
}
