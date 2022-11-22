#ifndef POINT
#define POINT POINT

#include <string>

class point {
   private:
   /** Coordinates */
    double x;
    double y;

   public:
    /** Constructors*/
    point() : x(0), y(0) {};
    point(double x, double y) : x(x), y(y) {};

    /** Getter and setter */
    double get_x() const;
    double get_y() const;

    /* Input from terminal */
    void input();

    /* Print Point */
    void print() const;

    /** To string*/
    std::string to_string() const;
};

#endif