#ifndef ARDMATH_H

#define ARDMATH_H

class ardMath {

public:

    float abs (float x)
    {
        float number;
        __ESBMC_assume ( number >= 0);
        return number;
    }

};
#endif
