#ifndef RECTANGLE
#define RECTANGLE RECTANGLE

#include "area.hpp"
#include "point.hpp"

class rectangle : public area {
    private:
     point p1 = point(0, 0);
     point p2 = point(0, 0);
    public:
     /** Get area specific values and calculates coa and area */
     void input() override;
     void print() const override;
};

#endif
