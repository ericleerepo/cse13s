#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int itersbbp = 0;
double pi_bbp() {
    double term = 1.0;
    double sum = 0.0;
    double outside = 0.0;
    double outside_den = 1.0;
    double inside = 0.0;
    double eightk = 0.0;
    for (double k = 0.0; absolute(term) > EPSILON; k++) {
        eightk = 8.0 * k;
        outside = 1.0 / outside_den;
        outside_den *= 16.0;
        inside = ((4.0 / (eightk + 1.0)) - (2.0 / (eightk + 4.0)) - (1.0 / (eightk + 5.0))
                  - (1.0 / (eightk + 6.0)));
        term = outside * inside;
        sum += term;
        itersbbp++;
    }
    return sum;
}
int pi_bbp_terms() {
    return itersbbp;
}
