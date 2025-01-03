#include "insert.h"

#include "set.h"

#include <stdio.h>

void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    int n = (int) length;
    for (int k = 1; k < n; k++) {
        int j = k;
        int temp = move(stats, arr[k]);
        while ((j > 0) && (cmp(stats, arr[j - 1], temp) == 1)) {
            arr[j] = move(stats, arr[j - 1]);
            j -= 1;
        }
        arr[j] = temp;
    }
}
