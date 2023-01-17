#include <iostream>
#include <string>

using namespace std;

#define WORDNUM 7
#define CHARACTERNUM 4

char characters[CHARACTERNUM]; // 0, 1, 2, 3, ...

string code[WORDNUM] = {"0", "10", "20", "30"};
char token[WORDNUM] = {'A', 'B', 'C', 'D'};

// Klasse 'node' - Deklaration und Definition
class node {
   public:
    node();
    void print();
    void travel(node* start);
    int leaf;
    node* sons[CHARACTERNUM];
};

node::node() {
    leaf = -1;
    for (size_t i = 0; i < CHARACTERNUM; i++) sons[i] = NULL;
}

void node::travel(node* start) {
    start->print();
    for (size_t i = 0; i < CHARACTERNUM; i++)
        if (start->sons[i] != NULL) travel(start->sons[i]);
}

void node::print() {
    cout << "node " << this << endl;
    cout << "leaf " << leaf << endl;
    if (leaf >= 0) cout << "lett " << token[leaf] << endl;
    for (size_t i = 0; i < CHARACTERNUM; i++) {
        cout << sons[i] << " ";
    }
    cout << endl;
}

node* root_node;  // Wurzel- und Laufnode sind global
node* run_node;   // weil sie ständig benötigt werden

// Initialisiert den Baum
void init_tree() {
    root_node = new node;  // Erzeuge zunächst eine Wurzel
    root_node->leaf = -2;  // leaf=-2 => Wurzel

    // Erzeuge neuen Pfad im Baum für jedes Codewort
    for (unsigned int i = 0; i < WORDNUM; i++) {
        run_node = root_node;  // Starte in Wurzel
        for (unsigned int j = 0; j < code[i].length(); j++)
            for (size_t c = 0; c < CHARACTERNUM; c++) {
                if (code[i][j] == characters[c]) {
                    if (run_node->sons[c] == NULL) run_node->sons[c] = new node;
                    run_node = run_node->sons[c];
                } else {
                    if (run_node->sons[c] == NULL) run_node->sons[c] = new node;
                }
            }
        run_node->leaf = i;  // leaf>0 => Blatt des Baumes
    }                        // leaf kodiert Index des Tokens
}

// Findet den Pfad bis zum Blatt für eine Zeichenkette
void find_leaf(string word) {
    cout << word << endl;

    run_node = root_node;  // Starte in der Wurzel

    for (unsigned int i = 0; i <= word.length(); i++) {
        if (run_node == nullptr)
            throw std::out_of_range("Terminated tree searching without finding the string \"" + word + "\"");

        if (run_node->leaf < 0) {
            for (size_t i = 0; i < CHARACTERNUM; i++) {
                if (word[i] == characters[i]) {
                    run_node = run_node->sons[i];
                    cout << " " << token[i];
                }
            }
        } else {  // ... sonst gib zugehöriges Token aus
            cout << " " << characters[i] << endl;
            run_node = root_node;
        }
    }
}

int main() {
    // Make CHARACTERNUM
    for (size_t i = 0; i < CHARACTERNUM; i++) characters[i] = '0' + i;
    cout << "CHARACTERNUM:" << endl;
    for (size_t i = 0; i < CHARACTERNUM; i++) cout << characters[i];
    cout << endl;

    init_tree();
    // root_node->travel(root_node);

    find_leaf("10");
}
