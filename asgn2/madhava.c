#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int itersm = 0;
double pi_madhava(void) {
    double rational = sqrt_newton(12);
    double numerator = 0.0;
    double denominator = 0.0;
    double term = 1.0;
    double sum = 0.0;
    double num = 1.0;
    for (double k = 0.0; absolute(term) > EPSILON; k++) {
        numerator = 1.0 / (num);
        num = (num * (-3.0));
        denominator = (2 * k) + 1;
        term = numerator / denominator;
        sum += term;
        itersm++;
    }
    double ans = rational * sum;
    return ans;
}
int pi_madhava_terms(void) {
    return itersm;
}
