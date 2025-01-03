#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int iterse = 0;
double pi_euler(void) {
    double term = 1.0;
    double sum = 0.0;
    double denominator = 1.0;
    for (double k = 1.0; absolute(term) > EPSILON; k++) {
        denominator = k * k;
        term = 1.0 / denominator;
        iterse++;
        sum += term;
    }
    double pi = sqrt_newton(6.0 * sum);
    return pi;
}
int pi_euler_terms(void) {
    return iterse;
}
