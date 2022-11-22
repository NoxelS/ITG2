#ifndef CIRCLE
#define CIRCLE CIRCLE

#include "area.hpp"
#include "point.hpp"

class circle : public area {
   private:
    point x_0 = point(0, 0);
    double r = 0;

   public:
    /** Get area specific values and calculates coa and area */
    void input() override;
    void print() const override;
};

#endif
