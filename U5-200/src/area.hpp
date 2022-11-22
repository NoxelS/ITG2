#ifndef AREA
#define AREA AREA

#include "point.hpp"

class area {
   private:
    /** Center of area*/
    point coa = point(0, 0);
    /** Area size */
    double area = 0;

   public:
    /** Get area specific values and calculates coa and area */
    virtual void input() = 0;
    virtual void print() const = 0;

    /** Getter and setter */
    point get_coa() const;
    double get_coa_x() const;
    double get_coa_y() const;
    double get_area() const;
    void set_area(double area);
    void set_coa(point coa);
};

#endif