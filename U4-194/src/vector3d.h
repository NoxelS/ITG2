#ifndef VECTOR3D
#define VECTOR3D VECTOR3D

#include <iostream>
using namespace std;

class vector3d {
   public:
    /* Used to proxy the product of two vectors depending on the output type */
    class scalarVecProxy {
       private:
        const vector3d &u;
        const vector3d &v;

       public:
        scalarVecProxy(const vector3d &u, const vector3d &v);
        /* Dot product */
        operator double() const;
        /* Vector Product*/
        operator vector3d() const;
    };
    double x, y, z;
    /* Constructors */
    vector3d();
    vector3d(double a);
    vector3d(double a, double b, double c);
    ~vector3d();

    /* Returns the absolute value of the vector */
    double abs() const;

    /* Returns the i-th component of the vector */
    double operator[](int i) const;

    /* Arithmetic operators */
    vector3d operator-() const;
    vector3d operator+() const;
    vector3d operator+(const vector3d &a) const;
    vector3d operator-(const vector3d &a) const;
    vector3d operator*(const vector3d &a) const;
    vector3d operator*(double d) const;
    vector3d operator+=(const vector3d &a);
    bool operator==(const vector3d &a) const;
    bool operator!=(const vector3d &a) const;
    friend vector3d operator*(double d, const vector3d &a);
    vector3d operator/(double d) const;

    /* Proxied dot/vec product*/
    scalarVecProxy operator%(const vector3d &a) const;

    /* Stream operators */
    friend ostream &operator<<(ostream &os, const vector3d &a);
    friend istream &operator>>(istream &is, vector3d &a);
};

#endif