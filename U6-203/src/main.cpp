#include <iostream>

#include "stack.h"

using namespace std;

#define PRINT(x)                             \
    cout << #x << ": ";                      \
    while (x.size()) cout << x.pop() << " "; \
    cout << endl;

int main() {
    stack<double> S0;
    S0.push(11.1);
    S0.push(12.2);
    S0.push(13.3);
    S0.push(14.4);
    stack<char> S1;
    S1.push('a');
    S1.push('b');
    S1.push('c');
    S1.push('d');

    // Cast stack<char> to stack<int>
    stack<int> S2(S1);

    PRINT(S2);
}
