#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int iter = 0;
double e() {
    double term = 1.0;
    double sum = 1.0;
    double denominator = 1.0;
    for (double k = 1.0; absolute(term) > EPSILON; k += 1.0) {
        denominator *= k;
        term = 1.0 / denominator;
        sum += term;
        iter += 1;
    }
    return sum;
}
int e_terms() {
    return iter;
}
