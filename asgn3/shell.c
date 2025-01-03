#include "shell.h"

#include "gaps.h"

#include <stdio.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (int k = 0; k < 142; k++) {
        int gap = gaps[k];
        int length = (int) n;
        if (gap < length) {
            for (int i = gap; i < length; i++) {
                int j = i;
                int temp = move(stats, A[i]);
                while ((j >= gap) && (cmp(stats, A[j - gap], temp) == 1)) {
                    A[j] = move(stats, A[j - gap]);
                    j -= gap;
                }
                A[j] = move(stats, temp);
            }
        }
    }
}
