/////////////////////////////////////////////////////
// complex Klasse
class complex {
  public:            
    double re,im;      
    // Default-Konstruktor muss existieren,
    // um temporäre Objekte zu erzeugen.
    complex() : re(0), im(0) {}
    complex(double a) : re(a), im(0) {}		  // notwendig für x[i]=0
    complex(double a, double b) : re(a), im(b) {} 
    complex operator+(const complex& z) {
        return(complex(re+z.re, im+z.im));
    }
};

ostream& operator<<(ostream& s, const complex& z) {
  cout << "(" << z.re << "," << z.im << ")";
  return(s);
}

double abs(const complex& z) {
  return(sqrt(z.re*z.re+z.im*z.im));
}
/////////////////////////////////////////////////////

