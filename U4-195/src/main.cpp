#include <iostream>

#include "stack.h"
using namespace std;

#define PRINT(x)                             \
    cout << #x << ": ";                      \
    while (x.size()) cout << x.pop() << " "; \
    cout << endl;

int main() {
    stack S0;  // DFLT-CTOR
    S0.push(11.1);
    S0.push(12.2);
    S0.push(13.3);
    S0.push(14.4);
    PRINT(S0);
}
