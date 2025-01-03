#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int itersw = 0;

double pi_wallis() {
    double four_k_squared = 0.0;
    double term = 0.0;
    double total = 1.0;
    for (double k = 1.0; absolute(1.0 - term) > EPSILON; k++) {
        four_k_squared = 4.0 * (k * k);
        term = four_k_squared / (four_k_squared - 1.0);
        total *= term;
        itersw++;
    }
    double pi = 2.0 * total;
    return pi;
}

int pi_wallis_factors() {
    return itersw;
}
