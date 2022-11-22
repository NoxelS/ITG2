#ifndef PLAINAREA
#define PLAINAREA PLAINAREA

#include "area.hpp"

class plainarea : public area {
   public:
    /** Get area specific values and calculates coa and area */
    void input() override;
    void print() const override;
};

#endif
