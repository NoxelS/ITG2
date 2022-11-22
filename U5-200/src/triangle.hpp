#ifndef TRIANGLE
#define TRIANGLE TRIANGLE

#include "area.hpp"
#include "point.hpp"

class triangle : public area {
   private:
    point p1 = point(0, 0);
    point p2 = point(0, 0);
    point p3 = point(0, 0);

   public:
    /** Get area specific values and calculates coa and area */
    void input() override;
    void print() const override;
};

#endif
