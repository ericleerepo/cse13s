#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int iters;
double pi_viete() {
    double term = 0.0;
    double sum = 1.0;
    double ak = 0.0;
    double old_ak = 0.0;
    for (double k = 1.0; absolute(1.0 - term) > EPSILON; k++) {
        ak = sqrt_newton(2.0 + old_ak);
        term = ak / 2.0;
        sum *= term;
        old_ak = ak;
        iters++;
    }
    double pi = 2.0 / sum;
    return pi;
}

int pi_viete_factors() {
    return iters;
}
