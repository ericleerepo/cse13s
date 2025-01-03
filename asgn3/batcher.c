#include "batcher.h"

#include <stdio.h>
#include <stdlib.h>

void comparator(Stats *stats, uint32_t *A, int x, int y) {
    if (cmp(stats, A[x], A[y]) == 1) {
        swap(stats, &A[x], &A[y]);
    }
}

int bit_length(int n) {
    int iter = 0;
    while (n) {
        iter++;
        n = n >> 1;
    }
    return iter;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    int length = (int) n;
    if (cmp(stats, length, 0) == 0) {
        exit(1);
    }
    int t = bit_length(n);
    int p = 1 << (t - 1);
    while (p > 0) {
        int q = 1 << (t - 1);
        int r = 0;
        int d = p;
        while (d > 0) {
            for (int i = 0; i < (length - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q = q >> 1;
            r = p;
        }
        p = p >> 1;
    }
}
