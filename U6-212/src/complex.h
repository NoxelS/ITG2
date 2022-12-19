// complex Klasse

using namespace std;

class complex {
  public:            
    double re,im;      
    complex(double a=0, double b=0) : re(a), im(b) {} 
    complex operator+(const complex& z) {
      return(complex(re+z.re, im+z.im));
    }
    bool operator==(const complex& z) {
      return(re==z.re && im==z.im);
    }
    bool operator!=(const complex& z) {
      return(re!=z.re || im!=z.im);
    }
};

ostream& operator<<(ostream& s, const complex& z) {
  cout << "(" << z.re << "," << z.im << ")";
  return(s);
}

double abs(const complex& z) {
  return(sqrt(z.re*z.re+z.im*z.im));
}

