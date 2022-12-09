#include<iostream>
#include "gettype.t"
using namespace std;

#define PRINT(x) cout << "\"" << #x << "\"\t = " << x << endl

int main() {
  int* pi = new int;                   PRINT(getType(*pi)); // INT
                                       PRINT(getType( pi)); // INT*
                                       PRINT(getType(&pi)); // INT**
  unsigned int* pu = new unsigned int; PRINT(getType(*pu)); // UNSIGNED INT
                                       PRINT(getType( pu)); // UNSIGNED INT*
  const int     ci=0;                  PRINT(getType(ci));  // INT

  char          c=0;                   PRINT(getType(c));   // CHAR
  char*         pc=0;                  PRINT(getType(pc));  // CHAR*

  float         f=0;                   PRINT(getType(f));   // FLOAT
  float*        pf=0;                  PRINT(getType(pf));  // FLOAT*
  double        d=0;                   PRINT(getType(d));   // DOUBLE
  double*       pd=0;                  PRINT(getType(pd));  // DOUBLE*

  bool          b=0;                   PRINT(getType(b));   // BOOL
  bool*         pb=0;                  PRINT(getType(pb));  // BOOL*

  string        s="";                  PRINT(getType(s));   // STRING
  // nicht in getType() ber�cksichtigt!
  long int      li=0;                  PRINT(getType(li));   // unbekannter Typ
}
