#include "vector3d.h"

#include <cmath>
#include <iostream>

using namespace std;

vector3d::scalarVecProxy::scalarVecProxy(const vector3d &u, const vector3d &v) : u(u), v(v) {}

vector3d::scalarVecProxy::operator double() const { return u.x * v.x + u.y * v.y + u.z * v.z; };

vector3d::scalarVecProxy::operator vector3d() const {
    return vector3d(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
};

vector3d::vector3d() : x(0), y(0), z(0){};
vector3d::vector3d(double a) : x(a), y(a), z(a){};
vector3d::vector3d(double a, double b, double c) : x(a), y(b), z(c){};
vector3d::~vector3d(){};

double vector3d::abs() const { return sqrt(x * x + y * y + z * z); };

double vector3d::operator[](int i) const {
    switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return 0;
    }
};

vector3d vector3d::operator-() const { return vector3d(-x, -y, -z); };

vector3d vector3d::operator+() const { return (*this); };

vector3d vector3d::operator+(const vector3d &a) const { return vector3d(x + a.x, y + a.y, z + a.z); };

vector3d vector3d::operator-(const vector3d &a) const { return (*this) + (-a); };

vector3d vector3d::operator*(const vector3d &a) const { return vector3d(x * a.x, y * a.y, z * a.z); };

vector3d vector3d::operator*(double d) const { return vector3d(x * d, y * d, z * d); };

vector3d vector3d::operator+=(const vector3d &a) { return (*this) = (*this) + a; };

bool vector3d::operator==(const vector3d &a) const { return x == a.x && y == a.y && z == a.z; };

bool vector3d::operator!=(const vector3d &a) const { return !((*this) == a); };

vector3d operator*(double d, const vector3d &a) { return a * d; };

vector3d vector3d::operator/(double d) const { return (*this) * (1 / d); };

vector3d::scalarVecProxy vector3d::operator%(const vector3d &a) const { return scalarVecProxy(*this, a); };

ostream &operator<<(ostream &os, const vector3d &a) {
    os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return os;
};