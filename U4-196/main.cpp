#include <iostream>
using namespace std;

class klasseA {
  private:
    int a1;
    class klasseB {
      private:
        int b1;
      public:
        int b2;
      friend klasseA;
    };
  public:
    klasseB Bobj;
    int a2;
    klasseA() {
      a1 = 1;
      a2 = 2;
      Bobj.b1 = 3;
      Bobj.b2 = 4;
    }
    void print() {
      cout << a1 << endl;
      cout << a2 << endl;
      cout << Bobj.b1 << endl;
      cout << Bobj.b2 << endl;
    }
};


int main() {
  klasseA Aobj;
  Aobj.print();
  // cout << Aobj.a1 << endl; // Ist privat
  cout << Aobj.a2 << endl;
  // cout << Aobj.Bobj.b1 << endl; // b1 ist nur friend in klasseA
  cout << Aobj.Bobj.b2 << endl;
}
