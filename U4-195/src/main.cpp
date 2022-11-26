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
    stack S1;
    S1.push(21.1);
    S1.push(22.2);
    S1.push(23.3);
    S1.push(24.4);
    stack S2(S1);  // COPY-CTOR
    stack S3;
    S3 = S2;  // ASSIGNMENT-OP
    stack S4(4, 4.4);  // INIT-CTOR
    stack S5(S4);      // COPY-CTOR
    PRINT(S0);
    PRINT(S1);
    PRINT(S2);
    PRINT(S3);
    PRINT(S4);
    PRINT(S5);
}
